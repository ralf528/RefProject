#include "stdafx.h"

#include "../../ScenePlayGame.h"
#include "../../PlayerCharacter.h"
#include "../../character.h"

#include "CheatManager.h"

CheatManager::CheatManager()
{
	LoadFunctions();
}
CheatManager::~CheatManager()
{
	m_Functions.clear();
}

vector<string> CheatManager::StringParse(const char* Message)
{
	vector<string> ParseMessage;
	if (Message == nullptr)
	{
		return ParseMessage;
	}

	char StrTemp[_MAX_FNAME];
	strcpy_s(StrTemp, _MAX_FNAME, Message);
	char* context = StrTemp;

	char* token = strtok_s(context, " ", &context);
	while (token)
	{
		ParseMessage.push_back(token);

		token = strtok_s(context, " ", &context);
	}

	return ParseMessage;
}

string CheatManager::ToLowerString(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void CheatManager::LoadFunctions()
{
	m_Functions.clear();
	m_Functions.insert(make_pair(ToLowerString("SetPosition"), &CheatManager::SetPosition));
}

bool CheatManager::ProcessCheat(const char* InputMessage)
{
	if (InputMessage == nullptr || InputMessage[0] != '/')
	{
		return false;
	}

	Parser CheatMsg = StringParse(InputMessage + 1);
	if (CheatMsg.empty())
	{
		return false;
	}

	auto Found = m_Functions.find(ToLowerString(CheatMsg[0]));
	if (Found == m_Functions.end())
	{
		return false;
	}

	FuncPointer func = Found->second;
	(this->*func)(CheatMsg);

	return true;
}

void CheatManager::SetPosition(Parser CheatMessage)
{
	LOG_MGR->addLog("%s", CheatMessage[0].c_str());

	if (CheatMessage.size() < 3)
	{
		return;
	}

	ScenePlayGame* nowState = static_cast<ScenePlayGame*>(STATE_MGR->nowScene());
	if (nowState == nullptr)
	{
		return;
	}

	PlayerCharacter* Player = nowState->GetPlayer();
	if (Player == nullptr)
	{
		return;
	}

	character* Character = Player->GetCharacter();
	if (Character == nullptr)
	{
		return;
	}

	long x = atol(CheatMessage[1].c_str());
	long y = atol(CheatMessage[2].c_str());

	Character->setPos(x, y);
};