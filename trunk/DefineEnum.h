#pragma once

namespace E_SkillSlot
{
	enum Type
	{
		None = 0,
		NormalAttack,
		Active_Dash,
		Active_ShootWhole,
		Active_Inbeatable,
		Passive_Skill1,
	};
};

namespace E_SkillModuleType
{
	enum Type
	{
		None = 0,
		NormalAttack,
		Dash,
		ShootWhole,
		Inbeatable,
		DotHeal,
	};
};

// 스킬 타입은 ..