#include "stdafx.h"
//#include "../../defines.h"
#include "../../ResourceMgr.h"
#include "TableManager.h"

using namespace std;

void TableManager::Load()
{
	// 전체를 로드하지 않고
	// 필요한 데이터만 즉시 로드
}

void TableManager::LoadSkillTemplate(int SkillID)
{
	auto Found = m_SkillDatas.find(SkillID);
	if (Found != m_SkillDatas.end())
	{
		return;
	}

	SkillTemplate Data;
	memset(&Data, 0, sizeof(SkillTemplate));

	switch (SkillID)
	{
	case 1:
		Data.SkillID = SkillID;
		Data.IconID = E_ImageID::imgID_NONID;
		Data.ModuleType = E_SkillModuleType::NormalAttack;
		Data.ArgumentA = 0;
		Data.ArgumentB = 0;
		Data.ArgumentC = 0;
		Data.ArgumentD = 0;
		break;

	case 2:
		Data.SkillID = SkillID;
		Data.IconID = E_ImageID::imgID_NONID;
		Data.ModuleType = E_SkillModuleType::Dash;
		break;

	case 3:
		Data.SkillID = SkillID;
		Data.IconID = E_ImageID::imgID_NONID;
		Data.ModuleType = E_SkillModuleType::ShootWhole;
		break;

	case 4:
		Data.SkillID = SkillID;
		Data.IconID = E_ImageID::imgID_NONID;
		Data.ModuleType = E_SkillModuleType::Inbeatable;
		break;

	case 5:
		Data.SkillID = SkillID;
		Data.IconID = E_ImageID::imgID_NONID;
		Data.ModuleType = E_SkillModuleType::DotHeal;
		Data.ArgumentA = 2;		// 회복량
		Data.ArgumentB = -1;	// 유지 시간
		Data.ArgumentC = 1;		// 회복 간격
		break;
	}

	if (Data.SkillID != 0)
	{
		m_SkillDatas.insert(make_pair(SkillID, Data));
	}
}

