#pragma once

#include "../../Singleton.h"
#include <map>

struct AnimationTemplate
{
	E_ImageID rcid;
	TCHAR path[_MAX_PATH];
	SIZE size;
	int countX;
	int countY;
	int speed;
	bool bFlag;
	bool bLoop;
	bool bPlay;
};

struct SkillTemplate
{
	E_SkillType type;
	E_ImageID rcid;
};

struct CharacterTemplate
{
	int TemplateID;

	std::map<E_SkillType, SkillTemplate> m_SkillDatas;
	std::map<E_AnimationType, AnimationTemplate> m_AnimationDatas;
};

struct ItemTemplate
{
	int ItemID;
	int ResourceID;
	int AgumentA;
	int AgumentB;
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
	void LoadCharacterTemplate(int TemplateID);
	void LoadItemTemplate(int ItemID);

	const CharacterTemplate* GetCharacterTemplate(int TemplateID);
	const ItemTemplate* GetItemTemplate(int ItemID);
	
private:
	std::map<int, CharacterTemplate> m_CharacterDatas;
	std::map<int, ItemTemplate> m_ItemDatas;
};

#define TABLE_MGR Singleton<TableManager>::GetInstance()