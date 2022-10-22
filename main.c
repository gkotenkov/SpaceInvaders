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

typedef struct XYPositionOfAnyObject{
    float x;
    float y;
} XYPosition;


XYPosition GetObjectPosition(float x, float y){
    XYPosition point;
    point.x = x;
    point.y = y;
    return point;
}

typedef struct AnyObjectProperties {
    XYPosition position;
    XYPosition size;
    COLORREF color;
    int objectType;
    int lifesRested;
    int levelStatus;
    XYPosition speed;
    float vecSpeed;
    float basicSpeed;
    float shootRange;
    BOOL shouldBeDeleted;
    BOOL levelInitMoveStatus;
    int playerScore;
    int destController;
    int animationController;
    BOOL objectDeliting;
    int initSide;
} AnyObject, *PAnyObject;


typedef struct PlayerSize {
    float width;
    float height;
} PS;

typedef struct EnemySize {
    float width;
    float height;
} ES;

typedef struct PlayerBulletSize {
    float width;
    float height;
} PBS;

typedef const struct EnemyBulletSize {
    float width;
    float height;
} EBS;

const PS ps = {128, 64};
const ES es = {128, 64};
const PBS pbs = {25, 25};
const EBS ebs = {20, 40};

BOOL FullScreen = FALSE;
BOOL MainMenuIndicator = FALSE;
BOOL GameIsOn = FALSE;
BOOL levelInitMoveStatus = FALSE;
BOOL HUDInitIndicator = FALSE;
BOOL SoundIndicator = FALSE;
BOOL ControlsIndicator = FALSE;
BOOL OpeningIndicator = FALSE;
BOOL YouWinIndicator = FALSE;
BOOL YouLoseIndicator = FALSE;
BOOL ShootingIndicator = FALSE;
BOOL MouseShootingIndicator = FALSE;

char FullScreenButtonName[20] = "Enable fullscreen";
char SoundButtonName[20] = "Disable sound";

const int PlayerPositionY = 600;

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


AnyObject player;

RECT rct;


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
    case 0:
        obj->levelStatus = 0;
        obj->color = PlayerColor;
        obj->size = GetObjectPosition(ps.width, ps.height);
        obj->playerScore = 0;
        obj->lifesRested = 10;
        break;
    case 2:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 2;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case 4:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 2;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case 3:
        obj->basicSpeed = 1*player.levelStatus;
        obj->color = EnemyBulletColor;
        obj->size = GetObjectPosition(pbs.width, pbs.height);
        break;
    case 1:
        obj->basicSpeed = 4;
        obj->color = PlayerBulletColor;
        obj->size = GetObjectPosition(ebs.width, ebs.height);
        break;
    case 5:
        obj->color = EnemyBulletColor;
        obj->size = GetObjectPosition(32, 1);
        obj->objectDeliting = FALSE;
        break;
    case 6:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 5;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 2;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case 7:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 30;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(416, 192);
        obj->basicSpeed = 2;
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
    player.levelStatus = 1;
    player.position.x = 576;

    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x -= 256;
    }

    x = 1344;
    y = 192;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x += 256;
    }

    x = -192;
    y = 320;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x -= 256;
    }

    x = 1344;
    y = 448;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x += 256;
    }

    lvl_DrawAbility = 1;
    WinShow(dc, &brush, &BM);
    Sleep(3000);
    lvl_DrawAbility = 0;
}


void InitLevel_2() {

    levelInitMoveStatus = FALSE;
    player.levelStatus = 2;
    player.position.x = 576;
    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x -= 256;
    }

    x = 1344;
    y = 192;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x += 256;
    }

    x = -192;
    y = 320;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 4);
        x -= 256;
    }

    x = 1280;
    y = 448;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, 6);
        x += 128;
    }

        lvl_DrawAbility = 2;
        WinShow(dc, &brush, &BM);
        Sleep(3000);
        lvl_DrawAbility = 0;
}


void InitLevel_3() {

    levelInitMoveStatus = FALSE;
    player.levelStatus = 3;
    player.position.x = 576;

    int x = -192;
    int y = 64;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 4);
        x -= 256;
    }

    x = 1344;
    y = 148;

    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x += 256;
    }

    x = -128;
    y = 232;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, 6);
        x -= 128;
    }

    x = 1344;
    y = 316;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 4);
        x += 256;
    }

    x = -192;
    y = 400;
    for (int i = 0; i < 5; i++){
        InitObject(NewArrayObject(), x, y, 2);
        x -= 256;
    }

    x = 1280;
    y = 484;
    for (int i = 0; i < 10; i++){
        InitObject(NewArrayObject(), x, y, 6);
        x += 128;
    }

        lvl_DrawAbility = 3;
        WinShow(dc, &brush, &BM);
        Sleep(3000);
        lvl_DrawAbility = 0;
}

