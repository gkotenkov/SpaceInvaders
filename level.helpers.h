
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


