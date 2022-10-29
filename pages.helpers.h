#pragma once

#include "constants.h"


void NewGame(){
        MouseShootingIndicator = FALSE;
        EndlessModeIndicator = FALSE;
        DeleteWholeArray();
        lvl_1_EnemyCount = 20;
        lvl_2_EnemyCount = 25;
        lvl_3_EnemyCount = 40;
        WinInit();
        GameIsOn = TRUE;
        HUDInitIndicator = TRUE;
        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_EndlessMode);
        DestroyWindow(MenuButton_SettingsHelp);
        DestroyWindow(MenuButton_Exit);
        WinShow(dc, &brush, &BM);
}

void BackToGame(){
    GameIsOn = TRUE;
    DestroyWindow(PauseButton_BackToGame);
    DestroyWindow(PauseButton_MainMenu);
}

void OnOffFullScreen(){
    DestroyWindow(SettingsHelpButton_Controls);
    DestroyWindow(SettingsHelpButton_Help);
    DestroyWindow(SettingsHelpButton_Almanac);
    DestroyWindow(SettingsHelpButton_Fullscreen);
    DestroyWindow(SettingsHelpButton_Sound);
    DestroyWindow(SettingsHelpButton_Difficulty);
    DestroyWindow(SettingsHelpButton_Back);;
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
            DestroyWindow(SettingsHelpButton_Controls);
            DestroyWindow(SettingsHelpButton_Help);
            DestroyWindow(SettingsHelpButton_Almanac);
            DestroyWindow(SettingsHelpButton_Fullscreen);
            DestroyWindow(SettingsHelpButton_Sound);
            DestroyWindow(SettingsHelpButton_Difficulty);
            DestroyWindow(SettingsHelpButton_Back);
        SettingsHelpIndicator = TRUE;
    } else {
        ChangeDisplaySettings(0, 0);
        SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOP, 360, 180, 1280, 720, SWP_SHOWWINDOW);
        FullScreen = FALSE;
        strcpy(FullScreenButtonName, "Enable fullscreen");
            DestroyWindow(SettingsHelpButton_Controls);
            DestroyWindow(SettingsHelpButton_Help);
            DestroyWindow(SettingsHelpButton_Almanac);
            DestroyWindow(SettingsHelpButton_Fullscreen);
            DestroyWindow(SettingsHelpButton_Sound);
            DestroyWindow(SettingsHelpButton_Difficulty);
            DestroyWindow(SettingsHelpButton_Back);
        SettingsHelpIndicator = TRUE;
    }
}

