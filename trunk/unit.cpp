#include "stdafx.h"
#include "unit.h"

StatusType::StatusType()
{
	m_value.clear();
}

int StatusType::GetValue()
{
	int result = 0;

	for (auto Each : m_value)
	{
		result += Each.second;
	}

	return result;
}

void StatusType::SetValue(ESTATUS_TYPE eType, int value)
{
	auto found = m_value.find(eType);
	if (found != m_value.end())
	{
		found->second = value;
		return;
	}

	m_value.insert(std::make_pair(eType, value));
}

void StatusType::AddValue(ESTATUS_TYPE eType, int value)
{
	auto found = m_value.find(eType);
	if (found != m_value.end())
	{
		found->second += value;
		return;
	}

	m_value.insert(std::make_pair(eType, value));
}

void Unit::incHP(int offset)
{
	m_nowHP += offset;

	if (getHP() > getMaxHP())
	{
		setHP(getMaxHP());
	}
}

void Unit::setCondition(int cond, int delay)
{
	m_Abnormal.AbnormalType = cond;
	m_Abnormal.Delay.m_deley = delay;
	m_Abnormal.Delay.m_lastTime = GetTickCount();
}

void Unit::UpdateCondition()
{
	if (m_Abnormal.AbnormalType == CONDITION_NORMAL)
	{
		return;
	}

	if (m_Abnormal.Delay.m_lastTime + m_Abnormal.Delay.m_deley >= GetTickCount())
	{
		m_Abnormal.AbnormalType = CONDITION_NORMAL;
		m_Abnormal.Delay.m_deley = 0;
		m_Abnormal.Delay.m_lastTime = 0;
	}
}