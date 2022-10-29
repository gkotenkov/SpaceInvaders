
XYPosition GetObjectPosition(float x, float y){
    XYPosition point;
    point.x = x;
    point.y = y;
    return point;
}

EMType GetPositionType(float x, float y, int id){
    EMType position;
    position.x = x;
    position.y = y;
    position.id = id;
    return position;
}

void InitObject(AnyObject* obj, float x, float y, int objectType, int id) {
	obj->position = GetObjectPosition(x, y);
	obj->speed = GetObjectPosition(0,0);
	obj->objectType = objectType;
	obj->shouldBeDeleted = FALSE;
    obj->id = id;

	switch(objectType){
    case player:
        obj->levelStatus = 0;
        obj->color = PlayerColor;
        obj->size = GetObjectPosition(ps.width, ps.height);
        obj->PlayerScore = 0;
        obj->lifesRested = 3;
        obj->animationController = 0;
        break;
    case simpleInvader:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1*Difficulty;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case laserShooter:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 1*Difficulty;
        obj->color = EnemyColor;
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case simpleInvaderBullet:
        obj->basicSpeed = 10*Difficulty;
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
        obj->id = id;
        break;
    case shieldInvader:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 5*Difficulty;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(es.width, es.height);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = 1;
        break;
    case motherShip:
        obj->levelInitMoveStatus = FALSE;
        obj->lifesRested = 60*Difficulty;
        obj->color = RGB(200, 200, 200);
        obj->size = GetObjectPosition(416, 192);
        obj->basicSpeed = 8;
        obj->destController = 1;
        obj->animationController = -1;
        break;
    case lifeHeart:
        obj->color = RGB(255, 0, 0);
        obj->size = GetObjectPosition(32, 32);
        obj->basicSpeed = 8;
        obj->levelInitMoveStatus = FALSE;
        break;
    default:
        //TODO: Error handling
        break;
	}
}

BOOL ObjectCollision(AnyObject bullet, AnyObject character){
    switch (character.objectType){
    case player:
        return (((bullet.position.x+bullet.size.x) > character.position.x) && (bullet.position.x < (character.position.x+character.size.x)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y+32) && (bullet.position.y < (character.position.y+character.size.y)));
        break;
    case simpleInvader:
        return (((bullet.position.x+bullet.size.x) > character.position.x+24) && (bullet.position.x < (character.position.x+character.size.x-24)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y+8) && (bullet.position.y < (character.position.y+character.size.y-8)));
        break;
    case laserShooter:
        return (((bullet.position.x+bullet.size.x) > character.position.x+24) && (bullet.position.x < (character.position.x+character.size.x-24)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y+8) && (bullet.position.y < (character.position.y+character.size.y-8)));
        break;
    case shieldInvader:
        return (((bullet.position.x+bullet.size.x) > character.position.x) && (bullet.position.x < (character.position.x+character.size.x)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y+16) && (bullet.position.y < (character.position.y+character.size.y-16)));
        break;
    case motherShip:
        return (((bullet.position.x+bullet.size.x) > character.position.x) && (bullet.position.x < (character.position.x+character.size.x)) &&
            ((bullet.position.y+bullet.size.y) > character.position.y) && (bullet.position.y < (character.position.y+character.size.y-96)));
        break;
    default:
        return FALSE;
        break;
    }
}

