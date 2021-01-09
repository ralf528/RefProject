#pragma once

#include "../../Singleton.h"
#include <map>

struct AnimationTemplate
{
	imgID id;
	char path[_MAX_PATH];
	SIZE size;
	int countX;
	int countY;
	int speed;
	bool bFlag;
	bool bLoop;
	bool bPlay;
};

struct CharacterTemplate
{
	int TemplateID;

	E_SkillType SkillType_1;
	E_SkillType SkillType_2;
	E_SkillType SkillType_3;
	E_SkillType SkillType_4;

	std::map<int, AnimationTemplate> m_AnimationDatas;
};

class TableManager
{
public:
	TableManager() {}
	~TableManager() {}

private:
	SINGLETON(TableManager);

public:
	void Load();
	void LoadTemplate(int TemplateID);

	const CharacterTemplate* GetCharacterTemplate(int TemplateID);
	
private:
	std::map<int, CharacterTemplate> m_CharacterDatas;
};

#define TABLE_MGR Singleton<TableManager>::GetInstance()