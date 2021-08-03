#pragma once

#include "Singleton.h"

struct SkillModule
{
	int ModuleType;
	int ArgumentA;
	int ArgumentB;
	int ArgumentC;
	int ArgumentD;
};

/*
	Update 에서 해당 캐릭터를 찾아서 해당 효과 부여
*/

class SkillModuleManager
{

private:
	SkillModuleManager();
	virtual ~SkillModuleManager();

	SINGLETON(SkillModuleManager);

public:
	void Initialize();
	void Release();
	void Update();

	void AddSkillModule(int InObjectID, int SkillModuleID);
	void RemoveSkillModule(int InObjectID, int SkillModuleID);

private:
	std::map<int, SkillModule> SkillModuleList;
};


#define MODULE_MGR Singleton<SkillModuleManager>::GetInstance()