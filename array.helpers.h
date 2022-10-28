void InitObject(AnyObject*, float, float, int, int);
XYPosition GetObjectPosition(float, float);
EMType GetPositionType(float, float, int);

PAnyObject NewArrayObject(){
    ObjectArrayCounter++;
    ObjectArray = realloc(ObjectArray, sizeof(*ObjectArray)* ObjectArrayCounter);
    return ObjectArray + ObjectArrayCounter - 1;
}

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

void AddBullet(float XPos, float YPos, int objectType, int id){
    PAnyObject obj = NewArrayObject();
    InitObject(obj, XPos, YPos, objectType, id);
    obj->shootRange = 600;
}

void NewPositionArrayObject(float x, float y, int id){
    PositionArrayCounter++;
    PositionArray = realloc(PositionArray, sizeof(*PositionArray)* PositionArrayCounter);
    PositionArray[PositionArrayCounter - 1] = GetPositionType(x, y, id);
}

void DeletePositionArrayObject(int id){
    int i = 0;
    while (i < PositionArrayCounter){
        if(PositionArray[i].id == id){
            PositionArrayCounter--;
            PositionArray[i] = PositionArray[PositionArrayCounter];
            PositionArray = realloc(PositionArray, sizeof(*PositionArray)* PositionArrayCounter);
        }
        else
            i++;
    }
}




