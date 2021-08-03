#pragma once

class CharacterStateBase
{
public:
	CharacterStateBase() {}
	virtual ~CharacterStateBase() {}

	virtual bool Begin() {}
	virtual bool End() {}

private:

};