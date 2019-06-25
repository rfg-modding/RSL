#pragma once
#include "Logger.h"

enum Opcodes : int
{
    NOP = 0x90,
    JMP_REL8 = 0xEB,
    PUSH = 0x68,
    MOV = 0xC7,
    RET = 0xC3
};

class CodeSnippet
{
public:
	CodeSnippet() = default;
	CodeSnippet(DWORD Address_, DWORD Length_) : Address(Address_), Length(Length_) { }

	DWORD Address = 0;
	DWORD Length = 0;
	std::vector <int> Opcodes;
};

class SnippetManager
{
public:

	static std::unordered_map <std::string, CodeSnippet> SnippetCache;

	static void BackupSnippet(std::string Name, DWORD Address, DWORD Length, bool NOP);
	static void RestoreSnippet(std::string Name, bool RemoveFromCache);
	static void NOPSnippet(std::string Name);
    static void ReplaceSnippet(std::string Name, DWORD Address, std::vector<int>& NewOpcodes);

private:
	SnippetManager() { };
};

