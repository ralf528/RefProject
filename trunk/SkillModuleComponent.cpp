#include "stdafx.h"
#include "SkillDefineEnum.h"
#include "SkillModuleComponent.h"

SkillModuleComponent::SkillModuleComponent()
{
	Initialize(nullptr);
}

SkillModuleComponent::~SkillModuleComponent()
{
	Release();
}

void SkillModuleComponent::Initialize(character* InOwner)
{
	OwnerCharacter = InOwner;
}

void SkillModuleComponent::Release()
{

}

void SkillModuleComponent::Update()
{
	for (auto& EachModule : SkillModuleList)
	{
		SkillModule& Module = EachModule.second;

		// check time
		if (Module.ExpireTime != -1)
		{
			if (EachModule.second.ExpireTime >= myUTIL::FpsTime::getWorldTime())
			{
				RemoveSkillModule(EachModule.first);
			}
		}

		ProcessSkillModule(Module);
	}
}

bool SkillModuleComponent::AddSkillModule(const SkillTemplate* InSkillTemplate)
{
	if (InSkillTemplate == nullptr)
	{
		return false;
	}

	SkillModule Module;
	ZeroMemory(&Module, sizeof(SkillModule));

	Module.SkillID = InSkillTemplate->SkillID;
	Module.SkillData = InSkillTemplate;

	Module.StartTime = myUTIL::FpsTime::getWorldTime();
	Module.ExpireTime = -1.f;

	SkillModuleList.insert(std::make_pair(Module.SkillID, Module));

	return true;
}

void SkillModuleComponent::RemoveSkillModule(int SkillModuleID)
{
	SkillModuleList.erase(SkillModuleID);
}

bool SkillModuleComponent::ProcessSkillModule(SkillModule& Module)
{
	if (OwnerCharacter == nullptr || Module.SkillData == nullptr)
	{
		return false;
	}

	switch (Module.SkillData->ModuleType)
	{
	case E_SkillModuleType::DotHeal:
		// A : HealAmount, B: ExpireTime, C : Term(second)
		const float CurrentTime = myUTIL::FpsTime::getWorldTime();
		if (Module.StartTime <= CurrentTime)
		{
			Module.StartTime = CurrentTime + Module.SkillData->ArgumentC;

			if (OwnerCharacter->getMP() < OwnerCharacter->getMaxMP())
			{
				OwnerCharacter->incMP(2);
				if (OwnerCharacter->getMP() > OwnerCharacter->getMaxMP())
				{
					OwnerCharacter->setMP(OwnerCharacter->getMaxHP());
				}
			}
		}
		break;
	}

	return true;
}