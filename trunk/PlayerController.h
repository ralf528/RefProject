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

	//< �κ��丮
	Inventory *m_inventory;

    //< �ڵ����
    bool m_bAutoMode;

    //< Ÿ����
    Monster* m_pTarget;
};
