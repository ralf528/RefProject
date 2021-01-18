#pragma once

#include <string>
#include <map>
#include <vector>
#include "../../Singleton.h"

using namespace std;

class CheatManager
{
	typedef vector<string> Parser;
	typedef void(CheatManager::*FuncPointer)(Parser);

public:
	CheatManager();
	virtual ~CheatManager();

private:
	SINGLETON(CheatManager);

private:
	vector<string> StringParse(const char* Message);
	string ToLowerString(string str);

public:
	void LoadFunctions();

	bool ProcessCheat(const char* InputMessage);

	// Cheat Function
	void SetPosition(Parser CheatMessage);

private:
	map<string, FuncPointer> m_Functions;
};

#define CHEAT_MGR Singleton<CheatManager>::GetInstance()

