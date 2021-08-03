#include "stdafx.h"
#include "SkillModuleManager.h"

SkillModuleManager::SkillModuleManager()
{
	Initialize();
}

SkillModuleManager::~SkillModuleManager()
{
	Release();
}

void SkillModuleManager::Initialize()
{

}

void SkillModuleManager::Release()
{

}

void SkillModuleManager::Update()
{

}

void SkillModuleManager::AddSkillModule(int InObjectID, int SkillModuleID)
{
	SkillModule Module;
	ZeroMemory(&Module, sizeof(SkillModule));

	SkillModuleList.insert(std::make_pair(InObjectID, Module));
}

void SkillModuleManager::RemoveSkillModule(int InObjectID, int SkillModuleID)
{

}