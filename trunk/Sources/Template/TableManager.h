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