void OnOffSound() {
        DestroyWindow(SettingsHelpButton_Controls);
        DestroyWindow(SettingsHelpButton_Help);
        DestroyWindow(SettingsHelpButton_Almanac);
        DestroyWindow(SettingsHelpButton_Fullscreen);
        DestroyWindow(SettingsHelpButton_Sound);
        DestroyWindow(SettingsHelpButton_Difficulty);
        DestroyWindow(SettingsHelpButton_Back);

    if (SoundIndicator){
        strcpy(SoundButtonName, "Enable sound");
        PlaySound(NULL, NULL, 0);
        SoundIndicator = FALSE;
        SettingsHelpIndicator = TRUE;
    } else {
        strcpy(SoundButtonName, "Disable sound");
        PlaySound(TEXT("spaceinvaders.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        SoundIndicator = TRUE;
        SettingsHelpIndicator = TRUE;
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
        DestroyWindow(MenuButton_EndlessMode);
        DestroyWindow(MenuButton_SettingsHelp);
        DestroyWindow(MenuButton_Exit);
        DestroyWindow(SettingsHelpButton_Controls);
        DestroyWindow(SettingsHelpButton_Help);
        DestroyWindow(SettingsHelpButton_Almanac);
        DestroyWindow(SettingsHelpButton_Fullscreen);
        DestroyWindow(SettingsHelpButton_Sound);
        DestroyWindow(SettingsHelpButton_Difficulty);
        DestroyWindow(SettingsHelpButton_Back);

        MenuButton_NewGame = CreateWindow("button", "Campaign", WS_VISIBLE | WS_CHILD,
                                               (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-100, 200, 40,
                                               hwnd, (HMENU)MenuButton_NewGame_id, NULL,  NULL);

        MenuButton_EndlessMode = CreateWindow("button", "Endless mode", WS_VISIBLE | WS_CHILD,
                                                  (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-50, 200, 40,
                                                  hwnd, (HMENU)MenuButton_EndlessMode_id, NULL,  NULL);

        MenuButton_SettingsHelp = CreateWindow("button", "Settings | Help", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2, 200, 40,
                                            hwnd, (HMENU)MenuButton_SettingsHelp_id, NULL,  NULL);

        MenuButton_Exit = CreateWindow("button", "Exit", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+50, 200, 40,
                                            hwnd, (HMENU)MenuButton_Exit_id, NULL,  NULL);
        MainMenuIndicator = FALSE;
    }
}

void Controls(RECT* rct){

        if (ControlsIndicator) {

        WinShow(dc, &brush, &BM);

        ControlsButton_Back = CreateWindow("button", "Back", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+250, 200, 40,
                                            hwnd, (HMENU)ControlsButton_Back_id, NULL,  NULL);
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

void EndlessMode (){
    if (SoundIndicator){
        PlaySound(TEXT("endless_mode_sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    ObjectArray = NULL;
    ObjectArrayCounter = 0;
    GameIsOn = TRUE;
    HUDInitIndicator = TRUE;
    EndlessModeIndicator = TRUE;
    WinInit();
    DestroyWindow(MenuButton_NewGame);
    DestroyWindow(MenuButton_EndlessMode);
    DestroyWindow(MenuButton_SettingsHelp);
    DestroyWindow(MenuButton_Exit);
    WinShow(dc, &brush, &BM);
}

void SettingsHelp(RECT* rct) {
    if (SettingsHelpIndicator){
        WinShow(dc, &brush, &BM);

        DestroyWindow(MenuButton_NewGame);
        DestroyWindow(MenuButton_EndlessMode);
        DestroyWindow(MenuButton_SettingsHelp);
        DestroyWindow(MenuButton_Exit);

        SettingsHelpButton_Controls = CreateWindow("button", "Controls", WS_VISIBLE | WS_CHILD,
                                               (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-150, 200, 40,
                                               hwnd, (HMENU)SettingsHelpButton_Controls_id, NULL,  NULL);

        SettingsHelpButton_Help = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD,
                                                  (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-100, 200, 40,
                                                  hwnd, (HMENU)SettingsHelpButton_Help_id, NULL,  NULL);

        SettingsHelpButton_Almanac = CreateWindow("button", "Almanac", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2-50, 200, 40,
                                            hwnd, (HMENU)SettingsHelpButton_Almanac_id, NULL,  NULL);

        SettingsHelpButton_Fullscreen = CreateWindow("button", FullScreenButtonName, WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2, 200, 40,
                                            hwnd, (HMENU)SettingsHelpButton_Fullscreen_id, NULL,  NULL);

        SettingsHelpButton_Sound = CreateWindow("button", SoundButtonName, WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+50, 200, 40,
                                            hwnd, (HMENU)SettingsHelpButton_Sound_id, NULL,  NULL);

        SettingsHelpButton_Difficulty = CreateWindow("button", DifficultyButtonName, WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+100, 200, 40,
                                            hwnd, (HMENU)SettingsHelpButton_Difficulty_id, NULL,  NULL);

        SettingsHelpButton_Back = CreateWindow("button", "Back", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+150, 200, 40,
                                            hwnd, (HMENU)SettingsHelpButton_Back_id, NULL,  NULL);
        SettingsHelpIndicator = FALSE;
    }
}

void SetDifficulty(){
        DestroyWindow(SettingsHelpButton_Controls);
        DestroyWindow(SettingsHelpButton_Help);
        DestroyWindow(SettingsHelpButton_Almanac);
        DestroyWindow(SettingsHelpButton_Fullscreen);
        DestroyWindow(SettingsHelpButton_Sound);
        DestroyWindow(SettingsHelpButton_Difficulty);
        DestroyWindow(SettingsHelpButton_Back);

    if (Difficulty == 1){
        strcpy(DifficultyButtonName, "Make enemies easier");
        SettingsHelpIndicator = TRUE;
        Difficulty = 2;
    } else if (Difficulty == 2){
        strcpy(DifficultyButtonName, "Make enemies stronger");
        SettingsHelpIndicator = TRUE;
        Difficulty = 1;
    } else {
        //TODO: Error handling
    }

}

void Help(RECT* rct) {

    if (HelpIndicator) {
            DestroyWindow(SettingsHelpButton_Controls);
            DestroyWindow(SettingsHelpButton_Help);
            DestroyWindow(SettingsHelpButton_Almanac);
            DestroyWindow(SettingsHelpButton_Fullscreen);
            DestroyWindow(SettingsHelpButton_Sound);
            DestroyWindow(SettingsHelpButton_Difficulty);
            DestroyWindow(SettingsHelpButton_Back);

        WinShow(dc, &brush, &BM);

        HelpButton_Back = CreateWindow("button", "Back", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+250, 200, 40,
                                            hwnd, (HMENU)HelpButton_Back_id, NULL,  NULL);
        HelpIndicator = FALSE;

        }
}

void Almanac(RECT* rct) {

    if (AlmanacIndicator) {

            DestroyWindow(SettingsHelpButton_Controls);
            DestroyWindow(SettingsHelpButton_Help);
            DestroyWindow(SettingsHelpButton_Almanac);
            DestroyWindow(SettingsHelpButton_Fullscreen);
            DestroyWindow(SettingsHelpButton_Sound);
            DestroyWindow(SettingsHelpButton_Difficulty);
            DestroyWindow(SettingsHelpButton_Back);

        WinShow(dc, &brush, &BM);

        AlmanacButton_Back = CreateWindow("button", "Back", WS_VISIBLE | WS_CHILD,
                                            (rct->right-rct->left)/2-100, (rct->bottom-rct->top)/2+250, 200, 40,
                                            hwnd, (HMENU)AlmanacButton_Back_id, NULL,  NULL);
        AlmanacIndicator = FALSE;

        }
}








