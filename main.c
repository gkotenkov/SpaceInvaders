#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MenuButton_NewGame_id 101
#define MenuButton_Controls_id 102
#define MenuButton_Fullscreen_id 103
#define MenuButton_Sound_id 104
#define MenuButton_Exit_id 105

#define PauseButton_BackToGame_id 201
#define PauseButton_MainMenu_id 202

#define ControlsButton_MainMenu_id 301

#define YouWinButton_MainMenu_id 401
#define YouLoseButton_MainMenu_id 402

#define ScoreTextWindow_id 1001

#include <Windows.h>

#include "draw.helpers.h"







XYPosition GetObjectPosition(float x, float y){
    XYPosition point;
    point.x = x;
    point.y = y;
    return point;
}


const int PlayerPositionY = 600;





BOOL ObjectCollision(AnyObject bullet, AnyObject character){
    if (character.objectType == 2){
        return (((bullet.position.x+bullet.size.x) > character.position.x+24) && (bullet.position.x < (character.position.x+character.size.x-24)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y+8) && (bullet.position.y < (character.position.y+character.size.y-8)));
    } else {
        return (((bullet.position.x+bullet.size.x) > character.position.x) && (bullet.position.x < (character.position.x+character.size.x)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y) && (bullet.position.y < (character.position.y+character.size.y)));
    }
}

PAnyObject NewArrayObject(){
    ObjectArrayCounter++;
    ObjectArray = realloc(ObjectArray, sizeof(*ObjectArray)* ObjectArrayCounter);
    return ObjectArray + ObjectArrayCounter - 1;
}

void WinShow(HDC dc, HBRUSH* brush, HBITMAP* PBM);

void InitLevel_1();

void InitLevel_2();

void InitLevel_3();


void DeleteArrayObject(){
    int i = 0;
    while (i < ObjectArrayCounter){
        if(ObjectArray[i].shouldBeDeleted){
            ObjectArrayCounter--;
            ObjectArray[i] = ObjectArray[ObjectArrayCounter];
            ObjectArray = realloc(ObjectArray, sizeof(*ObjectArray)* ObjectArrayCounter);
        }
        else
            i++;
    }
}

void DeleteWholeArray(){
    ObjectArray = NULL;
    ObjectArrayCounter = 0;
}


void InitObject(AnyObject* obj, float x, float y, int objectType) {
	obj->position = GetObjectPosition(x, y);
	obj->speed = GetObjectPosition(0,0);
	obj->objectType = objectType;
	obj->shouldBeDeleted = FALSE;

	switch(objectType){
    case player:
        obj->levelStatus = 0;
        obj->color = PlayerColor;
        obj->size = GetObjectPosition(ps.width, ps.height);
        obj->PlayerScore = 0;
        obj->lifesRested = 20;
        obj->animationController = 0;
        break;
    case simpleInvader:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case laserShooter:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case simpleInvaderBullet:
        obj->basicSpeed = 6*Player.levelStatus;
        obj->color = EnemyBulletColor;
        obj->size = GetObjectPosition(pbs.width, pbs.height);
        break;
    case playerBullet:
        obj->basicSpeed = 16;
        obj->color = PlayerBulletColor;
        obj->size = GetObjectPosition(ebs.width, ebs.height);
        break;
    case laserShooterBullet:
        obj->color = EnemyBulletColor;
        obj->size = GetObjectPosition(32, 1);
        obj->objectDeliting = FALSE;
        obj->basicSpeed = 12;
        break;
    case shieldInvader:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 5;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case motherShip:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 30;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(416, 192);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = -1;
        break;
    default:
        //TODO: Error handling
        break;
	}
}

void AddBullet(float XPos, float YPos, int objectType){
    PAnyObject obj = NewArrayObject();
    InitObject(obj, XPos, YPos, objectType);
    obj->shootRange = 600;
}






