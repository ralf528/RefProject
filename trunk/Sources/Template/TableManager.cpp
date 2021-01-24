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

void TableManager::LoadTemplate(int TemplateID)
{
	auto Found = m_CharacterDatas.find(TemplateID);
	if (Found != m_CharacterDatas.end())
	{
		return;
	}

	if (TemplateID == JOB_KNIGHT)
	{
		CharacterTemplate Data;
		Data.TemplateID = TemplateID;

		Data.SkillType_1 = E_SkillType_NormalAttack;
		Data.SkillType_2 = E_SkillType_Dash;
		Data.SkillType_3 = E_SkillType_ShootWhole;
		Data.SkillType_4 = E_SkillType_Inbeatable;

		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Idle, AnimationTemplate{ imgID_WARRIOR_IDLE , "Data/Resource/Image/character/warrior/warrior_idle.bmp", SIZE{0, 0}, 8, 8, 50, true, true, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Move, AnimationTemplate{ imgID_WARRIOR_MOVE , "Data/Resource/Image/character/warrior/warrior_walk.bmp", SIZE{0, 0}, 8, 8, 50, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Attack, AnimationTemplate{ imgID_WARRIOR_ATK  , "Data/Resource/Image/character/warrior/warrior_atk.bmp", SIZE{0, 0}, 18, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Die, AnimationTemplate{ imgID_WARRIOR_DIE  , "Data/Resource/Image/character/warrior/warrior_die.bmp", SIZE{0, 0}, 20, 8, 200, false, false, false }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::BeHit, AnimationTemplate{ imgID_WARRIOR_BEHIT, "Data/Resource/Image/character/warrior/warrior-gethit.bmp", SIZE{0, 0}, 7, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Dash, AnimationTemplate{ imgID_WARRIOR_DASH , "Data/Resource/Image/character/dash.bmp", SIZE{0, 0}, 5, 1, 40, false, false, true }));

		for (auto& each : Data.m_AnimationDatas)
		{
			RC_MGR->addImage(each.second.rcid, each.second.path, 0, 0, RM_TRANS);
			auto img = RC_MGR->findImage(each.second.rcid);
			if (img != nullptr)
			{
				each.second.size = img->getSize();
			}
		}

		m_CharacterDatas.insert(make_pair(TemplateID, Data));
	}
	else if (TemplateID == JOB_ARCHER)
	{
		CharacterTemplate Data;
		Data.TemplateID = TemplateID;

		Data.SkillType_1 = E_SkillType_NormalAttack;
		Data.SkillType_2 = E_SkillType_Dash;
		Data.SkillType_3 = E_SkillType_ShootWhole;
		Data.SkillType_4 = E_SkillType_Inbeatable;

		// 궁수 이미지
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Idle, AnimationTemplate{ imgID_ARCHER_IDLE , "Data/Resource/Image/character/archer/archer_idle.bmp", SIZE{0, 0}, 8, 8, 50, true, true, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Move, AnimationTemplate{ imgID_ARCHER_MOVE , "Data/Resource/Image/character/archer/archer_walk.bmp", SIZE{0, 0}, 8, 8, 50, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Attack, AnimationTemplate{ imgID_ARCHER_ATK  , "Data/Resource/Image/character/archer/archer_atk.bmp", SIZE{0, 0}, 12, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Die, AnimationTemplate{ imgID_ARCHER_DIE  , "Data/Resource/Image/character/warrior_die.bmp", SIZE{0, 0}, 20, 8, 200, false, false, false }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::BeHit, AnimationTemplate{ imgID_ARCHER_BEHIT, "Data/Resource/Image/character/archer/archer_behit.bmp", SIZE{0, 0}, 7, 8, 20, false, false, true }));
		Data.m_AnimationDatas.insert(make_pair(E_AnimationType::Dash, AnimationTemplate{ imgID_ARCHER_DASH , "Data/Resource/Image/character/dash.bmp", SIZE{0, 0}, 5, 1, 40, false, false, true }));

		for (auto& each : Data.m_AnimationDatas)
		{
			RC_MGR->addImage(each.second.rcid, each.second.path, 0, 0, RM_TRANS);
			auto img = RC_MGR->findImage(each.second.rcid);
			if (img != nullptr)
			{
				each.second.size = img->getSize();
			}
		}

		m_CharacterDatas.insert(make_pair(TemplateID, Data));
	}
}

const CharacterTemplate* TableManager::GetCharacterTemplate(int TemplateID)
{
	auto Found = m_CharacterDatas.find(TemplateID);
	if (Found == m_CharacterDatas.end())
	{
		LoadTemplate(TemplateID);

		Found = m_CharacterDatas.find(TemplateID);
		if (Found == m_CharacterDatas.end())
		{
			return nullptr;
		}
	}

	return &(Found->second);
}