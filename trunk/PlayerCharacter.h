#pragma once

class character;

class PlayerCharacter
{
public:
    PlayerCharacter() {}
    ~PlayerCharacter() {}

    void Init();
    void Release();
    void Update(float fDeltaTime);
    void Render(HDC hdc);

    character* GetCharacter();

    LRESULT	StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
    void SetAutoMode(bool AutoMode) { m_bAutoMode = AutoMode; }
    bool IsAutoMode() { return m_bAutoMode; }

private:
    void ProcessInputKey();

private:
    character* m_character;

    //< �ڵ����
    bool m_bAutoMode;

    //< Ÿ����
    Monster* m_pTarget;
};