void ObjectSetDestPoint(AnyObject* obj, float xPos, float yPos, float vecSpeed){
    XYPosition xyLen = GetObjectPosition(xPos - obj->position.x, yPos - obj->position.y);
    float destXY = sqrt(xyLen.x * xyLen.x + xyLen.y * xyLen.y);
    obj->speed.x = (float)(xyLen.x / destXY * vecSpeed);
    obj->speed.y = (float)(xyLen.y / destXY * vecSpeed);
    obj->vecSpeed = vecSpeed;
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

void DrawObject(AnyObject obj, HDC hdc) {

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
    case lifeHeart:

        DrawLifeHeart(hdc, obj);

        break;
    default:
        break;
    }

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
                int shootingIndicator = rand()%(1200/Difficulty);
                if (EndlessModeIndicator) shootingIndicator/=4;
                if (!shootingIndicator){
                AddBullet((obj->position.x+obj->size.x/2-ebs.width/2), (obj->position.y), simpleInvaderBullet, ++GlobalID);
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
                    int shootingIndicator = rand()%(1800/Difficulty);
                if (EndlessModeIndicator) shootingIndicator/=4;
                    if (!shootingIndicator){
                        obj->animationController = -1;

                        obj->destController = 0;
                        AddBullet((obj->position.x+48), (obj->position.y+obj->size.y), laserShooterBullet, obj->id);
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
                int id = -1;
                for (int i = 0; i < ObjectArrayCounter; i++){
                    if (ObjectCollision(*obj, ObjectArray[i]) && (ObjectArray[i].objectType == motherShip
                                                                 || ObjectArray[i].objectType == shieldInvader
                                                                 || ObjectArray[i].objectType == simpleInvader
                                                                 || ObjectArray[i].objectType == laserShooter)){
                        ObjectArray[i].lifesRested--;
                        obj->shouldBeDeleted = TRUE;
                        if(ObjectArray[i].lifesRested <= 0 && ObjectArray[i].objectType != motherShip){
                            ObjectArray[i].shouldBeDeleted = TRUE;
                            if (EndlessModeIndicator){
                                Player.PlayerScore += 200;
                                DeletePositionArrayObject(ObjectArray[i].id);
                            } else {
                            Player.PlayerScore += 100*Player.levelStatus;
                            }
                            id = ObjectArray[i].id;
                            if (rand()%(20*Difficulty) == 0){
                                AddBullet(ObjectArray[i].position.x+ObjectArray[i].size.x/2-12, ObjectArray[i].position.y, lifeHeart, ++GlobalID);
                            }
                            if (Player.levelStatus < 4){
                                LevelControl();
                            }
                        }
                    }
                }
                for (int i = 0; i < ObjectArrayCounter; i++){
                    if (ObjectArray[i].id == id) {
                        ObjectArray[i].shouldBeDeleted = TRUE;
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
                    if (ObjectCollision(*obj, Player) && Player.animationController <= 0) {
                        Player.lifesRested--;
                        Player.animationController = 1;
                        obj->objectDeliting = TRUE;
                        if (Player.lifesRested <= 0) {
                            Player.levelStatus = 0;
                            LevelControl();
                        }
                    }
                obj->size.y+=8*Difficulty;
                if (obj->size.y >= 600){
                    obj->size.x -= 0.8;
                    obj->position.x += 0.4;
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
            printf("%d\n", obj->animationController);
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
                            int shootingIndicator = rand()%(480/Difficulty);

                                switch(shootingIndicator){
                                case 0:
                                case 1:
                                    AddBullet((obj->position.x+112), (obj->position.y+160), simpleInvaderBullet, ++GlobalID);
                                    break;
                                case 2:
                                case 3:
                                    AddBullet((obj->position.x+192), (obj->position.y+160), simpleInvaderBullet, ++GlobalID);
                                    break;
                                case 4:
                                case 5:
                                    AddBullet((obj->position.x+272), (obj->position.y+160), simpleInvaderBullet, ++GlobalID);
                                    break;
                                case 6:
                                    obj->animationController = 1;
                                    obj->speed.x = 0;
                                    AddBullet((obj->position.x+48), (obj->position.y+208), laserShooterBullet, obj->id);
                                    AddBullet((obj->position.x+336), (obj->position.y+208), laserShooterBullet, obj->id);
                                    break;
                                case 7:
                                    InitObject(NewArrayObject(), -192-(rand()%5*256), 350+rand()%2*128, 2*(rand()%2+1), ++GlobalID);
                                    break;
                                case 8:
                                    InitObject(NewArrayObject(), 1344+(rand()%5*256), 350+rand()%2*128, 2*(rand()%2+1), ++GlobalID);
                                    break;
                                default:

                                    break;
                                }
                            }

                    }
                    if (obj->animationController > 0) {
                        obj->speed.x = 0;
                        obj->animationController++;
                        if (obj->animationController > 200){
                            obj->speed.x = obj->vecSpeed*obj->destController;
                            obj->animationController = -1;
                        }
                    }
                }
                obj->position.x+=obj->speed.x;
                obj->position.y+=obj->speed.y;
                break;
        case lifeHeart:
            if (obj->levelInitMoveStatus == FALSE){
                    ObjectSetDestPoint(obj, obj->position.x, obj->position.y+1, obj->basicSpeed);
                    obj->levelInitMoveStatus = TRUE;
                    obj->shootRange = (Player.position.y+Player.size.y/2)-obj->position.y;
            } else {
                obj->shootRange-=obj->vecSpeed;
                if (obj->shootRange <= 0){
                    obj->speed.x =0;
                    obj->speed.y =0;
                    levelInitMoveStatus = TRUE;
                }
            }
            if (ObjectCollision(*obj, Player)){
                if (Player.lifesRested < 3){
                    Player.lifesRested++;
                }
                obj->shouldBeDeleted = TRUE;
            }
            obj->position.y += obj->speed.y;
            break;
            }

        }

}

void CreateRandomEnemy(){
    float x, y;
    BOOL PositionIsOccupied = FALSE;
    int random = rand()%(120/Difficulty);
    switch (random){
    case 1: ;
        x = -192-(rand()%3*192);
        y = 64+(rand()%5+1)*84;
        for (int i = 0; i < PositionArrayCounter; i++){
            if(PositionArray[i].x == x && PositionArray[i].y == y){
                PositionIsOccupied = TRUE;
            }
        }
        if (!PositionIsOccupied){
            InitObject(NewArrayObject(), x, y, 2*(rand()%3+1), ++GlobalID);
            NewPositionArrayObject(x, y, GlobalID);
        }
        break;
    case 2: ;
        x = 1344+(rand()%3*192);
        y = 64+(rand()%5+1)*84;
        PositionIsOccupied = FALSE;
        for (int i = 0; i < PositionArrayCounter; i++){
            if(PositionArray[i].x == x && PositionArray[i].y == y){
                PositionIsOccupied = TRUE;
            }
        }
        if (!PositionIsOccupied){
            InitObject(NewArrayObject(), x, y, 2*(rand()%3+1), ++GlobalID);
            NewPositionArrayObject(x, y, GlobalID);

        }
        break;
    default:

        break;
    }
}











