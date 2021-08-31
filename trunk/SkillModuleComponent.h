#pragma once

/*
스킬 모듈 데이터 정보는
Skill Module Template 으로 따로 정의하고
SkillModule 에서는 실제로 걸리는 모듈의 정보
*/

class SkillTemplate;
class character;

struct SkillModule
{
	int SkillID;
	const SkillTemplate* SkillData;

	float StartTime;
	float ExpireTime;
};

/*
	Update 에서 해당 캐릭터를 찾아서 해당 효과 부여
*/

class SkillModuleComponent
{

public:
	SkillModuleComponent();
	virtual ~SkillModuleComponent();

public:
	void Initialize(character* InOwner);
	void Release();
	void Update();

	bool AddSkillModule(const SkillTemplate* InSkillTemplate);
	void RemoveSkillModule(int SkillModuleID);

	bool ProcessSkillModule(SkillModule& Module);

private:
	std::map<int, SkillModule> SkillModuleList;

	character* OwnerCharacter;
};


#define MODULE_MGR Singleton<SkillModuleComponent>::GetInstance()