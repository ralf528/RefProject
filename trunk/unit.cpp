#include "stdafx.h"
#include "unit.h"

void Unit::incHP(int offset)
{
	m_state.m_nowHP += offset;

	if (getHP() > getMaxHP())
	{
		setHP(getMaxHP());
	}
}