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
    case 1:
        SelectObject(hdcSrc, Lvl_1_BM);
        break;
    case 2:
        SelectObject(hdcSrc, Lvl_2_BM);
        break;
    case 3:
        SelectObject(hdcSrc, Lvl_3_BM);
        break;
    case 4:
        SelectObject(hdcSrc, BossBM);
        break;
    default:
        if (EndlessModeIndicator) {
            SelectObject(hdcSrc, EndlessModeBM);
        } else {
            SelectObject(hdcSrc, BM);
        }
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
        SetTextAlign(memDC, TA_CENTER);
        HFONT hfont = SelectObject(memDC, GeneralFont);
        TextOut(memDC, 640, 235, "by GK DEVELOPMENT", 17);
        DeleteObject(hfont);
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, OpeningFont);
        SetTextAlign(memDC, TA_CENTER);
        TextOut(memDC, 640, 125, "SPACE INVADERS", 14);
    }

    if (ControlsIndicator){

        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, GeneralFont);
        TextOut(memDC, 100, 125, "A   D", 5);
        TextOut(memDC, 1000, 125, "MOVE", 4);
        TextOut(memDC, 100, 250, "SPACE", 5);
        TextOut(memDC, 100, 375, "LEFT BUTTON", 11);
        TextOut(memDC, 1000, 375, "SINGLE SHOT", 11);
        TextOut(memDC, 1000, 225, "AUTO-", 5);
        TextOut(memDC, 1000, 275, "SHOOTING", 8);
        TextOut(memDC, 100, 475, "P", 1);
        TextOut(memDC, 100, 525, "ESCAPE", 6);
        TextOut(memDC, 1000, 500, "PAUSE", 5);
        TextOut(memDC, 400, 500, "----------------------------------------", 40);
        TextOut(memDC, 400, 375, "----------------------------------------", 40);
        TextOut(memDC, 400, 250, "----------------------------------------", 40);
        TextOut(memDC, 400, 125, "----------------------------------------", 40);

    }

    if (AlmanacIndicator){
        AnyObject SimpleInvader;
        AnyObject LaserShooter;
        AnyObject ShieldInvader;
        AnyObject MotherShip;
        InitObject(&SimpleInvader, 166, 20, simpleInvader, 0);
        InitObject(&LaserShooter, 166, 124, laserShooter, 0);
        InitObject(&ShieldInvader, 166, 208, shieldInvader, 0);
        InitObject(&MotherShip, 20, 272, motherShip, 0);

        DrawObject(SimpleInvader, memDC);
        DrawObject(LaserShooter, memDC);
        DrawObject(ShieldInvader, memDC);
        DrawObject(MotherShip, memDC);

        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, AlmanacFont);
        TextOut(memDC, 480, 30, "Simple Invader", 14);
        TextOut(memDC, 480, 124, "Laser Shooter", 13);
        TextOut(memDC, 480, 220, "Shield Invader", 14);
        TextOut(memDC, 480, 350, "MOTHERSHIP", 10);
        TextOut(memDC, 700, 30, "1 life. Shoots a regular bullet", 31);
        TextOut(memDC, 700, 124, "1 life. Shoots a laser ray", 26);
        TextOut(memDC, 700, 220, "5 lifes. Don't shoot", 20);
        TextOut(memDC, 700, 350, "60 lifes. Uses both types of bullets", 36);

        POINT points[10] = {
        {194+8, 520},
        {194+16, 520},
        {194+24, 520+8},
        {194+32, 520},
        {194+40, 520},
        {194+48, 520+8},
        {194+48, 520+16},
        {194+24, 520+40},
        {194, 520+16},
        {194, 520+8}
    };
    SelectObject(memDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDC, RGB (255, 0, 0));
    Polygon(memDC, points, 10);
    TextOut(memDC, 480, 518, "Life Heart", 10);
    TextOut(memDC, 700, 504, "Catch it to restore one health point", 37);
    TextOut(memDC, 700, 530, "You could not have more than 3 HP", 34);
    }

    if (HelpIndicator){

        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, HelpFont);
        SetTextAlign(memDC, TA_CENTER);
        TextOut(memDC, 640, 50, "In Campaign mode defeat all enemies to pass the level.", 54);
        TextOut(memDC, 640, 150, "In Endless mode survive as long as you can.", 44);
        TextOut(memDC, 640, 250, "Button 'Make enemies stronger' doubles enemies' HP, shootig rate and bullets speed.", 83);
        TextOut(memDC, 640, 300, "Also Life Hearts will spawn twice less often.", 45);
        SelectObject(memDC, GeneralFont);
        TextOut(memDC, 640, 450, "Avoid bullets! Survive! Save the galaxy!", 40);
        TextOut(memDC, 640, 500, "GOOD LUCK, ADVENTURER!", 22);
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
        SetTextAlign(dc, TA_CENTER);
        TextOut(dc, 640, 400, YouWinString, strlen(YouWinString));
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
        SetTextAlign(dc, TA_CENTER);
        TextOut(dc, 640, 400, YouLoseString, strlen(YouLoseString));
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







