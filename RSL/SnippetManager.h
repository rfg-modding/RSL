#pragma once
#include "Logger.h"
#include "ISnippetManager.h"

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

class SnippetManager : public ISnippetManager
{
public:
    SnippetManager() { }
    ~SnippetManager() { }

	std::unordered_map <std::string, CodeSnippet> SnippetCache;

	void BackupSnippet(std::string Name, DWORD Address, DWORD Length, bool NOP);
	void RestoreSnippet(std::string Name, bool RemoveFromCache);
	void NOPSnippet(std::string Name);
    void ReplaceSnippet(std::string Name, DWORD Address, std::vector<int>& NewOpcodes);
};

