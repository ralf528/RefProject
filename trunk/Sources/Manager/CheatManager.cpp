#include "stdafx.h"

#include "../../ScenePlayGame.h"
#include "../../PlayerController.h"
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

void CheatManager::LoadFunctions()
{
	m_Functions.clear();
	m_Functions.insert(make_pair(ToLowerString("SetPosition"), &CheatManager::SetPosition));
	m_Functions.insert(make_pair(ToLowerString("SwitchCharacter"), &CheatManager::SwitchCharacter));
	m_Functions.insert(make_pair(ToLowerString("AddItem"), &CheatManager::AddItem));
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

bool CheatManager::ProcessCheat(const TCHAR* InputMessage)
{
	char cTemp[_MAX_FNAME];
	WideCharToMultiByte(CP_ACP, 0, InputMessage, _MAX_FNAME, cTemp, _MAX_FNAME, NULL, NULL);

	return ProcessCheat(cTemp);
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

	PlayerController* Player = nowState->GetPlayerController();
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
}

void CheatManager::SwitchCharacter(Parser CheatMessage)
{
	LOG_MGR->addLog("%s", CheatMessage[0].c_str());

	if (CheatMessage.size() < 1)
	{
		return;
	}

	ScenePlayGame* nowState = static_cast<ScenePlayGame*>(STATE_MGR->nowScene());
	if (nowState == nullptr)
	{
		return;
	}

	PlayerController* Player = nowState->GetPlayerController();
	if (Player == nullptr)
	{
		return;
	}

	character* Character = Player->GetCharacter();
	if (Character == nullptr)
	{
		return;
	}

	int TemplateID = atoi(CheatMessage[1].c_str());
	POINT pos = Character->getPos();

	Character->SetJobType(static_cast<E_JobType>(TemplateID));
	Character->init();
	Character->setPos(pos);
}

void CheatManager::AddItem(Parser CheatMessage)
{
	LOG_MGR->addLog("%s", CheatMessage[0].c_str());

	if (CheatMessage.size() < 2)
	{
		return;
	}

	ScenePlayGame* nowState = static_cast<ScenePlayGame*>(STATE_MGR->nowScene());
	if (nowState == nullptr)
	{
		return;
	}

	PlayerController* Player = nowState->GetPlayerController();
	if (Player == nullptr)
	{
		return;
	}

	character* Character = Player->GetCharacter();
	if (Character == nullptr)
	{
		return;
	}

	int ItemTemplateID = atoi(CheatMessage[1].c_str());
	if (ItemTemplateID >= ITEM_FIRST && ItemTemplateID < ITEM_END)
	{
		Character->gainCollider((E_TileBrush)ItemTemplateID);
	}
}