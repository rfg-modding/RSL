#pragma once


/*void __stdcall D3D11CreateQueryHook(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
{
	std::call_once(HookD3D11CreateQueryInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CreateQuery() hook.\n", LogInfo, false, true);
		g_pd3dDevice = pDevice;
		D3D11DeviceFound = true;
	});
	//std::cout << "10 CREATEQUERYHOOK" << std::endl;
	return D3D11CreateQueryObject(pDevice, pQueryDesc, ppQuery);
}

void __stdcall D3D11DrawIndexedHook(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	std::call_once(HookD3D11DrawIndexedInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11DrawIndexed() hook.\n", LogInfo, false, true);
		g_pd3dDeviceContext = pContext;
		D3D11DeviceContextFound = true;
	});
	std::cout << "11 DRAWINDEXEDHOOK" << std::endl;
	return D3D11DrawIndexedObject(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

HRESULT __stdcall D3D11CheckFeatureSupportHook(ID3D11Device* pDevice, D3D11_FEATURE Feature, void* FeatureSupportData, UINT FeatureSupportDataSize)
{
	std::call_once(HookD3D11CheckFeatureSupportInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CheckFeatureSupport() hook.\n", LogInfo, false, true);
		g_pd3dDevice = pDevice;
		D3D11DeviceFound = true;
	});
	std::cout << "12 CHECKFEATURESUPPORTHOOK" << std::endl;
	return D3D11CheckFeatureSupportObject(pDevice, Feature, FeatureSupportData, FeatureSupportDataSize);
}

void __stdcall D3D11GetDeviceHook(ID3D11DeviceChild* Child, ID3D11Device** Device)
{
	std::call_once(HookD3D11GetDeviceInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CheckFeatureSupport() hook.\n", LogInfo, false, true);
		g_pd3dDevice = *Device;
		D3D11DeviceFound = true;
	});
	std::cout << "13 GETDEVICEHOOK" << std::endl;
	return D3D11GetDeviceObject(Child, Device);
}

void __stdcall D3D11BeginHook(ID3D11DeviceContext* Context, ID3D11Asynchronous* Async)
{
	std::call_once(HookD3D11BeginInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11Begin() hook.\n", LogInfo, false, true);
		g_pd3dDeviceContext = Context;
		D3D11DeviceContextFound = true;
	});
	//std::cout << "14 BEGINHOOK" << std::endl;
	return D3D11BeginObject(Context, Async);
}*/

/*	
ConsoleLog("Hooking GraphicsBeginFrame().\n", LogInfo, false, true);
if (MH_CreateHook((DWORD*)(ModuleBase + 0x86DD00), GraphicsBeginFrameHook, (LPVOID*)&GraphicsBeginFrame) != MH_OK)
{
	ConsoleLog("Failed to create GraphicsBeginFrame() hook. RFGR Script loader deactivating.", LogError, false, true, true);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}
ConsoleLog("Successfully created GraphicsBeginFrame() hook.", LogInfo, false, true, true);
if (MH_EnableHook((DWORD*)(ModuleBase + 0x86DD00)) != MH_OK)
{
	ConsoleLog("Failed to enable GraphicsBeginFrame() hook. RFGR Script loader deactivating.", LogError, false, true, true);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}
ConsoleLog("Sucessfully enabled GraphicsBeginFrame() hook.", LogInfo, false, true, true);
ConsoleLog("Sucessfully hooked GraphicsBeginFrame().\n", LogInfo, false, true);*/



/*
B BTest;
B* BTestPointer = &BTest;

unsigned char* bytePtr = reinterpret_cast<unsigned char*>(BTestPointer);
bytePtr += 4;

std::cout << "*(int*)(BTestPointer + 0x4): " << *(int*)(bytePtr) << std::endl;// *(int*)(BTestPointer + 0x4) << std::endl;
*/


