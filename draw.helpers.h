#pragma once

#include "global.indicators.h"
#include  "global.variables.h"


void LevelControl();

void DrawPlayerSpaceship (HDC hdc, AnyObject obj) {
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
}

void DrawPlayer (HDC hdc, AnyObject obj) {
    if (obj.animationController <= 0 ) {
            DrawPlayerSpaceship(hdc, obj);

        } else if (obj.animationController > 0 && obj.animationController < 64){

            Player.speed.x = 0;
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255, 255, 255));

            Ellipse(hdc, obj.position.x+obj.size.x/2-obj.animationController,  obj.position.y+obj.size.y/2-obj.animationController,
                    obj.position.x+obj.size.x/2+obj.animationController,  obj.position.y+obj.size.y/2+obj.animationController);
                    Player.animationController++;
                    printf("%d\n", obj.animationController);
            if (obj.animationController > 16){

                SetDCBrushColor(hdc, RGB(255, 255, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-obj.animationController+16,  obj.position.y+obj.size.y/2-obj.animationController+16,
                    obj.position.x+obj.size.x/2+obj.animationController-16,  obj.position.y+obj.size.y/2+obj.animationController-16);
                    Player.animationController++;
                    printf("%d\n", obj.animationController);

            }
            if (obj.animationController > 32) {

                SetDCBrushColor(hdc, RGB(255, 128, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-obj.animationController+32,  obj.position.y+obj.size.y/2-obj.animationController+32,
                    obj.position.x+obj.size.x/2+obj.animationController-32,  obj.position.y+obj.size.y/2+obj.animationController-32);
                    Player.animationController++;
                    printf("%d\n", obj.animationController);
            }
            if (obj.animationController > 48) {

                SetDCBrushColor(hdc, RGB(255, 0, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-obj.animationController+48,  obj.position.y+obj.size.y/2-obj.animationController+48,
                    obj.position.x+obj.size.x/2+obj.animationController-48,  obj.position.y+obj.size.y/2+obj.animationController-48);
                    Player.animationController++;
                    printf("%d\n", obj.animationController);
            }

        } else if (obj.animationController >= 64 && obj.animationController < 128) {

            Player.speed.x = 0;
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255, 255, 255));
            Ellipse(hdc, obj.position.x+obj.size.x/2-(128-obj.animationController),  obj.position.y+obj.size.y/2-(128-obj.animationController),
                    obj.position.x+obj.size.x/2+(128-obj.animationController),  obj.position.y+obj.size.y/2+(128-obj.animationController));
            Player.animationController++;

            if (obj.animationController > 80){

                SetDCBrushColor(hdc, RGB(255, 255, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-(128-obj.animationController-16),  obj.position.y+obj.size.y/2-(128-obj.animationController-16),
                    obj.position.x+obj.size.x/2+(128-obj.animationController-16),  obj.position.y+obj.size.y/2+(128-obj.animationController-16));
                    Player.animationController++;
                    printf("%d\n", obj.animationController);

            }
            if (obj.animationController > 96) {

                SetDCBrushColor(hdc, RGB(255, 128, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-(128-obj.animationController-32),  obj.position.y+obj.size.y/2-(128-obj.animationController-32),
                    obj.position.x+obj.size.x/2+(128-obj.animationController-32),  obj.position.y+obj.size.y/2+(128-obj.animationController-32));
                    Player.animationController++;
                    printf("%d\n", obj.animationController);
            }
            if (obj.animationController > 112) {

                SetDCBrushColor(hdc, RGB(255, 0, 0));

                Ellipse(hdc, obj.position.x+obj.size.x/2-(128-obj.animationController-48),  obj.position.y+obj.size.y/2-(128-obj.animationController-48),
                    obj.position.x+obj.size.x/2+(128-obj.animationController-48),  obj.position.y+obj.size.y/2+(128-obj.animationController-48));
                    Player.animationController++;
                    printf("%d\n", obj.animationController);
            }

            printf("%d\n", obj.animationController);

        } else if (obj.animationController >= 128 && obj.animationController < 512) {

            if(obj.animationController < 150) Player.position.x = 576;

            int blink = obj.animationController;
            if ((blink > 192 && blink < 224) ||
                (blink > 256 && blink < 288) ||
                (blink > 320 && blink < 352) ||
                (blink > 384 && blink < 416) ||
                (blink > 448 && blink < 480)){

                DrawPlayerSpaceship(hdc, obj);
            }
            Player.animationController++;

        } else if (obj.animationController >= 512){
            Player.animationController = 0;
            printf("%d\n", obj.animationController);
        }


}

void DrawMotherShip (HDC hdc, AnyObject obj) {
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
                Rectangle(hdc, 400, 5, 400+8*obj.lifesRested, 25);
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
}

void DrawSimpleInvader (HDC hdc, AnyObject obj) {
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
}

void DrawPlayerBullet (HDC hdc, AnyObject obj) {
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
}

void DrawSimpleInvaderBullet (HDC hdc, AnyObject obj) {
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, obj.color);

        Rectangle(hdc,	(int)obj.position.x, (int)obj.position.y,
            (int)(obj.position.x + obj.size.x), (int)(obj.position.y + obj.size.y));
}

void DrawLaserShooter (HDC hdc, AnyObject obj) {
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
}

void DrawLaserShooterBullet (HDC hdc, AnyObject obj) {
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
}

void DrawShieldInvader (HDC hdc, AnyObject obj) {
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
}



