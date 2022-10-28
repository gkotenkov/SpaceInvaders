#pragma once


typedef struct XYPositionOfAnyObject{
    float x;
    float y;
} XYPosition;

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
    int PlayerScore;
    int destController;
    int animationController;
    BOOL objectDeliting;
    int initSide;
    int id;
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

typedef enum ObjectTypes {
    player = 0,
    playerBullet = 1,
    simpleInvader = 2,
    simpleInvaderBullet = 3,
    laserShooter = 4,
    laserShooterBullet = 5,
    shieldInvader = 6,
    motherShip = 7,
    lifeHeart = 8
} ObjType;

typedef struct EndlessModeType{
    float x;
    float y;
    int id;
} EMType, *PEMType;