void InitLevel_4() {

    levelInitMoveStatus = FALSE;
    player.levelStatus = 4;
    player.position.x = 576;

    InitObject(NewArrayObject(), -544, 100, 7);

    lvl_DrawAbility = 4;
    WinShow(dc, &brush, &BM);
    Sleep(3000);
    lvl_DrawAbility = 0;
}

void WinInit() {
	InitObject(&player, ((rct.right-rct.left))/2-64, PlayerPositionY, 0);
	InitLevel_1();
}

void PlayerControl(){
    static float playerSpeed = 2;
    player.speed.x = 0;
    player.speed.y = 0;
    if (GetKeyState('A') < 0 && player.position.x >= 4){
        player.speed.x = -playerSpeed;
    }
    if (GetKeyState('D') < 0 && player.position.x <= 1132){
        player.speed.x = playerSpeed;
    }
}


void LevelControl(){

    switch(player.levelStatus){
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
            player.levelStatus = 5;
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
        case 0:
            break;
        case 2:
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
                int shootingIndicator = rand()%(9000/player.levelStatus);
                if (!shootingIndicator){
                AddBullet((obj->position.x+obj->size.x/2-ebs.width/2), (obj->position.y), 3);
                }
            }
            break;
        case 4:
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
                    int shootingIndicator = rand()%(9000/player.levelStatus);
                    if (!shootingIndicator){
                        obj->animationController = -1;

                        obj->destController = 0;
                        AddBullet((obj->position.x+48), (obj->position.y+obj->size.y), 5);
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
            break;
        case 1:
            obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange < 0){
                    obj->shouldBeDeleted = TRUE;
                }
                ObjectSetDestPoint(obj, obj->position.x, obj->position.y-650, obj->basicSpeed);
                for (int i = 0; i < ObjectArrayCounter; i++){
                    if (ObjectCollision(*obj, ObjectArray[i]) && (ObjectArray[i].objectType == 7 || ObjectArray[i].objectType == 6 || ObjectArray[i].objectType == 2 || ObjectArray[i].objectType == 4)){
                        ObjectArray[i].lifesRested--;
                        obj->shouldBeDeleted = TRUE;
                        if(ObjectArray[i].lifesRested <= 0 && ObjectArray[i].objectType != 7){
                            ObjectArray[i].shouldBeDeleted = TRUE;
                            player.playerScore += 100*player.levelStatus;
                            if (player.levelStatus < 4){
                                LevelControl();
                            }
                        }
                    }
                }
            break;
        case 3:
            obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange < 0){
                    obj->shouldBeDeleted = TRUE;
                    printf("%d\n", ObjectArrayCounter);
                }
                ObjectSetDestPoint(obj, obj->position.x, obj->position.y+650, obj->basicSpeed);

                if (ObjectCollision(*obj, player)) {
                    player.lifesRested--;
                    obj->shouldBeDeleted = TRUE;
                    if (player.lifesRested <= 0) {
                        player.levelStatus = 0;
                        LevelControl();
                    }
                }

            break;
            case 5:
                if (obj->size.x <=0) obj->shouldBeDeleted = TRUE;

                if (!obj->objectDeliting) {
                    if (ObjectCollision(*obj, player)) {
                        player.lifesRested--;
                        obj->objectDeliting = TRUE;
                        if (player.lifesRested <= 0) {
                            player.levelStatus = 0;
                            LevelControl();
                        }
                    }
                }
                obj->size.y+=2;
                if (obj->size.y >= 600){
                    obj->size.x -= 0.2;
                    obj->position.x += 0.1;
                }

            break;
            case 6:
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
                break;
            case 7:
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
                            printf("%f\n", obj->position.x);
                            int shootingIndicator = rand()%(3000);
                                switch(shootingIndicator){
                                case 0:
                                case 1:
                                    AddBullet((obj->position.x+112), (obj->position.y+160), 3);
                                    break;
                                case 2:
                                case 3:
                                    AddBullet((obj->position.x+192), (obj->position.y+160), 3);
                                    break;
                                case 4:
                                case 5:
                                    AddBullet((obj->position.x+272), (obj->position.y+160), 3);
                                    break;
                                case 6:
                                    obj->animationController = 1;
                                    obj->speed.x = 0;
                                    AddBullet((obj->position.x+48), (obj->position.y+208), 5);
                                    AddBullet((obj->position.x+336), (obj->position.y+208), 5);
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
                break;
        }

        obj->position.x+=obj->speed.x;
        obj->position.y+=obj->speed.y;
        }

}

