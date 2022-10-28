

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "draw.helpers.h"

#include "constants.h"

#include "array.helpers.h"

#include "object.helpers.h"

#include "win.helpers.h"

#include "level.helpers.h"

#include "pages.helpers.h"

LRESULT WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int main() {


    BM = (HBITMAP)LoadImage(NULL, TEXT("background.bmp"), IMAGE_BITMAP, 0, 0,  LR_LOADFROMFILE);
    BossBM = (HBITMAP)LoadImage(NULL, TEXT("background_1.bmp"), IMAGE_BITMAP, 0, 0,  LR_LOADFROMFILE);
    Lvl_1_BM = (HBITMAP)LoadImage(NULL, TEXT("background_2.bmp"), IMAGE_BITMAP, 0, 0,  LR_LOADFROMFILE);
    brush = CreatePatternBrush(BM);
    GeneralFont = CreateFont(40, 20, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);
    ScoreFont = CreateFont(18, 9, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);
    OpeningFont = CreateFont(120, 60, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);

	WNDCLASSA wcl;
		memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.hbrBackground = brush;
		wcl.lpszClassName = "MyWindow";
		wcl.lpfnWndProc = WinProc;
		wcl.hCursor = LoadCursorA(NULL, IDC_CROSS);

	RegisterClassA(&wcl);

	hwnd = CreateWindow(
		"MyWindow",
		"SpaceInvaders",
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		360, 180, 1280, 720,
		NULL, NULL, NULL, NULL
	);



	ShowWindow(hwnd, SW_SHOWNORMAL);

    SoundIndicator = TRUE;
    OpeningIndicator = TRUE;

    PlaySound(TEXT("spaceinvaders.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    SetTimer(hwnd, 2, 250, NULL);
    SetTimer(hwnd, 3, 10, NULL);

	MSG msg;
	while (1) {
            dc = GetDC(hwnd);
            if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)){

                if(msg.message == WM_QUIT) break;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else {
                Opening();
                MainMenu(&rct);
                Controls(&rct);
                YouWin(&rct);
                YouLose(&rct);
                if (GameIsOn){
                }
            }
            ReleaseDC(hwnd, dc);
	}

	return 0;
}

LRESULT WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
    case WM_TIMER:
        if(wParam == 1) {
            if (GameIsOn && levelInitMoveStatus && Player.animationController <= 0){
                        AddBullet(Player.position.x+Player.size.x/2-8, Player.position.y-16, playerBullet, ++GlobalID);
            }
        }
        if (wParam == 2) {
            MouseShootingIndicator = TRUE;
        }
        if (wParam == 3) {
            if (GameIsOn){
                WinMove();
                    WinShow(dc, &brush, &BM);
                }
        }
        break;
    case WM_SYSCOMMAND:
        switch (wParam) {
        case SC_MAXIMIZE:
            OnOffFullScreen();
            break;
        default:
            return DefWindowProcA(hwnd, message, wParam, lParam);
            break;
        }
        break;
    case WM_SIZE:
    GetClientRect(hwnd, &rct);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch(wParam){
        case 'P':
        case VK_ESCAPE:
            if (GameIsOn){
                PauseMenu();
            }
            break;
        case VK_SPACE:
            if (ShootingIndicator){
                KillTimer(hwnd, 1);
                ShootingIndicator = FALSE;
            } else {
                SetTimer(hwnd, 1, 200, NULL);
                ShootingIndicator = TRUE;
            }
            break;
        default:
            break;
    }
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam)){
        //////////////////////
        case MenuButton_NewGame_id:
            NewGame();
            break;
        case MenuButton_EndlessMode_id:
            EndlessMode();
            break;
        case MenuButton_SettingsHelp_id:

            break;
        case MenuButton_Exit_id:
            PostQuitMessage(0);
            break;
        /////////////////////

        case SettingsHelpButton_Controls_id:
        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_EndlessMode);
        DestroyWindow(MenuButton_SettingsHelp);
        DestroyWindow(MenuButton_Exit);
            ControlsIndicator = TRUE;
            break;
        case SettingsHelpButton_Fullscreen_id:
            OnOffFullScreen();
            break;
        case SettingsHelpButton_Sound_id:
            OnOffSound();
            break;

        case PauseButton_BackToGame_id:
            BackToGame();
            break;
        case PauseButton_MainMenu_id:
             MainMenuIndicator = TRUE;
             DestroyWindow(PauseButton_BackToGame);
             DestroyWindow(PauseButton_MainMenu);
             break;

        case ControlsButton_Back_id:
             MainMenuIndicator = TRUE;
             DestroyWindow(ControlsButton_Back);
             break;
        case YouWinButton_MainMenu_id:
             MainMenuIndicator = TRUE;
             DestroyWindow(YouWinButton_MainMenu);
             break;
        case YouLoseButton_MainMenu_id:
            MainMenuIndicator = TRUE;
            DestroyWindow(YouLoseButton_MainMenu);
            break;
        default:

            break;
        }
        break;
    case WM_LBUTTONDOWN:
        if(GameIsOn){
            if (levelInitMoveStatus && !ShootingIndicator && MouseShootingIndicator && Player.animationController <= 0){
                    AddBullet(Player.position.x+Player.size.x/2-8, Player.position.y-16, playerBullet, ++GlobalID);
                    MouseShootingIndicator = FALSE;
            }
        }
        break;
    default:
        return DefWindowProcA(hwnd, message, wParam, lParam);
        break;
    }
    return 0;
}








