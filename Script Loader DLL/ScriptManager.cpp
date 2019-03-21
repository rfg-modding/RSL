#include "ScriptManager.h"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

const char* TestFunc()
{
	return "Test";
}

void ScriptManager::Initialize()
{
	//See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	//and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	//Excluded the ffi lib for now. Current goal is to sandbox lua for user
	//safety. Might change this later on.
	LuaState.open_libraries
	(
		sol::lib::base,
		sol::lib::package,
		sol::lib::coroutine,
		sol::lib::string,
		sol::lib::os,
		sol::lib::math,
		sol::lib::table,
		sol::lib::debug,
		sol::lib::bit32,
		sol::lib::io,
		sol::lib::ffi,
		sol::lib::jit
	);
	SetupLua();
}

void ScriptManager::SetupLua()
{
	RunScript(GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
	
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	LuaState["GetScriptLoaderVersion"] = &GetScriptLoaderVersion;
	LuaState["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;

	//LogType enums defined in lua
	auto LoggerTable = LuaState["Logger"].get_or_create<sol::table>(); //Todo: Add to RSL table.
	LoggerTable["OpenLogFile"] = Logger::OpenLogFile;
	LoggerTable["CloseLogFile"] = Logger::CloseLogFile;
	LoggerTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	LoggerTable["Log"] = Logger::Log;
	LoggerTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	LoggerTable["GetFlagString"] = Logger::GetFlagString;
	LoggerTable["LogToFile"] = Logger::LogToFile;
	LoggerTable["GetTimeString"] = Logger::GetTimeString;
	
	RfgTable.new_usertype<vector>
	(
		"vector",
		"new", sol::constructors<sol::types<const vector&>, sol::types<float>, sol::types<float, float, float>>(),
		sol::meta_function::addition, &vector::operator+,
		sol::meta_function::subtraction, &vector::operator-,
		sol::meta_function::multiplication, &vector::operator*,
		sol::meta_function::equal_to, &vector::operator==,
		"Cross", &vector::Cross,
		"Magnitude", &vector::Magnitude,
		"SetAll", &vector::SetAll,
		"x", &vector::x,
		"y", &vector::y,
		"z", &vector::z
	);
	RfgTable.new_usertype<matrix>
	(
		"matrix",
		"new", sol::constructors<sol::types<const matrix&>, sol::types<float>, sol::types<vector, vector, vector>>(),
		sol::meta_function::addition, &matrix::operator+,
		sol::meta_function::subtraction, &matrix::operator-,
		sol::meta_function::equal_to, &matrix::operator==,
		"SetAll", &matrix::SetAll,
		"rvec", &matrix::rvec,
		"uvec", &matrix::uvec,
		"fvec", &matrix::fvec
	);	
	RfgTable.new_usertype<matrix43>
	(
		"matrix43",
		"new", sol::constructors<sol::types<const matrix43&>, sol::types<float>, sol::types<matrix, vector>>(),
		sol::meta_function::addition, &matrix43::operator+,
		sol::meta_function::subtraction, &matrix43::operator-,
		sol::meta_function::equal_to, &matrix43::operator==,
		"SetAll", &matrix43::SetAll,
		"Rotation", &matrix43::m_rotation,
		"Translation", &matrix43::m_translation
	);
	RfgTable.new_usertype<AttachInfoData> //Note: I have no idea if the last 3 vars are correct. Bit fields are odd with sol2.
	(
		"AttachInfoData",
		"new", sol::constructors<sol::types<const AttachInfoData&>>(),
		"ParentHandle", &AttachInfoData::parent_handle,
		"ParentPropPoint", &AttachInfoData::parent_prop_point,
		"ChildPropPoint", &AttachInfoData::child_prop_point,
		"RelativeTransform", &AttachInfoData::relative_transform,
		"UseRelativeTransform", sol::property(itsy_bitsy::read<AttachInfoData, 60>, itsy_bitsy::write<AttachInfoData, 60>),
		"UpdatePhysics", sol::property(itsy_bitsy::read<AttachInfoData, 61>, itsy_bitsy::write<AttachInfoData, 61>),
		"Updated", sol::property(itsy_bitsy::read<AttachInfoData, 60>, itsy_bitsy::write<AttachInfoData, 60>)
	);
	RfgTable.new_usertype<ContactNode>
	(
		"ContactNode",
		"new", sol::constructors<sol::types<const ContactNode&>>(),
		"ContactedObject", &ContactNode::m_contacted_object,
		"NumberOfContacts", &ContactNode::m_num_contacts,
		"Previous", &ContactNode::prev,
		"Next", &ContactNode::next
	);
	RfgTable.new_usertype<ObjectContactInfo>
	(
		"ObjectContactInfo",
		"new", sol::constructors<sol::types<const ObjectContactInfo&>>(),
		"ContactList", &ObjectContactInfo::m_contact_list
	);

	//Next is ObjectFlags bitfield
}

void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		Scripts.clear();
		std::string ScriptFolderPath(GetEXEPath(false) + "RFGR Script Loader/Scripts/");

		std::string ThisScriptPath;
		std::string ThisScriptFolderPath;
		std::string ThisScriptName;

		for (auto& i : fs::directory_iterator(ScriptFolderPath))
		{
			if (IsValidScriptExtensionFromPath(i.path().string()))
			{
				ThisScriptPath = i.path().string();
				ThisScriptFolderPath = GetScriptFolderFromPath(i.path().string());
				ThisScriptName = GetScriptNameFromPath(i.path().string());
				Scripts.push_back(Script(ThisScriptPath, ThisScriptFolderPath, ThisScriptName));

				//Logger::Log(i.path().string(), LogInfo);
				//Logger::Log("Script Name: " + ThisScriptName, LogInfo);
				//Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
			}
		}
	}
	catch(std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception when scanning scripts folder, Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogFatalError, true, true);
		//strcpy(Ex.what, ExceptionInfo.c_str());
		//throw(Ex);
	}
}

