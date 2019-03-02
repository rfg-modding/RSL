#pragma once
//#include "Globals.h"
#include "Logger.h"

class CodeSnippet
{
public:
	CodeSnippet() { } 
	CodeSnippet(DWORD Address_, DWORD Length_) : Address(Address_), Length(Length_) { }

	DWORD Address = 0;
	DWORD Length = 0;
	std::vector <int> Opcodes;
};

class SnippetManager
{
public:
	//SnippetManager();
	//~SnippetManager();

	static std::map <std::string, CodeSnippet> SnippetCache;

	static void BackupSnippet(std::string Name, DWORD Address, DWORD Length, bool NOP);
	static void RestoreSnippet(std::string Name, bool RemoveFromCache);
	static void NOPSnippet(std::string Name);

private:
	SnippetManager() { };
};

