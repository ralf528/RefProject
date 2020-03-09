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

private:
    void ProcessInputKey();

private:
    character* m_character;
};
