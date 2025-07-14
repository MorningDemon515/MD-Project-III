#include "Main.h"

#include "Scene.h"

bool run = true;
extern HWND WindowHanled;

void InitWindow(const char* title, HINSTANCE instanceHanled, int show);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR pCmdLine,
    int nShowCmd)
{
    InitWindow("MDP-III", hInstance, nShowCmd);

    MSG msg;

    Scene scene = Scene();

    while (run)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                run = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            scene.Draw();
        }

    }

    DestroyWindow(WindowHanled);
    UnregisterClass(L"Window Class", hInstance);
    return (int)msg.wParam;
}

void ErrorMessage_1(const char* message)
{
    MessageBoxA(NULL, message, "Engine Error!", MB_OK);
}

void ErrorMessage_2(HWND hwnd, const char* message)
{
    MessageBoxA(hwnd, message, "Engine Error!", MB_OK);
}

float TimeDelta()
{
    static float lastTime = 0.0f;
    static float currentTime = 0.0f;
    currentTime = (float)clock() / CLOCKS_PER_SEC;
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;

}