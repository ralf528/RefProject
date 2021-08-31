#pragma once

/*
��ų ��� ������ ������
Skill Module Template ���� ���� �����ϰ�
SkillModule ������ ������ �ɸ��� ����� ����
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
	Update ���� �ش� ĳ���͸� ã�Ƽ� �ش� ȿ�� �ο�
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