/*
void ProgramManager::LoadDataFromConfig()
{
	std::string ExePath = GetEXEPath(false);
	if (fs::exists(ExePath + "RFGR Script Loader/Settings.txt"))
	{
		// read a JSON file
		std::ifstream Config(ExePath + "RFGR Extended Camera/Settings.txt");
		Config >> MainConfig;
		Config.close();
	}
	else
	{
	CreateDirectoryIfNull(ExePath + "RFGR Script Loader/");
	std::cout << "Settings.txt not found. Creating from default values." << std::endl;

	MainConfig["Default free camera speed"] = 0.3;
	//MainConfig["Default rotation speed"] = 0.7;
	//MainConfig["Create output console"] = true;

	//Keybinds
	/*MainConfig["Keybinds"]["Decrease camera speed"] = "q";
	MainConfig["Keybinds"]["Increase camera speed"] = "e";
	MainConfig["Keybinds"]["Toggle free camera"] = "VK_NUMPAD1";
	MainConfig["Keybinds"]["Toggle hud"] = "VK_NUMPAD2";
	MainConfig["Keybinds"]["Toggle fog"] = "VK_NUMPAD3";
	MainConfig["Keybinds"]["Camera forward"] = "VK_UP";
	MainConfig["Keybinds"]["Camera backward"] = "VK_DOWN";
	MainConfig["Keybinds"]["Camera left"] = "VK_LEFT";
	MainConfig["Keybinds"]["Camera right"] = "VK_RIGHT";
	MainConfig["Keybinds"]["Camera up"] = "z";
	MainConfig["Keybinds"]["Camera down"] = "x";

	//Rotation Keybinds
	MainConfig["Keybinds"]["Decrease rotation speed"] = "t";
	MainConfig["Keybinds"]["Increase rotation speed"] = "y";
	MainConfig["Keybinds"]["Toggle manual rotation control"] = "VK_NUMPAD4";
	MainConfig["Keybinds"]["Reset rotation"] = "VK_NUMPAD5";
	MainConfig["Keybinds"]["Lock pitch"] = "VK_NUMPAD7";
	MainConfig["Keybinds"]["Lock yaw"] = "VK_NUMPAD8";
	MainConfig["Keybinds"]["Lock roll"] = "VK_NUMPAD9";
	MainConfig["Keybinds"]["Decrease pitch"] = "VK_INSERT";
	MainConfig["Keybinds"]["Increase pitch"] = "VK_DELETE";
	MainConfig["Keybinds"]["Decrease yaw"] = "VK_END";
	MainConfig["Keybinds"]["Increase yaw"] = "VK_HOME";
	MainConfig["Keybinds"]["Decrease roll"] = "VK_NEXT";
	MainConfig["Keybinds"]["Increase roll"] = "VK_PRIOR";

	// write prettified JSON to another file
	std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings.txt");
	ConfigOutput << std::setw(4) << MainConfig << std::endl;
	ConfigOutput.close();
	}

	HKL KeyboardLayout = GetKeyboardLayout(0);
	//VkKeyScanEx(YOUR_CHAR, currentKBL);

	//ConsoleLog("Keyboard layout created", LogWarning, false, true, true);

	DefaultFreeCameraSpeed = MainConfig["Default free camera speed"].get<float>();
	//DefaultRotationSpeed = MainConfig["Default rotation speed"].get<float>();
	//UseConsole = MainConfig["Create output console"].get<bool>();

	ConsoleLog("Loading keybinds", LogWarning, false, true, true);

	KeyDecreaseCameraSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Decrease camera speed"].get<int>(), KeyboardLayout);
	ConsoleLog("KeyDecreaseCameraSpeed Set", LogError, false, true, true);
	KeyIncreaseCameraSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Increase camera speed"].get<char>(), KeyboardLayout);
	KeyToggleFreecamera = VkKeyScanEx(MainConfig["Keybinds"]["Toggle free camera"].get<char>(), KeyboardLayout);
	KeyToggleHud = VkKeyScanEx(MainConfig["Keybinds"]["Toggle hud"].get<char>(), KeyboardLayout);
	KeyToggleFog = VkKeyScanEx(MainConfig["Keybinds"]["Toggle fog"].get<char>(), KeyboardLayout);
	KeyCameraForward = VkKeyScanEx(MainConfig["Keybinds"]["Camera forward"].get<char>(), KeyboardLayout);
	KeyCameraBackward = VkKeyScanEx(MainConfig["Keybinds"]["Camera backward"].get<char>(), KeyboardLayout);
	KeyCameraLeft = VkKeyScanEx(MainConfig["Keybinds"]["Camera left"].get<char>(), KeyboardLayout);
	KeyCameraRight = VkKeyScanEx(MainConfig["Keybinds"]["Camera right"].get<char>(), KeyboardLayout);
	KeyCameraUp = VkKeyScanEx(MainConfig["Keybinds"]["Camera up"].get<char>(), KeyboardLayout);
	KeyCameraDown = VkKeyScanEx(MainConfig["Keybinds"]["Camera down"].get<char>(), KeyboardLayout);

	ConsoleLog("Loading rotation control keybinds", LogWarning, false, true, true);

	KeyDecreaseRotationSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Decrease rotation speed"].get<char>(), KeyboardLayout);
	KeyIncreaseRotationSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Inrease rotation speed"].get<char>(), KeyboardLayout);
	KeyToggleRotationControl = VkKeyScanEx(MainConfig["Keybinds"]["Toggle manual rotation control"].get<char>(), KeyboardLayout);
	KeyResetRotation = VkKeyScanEx(MainConfig["Keybinds"]["Reset rotation"].get<char>(), KeyboardLayout);
	KeyLockPitch = VkKeyScanEx(MainConfig["Keybinds"]["Lock pitch"].get<char>(), KeyboardLayout);
	KeyLockYaw = VkKeyScanEx(MainConfig["Keybinds"]["Lock yaw"].get<char>(), KeyboardLayout);
	KeyLockRoll = VkKeyScanEx(MainConfig["Keybinds"]["Lock roll"].get<char>(), KeyboardLayout);
	KeyDecreasePitch = VkKeyScanEx(MainConfig["Keybinds"]["Decrease pitch"].get<char>(), KeyboardLayout);
	KeyIncreasePitch = VkKeyScanEx(MainConfig["Keybinds"]["Increase pitch"].get<char>(), KeyboardLayout);
	KeyDecreaseYaw = VkKeyScanEx(MainConfig["Keybinds"]["Decrease yaw"].get<char>(), KeyboardLayout);
	KeyIncreaseYaw = VkKeyScanEx(MainConfig["Keybinds"]["Increase yaw"].get<char>(), KeyboardLayout);
	KeyDecreaseRoll = VkKeyScanEx(MainConfig["Keybinds"]["Decrease roll"].get<char>(), KeyboardLayout);
	KeyIncreaseRoll = VkKeyScanEx(MainConfig["Keybinds"]["Increase roll"].get<char>(), KeyboardLayout);
}*/

	/*ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr))
	{
		hr = pVoice->Speak(L"<pitch middle = '10'>RFGR script loader activated", SPF_IS_XML, NULL);
		pVoice->Release();
		pVoice = NULL;
	}

	::CoUninitialize();*/

