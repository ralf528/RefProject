#pragma once

class character;
class Inventory;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

    void Init();
    void Release();
    void Update(float fDeltaTime);
    void Render(HDC hdc);
	void RenderInventory(HDC hdc);

    character* GetCharacter();

    LRESULT	StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
    void SetAutoMode(bool AutoMode) { m_bAutoMode = AutoMode; }
    bool IsAutoMode() { return m_bAutoMode; }

	void AddItem(int InObjectID);
	bool UseItem(int InItemID);

private:
    void ProcessInputKey();

private:
    character* m_character;

	//< 인벤토리
	Inventory *m_inventory;

    //< 자동모드
    bool m_bAutoMode;

    //< 타겟팅
    Monster* m_pTarget;
};
