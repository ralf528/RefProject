#pragma once

#include "Singleton.h"

class SkillManager
{
private:
    SkillManager();
    virtual ~SkillManager();

    SINGLETON(SkillManager);

public:

    bool ProcessSkill();

private:
};

#define SKILL_MGR Singleton<SkillManager>::GetInstance()