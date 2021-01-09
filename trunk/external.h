#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 전역헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// C 런타임 헤더 파일입니다.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, C형헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <fmod.h>

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, C++형헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <iostream>	//< stdio.h stdlib.h string.h 외에 여러가지가 들어있음
#include <list>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 윈도우형헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <winSock2.h>

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 라이브러리헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#pragma comment(lib, "ws2_32")

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 전역헤더, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include "defines.h"
#include "DefineEnum.h"
#include "mytype.h"
#include "myUTIL.h"
using namespace myUTIL;
#include "Singleton.h"

//#include "cEffect.h"
#include "GameManager.h"
#include "StateMgr.h"
#include "ImageNode.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "JN_LogMgr.h"
#include "Camera.h"
#include "monsterMgr.h"
//#include "other_mgr.h"
//#include "SoundMgr.h"
#include "AniMgr.h"

#include "ButtonClass.h"
#include "Scene/Popup/Popup_Loot.h"
#include "InputString.h"

#include "PopupMgr.h"

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 전역변수, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
extern HINSTANCE	g_hInst;						//인스턴스의 핸들선언(운영체제에서 정해줄 번호)
extern HWND			g_hWnd;							//윈도우의 핸들(윈도우를 대표하는 번호)