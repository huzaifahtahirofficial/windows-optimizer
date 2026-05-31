#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <string>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")

// Global variables
HINSTANCE hInst;
HWND hWndMain;
HFONT hFontMain, hFontSmall, hFontTitle;
char statusMsg[256] = "SYSTEM SECURE. READY FOR OPTIMIZATION...";

COLORREF clrBack = RGB(10, 10, 12);
COLORREF clrAccent = RGB(0, 195, 255);
COLORREF clrWhite = RGB(245, 245, 247);

#define ID_BTN_AETHER 201
#define ID_BTN_KINETIC 202
#define ID_BTN_FLUX 203
#define ID_BTN_CORESYNC 204

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ApplyAppleStyle(HWND);
void UpdateStatus(HWND hWnd, const char* msg);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    InitCommonControls();
    
    const char* CLASS_NAME = "SkelerLabs_OS";

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME; // FIXED: Changed from hClassName
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(clrBack);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wc.hIconSm = wc.hIcon;

    if (!RegisterClassEx(&wc)) return 0;

    hWndMain = CreateWindowEx(
        WS_EX_LAYERED, 
        CLASS_NAME, 
        "SKELER SECURITY | NEURAL ENGINE", 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 650, 
        NULL, NULL, hInstance, NULL
    );

    if (!hWndMain) return 0;

    SetLayeredWindowAttributes(hWndMain, 0, 245, LWA_ALPHA);
    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }
    return 0;
}

void UpdateStatus(HWND hWnd, const char* msg) {
    strncpy(statusMsg, msg, 255);
    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);
}

void ApplyAppleStyle(HWND hWnd) {
    hFontTitle = CreateFont(42, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
    hFontMain = CreateFont(22, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
    hFontSmall = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Consolas");

    CreateWindowEx(0, "BUTTON", "AETHER SCRUB", WS_VISIBLE | WS_CHILD | BS_FLAT, 50, 150, 380, 180, hWnd, (HMENU)ID_BTN_AETHER, hInst, NULL);
    CreateWindowEx(0, "BUTTON", "KINETIC OVERDRIVE", WS_VISIBLE | WS_CHILD | BS_FLAT, 450, 150, 380, 180, hWnd, (HMENU)ID_BTN_KINETIC, hInst, NULL);
    CreateWindowEx(0, "BUTTON", "FLUX OPTIMIZER", WS_VISIBLE | WS_CHILD | BS_FLAT, 50, 350, 380, 180, hWnd, (HMENU)ID_BTN_FLUX, hInst, NULL);
    CreateWindowEx(0, "BUTTON", "CORE SYNC", WS_VISIBLE | WS_CHILD | BS_FLAT, 450, 350, 380, 180, hWnd, (HMENU)ID_BTN_CORESYNC, hInst, NULL);

    for (int i = 201; i <= 204; i++) {
        SendMessage(GetDlgItem(hWnd, i), WM_SETFONT, (WPARAM)hFontMain, TRUE);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: 
            ApplyAppleStyle(hWnd); 
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rect; GetClientRect(hWnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            
            SelectObject(hdc, hFontTitle); SetTextColor(hdc, clrWhite);
            TextOut(hdc, 50, 40, "SKELER SECURITY", 15);

            SelectObject(hdc, hFontSmall); SetTextColor(hdc, clrAccent);
            TextOut(hdc, 55, 90, "SYSTEM INTELLIGENCE ACTIVATED // SKELER LABS", 45);

            RECT footer = {0, rect.bottom - 40, rect.right, rect.bottom};
            HBRUSH hFootB = CreateSolidBrush(RGB(20, 20, 25));
            FillRect(hdc, &footer, hFootB); DeleteObject(hFootB);

            SetTextColor(hdc, RGB(0, 255, 120));
            TextOut(hdc, 20, rect.bottom - 30, statusMsg, strlen(statusMsg));

            EndPaint(hWnd, &ps);
        } break;

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            switch (id) {
                case ID_BTN_AETHER:
                    UpdateStatus(hWnd, "STATUS: INCINERATING SYSTEM JUNK...");
                    ShellExecute(NULL, "open", "cleanmgr.exe", "/d C:", NULL, SW_SHOWNORMAL);
                    system("start cmd /c \"title SkelerSecurity Engine && color 0b && echo [!] SCRUBBING SYSTEM CACHE... && del /s /f /q %temp%\\*.* && echo [!] CLEANUP COMPLETE. && pause\"");
                    UpdateStatus(hWnd, "STATUS: AETHER SCRUB COMPLETE.");
                    break;

                case ID_BTN_KINETIC:
                    UpdateStatus(hWnd, "STATUS: ENGAGING KINETIC GRAPHICS OVERDRIVE...");
                    system("powercfg /setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c");
                    ShellExecute(NULL, "open", "ms-settings:display-advancedgraphics", NULL, NULL, SW_SHOWNORMAL);
                    UpdateStatus(hWnd, "STATUS: GRAPHICS PRIORITIZATION ACTIVE.");
                    break;

                case ID_BTN_FLUX:
                    UpdateStatus(hWnd, "STATUS: RE-ROUTING DNS PATHWAYS...");
                    system("ipconfig /flushdns");
                    UpdateStatus(hWnd, "STATUS: NETWORK FLUX OPTIMIZED.");
                    break;

                case ID_BTN_CORESYNC:
                    UpdateStatus(hWnd, "STATUS: VALIDATING CORE SYSTEM INTEGRITY...");
                    ShellExecute(NULL, "runas", "cmd.exe", "/k title SkelerSecurity Sentinel && sfc /scannow", NULL, SW_SHOWNORMAL);
                    UpdateStatus(hWnd, "STATUS: CORE SCAN INITIATED IN SEPARATE TERMINAL.");
                    break;
            }
        } break;

        case WM_CTLCOLORBTN: return (LRESULT)CreateSolidBrush(clrBack);
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