void ObjectSetDestPoint(AnyObject* obj, float xPos, float yPos, float vecSpeed){
    XYPosition xyLen = GetObjectPosition(xPos - obj->position.x, yPos - obj->position.y);
    float destXY = sqrt(xyLen.x * xyLen.x + xyLen.y * xyLen.y);
    obj->speed.x = (float)(xyLen.x / destXY * vecSpeed);
    obj->speed.y = (float)(xyLen.y / destXY * vecSpeed);
    obj->vecSpeed = vecSpeed;
}


void InitLevel_1() {
    levelInitMoveStatus = FALSE;
    Player.levelStatus = 1;
    Player.position.x = 576;

    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x -= 256;
    }

    x = 1344;
    y = 192;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x += 256;
    }

    x = -192;
    y = 320;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x -= 256;
    }

    x = 1344;
    y = 448;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x += 256;
    }

    lvl_DrawAbility = 1;
    WinShow(dc, &brush, &BM);
    Sleep(3000);
    lvl_DrawAbility = 0;
}


void InitLevel_2() {

    levelInitMoveStatus = FALSE;
    Player.levelStatus = 2;
    Player.position.x = 576;
    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x -= 256;
    }

    x = 1344;
    y = 192;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x += 256;
    }

    x = -192;
    y = 320;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, laserShooter);
        x -= 256;
    }

    x = 1280;
    y = 448;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, shieldInvader);
        x += 128;
    }

        lvl_DrawAbility = 2;
        WinShow(dc, &brush, &BM);
        Sleep(3000);
        lvl_DrawAbility = 0;
}


void InitLevel_3() {

    levelInitMoveStatus = FALSE;
    Player.levelStatus = 3;
    Player.position.x = 576;

    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, laserShooter);
        x -= 256;
    }

    x = 1344;
    y = 148;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x += 256;
    }

    x = -128;
    y = 232;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, shieldInvader);
        x -= 128;
    }

    x = 1344;
    y = 316;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, laserShooter);
        x += 256;
    }

    x = -192;
    y = 400;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, simpleInvader);
        x -= 256;
    }

    x = 1280;
    y = 484;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, shieldInvader);
        x += 128;
    }

        lvl_DrawAbility = 3;
        WinShow(dc, &brush, &BM);
        Sleep(3000);
        lvl_DrawAbility = 0;
}

void InitLevel_4() {

    levelInitMoveStatus = FALSE;
    Player.levelStatus = 4;
    Player.position.x = 576;

    InitObject(NewArrayObject(), -544, 100, motherShip);

    lvl_DrawAbility = 4;
    WinShow(dc, &brush, &BM);
    Sleep(3000);
    lvl_DrawAbility = 0;
}

void WinInit() {
	InitObject(&Player, ((rct.right-rct.left))/2-64, PlayerPositionY, player);
	InitLevel_1();
}

void PlayerControl(){
    static float PlayerSpeed = 12;
    Player.speed.x = 0;
    Player.speed.y = 0;
    if (GetKeyState('A') < 0 && Player.position.x >= 4){
        Player.speed.x = -PlayerSpeed;
    }
    if (GetKeyState('D') < 0 && Player.position.x <= 1132){
        Player.speed.x = PlayerSpeed;
    }
}


void LevelControl(){

    switch(Player.levelStatus){
    case 0:
        GameIsOn = FALSE;
        YouLoseIndicator = TRUE;
        break;
    case 1:
        lvl_1_EnemyCount--;
        if (lvl_1_EnemyCount <= 0){
            DeleteWholeArray();
            WinShow(dc, &brush, &BM);
            InitLevel_2();
        }
        break;
    case 2:
        lvl_2_EnemyCount--;
        if (lvl_2_EnemyCount <= 0){
            DeleteWholeArray();
            WinShow(dc, &brush, &BM);
            InitLevel_3();
        }
        break;
    case 3:
        lvl_3_EnemyCount--;
        if (lvl_3_EnemyCount <= 0){
            DeleteWholeArray();
            WinShow(dc, &brush, &BM);
            InitLevel_4();
        }
        break;
    case 4:
            GameIsOn = FALSE;
            Player.levelStatus = 5;
            WinShow(dc, &brush, &BM);
            LevelControl();
        break;
    case 5:
            YouWinIndicator = TRUE;
        break;
    default:
        break;
    }
}

