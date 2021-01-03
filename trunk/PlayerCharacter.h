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

    //< 자동모드
    bool m_bAutoMode;

    //< 타겟팅
    Monster* m_pTarget;
};
