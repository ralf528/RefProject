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
	Update ���� �ش� ĳ���͸� ã�Ƽ� �ش� ȿ�� �ο�
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