void WinMove(){
    PlayerControl();
    ObjectMove(&player);
    for(int i=0; i < ObjectArrayCounter; i++) ObjectMove(ObjectArray+i);
    DeleteArrayObject();
}


void DrawObject(AnyObject obj, HDC hdc) {

    //BOOL (*shape)(HDC, int, int, int, int);

    switch (obj.objectType){
    case 7:

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(100, 100, 100));

            POINT MotherShip_BodyShape[20] = {
                {obj.position.x, obj.position.y+128},
                {obj.position.x+16, obj.position.y+112},
                {obj.position.x+400, obj.position.y+112},
                {obj.position.x+416, obj.position.y+128},
                {obj.position.x+416, obj.position.y+160},
                {obj.position.x+400, obj.position.y+176},
                {obj.position.x+320, obj.position.y+176},
                {obj.position.x+304, obj.position.y+160},
                {obj.position.x+272, obj.position.y+160},
                {obj.position.x+256, obj.position.y+176},
                {obj.position.x+240, obj.position.y+176},
                {obj.position.x+224, obj.position.y+160},
                {obj.position.x+192, obj.position.y+160},
                {obj.position.x+176, obj.position.y+176},
                {obj.position.x+160, obj.position.y+176},
                {obj.position.x+144, obj.position.y+160},
                {obj.position.x+112, obj.position.y+160},
                {obj.position.x+96, obj.position.y+176},
                {obj.position.x+16, obj.position.y+176},
                {obj.position.x, obj.position.y+160},
                };

            Polygon(hdc, MotherShip_BodyShape, 20);

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(200, 200, 200));

            POINT MotherShip_KokpitShape[18] = {
                {obj.position.x+64, obj.position.y+96},
                {obj.position.x+96, obj.position.y+64},
                {obj.position.x+320, obj.position.y+64},
                {obj.position.x+352, obj.position.y+96},
                {obj.position.x+352, obj.position.y+144},
                {obj.position.x+320, obj.position.y+144},
                {obj.position.x+304, obj.position.y+128},
                {obj.position.x+272, obj.position.y+128},
                {obj.position.x+256, obj.position.y+112},
                {obj.position.x+240, obj.position.y+112},
                {obj.position.x+224, obj.position.y+128},
                {obj.position.x+192, obj.position.y+128},
                {obj.position.x+176, obj.position.y+112},
                {obj.position.x+160, obj.position.y+112},
                {obj.position.x+144, obj.position.y+128},
                {obj.position.x+112, obj.position.y+128},
                {obj.position.x+96, obj.position.y+144},
                {obj.position.x+64, obj.position.y+144},
                };

            Polygon(hdc, MotherShip_KokpitShape, 18);

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(100, 100, 100));

            POINT MotherShip_BodyPartShape[12] = {
                {obj.position.x+144, obj.position.y+80},
                {obj.position.x+128, obj.position.y+64},
                {obj.position.x+112, obj.position.y+48},
                {obj.position.x+112, obj.position.y+32},
                {obj.position.x+128, obj.position.y+32},
                {obj.position.x+144, obj.position.y+48},
                {obj.position.x+272, obj.position.y+48},
                {obj.position.x+288, obj.position.y+32},
                {obj.position.x+304, obj.position.y+32},
                {obj.position.x+304, obj.position.y+48},
                {obj.position.x+288, obj.position.y+64},
                {obj.position.x+272, obj.position.y+80},
                };

            Polygon(hdc, MotherShip_BodyPartShape, 12);

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255, 0, 0));

            POINT MotherShip_LeftLaserGunShape[14] = {
                {obj.position.x+32, obj.position.y+112},
                {obj.position.x+48, obj.position.y+96},
                {obj.position.x+80, obj.position.y+96},
                {obj.position.x+96, obj.position.y+112},
                {obj.position.x+80, obj.position.y+128},
                {obj.position.x+80, obj.position.y+160},
                {obj.position.x+96, obj.position.y+176},
                {obj.position.x+80, obj.position.y+192},
                {obj.position.x+80, obj.position.y+208},
                {obj.position.x+48, obj.position.y+208},
                {obj.position.x+48, obj.position.y+192},
                {obj.position.x+32, obj.position.y+176},
                {obj.position.x+48, obj.position.y+160},
                {obj.position.x+48, obj.position.y+128},
            };
            POINT MotherShip_RightLaserGunShape[14];
            for (int i = 0; i < 14; i++){
                MotherShip_RightLaserGunShape[i] = MotherShip_LeftLaserGunShape[i];
                MotherShip_RightLaserGunShape[i].x += 288;
            }
            Polygon(hdc, MotherShip_RightLaserGunShape, 14);
            Polygon(hdc, MotherShip_LeftLaserGunShape, 14);

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(0, 0, 100));

            POINT MotherShip_LeftGunShape[16] = {

                {obj.position.x+160, obj.position.y+32},
                {obj.position.x+176, obj.position.y+16},
                {obj.position.x+176, obj.position.y+64},
                {obj.position.x+192, obj.position.y+80},
                {obj.position.x+176, obj.position.y+96},
                {obj.position.x+176, obj.position.y+128},
                {obj.position.x+192, obj.position.y+144},
                {obj.position.x+176, obj.position.y+160},
                {obj.position.x+176, obj.position.y+224},
                {obj.position.x+160, obj.position.y+208},
                {obj.position.x+160, obj.position.y+160},
                {obj.position.x+144, obj.position.y+144},
                {obj.position.x+160, obj.position.y+128},
                {obj.position.x+160, obj.position.y+96},
                {obj.position.x+144, obj.position.y+80},
                {obj.position.x+160, obj.position.y+64},
            };

            POINT MotherShip_RightGunShape[16];

            for (int i = 0; i < 16; i++){
                MotherShip_RightGunShape[i] = MotherShip_LeftGunShape[i];
                MotherShip_RightGunShape[i].x += 80;
            }
            MotherShip_RightGunShape[0].y -= 16;
            MotherShip_RightGunShape[1].y += 16;
            MotherShip_RightGunShape[8].y -= 16;
            MotherShip_RightGunShape[9].y += 16;

            Polygon(hdc, MotherShip_RightGunShape, 16);
            Polygon(hdc, MotherShip_LeftGunShape, 16);


            SelectObject(hdc, GetStockObject(DC_BRUSH));
            if (obj.lifesRested > 0) {
                SetDCBrushColor(hdc, RGB(0, 255, 0));
                Rectangle(hdc, 395, 0, 885, 30);
                SetDCBrushColor(hdc, RGB(255, 0, 0));
                Rectangle(hdc, 400, 5, 880, 25);
            }

            if (obj.lifesRested > 24){
               SetDCBrushColor(hdc, RGB(255, 0, 0));
            Rectangle(hdc, obj.position.x+16, obj.position.y+128, obj.position.x+32, obj.position.y+160);
            Rectangle(hdc, obj.position.x+384, obj.position.y+128, obj.position.x+400, obj.position.y+160);
            } else if (obj.lifesRested > 18){
               SetDCBrushColor(hdc, RGB(255, 128, 0));
            Rectangle(hdc, obj.position.x+16, obj.position.y+128, obj.position.x+32, obj.position.y+160);
            Rectangle(hdc, obj.position.x+384, obj.position.y+128, obj.position.x+400, obj.position.y+160);
            } else if (obj.lifesRested > 12){
               SetDCBrushColor(hdc, RGB(255, 255, 0));
            Rectangle(hdc, obj.position.x+16, obj.position.y+128, obj.position.x+32, obj.position.y+160);
            Rectangle(hdc, obj.position.x+384, obj.position.y+128, obj.position.x+400, obj.position.y+160);
            } else if (obj.lifesRested > 6){
               SetDCBrushColor(hdc, RGB(128, 255, 0));
            Rectangle(hdc, obj.position.x+16, obj.position.y+128, obj.position.x+32, obj.position.y+160);
            Rectangle(hdc, obj.position.x+384, obj.position.y+128, obj.position.x+400, obj.position.y+160);
            } else if (obj.lifesRested > 0){
               SetDCBrushColor(hdc, RGB(0, 255, 0));
            Rectangle(hdc, obj.position.x+16, obj.position.y+128, obj.position.x+32, obj.position.y+160);
            Rectangle(hdc, obj.position.x+384, obj.position.y+128, obj.position.x+400, obj.position.y+160);
            } else {
                if (BossDeathBOOM <=640){
                BossDeathBOOM++;
                SelectObject(hdc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(hdc, RGB(255, 0, 0));
                Ellipse(hdc, obj.position.x+208-BossDeathBOOM, obj.position.y+128-BossDeathBOOM, obj.position.x+obj.size.x-208+BossDeathBOOM, obj.position.y+obj.size.y-128+BossDeathBOOM);
                if (BossDeathBOOM > 40){
                    SetDCBrushColor(hdc, RGB(255, 128, 0));
                    Ellipse(hdc, obj.position.x+208-BossDeathBOOM+40, obj.position.y+128-BossDeathBOOM+40, obj.position.x+obj.size.x-208+BossDeathBOOM-40, obj.position.y+obj.size.y-128+BossDeathBOOM-40);

                    if (BossDeathBOOM > 80){
                    SetDCBrushColor(hdc, RGB(255, 255, 0));
                    Ellipse(hdc, obj.position.x+208-BossDeathBOOM+80, obj.position.y+128-BossDeathBOOM+80, obj.position.x+obj.size.x-208+BossDeathBOOM-80, obj.position.y+obj.size.y-128+BossDeathBOOM-80);

                        if (BossDeathBOOM > 120){
                        SetDCBrushColor(hdc, RGB(255, 255, 255));
                        Ellipse(hdc, obj.position.x+208-BossDeathBOOM+120, obj.position.y+128-BossDeathBOOM+120, obj.position.x+obj.size.x-208+BossDeathBOOM-120, obj.position.y+obj.size.y-128+BossDeathBOOM-120);
                        }
                    }
                }
                } else {
                    Sleep(1000);
                    LevelControl();
                }
            }
        break;
    case 0:
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, obj.color);

        POINT PlayerWingsShape[18] = {
            {obj.position.x, obj.position.y+40},
            {obj.position.x+8, obj.position.y+48},
            {obj.position.x+24, obj.position.y+40},
            {obj.position.x+32, obj.position.y+40},
            {obj.position.x+48, obj.position.y+32},
            {obj.position.x+80, obj.position.y+32},
            {obj.position.x+96, obj.position.y+40},
            {obj.position.x+104, obj.position.y+40},
            {obj.position.x+120, obj.position.y+48},
            {obj.position.x+128, obj.position.y+40},
            {obj.position.x+128, obj.position.y+48},
            {obj.position.x+120, obj.position.y+56},
            {obj.position.x+88, obj.position.y+56},
            {obj.position.x+72, obj.position.y+48},
            {obj.position.x+56, obj.position.y+48},
            {obj.position.x+40, obj.position.y+56},
            {obj.position.x+8, obj.position.y+56},
            {obj.position.x, obj.position.y+48},
            };
        Polygon(hdc, PlayerWingsShape, 18);
        DeleteObject(PlayerWingsShape);

        SetDCBrushColor(hdc, RGB(18, 240, 217));
        POINT PlayerBodyShape[15] = {
            {obj.position.x+56, obj.position.y},
            {obj.position.x+56, obj.position.y+16},
            {obj.position.x+64, obj.position.y+8},
            {obj.position.x+72, obj.position.y+16},
            {obj.position.x+72, obj.position.y},
            {obj.position.x+80, obj.position.y+8},
            {obj.position.x+80, obj.position.y+16},
            {obj.position.x+72, obj.position.y+32},
            {obj.position.x+72, obj.position.y+56},
            {obj.position.x+80, obj.position.y+64},
            {obj.position.x+48, obj.position.y+64},
            {obj.position.x+56, obj.position.y+56},
            {obj.position.x+56, obj.position.y+32},
            {obj.position.x+48, obj.position.y+16},
            {obj.position.x+48, obj.position.y+8},
            };
        Polygon(hdc, PlayerBodyShape, 15);

        POINT PlayerEngineShape_Left[4] = {
            {obj.position.x+32, obj.position.y+16},
            {obj.position.x+32, obj.position.y+64},
            {obj.position.x+24, obj.position.y+56},
            {obj.position.x+24, obj.position.y+24},
            };
        Polygon(hdc, PlayerEngineShape_Left, 4);

        POINT PlayerEngineShape_Right[4] = {
            {obj.position.x+96, obj.position.y+16},
            {obj.position.x+96, obj.position.y+64},
            {obj.position.x+104, obj.position.y+56},
            {obj.position.x+104, obj.position.y+24},
            };
        Polygon(hdc, PlayerEngineShape_Right, 4);


        break;
    case 2:

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, obj.color);

        if (obj.animationController >= 0){
            POINT EnemyShape[36] = {
                {obj.position.x+24, obj.position.y+32},
                {obj.position.x+32, obj.position.y+32},
                {obj.position.x+32, obj.position.y+24},
                {obj.position.x+40, obj.position.y+24},
                {obj.position.x+40, obj.position.y+16},
                {obj.position.x+48, obj.position.y+16},
                {obj.position.x+48, obj.position.y},
                {obj.position.x+56, obj.position.y},
                {obj.position.x+56, obj.position.y+16},
                {obj.position.x+72, obj.position.y+16},
                {obj.position.x+72, obj.position.y},
                {obj.position.x+80, obj.position.y},
                {obj.position.x+80, obj.position.y+16},
                {obj.position.x+88, obj.position.y+16},
                {obj.position.x+88, obj.position.y+24},
                {obj.position.x+96, obj.position.y+24},
                {obj.position.x+96, obj.position.y+32},
                {obj.position.x+104, obj.position.y+32},
                {obj.position.x+104, obj.position.y+56},
                {obj.position.x+96, obj.position.y+56},
                {obj.position.x+96, obj.position.y+40},
                {obj.position.x+88, obj.position.y+40},
                {obj.position.x+88, obj.position.y+64},
                {obj.position.x+72, obj.position.y+64},
                {obj.position.x+72, obj.position.y+56},
                {obj.position.x+80, obj.position.y+56},
                {obj.position.x+80, obj.position.y+48},
                {obj.position.x+48, obj.position.y+48},
                {obj.position.x+48, obj.position.y+56},
                {obj.position.x+56, obj.position.y+56},
                {obj.position.x+56, obj.position.y+64},
                {obj.position.x+40, obj.position.y+64},
                {obj.position.x+40, obj.position.y+40},
                {obj.position.x+32, obj.position.y+40},
                {obj.position.x+32, obj.position.y+56},
                {obj.position.x+24, obj.position.y+56},
                };

                Polygon(hdc, EnemyShape, 36);
        } else if (obj.animationController < 0){

            POINT EnemyShape[36] = {
            {obj.position.x+24, obj.position.y+32},
            {obj.position.x+24, obj.position.y+8},
            {obj.position.x+32, obj.position.y+8},
            {obj.position.x+32, obj.position.y+24},
            {obj.position.x+40, obj.position.y+24},
            {obj.position.x+40, obj.position.y+16},
            {obj.position.x+48, obj.position.y+16},
            {obj.position.x+48, obj.position.y},
            {obj.position.x+56, obj.position.y},
            {obj.position.x+56, obj.position.y+16},
            {obj.position.x+72, obj.position.y+16},
            {obj.position.x+72, obj.position.y},
            {obj.position.x+80, obj.position.y},
            {obj.position.x+80, obj.position.y+16},
            {obj.position.x+88, obj.position.y+16},
            {obj.position.x+88, obj.position.y+24},
            {obj.position.x+96, obj.position.y+24},
            {obj.position.x+96, obj.position.y+8},
            {obj.position.x+104, obj.position.y+8},
            {obj.position.x+104, obj.position.y+32},
            {obj.position.x+96, obj.position.y+32},
            {obj.position.x+96, obj.position.y+40},
            {obj.position.x+88, obj.position.y+40},
            {obj.position.x+88, obj.position.y+64},
            {obj.position.x+72, obj.position.y+64},
            {obj.position.x+72, obj.position.y+56},
            {obj.position.x+80, obj.position.y+56},
            {obj.position.x+80, obj.position.y+48},
            {obj.position.x+48, obj.position.y+48},
            {obj.position.x+48, obj.position.y+56},
            {obj.position.x+56, obj.position.y+56},
            {obj.position.x+56, obj.position.y+64},
            {obj.position.x+40, obj.position.y+64},
            {obj.position.x+40, obj.position.y+40},
            {obj.position.x+32, obj.position.y+40},
            {obj.position.x+32, obj.position.y+32},
            };

            Polygon(hdc, EnemyShape, 36);
        }
        SetDCBrushColor(hdc, RGB(0, 0, 0));
        Rectangle(hdc, obj.position.x+48, obj.position.y+24, obj.position.x+56, obj.position.y+40);
        Rectangle(hdc, obj.position.x+72, obj.position.y+24, obj.position.x+80, obj.position.y+40);


        break;
    case 1:
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, RGB(18, 240, 217));

        POINT PlayerBulletShape[6] = {
            {obj.position.x+8, obj.position.y},
            {obj.position.x+16, obj.position.y+16},
            {obj.position.x+16, obj.position.y+32},
            {obj.position.x+8, obj.position.y+24},
            {obj.position.x, obj.position.y+32},
            {obj.position.x, obj.position.y+16},
            };
        Polygon(hdc, PlayerBulletShape, 6);

        break;
    case 3:

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, obj.color);

        Rectangle(hdc,	(int)obj.position.x, (int)obj.position.y,
            (int)(obj.position.x + obj.size.x), (int)(obj.position.y + obj.size.y));

        break;
    case 4:
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, RGB(0, 0, 255));
        if (obj.animationController > 0) {
            POINT LaserShooterShape[32] = {
                {obj.position.x+24, obj.position.y},
                {obj.position.x+32, obj.position.y},
                {obj.position.x+32, obj.position.y+24},
                {obj.position.x+40, obj.position.y+24},
                {obj.position.x+40, obj.position.y+16},
                {obj.position.x+48, obj.position.y+16},
                {obj.position.x+48, obj.position.y+8},
                {obj.position.x+56, obj.position.y+8},
                {obj.position.x+56, obj.position.y},
                {obj.position.x+72, obj.position.y},
                {obj.position.x+72, obj.position.y+8},
                {obj.position.x+80, obj.position.y+8},
                {obj.position.x+80, obj.position.y+16},
                {obj.position.x+88, obj.position.y+16},
                {obj.position.x+88, obj.position.y+24},
                {obj.position.x+96, obj.position.y+24},
                {obj.position.x+96, obj.position.y},
                {obj.position.x+104, obj.position.y},
                {obj.position.x+104, obj.position.y+32},
                {obj.position.x+96, obj.position.y+32},
                {obj.position.x+96, obj.position.y+40},
                {obj.position.x+88, obj.position.y+40},
                {obj.position.x+88, obj.position.y+48},
                {obj.position.x+80, obj.position.y+48},
                {obj.position.x+80, obj.position.y+56},
                {obj.position.x+48, obj.position.y+56},
                {obj.position.x+48, obj.position.y+48},
                {obj.position.x+40, obj.position.y+48},
                {obj.position.x+40, obj.position.y+40},
                {obj.position.x+32, obj.position.y+40},
                {obj.position.x+32, obj.position.y+32},
                {obj.position.x+24, obj.position.y+32},
                };
            Polygon(hdc, LaserShooterShape, 32);
        } else if (obj.animationController < 0) {
            POINT LaserShooterShape[37] = {
                {obj.position.x+8, obj.position.y},
                {obj.position.x+16, obj.position.y},
                {obj.position.x+16, obj.position.y+24},
                {obj.position.x+40, obj.position.y+24},
                {obj.position.x+40, obj.position.y+16},
                {obj.position.x+48, obj.position.y+16},
                {obj.position.x+48, obj.position.y+8},
                {obj.position.x+56, obj.position.y+8},
                {obj.position.x+56, obj.position.y},
                {obj.position.x+72, obj.position.y},
                {obj.position.x+72, obj.position.y+8},
                {obj.position.x+80, obj.position.y+8},
                {obj.position.x+80, obj.position.y+16},
                {obj.position.x+88, obj.position.y+16},
                {obj.position.x+88, obj.position.y+24},
                {obj.position.x+112, obj.position.y+24},
                {obj.position.x+112, obj.position.y},
                {obj.position.x+120, obj.position.y},
                {obj.position.x+120, obj.position.y+32},
                {obj.position.x+96, obj.position.y+32},
                {obj.position.x+96, obj.position.y+40},
                {obj.position.x+88, obj.position.y+40},
                {obj.position.x+88, obj.position.y+48},
                {obj.position.x+72, obj.position.y+48},
                {obj.position.x+72, obj.position.y+56},
                {obj.position.x+80, obj.position.y+56},
                {obj.position.x+80, obj.position.y+64},
                {obj.position.x+48, obj.position.y+64},
                {obj.position.x+48, obj.position.y+56},
                {obj.position.x+56, obj.position.y+56},
                {obj.position.x+56, obj.position.y+48},
                {obj.position.x+48, obj.position.y+48},
                {obj.position.x+40, obj.position.y+48},
                {obj.position.x+40, obj.position.y+40},
                {obj.position.x+32, obj.position.y+40},
                {obj.position.x+32, obj.position.y+32},
                {obj.position.x+8, obj.position.y+32},
                };
            Polygon(hdc, LaserShooterShape, 37);
        }

        SelectObject(hdc, brush);
        SetDCBrushColor(hdc, RGB(0, 0, 0));
        Rectangle(hdc, obj.position.x+48, obj.position.y+24, obj.position.x+56, obj.position.y+40);
        Rectangle(hdc, obj.position.x+72, obj.position.y+24, obj.position.x+80, obj.position.y+40);

        break;
    case 5:
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, RGB(255, 0, 0));
        Rectangle(hdc, (int)obj.position.x, (int)obj.position.y, (int)(obj.position.x + obj.size.x), (int)(obj.position.y + obj.size.y));

        if ((int)(obj.position.x + obj.size.x - 5) >= 0) {
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255, 140, 0));
            Rectangle(hdc, (int)(obj.position.x+5), (int)obj.position.y, (int)(obj.position.x + obj.size.x - 5), (int)(obj.position.y + obj.size.y));
        }

        if ((int)(obj.position.x + obj.size.x - 10) >= 0) {
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, obj.color);
            Rectangle(hdc, (int)(obj.position.x+10), (int)obj.position.y, (int)(obj.position.x + obj.size.x - 10), (int)(obj.position.y + obj.size.y));
        }
        break;
    case 6:
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, obj.color);

             POINT LaserShooterShape[20] = {
                {obj.position.x, obj.position.y+24},
                {obj.position.x+24, obj.position.y+24},
                {obj.position.x+24, obj.position.y+16},
                {obj.position.x+48, obj.position.y+16},
                {obj.position.x+48, obj.position.y+8},
                {obj.position.x+80, obj.position.y+8},
                {obj.position.x+80, obj.position.y+16},
                {obj.position.x+104, obj.position.y+16},
                {obj.position.x+104, obj.position.y+24},
                {obj.position.x+128, obj.position.y+24},
                {obj.position.x+128, obj.position.y+40},
                {obj.position.x+104, obj.position.y+40},
                {obj.position.x+104, obj.position.y+48},
                {obj.position.x+80, obj.position.y+48},
                {obj.position.x+80, obj.position.y+56},
                {obj.position.x+48, obj.position.y+56},
                {obj.position.x+48, obj.position.y+48},
                {obj.position.x+24, obj.position.y+48},
                {obj.position.x+24, obj.position.y+40},
                {obj.position.x, obj.position.y+40},
                };
            Polygon(hdc, LaserShooterShape, 20);

            SelectObject(hdc, GetStockObject(DC_BRUSH));

            switch(obj.lifesRested){
            case 5:
                SetDCBrushColor(hdc, RGB(255, 0, 0));
                break;
            case 4:
                SetDCBrushColor(hdc, RGB(255, 128, 0));
                break;
            case 3:
                SetDCBrushColor(hdc, RGB(255, 255, 0));
                break;
            case 2:
                SetDCBrushColor(hdc, RGB(128, 255, 0));
                break;
            case 1:
                SetDCBrushColor(hdc, RGB(0, 255, 0));
                break;
            default:
                break;

            }
            Rectangle(hdc, obj.position.x+48, obj.position.y+24, obj.position.x+80, obj.position.y+40);

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

        DrawObject(player, memDC);

        for(int i=0; i < ObjectArrayCounter; i++) DrawObject(ObjectArray[i], memDC);

        char ScoreIdString[20];
        sprintf(ScoreIdString, "SCORE: %d", player.playerScore);
        SetTextColor(memDC, RGB(0, 255, 0));
        SetBkMode(memDC, TRANSPARENT);
        SelectObject(memDC, ScoreFont);
        TextOut(memDC, 20, 20, ScoreIdString, strlen(ScoreIdString));
        for (int i = 1; i < (player.lifesRested + 1); i++) {
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
        sprintf(YouWinString, "YOUR SCORE: %d", player.playerScore);
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
        sprintf(YouLoseString, "YOUR SCORE: %d", player.playerScore);
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
		WS_OVERLAPPEDWINDOW,
		360, 180, 1298, 767,
		NULL, NULL, NULL, NULL
	);



	ShowWindow(hwnd, SW_SHOWNORMAL);

    SoundIndicator = TRUE;
    OpeningIndicator = TRUE;

    PlaySound(TEXT("spaceinvaders.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    SetTimer(hwnd, 2, 250, NULL);
    SetTimer(hwnd, 3, 10, NULL);
    int counter = 0;

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
                    WinMove();
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
            if (GameIsOn && levelInitMoveStatus){
                        AddBullet(player.position.x+player.size.x/2-8, player.position.y-16, 1);
            }
        }
        if (wParam == 2) {
            MouseShootingIndicator = TRUE;
        }
        if (wParam == 3) {
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



        /*case ScoreTextWindow_id: ;

            char ScoreIdString[20];
            sprintf(ScoreIdString, "SCORE: %d", player.playerScore);

            if(HIWORD(lParam) == EN_UPDATE){
                SetWindowText(ScoreTextWindow, ScoreIdString);
            }
            break;*/
        default:

            break;
        }
        break;
    case WM_LBUTTONDOWN:
        if(GameIsOn){
            if (levelInitMoveStatus && !ShootingIndicator && MouseShootingIndicator){
                    //CreateThread(NULL, 0, AddBullet, (player.position.x+player.size.x/2-10, player.position.y-10, 1), 0, NULL );
                    AddBullet(player.position.x+player.size.x/2-8, player.position.y-16, 1);
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