void ScriptManager::ScanScriptsSubFolders()
{

}

bool ScriptManager::RunScript(std::string FullPath)
{
	if (IsValidScriptExtensionFromPath(FullPath))
	{
		try
		{
			auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
			{
				return pfr;
			}, sol::load_mode::text);

			if (!CodeResult.valid())
			{
				sol::error ScriptError = CodeResult;
				std::exception ScriptException(ScriptError.what());
				throw(ScriptException);
			}
			return true;
		}
		catch (std::exception& Exception)
		{
			Logger::Log(std::string("Exception caught when running " + GetScriptNameFromPath(FullPath) + std::string(Exception.what())), LogLua | LogError);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ScriptManager::RunScript(size_t Index)
{
	std::string FullPath = Scripts[Index].FullPath;
	try
	{
		auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Scripts[Index].Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

bool ScriptManager::RunStringAsScript(std::string Buffer, std::string Name)
{
	try
	{
		auto CodeResult = LuaState.script(Buffer, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		});

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

std::string ScriptManager::GetScriptNameFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(i + 1, FullPath.length() - i);
			}
		}
	}
	return std::string();
}

std::string ScriptManager::GetScriptFolderFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(0, i + 1);
			}
		}
	}
	return std::string();
}

std::string ScriptManager::GetScriptExtensionFromPath(std::string FullPath)
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (FullPath.compare(i, 1, ".") == 0)
		{
			return FullPath.substr(i + 1, FullPath.length() - i);
		}
	}
	return std::string();
}

bool ScriptManager::IsValidScriptExtensionFromPath(std::string FullPath)
{
	if (IsValidScriptExtension(GetScriptExtensionFromPath(FullPath)))
	{
		return true;
	}
	return false;
}

bool ScriptManager::IsValidScriptExtension(std::string Extension)
{
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
	if (Extension == "lua")
	{
		return true;
	}
	return false;
}

