#pragma once
#include <windows.h>
#include "custom.types.h"

char FullScreenButtonName[20] = "Enable fullscreen";
char SoundButtonName[20] = "Disable sound";


COLORREF PlayerColor = RGB(0, 255, 0);
COLORREF EnemyColor = RGB(255, 0, 0);
COLORREF PlayerBulletColor = RGB(0, 255, 255);
COLORREF EnemyBulletColor = RGB(255, 255, 255);

PAnyObject ObjectArray = NULL;


int ObjectArrayCounter = 0;;
int lvl_1_EnemyCount = 20;
int lvl_2_EnemyCount = 25;
int lvl_3_EnemyCount = 40;
int lvl_DrawAbility = 0;
int BossDeathBOOM = 0;
int OpeningLoading = 435;


AnyObject Player;

RECT rct;

ObjType type;

const PS ps = {128, 64};
const ES es = {128, 64};
const PBS pbs = {25, 25};
const EBS ebs = {20, 40};

HWND hwnd;
HWND MenuButton_NewGame;
HWND MenuButton_Controls;
HWND MenuButton_Fullscreen;
HWND MenuButton_Sound;
HWND MenuButton_Exit;
HWND PauseButton_BackToGame;
HWND PauseButton_MainMenu;
HWND ScoreTextWindow;
HWND ControlsButton_MainMenu;
HWND YouWinButton_MainMenu;
HWND YouLoseButton_MainMenu;
HDC dc;
HANDLE hBitmap01;
HBITMAP BM;
HBRUSH brush;

HFONT ScoreFont = NULL;
HFONT GeneralFont = NULL;
HFONT OpeningFont = NULL;