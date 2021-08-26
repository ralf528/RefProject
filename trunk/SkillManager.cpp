#include "stdafx.h"
#include "SkillManager.h"

SkillManager::SkillManager()
{
	Init();
}

SkillManager::~SkillManager()
{
	Release();
}

void SkillManager::Init()
{
	m_CoolTimeList.clear();
}

void SkillManager::Release()
{
	m_CoolTimeList.clear();
}

void SkillManager::Update()
{
	UpdateCoolTime();
}

bool SkillManager::ProcessSkill()
{

	return true;
}

void SkillManager::UpdateCoolTime()
{
	if (m_CoolTimeList.size() <= 0)
	{
		return;
	}

	for (auto EachObject : m_CoolTimeList)
	{
		std::vector<int> DeleteList;

		for (auto CoolTimeList : EachObject.second)
		{
			if (CoolTimeList.second.StartTime + CoolTimeList.second.CoolTime <= myUTIL::FpsTime::getWorldTime())
			{
				DeleteList.push_back(CoolTimeList.second.SkillType);
			}
		}

		for (auto EachDelete : DeleteList)
		{
			RemoveCoolTime(EachObject.first, EachDelete);
		}
	}
}

void SkillManager::SetCoolTime(int ObjectID, int SkillType, float CoolTime)
{
	auto ObjectInfo = m_CoolTimeList.find(ObjectID);
	if (ObjectInfo == m_CoolTimeList.end())
	{
		CoolTimeMap CoolTimeList;
		CoolTimeInfo CoolInfo;
		CoolInfo.SkillType = SkillType;
		CoolInfo.CoolTime = CoolTime;
		CoolInfo.StartTime = myUTIL::FpsTime::getWorldTime();

		CoolTimeList.insert(std::make_pair(SkillType, CoolInfo));
		
		m_CoolTimeList.insert(std::make_pair(ObjectID, CoolTimeList));
		return;
	}

	CoolTimeMap& CoolTimeList = ObjectInfo->second;

	auto FoundCoolTime = CoolTimeList.find(SkillType);
	if (FoundCoolTime == CoolTimeList.end())
	{
		CoolTimeInfo CoolInfo;
		CoolInfo.SkillType = SkillType;
		CoolInfo.CoolTime = CoolTime;
		CoolInfo.StartTime = myUTIL::FpsTime::getWorldTime();

		CoolTimeList.insert(std::make_pair(SkillType, CoolInfo));
		return;
	}

	// 이미 쿨타임이 있는데 또 추가?
	CoolTimeInfo& CoolInfo = FoundCoolTime->second;
	CoolInfo.SkillType = SkillType;
	CoolInfo.CoolTime = CoolTime;
	CoolInfo.StartTime = myUTIL::FpsTime::getWorldTime();

	CoolTimeList.insert(std::make_pair(SkillType, CoolInfo));
}

float SkillManager::GetCoolTime(int ObjectID, int SkillType)
{
	auto ObjectInfo = m_CoolTimeList.find(ObjectID);
	if (ObjectInfo == m_CoolTimeList.end())
	{
		return 0.f;
	}

	CoolTimeMap& CoolTimeList = ObjectInfo->second;

	auto FoundCoolTime = CoolTimeList.find(SkillType);
	if (FoundCoolTime == CoolTimeList.end())
	{
		return 0.f;
	}

	return FoundCoolTime->second.CoolTime;
}

void SkillManager::RemoveCoolTime(int ObjectID, int SkillType)
{
	auto ObjectInfo = m_CoolTimeList.find(ObjectID);
	if (ObjectInfo == m_CoolTimeList.end())
	{
		return;
	}

	CoolTimeMap& CoolTimeList = ObjectInfo->second;

	auto FoundCoolTime = CoolTimeList.find(SkillType);
	if (FoundCoolTime != CoolTimeList.end())
	{
		CoolTimeList.erase(SkillType);
	}
}