/*typedef void(__stdcall* D3D11CreateQuery) (ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);
D3D11CreateQuery D3D11CreateQueryObject;

typedef void(__stdcall* D3D11DrawIndexed) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
D3D11DrawIndexed D3D11DrawIndexedObject;

typedef HRESULT(__stdcall* D3D11CheckFeatureSupport) (ID3D11Device* pDevice, D3D11_FEATURE Feature, void* FeatureSupportData, UINT FeatureSupportDataSize);
D3D11CheckFeatureSupport D3D11CheckFeatureSupportObject;

typedef void(__stdcall* D3D11GetDevice) (ID3D11DeviceChild* Child, ID3D11Device** Device);
D3D11GetDevice D3D11GetDeviceObject;

typedef void(__stdcall* D3D11Begin) (ID3D11DeviceContext* Context, ID3D11Asynchronous* Async);
D3D11Begin D3D11BeginObject;*/


/*Here we call all our hooks
If you find yourself still not understanding
what each function is doing then I recommend you study some
assembly and try to learn the basic instructions :)
*/


//Setup our infinite ammo by changing an instruction
//You can also ignore the instructions
//Store where we jump back to after our hook
/*DWORD AmmoJmpBack = 0;
__declspec(naked) void InfiniteAmmo()
{
	//here's where ammo would normally be decreased
	//we will overwrite that instruction with something else
	__asm INC[ESI]
		//Make sure all the original instructions also run(within you're set of bytes)
		//this will prevent any crashing
		__asm push edi
	//When copying instructions from cheat engine/olly make sure to change any numbers to
	//0x so the compiler knows that its a hexadecimal value e.g. [esp+14] becomes [esp+0x14]
	__asm mov edi, [esp + 0x14]
		//Jump back to our original code
		__asm jmp[AmmoJmpBack]
}


//Store where we jump back to after our hook
DWORD FlyingJmpBack = 0;
//stores the register's address
DWORD YaxisRegister = 0x0;
DWORD YAxisPtr;

//Store our player's y axis into our dword
__declspec(naked) void GetPlayerYaxis()
{
	//Run the instructions the same as before
	//EXCEPT we take the address within ESI(Our Y axis)
	//AND later on modify it so we can fly
	//The offset of 0x3x tells us that ESI + 3C gives us
	//Y Axis, ESI is likely to point to our player base(unchecked)
	__asm MOV ECX, [ESI + 0x3C]
		//Throw our address into our DWORD YaxisRegister so we can
		//later modify the float value the address points to
		__asm MOV YaxisRegister, ESI
	__asm MOV[ESI + 0x08], EDX
	//Jump back to our original code
	__asm jmp[FlyingJmpBack]
}*/

