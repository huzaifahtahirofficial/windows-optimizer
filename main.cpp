#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlobj.h>
#include <stdio.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")

HINSTANCE hInst;
HFONT hF_Title, hF_Btn, hF_Log, hF_Score;
HWND hLog;
int optScore = 35; // Initial score

// --- DESIGN SYSTEM ---
COLORREF clrBack   = RGB(10, 10, 15);     
COLORREF clrBtn    = RGB(25, 25, 35);   
COLORREF clrCyan   = RGB(0, 210, 255);  
COLORREF clrWhite  = RGB(245, 245, 250); 

#define ID_SCRUB 701
#define ID_OVERDRIVE 702
#define ID_STEALTH 703
#define ID_SENTINEL 704

void Log(const char* m) {
    SendMessage(hLog, LB_ADDSTRING, 0, (LPARAM)m);
    SendMessage(hLog, WM_VSCROLL, SB_BOTTOM, 0);
}

void RunTool(const char* t, const char* c) {
    char cmd[1024];
    sprintf(cmd, "/c title X-INSPECT: %s && color 0b && echo [!] STARTING %s... && %s && echo. && echo [SUCCESS] FINISHED. && pause", t, t, c);
    ShellExecute(NULL, "open", "cmd.exe", cmd, NULL, SW_SHOWNORMAL);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            hF_Title = CreateFont(50,0,0,0,FW_BOLD,0,0,0,0,0,0,CLEARTYPE_QUALITY,0,"Segoe UI");
            hF_Btn   = CreateFont(20,0,0,0,FW_BOLD,0,0,0,0,0,0,CLEARTYPE_QUALITY,0,"Segoe UI");
            hF_Log   = CreateFont(15,0,0,0,0,0,0,0,0,0,0,CLEARTYPE_QUALITY,0,"Consolas");
            hF_Score = CreateFont(70,0,0,0,FW_BOLD,0,0,0,0,0,0,CLEARTYPE_QUALITY,0,"Segoe UI");

            CreateWindowEx(0, "BUTTON", "SYSTEM SCRUB", WS_VISIBLE|WS_CHILD|BS_OWNERDRAW, 50, 430, 430, 100, hWnd, (HMENU)ID_SCRUB, hInst, 0);
            CreateWindowEx(0, "BUTTON", "NEURAL OVERDRIVE", WS_VISIBLE|WS_CHILD|BS_OWNERDRAW, 500, 430, 430, 100, hWnd, (HMENU)ID_OVERDRIVE, hInst, 0);
            CreateWindowEx(0, "BUTTON", "AEGIS STEALTH", WS_VISIBLE|WS_CHILD|BS_OWNERDRAW, 50, 550, 430, 100, hWnd, (HMENU)ID_STEALTH, hInst, 0);
            CreateWindowEx(0, "BUTTON", "SENTINEL SCAN", WS_VISIBLE|WS_CHILD|BS_OWNERDRAW, 500, 550, 430, 100, hWnd, (HMENU)ID_SENTINEL, hInst, 0);

            hLog = CreateWindowEx(0, "LISTBOX", NULL, WS_VISIBLE|WS_CHILD|LBS_NOSEL|WS_VSCROLL, 430, 170, 500, 230, hWnd, NULL, hInst, 0);
            SendMessage(hLog, WM_SETFONT, (WPARAM)hF_Log, TRUE);
            Log(" [X-INSPECT] CORE ENGINE INITIALIZED.");
        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps; HDC hdc = BeginPaint(hWnd, &ps);
            RECT r; GetClientRect(hWnd, &r);
            SetBkMode(hdc, TRANSPARENT);
            HBRUSH bg = CreateSolidBrush(clrBack); FillRect(hdc, &r, bg); DeleteObject(bg);

            SelectObject(hdc, hF_Title); SetTextColor(hdc, clrWhite);
            TextOut(hdc, 50, 40, "X-INSPECT", 9);
            SetTextColor(hdc, clrCyan); SelectObject(hdc, hF_Log);
            TextOut(hdc, 55, 105, "ADVANCED SYSTEM DIAGNOSTICS & PERFORMANCE ENGINE", 48);

            // Circular Dashboard
            HPEN p = CreatePen(PS_SOLID, 15, clrCyan); SelectObject(hdc, p);
            Arc(hdc, 80, 170, 330, 420, 0, 0, 0, 0); DeleteObject(p);

            char s[10]; sprintf(s, "%d", optScore);
            SelectObject(hdc, hF_Score); SetTextColor(hdc, clrWhite);
            TextOut(hdc, 135, 235, s, strlen(s));
            SelectObject(hdc, hF_Log); SetTextColor(hdc, clrCyan);
            TextOut(hdc, 145, 320, "OPT-SCORE", 9);

            EndPaint(hWnd, &ps);
        } break;

        case WM_DRAWITEM: {
            LPDRAWITEMSTRUCT p = (LPDRAWITEMSTRUCT)lp;
            bool dn = p->itemState & ODS_SELECTED;
            HBRUSH b = CreateSolidBrush(dn ? clrCyan : clrBtn);
            FillRect(p->hDC, &p->rcItem, b); DeleteObject(b);
            HBRUSH br = CreateSolidBrush(clrCyan); FrameRect(p->hDC, &p->rcItem, br); DeleteObject(br);
            SetTextColor(p->hDC, dn ? clrBack : clrWhite);
            SelectObject(p->hDC, hF_Btn); SetBkMode(p->hDC, 1);
            char t[128]; GetWindowText(p->hwndItem, t, 128);
            DrawText(p->hDC, t, -1, &p->rcItem, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
            return TRUE;
        }

        case WM_CTLCOLORLISTBOX: {
            HDC hdc = (HDC)wp; SetTextColor(hdc, clrCyan); SetBkColor(hdc, RGB(20,20,30));
            return (LRESULT)CreateSolidBrush(RGB(20,20,30));
        }

        case WM_COMMAND: {
            int id = LOWORD(wp);
            if(id == ID_SCRUB) {
                Log(" [!] EXECUTING SYSTEM SCRUB...");
                ShellExecute(0, "open", "cleanmgr.exe", "/d C:", 0, 1);
                RunTool("SCRUB", "del /q /s %temp%\\*.* && del /q /s C:\\Windows\\Temp\\*.*");
                optScore += 15;
            }
            if(id == ID_OVERDRIVE) {
                Log(" [!] ENGAGING NEURAL OVERDRIVE...");
                system("powercfg /setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c");
                ShellExecute(0, "open", "ms-settings:display-advancedgraphics", 0, 0, 1);
                optScore += 10;
            }
            if(id == ID_STEALTH) {
                Log(" [!] SEVERING TELEMETRY UPLINKS...");
                RunTool("STEALTH", "sc stop DiagTrack && sc config DiagTrack start= disabled && ipconfig /flushdns");
                optScore += 20;
            }
            if(id == ID_SENTINEL) {
                Log(" [!] STARTING SENTINEL REPAIR SCAN...");
                RunTool("SENTINEL", "sfc /scannow");
                optScore += 20;
            }
            if(optScore > 100) optScore = 100;
            InvalidateRect(hWnd, 0, 1);
        } break;

        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR c, int s) {
    hInst = h;
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc; wc.hInstance = h; 
    wc.hIcon = LoadIcon(h, MAKEINTRESOURCE(IDI_APP_ICON));
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(0, IDC_ARROW); wc.lpszClassName = "XINSPECT";
    RegisterClassEx(&wc);
    CreateWindow("XINSPECT", "X-INSPECT // System Intelligence", WS_OVERLAPPEDWINDOW|WS_VISIBLE, 100, 100, 1030, 750, 0, 0, h, 0);
    MSG msg; while(GetMessage(&msg, 0, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
    return 0;
}