typedef struct ThreadParams{
        HDC memDC;
        HDC hdcSrc;
    } TParams, *PTParams;

DWORD WINAPI WorkThread(LPVOID lpvoid){
    PTParams params = (PTParams)lpvoid;
    return BitBlt(params->memDC, 0, 0, 1280, 720, params->hdcSrc, 0, 0, SRCCOPY);
}

void ObjectMove(AnyObject *obj){

    if(GameIsOn){
        if (obj->position.x < 0) {
            obj->initSide = 1;
        } else if (obj->position.x+obj->size.x > 1280) {
            obj->initSide = -1;
        }
        switch(obj->objectType){
        case player:
            if (obj->animationController <= 0 || obj->animationController >=128){
                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
            }
            break;
        case simpleInvader:
            if (obj->levelInitMoveStatus == FALSE){
                ObjectSetDestPoint(obj, obj->position.x+1*obj->initSide, obj->position.y, obj->basicSpeed);
                obj->levelInitMoveStatus = TRUE;
                obj->shootRange = 1344;
            } else {
                obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange <= 0){
                    obj->destController *= -1;
                    obj->animationController = obj->destController;
                    ObjectSetDestPoint(obj, obj->position.x+obj->destController*obj->initSide, obj->position.y, obj->basicSpeed/4);
                    obj->shootRange = 128;
                    levelInitMoveStatus = TRUE;
                }
            }
            if (obj->vecSpeed == obj->basicSpeed/4){
                int shootingIndicator = rand()%(1200/Player.levelStatus);
                if (!shootingIndicator){
                AddBullet((obj->position.x+obj->size.x/2-ebs.width/2), (obj->position.y), simpleInvaderBullet);
                }
            }
            obj->position.x+=obj->speed.x;
            obj->position.y+=obj->speed.y;
            break;
        case laserShooter:
            if (obj->levelInitMoveStatus == FALSE){
                ObjectSetDestPoint(obj, obj->position.x+obj->initSide, obj->position.y, obj->basicSpeed);
                obj->levelInitMoveStatus = TRUE;
                obj->shootRange = 1280;
            } else {
                obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange <= 0){
                        obj->speed.x =0;
                        obj->speed.y =0;
                    levelInitMoveStatus = TRUE;
                    int shootingIndicator = rand()%(9000/Player.levelStatus);
                    if (!shootingIndicator){
                        obj->animationController = -1;

                        obj->destController = 0;
                        AddBullet((obj->position.x+48), (obj->position.y+obj->size.y), laserShooterBullet);
                }
            }
            if (obj->destController >=0){
                    obj->destController++;
                    if (obj->destController >= 200){
                        obj->animationController = 1;
                        obj->destController = -1;
                    }
                }
            }
            obj->position.x+=obj->speed.x;
            obj->position.y+=obj->speed.y;
            break;
        case playerBullet:
            obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange < 0){
                    obj->shouldBeDeleted = TRUE;
                }
                ObjectSetDestPoint(obj, obj->position.x, obj->position.y-650, obj->basicSpeed);
                for (int i = 0; i < ObjectArrayCounter; i++){
                    if (ObjectCollision(*obj, ObjectArray[i]) && (ObjectArray[i].objectType == motherShip
                                                                 || ObjectArray[i].objectType == shieldInvader
                                                                 || ObjectArray[i].objectType == simpleInvader
                                                                 || ObjectArray[i].objectType == laserShooter)){
                        ObjectArray[i].lifesRested--;
                        obj->shouldBeDeleted = TRUE;
                        if(ObjectArray[i].lifesRested <= 0 && ObjectArray[i].objectType != motherShip){
                            ObjectArray[i].shouldBeDeleted = TRUE;
                            Player.PlayerScore += 100*Player.levelStatus;
                            if (Player.levelStatus < 4){
                                LevelControl();
                            }
                        }
                    }
                }
            obj->position.x+=obj->speed.x;
            obj->position.y+=obj->speed.y;
            break;
        case simpleInvaderBullet:
            obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange < 0){
                    obj->shouldBeDeleted = TRUE;
                }
                ObjectSetDestPoint(obj, obj->position.x, obj->position.y+650, obj->basicSpeed);

                if (ObjectCollision(*obj, Player) && Player.animationController <= 0 ) {
                    Player.lifesRested--;
                    Player.animationController = 1;
                    obj->shouldBeDeleted = TRUE;
                    if (Player.lifesRested <= 0) {
                        Player.levelStatus = 0;
                        LevelControl();
                    }
                }

                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
                break;
            case laserShooterBullet:
                if (obj->size.x <=0) obj->shouldBeDeleted = TRUE;

                if (!obj->objectDeliting) {
                    if (ObjectCollision(*obj, Player) && Player.animationController <= 0) {
                        Player.lifesRested--;
                        Player.animationController = 1;
                        obj->objectDeliting = TRUE;
                        if (Player.lifesRested <= 0) {
                            Player.levelStatus = 0;
                            LevelControl();
                        }
                    }
                }
                obj->size.y+=2;
                if (obj->size.y >= 600){
                    obj->size.x -= 0.2;
                    obj->position.x += 0.1;
                }

                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
                break;
            case shieldInvader:
                if (obj->levelInitMoveStatus == FALSE){
                    ObjectSetDestPoint(obj, obj->position.x+obj->initSide, obj->position.y, obj->basicSpeed);
                    obj->levelInitMoveStatus = TRUE;
                    obj->shootRange = 1280;
                } else {
                    obj->shootRange-=obj->vecSpeed;
                    if (obj->shootRange <= 0){
                        obj->speed.x =0;
                        obj->speed.y =0;
                        levelInitMoveStatus = TRUE;
                    }
                }
                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
                break;
            case motherShip:
                if (obj->lifesRested > 0){
                    if (obj->animationController < 0){

                        if (obj->levelInitMoveStatus == FALSE){
                            ObjectSetDestPoint(obj, 800, 100, obj->basicSpeed);
                            obj->levelInitMoveStatus = TRUE;
                            obj->shootRange = 1344;
                        } else {
                            obj->shootRange-=obj->vecSpeed;
                            if (obj->shootRange <= 0){
                                obj->destController *= -1;
                                ObjectSetDestPoint(obj, obj->position.x+obj->destController, obj->position.y, obj->basicSpeed/4);
                                obj->shootRange = 736;
                                levelInitMoveStatus = TRUE;
                            }
                        }

                        if (obj->vecSpeed == obj->basicSpeed/4){
                            int shootingIndicator = rand()%(3000);
                                switch(shootingIndicator){
                                case 0:
                                case 1:
                                    AddBullet((obj->position.x+112), (obj->position.y+160), simpleInvaderBullet);
                                    break;
                                case 2:
                                case 3:
                                    AddBullet((obj->position.x+192), (obj->position.y+160), simpleInvaderBullet);
                                    break;
                                case 4:
                                case 5:
                                    AddBullet((obj->position.x+272), (obj->position.y+160), simpleInvaderBullet);
                                    break;
                                case 6:
                                    obj->animationController = 1;
                                    obj->speed.x = 0;
                                    AddBullet((obj->position.x+48), (obj->position.y+208), laserShooterBullet);
                                    AddBullet((obj->position.x+336), (obj->position.y+208), laserShooterBullet);
                                    break;
                                case 7:
                                    InitObject(NewArrayObject(), -192-(rand()%5*256), 350+rand()%2*128, 2*(rand()%2+1));
                                    break;
                                case 8:
                                    InitObject(NewArrayObject(), 1344+(rand()%5*256), 350+rand()%2*128, 2*(rand()%2+1));
                                    break;
                                default:

                                    break;
                                }
                            }

                    }
                    if (obj->animationController > 0) {
                        obj->speed.x = 0;
                        obj->animationController++;
                        if (obj->animationController > 500){
                            obj->speed.x = obj->vecSpeed*obj->destController;
                            obj->animationController = -1;
                        }
                    }
                }
                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
                break;
            }

        }

}