/*	//ImGui::InputInt("Max FPS", MaxFPS, 1, 10);
	//ImGui::SameLine();

	ImGui::Text("Player.Object.Position: ");
	ImGui::SameLine();
	std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
	ImGui::Text(PlayerPositionString.c_str());

	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat3("Player Position Target", PlayerPositionTargetArray, 3);
	ImGui::SameLine();
	if (ImGui::Button("Sync##PlayerPositionTarget"))
	{
		PlayerPositionTargetArray[0] = PlayerPtr->Position.x;
		PlayerPositionTargetArray[1] = PlayerPtr->Position.y;
		PlayerPositionTargetArray[2] = PlayerPtr->Position.z;
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##PlayerPositionTarget"))
	{
		PlayerPtr->Position.x = PlayerPositionTargetArray[0];
		PlayerPtr->Position.y = PlayerPositionTargetArray[1];
		PlayerPtr->Position.z = PlayerPositionTargetArray[2];
		//NeedPlayerPosSet = true;

		std::cout << "Unsafely teleporting player to (" << PlayerPositionTargetArray[0] << ", " << PlayerPositionTargetArray[1] << ", " << PlayerPositionTargetArray[2] << ")!" << std::endl;
		HumanTeleportUnsafe(PlayerPtr, vector(PlayerPositionTargetArray[0], PlayerPositionTargetArray[1], PlayerPositionTargetArray[2]), PlayerPtr->Orientation);
	}

	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat3("Player velocity: ", (float*)&PlayerPtr->Velocity); //PlayerVelocityTargetArray);
	ImGui::SameLine();
	if (ImGui::Button("Sync##PlayerVelocityTarget"))
	{
		PlayerVelocityTargetArray[0] = PlayerPtr->Velocity.x;
		PlayerVelocityTargetArray[1] = PlayerPtr->Velocity.y;
		PlayerVelocityTargetArray[2] = PlayerPtr->Velocity.z;
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##PlayerVelocityTarget"))
	{
		PlayerPtr->Velocity.x = PlayerVelocityTargetArray[0];
		PlayerPtr->Velocity.y = PlayerVelocityTargetArray[1];
		PlayerPtr->Velocity.z = PlayerVelocityTargetArray[2];
		NeedPlayerVelocitySet = true;
	}*/





/*#define JsonCatchAll(FileName) \
catch (nlohmann::json::parse_error& Exception) \
{ \
	Logger::Log(std::string("Parse exception caught while parsing " + "\"" + FileName + "\""), LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage(std::string("Parse exception caught while parsing " + "\"" + FileName + "\"")); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::invalid_iterator& Exception) \
{ \
	Logger::Log("Invalid iterator exception caught while parsing" + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Invalid iterator exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::type_error& Exception) \
{ \
	Logger::Log("Type error exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Type error exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::out_of_range& Exception) \
{ \
	Logger::Log("Out of range exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Out of range exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::other_error& Exception) \
{ \
	Logger::Log("Other error exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Other error exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Other error parse exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (std::exception& Exception) \
{ \
	Logger::Log("General exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("General exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
 \
	return false; \
} \
catch (...) \
{ \
	Logger::Log("Default exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception caught while parsing " + "\"" + FileName + "\"", "Json default exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
 \
	return false; \
} */

/*
template<typename Callable>
auto JsonExceptionHandler(Callable&& Function, std::string FileName, std::string Action, std::string ActionConjugated, std::string Message) -> decltype(Function())
{
	try
	{
		return Function();
	}
	catch (nlohmann::json::parse_error& Exception)
	{
		Logger::Log("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::invalid_iterator& Exception)
	{
		Logger::Log("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::type_error& Exception)
	{
		Logger::Log("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::out_of_range& Exception)
	{
		Logger::Log("Out of range exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::other_error& Exception)
	{
		Logger::Log("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json other error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (std::exception& Exception)
	{
		Logger::Log("General exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("General exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (...)
	{
		Logger::Log("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);

		std::string ExceptionMessage("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json default exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
}
*/