void TableManager::LoadCharacterTemplate(int TemplateID)
{
	auto Found = m_CharacterDatas.find(TemplateID);
	if (Found != m_CharacterDatas.end())
	{
		return;
	}

	CharacterTemplate Data;
	Data.TemplateID = 0;

	if (TemplateID == JOB_KNIGHT)
	{
		Data.TemplateID = TemplateID;

		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::NormalAttack, 1));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_Dash, 2));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_ShootWhole, 3));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_Inbeatable, 4));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Passive_Skill1, 5));

		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Idle, AnimationTemplate{ imgID_WARRIOR_IDLE , L"Data/Resource/Image/character/warrior/warrior_idle.bmp", SIZE{0, 0}, 8, 8, 50, true, true, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Move, AnimationTemplate{ imgID_WARRIOR_MOVE , L"Data/Resource/Image/character/warrior/warrior_walk.bmp", SIZE{0, 0}, 8, 8, 50, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Attack, AnimationTemplate{ imgID_WARRIOR_ATK  , L"Data/Resource/Image/character/warrior/warrior_atk.bmp", SIZE{0, 0}, 18, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Die, AnimationTemplate{ imgID_WARRIOR_DIE  , L"Data/Resource/Image/character/warrior/warrior_die.bmp", SIZE{0, 0}, 20, 8, 200, false, false, false }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::BeHit, AnimationTemplate{ imgID_WARRIOR_BEHIT, L"Data/Resource/Image/character/warrior/warrior-gethit.bmp", SIZE{0, 0}, 7, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Dash, AnimationTemplate{ imgID_WARRIOR_DASH , L"Data/Resource/Image/character/dash.bmp", SIZE{0, 0}, 5, 1, 40, false, false, true }));

		for (auto& each : Data.m_AnimationDatas)
		{
			RC_MGR->addImage(each.second.rcid, each.second.path, 0, 0, RM_TRANS);
			auto img = RC_MGR->findImage(each.second.rcid);
			if (img != nullptr)
			{
				each.second.size = img->getSize();
			}
		}
	}
	else if (TemplateID == JOB_ARCHER)
	{
		Data.TemplateID = TemplateID;

		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::NormalAttack, 1));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_Dash, 2));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_ShootWhole, 3));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Active_Inbeatable, 4));
		Data.m_SkillDatas.insert(make_pair(E_SkillSlot::Passive_Skill1, 5));

		// 궁수 이미지
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Idle, AnimationTemplate{ imgID_ARCHER_IDLE , L"Data/Resource/Image/character/archer/archer_idle.bmp", SIZE{0, 0}, 8, 8, 50, true, true, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Move, AnimationTemplate{ imgID_ARCHER_MOVE , L"Data/Resource/Image/character/archer/archer_walk.bmp", SIZE{0, 0}, 8, 8, 50, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Attack, AnimationTemplate{ imgID_ARCHER_ATK  , L"Data/Resource/Image/character/archer/archer_atk.bmp", SIZE{0, 0}, 12, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Die, AnimationTemplate{ imgID_ARCHER_DIE  , L"Data/Resource/Image/character/warrior_die.bmp", SIZE{0, 0}, 20, 8, 200, false, false, false }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::BeHit, AnimationTemplate{ imgID_ARCHER_BEHIT, L"Data/Resource/Image/character/archer/archer_behit.bmp", SIZE{0, 0}, 7, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Dash, AnimationTemplate{ imgID_ARCHER_DASH , L"Data/Resource/Image/character/dash.bmp", SIZE{0, 0}, 5, 1, 40, false, false, true }));

		for (auto& each : Data.m_AnimationDatas)
		{
			RC_MGR->addImage(each.second.rcid, each.second.path, 0, 0, RM_TRANS);
			auto img = RC_MGR->findImage(each.second.rcid);
			if (img != nullptr)
			{
				each.second.size = img->getSize();
			}
		}
	}

	if (Data.TemplateID != 0)
	{
		m_CharacterDatas.insert(make_pair(TemplateID, Data));
	}
}

void TableManager::LoadItemTemplate(int ItemID)
{
	auto Found = m_ItemDatas.find(ItemID);
	if (Found != m_ItemDatas.end())
	{
		return;
	}

	ItemTemplate Data;
	Data.ItemID = 0;
	
	switch (ItemID)
	{
	case ITEM_POTION_VENOM:
		Data.ItemID = ItemID;
		Data.ResourceID = 0;
		Data.AgumentA = 0;
		Data.AgumentB = 0;
		break;
	}

	if (ItemID != 0)
	{
		m_ItemDatas.insert(make_pair(ItemID, Data));
	}
}

const SkillTemplate* TableManager::GetSkillTemplate(int SkillID)
{
	auto Found = m_SkillDatas.find(SkillID);
	if (Found == m_SkillDatas.end())
	{
		LoadSkillTemplate(SkillID);

		Found = m_SkillDatas.find(SkillID);
		if (Found == m_SkillDatas.end())
		{
			return nullptr;
		}
	}

	return &(Found->second);

	return nullptr;
}

const CharacterTemplate* TableManager::GetCharacterTemplate(int TemplateID)
{
	auto Found = m_CharacterDatas.find(TemplateID);
	if (Found == m_CharacterDatas.end())
	{
		LoadCharacterTemplate(TemplateID);

		Found = m_CharacterDatas.find(TemplateID);
		if (Found == m_CharacterDatas.end())
		{
			return nullptr;
		}
	}

	return &(Found->second);
}

const ItemTemplate* TableManager::GetItemTemplate(int ItemID)
{
	auto Found = m_ItemDatas.find(ItemID);
	if (Found == m_ItemDatas.end())
	{
		LoadItemTemplate(ItemID);

		Found = m_ItemDatas.find(ItemID);
		if (Found == m_ItemDatas.end())
		{
			return nullptr;
		}
	}

	return &(Found->second);
}