#pragma once

#include "constants.h"


void NewGame(){
        ObjectArray = NULL;
        ObjectArrayCounter = 0;
        lvl_1_EnemyCount = 20;
        lvl_2_EnemyCount = 25;
        lvl_3_EnemyCount = 40;
        WinInit();
        GameIsOn = TRUE;
        HUDInitIndicator = TRUE;
        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_Controls);
        DestroyWindow(MenuButton_Sound);
        DestroyWindow(MenuButton_Fullscreen);
        DestroyWindow(MenuButton_Exit);
        WinShow(dc, &brush, &BM);
}

void BackToGame(){
    GameIsOn = TRUE;
    DestroyWindow(PauseButton_BackToGame);
    DestroyWindow(PauseButton_MainMenu);
}

void OnOffFullScreen(){
    if (!FullScreen){
        DEVMODE dm;
        memset(&dm, 0 ,sizeof(DEVMODE));
        dm.dmSize=sizeof(DEVMODE);
        dm.dmPelsWidth=1280;
        dm.dmPelsHeight=720;
        dm.dmFields=DM_PELSWIDTH|DM_PELSHEIGHT;
        ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

        SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 1280, 720, SWP_SHOWWINDOW);
        FullScreen = TRUE;
        strcpy(FullScreenButtonName, "Disable fullscreen");
        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_Controls);
        DestroyWindow(MenuButton_Fullscreen);
        DestroyWindow(MenuButton_Sound);
        DestroyWindow(MenuButton_Exit);
        MainMenuIndicator = TRUE;
    } else {
        ChangeDisplaySettings(0, 0);
        SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOP, 360, 180, 1280, 720, SWP_SHOWWINDOW);
        FullScreen = FALSE;
        strcpy(FullScreenButtonName, "Enable fullscreen");
        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_Controls);
        DestroyWindow(MenuButton_Fullscreen);
        DestroyWindow(MenuButton_Sound);
        DestroyWindow(MenuButton_Exit);
        MainMenuIndicator = TRUE;
    }
}

void OnOffSound() {
    if (SoundIndicator){
        strcpy(SoundButtonName, "Enable sound");
        PlaySound(NULL, NULL, 0);
        SoundIndicator = FALSE;
        MainMenuIndicator = TRUE;
    } else {
        strcpy(SoundButtonName, "Disable sound");
        PlaySound(TEXT("spaceinvaders.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        SoundIndicator = TRUE;
        MainMenuIndicator = TRUE;
    }
}

void PauseMenu(){

            if (GameIsOn){
                GameIsOn = FALSE;
                WinShow(dc, &brush, &BM);
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(255, 255, 255));

                Rectangle(dc, (rct.right-rct.left)/2-60, (rct.bottom-rct.top)/2-50,
                 (rct.right-rct.left)/2-20, (rct.bottom-rct.top)/2+50);
                Rectangle(dc, (rct.right-rct.left)/2+20, (rct.bottom-rct.top)/2-50,
                 (rct.right-rct.left)/2+60, (rct.bottom-rct.top)/2+50);

                PauseButton_BackToGame = CreateWindow("button", "Back To Game", WS_VISIBLE | WS_CHILD,
                                                           (rct.right-rct.left)/2-60, (rct.bottom-rct.top)/2-100, 120, 40,
                                                           hwnd, (HMENU)PauseButton_BackToGame_id, NULL,  NULL);

                PauseButton_MainMenu = CreateWindow("button", "Main Menu", WS_VISIBLE | WS_CHILD,
                                                           (rct.right-rct.left)/2-60, (rct.bottom-rct.top)/2+60, 120, 40,
                                                           hwnd, (HMENU)PauseButton_MainMenu_id, NULL,  NULL);
            }
}



void MainMenu(RECT* rct) {
    if (MainMenuIndicator){
        WinShow(dc, &brush, &BM);

        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_Controls);
        DestroyWindow(MenuButton_Fullscreen);
        DestroyWindow(MenuButton_Sound);
        DestroyWindow(MenuButton_Exit);

        MenuButton_NewGame = CreateWindow("button", "New Game", WS_VISIBLE | WS_CHILD,
                                               (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-100, 200, 40,
                                               hwnd, (HMENU)MenuButton_NewGame_id, NULL,  NULL);

        MenuButton_Controls = CreateWindow("button", "Controls", WS_VISIBLE | WS_CHILD,
                                                  (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-50, 200, 40,
                                                  hwnd, (HMENU)MenuButton_Controls_id, NULL,  NULL);

        MenuButton_Fullscreen = CreateWindow("button", FullScreenButtonName, WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2, 200, 40,
                                            hwnd, (HMENU)MenuButton_Fullscreen_id, NULL,  NULL);

        MenuButton_Sound = CreateWindow("button", SoundButtonName, WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+50, 200, 40,
                                            hwnd, (HMENU)MenuButton_Sound_id, NULL,  NULL);

        MenuButton_Exit = CreateWindow("button", "Exit", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+100, 200, 40,
                                            hwnd, (HMENU)MenuButton_Exit_id, NULL,  NULL);
        MainMenuIndicator = FALSE;
    }
}

void Controls(RECT* rct){
        if (ControlsIndicator) {


        WinShow(dc, &brush, &BM);

        ControlsButton_MainMenu = CreateWindow("button", "Main menu", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+200, 200, 40,
                                            hwnd, (HMENU)ControlsButton_MainMenu_id, NULL,  NULL);
        ControlsIndicator = FALSE;

        }
}

void Opening(){
    if (OpeningIndicator){
        WinShow(dc, &brush, &BM);
        Sleep(1);
        OpeningLoading += 4;
        if (OpeningLoading >= 845) {
                OpeningIndicator = FALSE;
                MainMenuIndicator = TRUE;
                Sleep(500);
        }
    }
}

void YouWin(RECT* rct){
    if(YouWinIndicator){
            WinShow(dc, &brush, &BM);
            YouWinButton_MainMenu = CreateWindow("button", "Main menu", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+200, 200, 40,
                                            hwnd, (HMENU)YouWinButton_MainMenu_id, NULL,  NULL);
    YouWinIndicator = FALSE;
    }

}

void YouLose(RECT* rct){
    if(YouLoseIndicator){
            WinShow(dc, &brush, &BM);
            YouLoseButton_MainMenu = CreateWindow("button", "Main menu", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+200, 200, 40,
                                            hwnd, (HMENU)YouLoseButton_MainMenu_id, NULL,  NULL);
    YouLoseIndicator = FALSE;
    }

}