/*Test of rl_draw::string(). Currently this just freezes the game. Will
probably end up just using an external lib to render text for now.*/
/*if (ImGui::Button("Test draw string"))
{
	rl_primitive_state* PrimitiveState;
	PrimitiveState = new rl_primitive_state;
	PrimitiveState->d.v.m_alpha_mode = 5;
	PrimitiveState->d.v.m_clamp_mode = 0;
	PrimitiveState->d.v.m_color_write_mode = 0;
	PrimitiveState->d.v.m_const_alpha = 0xFF;
	PrimitiveState->d.v.m_cull_mode = 0;
	PrimitiveState->d.v.m_msaa = 0;
	PrimitiveState->d.v.m_scissor = 0;
	PrimitiveState->d.v.m_stencil_mode = 0;
	PrimitiveState->d.v.m_valid = 1;
	PrimitiveState->d.v.m_zbias_mode = 0;
	PrimitiveState->d.v.m_zbuf_mode = 0;

	rl_draw_string(GlobalRlDrawPtr, nullptr, 100.0f, 100.0f, "Test string draw!!!", true, 0, PrimitiveState);
}*/

/*This is experimental code meant to manipulate the remnants of the games
debug console. Currently just tries to activate it. Later on I'll try to
manually add commands to it and run them. If that works, then I'll add them
to the lua system and port them through the overlay lua console.*/
/*ImGui::Text("Console Mode: "); ImGui::SameLine();
ImGui::TextColored(SecondaryTextColor, std::to_string((int)console_get_console_mode).c_str());
if (ImGui::Button("VCM_NORMAL (0)"))
{
	console_set_console_mode(VCM_NORMAL);
}
if (ImGui::Button("VCM_CHAT (1)"))
{
	console_set_console_mode(VCM_CHAT);
}
if (ImGui::Button("VCM_TEAMCHAT (2)"))
{
	console_set_console_mode(VCM_TEAMCHAT);
}

if (ImGui::Button("Console init"))
{
	vconsole_config* ConsoleConfig;
	ConsoleConfig = new vconsole_config; //Todo: Fix this if actually using. This is for testing purposes only and will cause a memory leak.
	ConsoleConfig->screen_width = 1680;
	ConsoleConfig->screen_height = 1050;
	ConsoleConfig->save_history = true;
	ConsoleConfig->safe_area_left = 0;
	Console_Init(ConsoleConfig);
}
if (ImGui::Button("Console activate"))
{
	Console_Activate();
}
if (ImGui::Button("Console deactivate"))
{
	Console_Deactivate();
}*/







/*ImGui::Separator();

if (ImGui::CollapsingHeader("Globals"))
{

}
ImGui::Separator();*/

//ImGui::Text("FPS: ");
//ImGui::Separator();

/*if (ImGui::CollapsingHeader("Global explosion modifiers##GlobalExplosionModifiersMain"))
{
	if (ImGui::Button("Reset to defaults##GlobalExplosionModifiersMain"))
	{
		GlobalExplosionStrengthMultiplier = 1.0f;
		UseGlobalExplosionStrengthMultiplier = false;
		UseExplosionRadiusLimits = true;
		MinimumExplosionRadius = 0.0f;
		MaximumExplosionRadius = 12.0f;
	}
	ImGui::PushItemWidth(232.0f);
	ImGui::SliderFloat("Global explosion strength multiplier", &GlobalExplosionStrengthMultiplier, 0.01f, 10.0f);
	ImGui::SameLine(); ImGui::Checkbox("Use", &UseGlobalExplosionStrengthMultiplier);
	ImGui::Checkbox("Use explosion radius limits", &UseExplosionRadiusLimits);
	Utilities::GUI::TooltipOnPrevious("If you turn this off be very very careful with the explosion multipliers. Too high and it's very easy to freeze/crash the game. My game froze at 4x explosions with no radius limits.");
	ImGui::InputFloat("Minimum explosion radius", &MinimumExplosionRadius, 0.1f, 1.0f, 3);
	ImGui::InputFloat("Maximum explosion radius", &MaximumExplosionRadius, 0.1f, 1.0f, 3);
}
else
{
	ImGui::SameLine(); ImGui::TextColored(ColorRed, " [Experimental]");
}*/

//ImGui::Separator();

//DrawTeleportGui(false, "Teleport", &TeleportWindowOpen, MainOverlayWindowFlags);
//ImGui::Separator();

//DrawPlayerVariablesGui(false, "Player variables", &PlayerVariablesGuiOpen, MainOverlayWindowFlags);
//ImGui::Separator();

//ImGui::Text("Misc Program Values:");