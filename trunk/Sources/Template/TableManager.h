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
	int SkillID;
	E_ImageID IconID;
	E_SkillModuleType::Type ModuleType;
	int ArgumentA;
	int ArgumentB;
	int ArgumentC;
	int ArgumentD;
};

struct CharacterTemplate
{
	int TemplateID;

	std::map<E_SkillSlot::Type, int> m_SkillDatas;
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
	void LoadSkillTemplate(int SkillID);
	void LoadCharacterTemplate(int TemplateID);
	void LoadItemTemplate(int ItemID);

	const SkillTemplate* GetSkillTemplate(int SkillID);
	const CharacterTemplate* GetCharacterTemplate(int TemplateID);
	const ItemTemplate* GetItemTemplate(int ItemID);
	
private:
	std::map<int, SkillTemplate> m_SkillDatas;
	std::map<int, CharacterTemplate> m_CharacterDatas;
	std::map<int, ItemTemplate> m_ItemDatas;
};

#define TABLE_MGR Singleton<TableManager>::GetInstance()