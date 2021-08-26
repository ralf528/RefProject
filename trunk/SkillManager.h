#pragma once

#include "Singleton.h"

struct CoolTimeInfo
{
	int SkillType;
	float CoolTime;
	float StartTime;
};

class SkillManager
{
private:
    SkillManager();
    virtual ~SkillManager();

    SINGLETON(SkillManager);

public:
	void Init();
	void Release();
	void Update();

	bool ProcessSkill();

	// Skill Cool Time
	void UpdateCoolTime();
	void SetCoolTime(int ObjectID, int SkillType, float CoolTime);
	float GetCoolTime(int ObjectID, int SkillType);
	void RemoveCoolTime(int ObjectID, int SkillType);

private:
	typedef std::map<int, CoolTimeInfo> CoolTimeMap;
	std::map<int, CoolTimeMap> m_CoolTimeList;
};

#define SKILL_MGR Singleton<SkillManager>::GetInstance()