void WinMove(){
    PlayerControl();
    ObjectMove(&Player);
    for(int i=0; i < ObjectArrayCounter; i++) ObjectMove(ObjectArray+i);
    DeleteArrayObject();
}

void DrawObject(AnyObject obj, HDC hdc) {

    //BOOL (*shape)(HDC, int, int, int, int);

    switch (obj.objectType){
    case motherShip:

        DrawMotherShip(hdc, obj);

        break;
    case player:

        DrawPlayer(hdc, obj);

        break;
    case simpleInvader:

        DrawSimpleInvader(hdc, obj);

        break;
    case playerBullet:

        DrawPlayerBullet(hdc, obj);

        break;
    case simpleInvaderBullet:

        DrawSimpleInvaderBullet(hdc, obj);

        break;
    case laserShooter:

        DrawLaserShooter(hdc, obj);

        break;
    case laserShooterBullet:

        DrawLaserShooterBullet(hdc, obj);

        break;
    case shieldInvader:

        DrawShieldInvader(hdc, obj);

        break;
    default:
        break;
    }

}


void WinShow(HDC dc, HBRUSH* Abrush, HBITMAP* PBM){
    HDC hdcSrc = CreateCompatibleDC(dc);
    HDC memDC = CreateCompatibleDC(dc);

    HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right-rct.left, rct.bottom-rct.top);
    SelectObject(hdcSrc, *PBM);
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

        char ScoreIdString[20];
        sprintf(ScoreIdString, "SCORE: %d", Player.PlayerScore);
        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, ScoreFont);
        TextOut(memDC, 20, 20, ScoreIdString, strlen(ScoreIdString));
        for (int i = 1; i < (Player.lifesRested + 1); i++) {
            POINT points[10] = { {1231-i*32, 30}, {1235-i*32, 26}, {1239-i*32, 26}, {1243-i*32, 30}, {1247-i*32, 26}, {1251-i*32, 26}, {1255-i*32, 30}, {1255-i*32, 34}, {1243-i*32, 44}, {1231-i*32, 34} };
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

LRESULT WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int main() {


    BM = (HBITMAP)LoadImage(NULL, TEXT("background.bmp"), IMAGE_BITMAP, 0, 0,  LR_LOADFROMFILE);
    brush = CreatePatternBrush(BM);
    GeneralFont = CreateFont(40, 20, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);
    ScoreFont = CreateFont(30, 15, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);
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
                    WinShow(dc, &brush, &BM);
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
                        AddBullet(Player.position.x+Player.size.x/2-8, Player.position.y-16, 1);
            }
        }
        if (wParam == 2) {
            MouseShootingIndicator = TRUE;
        }
        if (wParam == 3) {
            if (GameIsOn){
                WinMove();
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
        case MenuButton_NewGame_id:
            NewGame();
            break;
        case MenuButton_Controls_id:
            DestroyWindow(MenuButton_NewGame);
            DestroyWindow(MenuButton_Controls);
            DestroyWindow(MenuButton_Fullscreen);
            DestroyWindow(MenuButton_Sound);
            DestroyWindow(MenuButton_Exit);
            ControlsIndicator = TRUE;
            break;
        case MenuButton_Fullscreen_id:
            OnOffFullScreen();
            break;
        case MenuButton_Sound_id:
            OnOffSound();
            break;
        case MenuButton_Exit_id:
            PostQuitMessage(0);

        case PauseButton_BackToGame_id:
            BackToGame();
            break;
        case PauseButton_MainMenu_id:
             MainMenuIndicator = TRUE;
             DestroyWindow(PauseButton_BackToGame);
             DestroyWindow(PauseButton_MainMenu);
             break;

        case ControlsButton_MainMenu_id:
             MainMenuIndicator = TRUE;
             DestroyWindow(ControlsButton_MainMenu);
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
                    AddBullet(Player.position.x+Player.size.x/2-8, Player.position.y-16, 1);
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
