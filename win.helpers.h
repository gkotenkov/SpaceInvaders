void InitLevel_1();



void WinInit() {
	InitObject(&Player, ((rct.right-rct.left))/2-64, PlayerPositionY, player, -1000);
	if (EndlessModeIndicator) {
        Player.levelStatus = 6;
	} else {
        InitLevel_1();
	}
}

typedef struct RedrawBackgroundThreadParams{
        HDC memDC;
        HDC hdcSrc;
    } TParams, *PTParams;

DWORD WINAPI WorkThread(LPVOID lpvoid){
    PTParams params = (PTParams)lpvoid;
    return BitBlt(params->memDC, 0, 0, 1280, 720, params->hdcSrc, 0, 0, SRCCOPY);
}

void WinMove(){
    PlayerControl();
    ObjectMove(&Player);
    if (EndlessModeIndicator){
        CreateRandomEnemy();
    }
    for(int i=0; i < ObjectArrayCounter; i++) ObjectMove(ObjectArray+i);
    DeleteArrayObject();
}

void WinShow(HDC dc, HBRUSH* Abrush, HBITMAP* PBM){
    HDC hdcSrc = CreateCompatibleDC(dc);
    HDC memDC = CreateCompatibleDC(dc);

    HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right-rct.left, rct.bottom-rct.top);
    switch (Player.levelStatus) {
    case 4:
        SelectObject(hdcSrc, BossBM);
        break;
    case 1:
        SelectObject(hdcSrc, Lvl_1_BM);
        break;
    default:
        SelectObject(hdcSrc, BM);
        break;
    }
    SelectObject(memDC, memBM);



    TParams param = {memDC, hdcSrc};
    PTParams pparam = &param;
    LPVOID lpvoid = (LPVOID)pparam;
    HANDLE thread = CreateThread(NULL, 0, WorkThread, lpvoid, 0, NULL);



    /*HDC memDC = CreateCompatibleDC(dc);
    HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right-rct.left, rct.bottom-rct.top);
    SelectObject(memDC, memBM);
    FillRect(memDC, &rct, CreatePatternBrush(BM));*/


    HDC LevelDC = CreateCompatibleDC(dc);
    HBITMAP LevelBM;
    switch(lvl_DrawAbility){
    case 1:
        LevelBM = (HBITMAP)LoadImage(NULL, TEXT("level_1.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(LevelDC, LevelBM);
        break;
    case 2:
        LevelBM = (HBITMAP)LoadImage(NULL, TEXT("level_2.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(LevelDC, LevelBM);
        break;
    case 3:
        LevelBM = (HBITMAP)LoadImage(NULL, TEXT("level_3.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(LevelDC, LevelBM);
        break;
    case 4:
        LevelBM = (HBITMAP)LoadImage(NULL, TEXT("final_level.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(LevelDC, LevelBM);
        break;
    default:

        break;
    }


    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    if(OpeningIndicator){

        SelectObject(memDC, GetStockObject(DC_BRUSH));
        SetDCBrushColor(memDC, RGB(0, 0, 0));
        Rectangle(memDC, 430, 600, 850, 640);
        SetDCBrushColor(memDC, RGB(0, 255, 0));
        Rectangle(memDC, 435, 605, OpeningLoading, 635);
        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        HFONT hfont = SelectObject(memDC, GeneralFont);
        TextOut(memDC, 420, 235, "by GK DEVELOPMENT", 17);
        DeleteObject(hfont);
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, OpeningFont);
        TextOut(memDC, 100, 125, "SPACE INVADERS", 14);
    }

    if (ControlsIndicator){

        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, GeneralFont);
        TextOut(memDC, 100, 125, "A   D", 5);
        TextOut(memDC, 1000, 125, "MOVE", 4);
        TextOut(memDC, 100, 250, "SPACE", 5);
        TextOut(memDC, 100, 300, "LEFT BUTTON", 11);
        TextOut(memDC, 1000, 275, "SHOOT", 5);
        TextOut(memDC, 100, 400, "P", 1);
        TextOut(memDC, 100, 450, "ESCAPE", 6);
        TextOut(memDC, 1000, 425, "PAUSE", 5);
        TextOut(memDC, 400, 425, "----------------------------------------", 40);
        TextOut(memDC, 400, 275, "----------------------------------------", 40);
        TextOut(memDC, 400, 125, "----------------------------------------", 40);

    }

    if (GameIsOn){

        DrawObject(Player, memDC);

        for(int i=0; i < ObjectArrayCounter; i++) DrawObject(ObjectArray[i], memDC);
        DrawHUD(memDC);
        char ScoreIdString[20];
        sprintf(ScoreIdString, "SCORE: %d", Player.PlayerScore);
        SetTextColor(memDC, RGB(0, 0, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, ScoreFont);
        TextOut(memDC, 17, 6, ScoreIdString, strlen(ScoreIdString));
        for (int i = 1; i < (Player.lifesRested + 1); i++) {
            POINT points[10] = { {1271-i*48, 10}, {1275-i*48, 6}, {1279-i*48, 6}, {1283-i*48, 10}, {1287-i*48, 6}, {1291-i*48, 6}, {1295-i*48, 10}, {1295-i*48, 14}, {1283-i*48, 24}, {1271-i*48, 14} };
            SelectObject(memDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(memDC, RGB (255, 0, 0));
            Polygon(memDC, points, 10);
        }
    }

    BitBlt(dc, 0, 0, rct.right-rct.left, rct.bottom-rct.top, memDC, 0, 0, SRCCOPY);

    if (lvl_DrawAbility > 0) BitBlt(dc, 440, 200, 400, 144, LevelDC, 0, 0, SRCCOPY);
    if (YouWinIndicator){
        HDC YouWinDC = CreateCompatibleDC(dc);
        HBITMAP YouWinBM = (HBITMAP)LoadImage(NULL, TEXT("you_win.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(YouWinDC, YouWinBM);
        char YouWinString[30];
        sprintf(YouWinString, "YOUR SCORE: %d", Player.PlayerScore);
        SetTextColor(dc, RGB(0, 255, 0));
        SetBkMode(dc, TRANSPARENT);
        SelectObject(dc, GeneralFont);
        TextOut(dc, strlen(YouWinString)*10/2+400, 400, YouWinString, strlen(YouWinString));
        BitBlt(dc, 440, 200, 400, 144, YouWinDC, 0, 0, SRCCOPY);
        DeleteObject(YouWinBM);
        DeleteDC(YouWinDC);
    }

    if (YouLoseIndicator){
        HDC YouLoseDC = CreateCompatibleDC(dc);
        HBITMAP YouLoseBM = (HBITMAP)LoadImage(NULL, TEXT("you_lose.bmp"), IMAGE_BITMAP, 400, 144,  LR_LOADFROMFILE);
        SelectObject(YouLoseDC, YouLoseBM);
        char YouLoseString[30];
        sprintf(YouLoseString, "YOUR SCORE: %d", Player.PlayerScore);
        SetTextColor(dc, RGB(0, 255, 0));
        SetBkMode(dc, TRANSPARENT);
        SelectObject(dc, GeneralFont);
        TextOut(dc, strlen(YouLoseString)*10/2+400, 400, YouLoseString, strlen(YouLoseString));
        BitBlt(dc, 440, 200, 400, 144, YouLoseDC, 0, 0, SRCCOPY);
        DeleteObject(YouLoseBM);
        DeleteDC(YouLoseDC);
    }

    DeleteObject(hdcSrc);
    DeleteDC(LevelDC);
    DeleteObject(LevelBM);
    DeleteDC(memDC);
    DeleteObject(memBM);
}







