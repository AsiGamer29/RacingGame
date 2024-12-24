#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "LevelSetup.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

class PhysicEntity
{
protected:

    PhysicEntity(PhysBody* _body, Module* _listener)
        : body(_body)
        , listener(_listener)
    {
        body->listener = listener;
    }

public:
    virtual ~PhysicEntity() = default;
    virtual void Update() = 0;

    virtual int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal)
    {
        return 0;
    }

    CollisionType GetCollisionType() const { return collisionType; }
    PhysBody* body;

protected:

    Module* listener;
    CollisionType collisionType;
};

//------------------------------------------------------------------------------------ Snow Zone -------------------------------------------------------------------------------------

class SnowZone_1 : public PhysicEntity {
public:
    SnowZone_1(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(175, 371, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y                                         
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_2 : public PhysicEntity {
public:
    SnowZone_2(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(175, 607, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y   
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_3 : public PhysicEntity {
public:
    SnowZone_3(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(275, 435, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_4 : public PhysicEntity {
public:
    SnowZone_4(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(356, 559, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_5 : public PhysicEntity {
public:
    SnowZone_5(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(365, 175, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_14 : public PhysicEntity {
public:
    SnowZone_14(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(789, 495, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_15 : public PhysicEntity {
public:
    SnowZone_15(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(894, 528, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_16 : public PhysicEntity {
public:
    SnowZone_16(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(704, 460, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_17 : public PhysicEntity {
public:
    SnowZone_17(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(1060, 275, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_18 : public PhysicEntity {
public:
    SnowZone_18(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(925, 300, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_19 : public PhysicEntity {
public:
    SnowZone_19(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(738, 188, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_20 : public PhysicEntity {
public:
    SnowZone_20(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(807, 329, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_21 : public PhysicEntity {
public:
    SnowZone_21(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(807, 97, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_22 : public PhysicEntity {
public:
    SnowZone_22(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(955, 62, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};


class SnowZone_23 : public PhysicEntity {
public:
    SnowZone_23(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(1245, 279, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_24 : public PhysicEntity {
public:
    SnowZone_24(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(1158, 574, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_25 : public PhysicEntity {
public:
    SnowZone_25(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(895, 692, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_6 : public PhysicEntity {
public:
    SnowZone_6(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(562, 210, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_7 : public PhysicEntity {
public:
    SnowZone_7(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(608, 370, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_8 : public PhysicEntity {
public:
    SnowZone_8(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(414, 35, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_9 : public PhysicEntity {
public:
    SnowZone_9(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(75, 98, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_10 : public PhysicEntity {
public:
    SnowZone_10(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(43, 522, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};


class SnowZone_11 : public PhysicEntity {
public:
    SnowZone_11(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(230, 692, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_12 : public PhysicEntity {
public:
    SnowZone_12(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(480, 570, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_13 : public PhysicEntity {
public:
    SnowZone_13(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(448, 368, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_26 : public PhysicEntity {
public:
    SnowZone_26(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(43, 205, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class SnowZone_27 : public PhysicEntity {
public:
    SnowZone_27(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(644, 663, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

//------------------------------------------------------------------------------------ Darkened Snow Zone -------------------------------------------------------------------------------------

class DarkenedSnowZone_1 : public PhysicEntity {
public:
    DarkenedSnowZone_1(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(175, 542, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_2 : public PhysicEntity {
public:
    DarkenedSnowZone_2(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(220, 176, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_3 : public PhysicEntity {
public:
    DarkenedSnowZone_3(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(560, 142, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_4 : public PhysicEntity {
public:
    DarkenedSnowZone_4(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(43, 296, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_5 : public PhysicEntity {
public:
    DarkenedSnowZone_5(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(660, 527, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_6 : public PhysicEntity {
public:
    DarkenedSnowZone_6(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(807, 237, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class DarkenedSnowZone_7 : public PhysicEntity {
public:
    DarkenedSnowZone_7(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(1170, 62, coords, coordCount), _listener)
        , texture(_texture) //             position:   x    y  
    {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class CheckpointSensor : public PhysicEntity {
public:
    CheckpointSensor(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(670, 270, coords, coordCount), _listener)
    {                                               // x y
        collisionType = CHECKPOINT_SENSOR_1;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, YELLOW);
    }

private:
    Texture2D texture;
};

class CheckpointSensor_2 : public PhysicEntity {
public:
    CheckpointSensor_2(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(1192, 232, coords, coordCount), _listener)
    {                                               // x y
        collisionType = CHECKPOINT_SENSOR_2;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, YELLOW);
    }

private:
    Texture2D texture;
};

class CheckpointSensor_3 : public PhysicEntity {
public:
    CheckpointSensor_3(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(700, 600, coords, coordCount), _listener)
    {                                               // x    y
        collisionType = CHECKPOINT_SENSOR_3;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, YELLOW);
    }

private:
    Texture2D texture;
};

class CheckpointSensor_4 : public PhysicEntity {
public:
    CheckpointSensor_4(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(260, 650, coords, coordCount), _listener)
    {                                               // x    y
        collisionType = CHECKPOINT_SENSOR_4;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, YELLOW);
    }

private:
    Texture2D texture;
};

class FinishCheckpointSensor : public PhysicEntity {
public:
    FinishCheckpointSensor(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(88, 450, coords, coordCount), _listener)
    {                                               // x    y
        collisionType = FINISH_CHECKPOINT_SENSOR;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, YELLOW);
    }
public:
    int CountSensor = 0;
    int isActivated_1 = false;
    int isActivated_2 = false;
    int isActivated_3 = false;
    int isActivated_4 = false;
    int lap = 0;
private:
    Texture2D texture;
};

//------------------------------------------------------------------------------------ Collisions -------------------------------------------------------------------------------------

class Collisions : public PhysicEntity {
public:
    Collisions(ModulePhysics* physics, const int* coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateChain(0, 0, coords, coordCount), _listener)
        , texture(_texture)
    {
        collisionType = DEFAULT;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
    }

protected:
    Texture2D texture;
};

class Internal_Collision : public Collisions {
public:
    static constexpr int coords[208] = {
        241, 577, 273, 577, 273, 479, 257, 479, 257, 145, 273, 145, 273, 129, 287, 129,
        287, 145, 351, 145, 351, 161, 385, 161, 385, 145, 415, 145, 415, 161, 447, 161,
        447, 177, 543, 177, 543, 193, 575, 193, 575, 209, 623, 209, 623, 223, 607, 223,
        607, 449, 735, 449, 735, 465, 831, 465, 831, 481, 897, 481, 897, 433, 913, 433,
        913, 241, 977, 241, 977, 225, 1041, 225, 1041, 209, 1055, 209, 1055, 225, 1089, 225,
        1089, 209, 1103, 209, 1103, 225, 1119, 225, 1119, 239, 1103, 239, 1103, 255, 1057, 255,
        1057, 239, 1023, 239, 1023, 255, 991, 255, 991, 271, 977, 271, 977, 255, 927, 255,
        927, 289, 943, 289, 943, 337, 1039, 337, 1039, 351, 959, 351, 959, 367, 943, 367,
        943, 447, 927, 447, 927, 591, 911, 591, 911, 623, 897, 623, 897, 543, 849, 543,
        849, 527, 817, 527, 817, 511, 801, 511, 801, 495, 657, 495, 657, 479, 607, 479,
        607, 495, 593, 495, 593, 239, 577, 239, 577, 223, 497, 223, 497, 207, 449, 207,
        449, 191, 417, 191, 417, 175, 383, 175, 383, 191, 353, 191, 353, 175, 303, 175,
        303, 191, 287, 191, 287, 561, 303, 561, 303, 577, 367, 577, 367, 591, 241, 591
    };

    Internal_Collision(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 208, _listener, _texture) {}
};

class Internal_Collision_2 : public Collisions {
public:
    static constexpr int coords[16] = {
    161, 479, 161, 417, 177, 417,
    177, 257, 191, 257, 191, 447,
    175, 447, 175, 479
    };

    Internal_Collision_2(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 16, _listener, _texture) {}
};

class Internal_Collision_3 : public Collisions {
public:
    static constexpr int coords[8] = {
    929, 193,
    943, 193,
    943, 207,
    929, 207
    };

    Internal_Collision_3(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Internal_Collision_4 : public Collisions {
public:
    static constexpr int coords[8] = {
    1009, 289,
    1039, 289,
    1039, 303,
    1009, 303
    };

    Internal_Collision_4(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Internal_Collision_5 : public Collisions {
public:
    static constexpr int coords[8] = {
    1105, 337,
    1135, 337,
    1135, 351,
    1105, 351
    };

    Internal_Collision_5(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class External : public Collisions {
public:
    static constexpr int coords[108] = {
        1263, 509, 1263, 31, 1248, 31, 1247, 15, 784, 15, 782, 30, 768, 31, 767, 334,
752, 334, 751, 350, 736, 350, 735, 32, 720, 31, 719, 16, 31, 17, 31, 32, 16, 31,
15, 687, 30, 688, 32, 704, 448, 703, 448, 688, 465, 688, 464, 415, 449, 414,
448, 399, 433, 399, 431, 383, 416, 383, 415, 367, 400, 366, 400, 337, 416, 337,
416, 320, 430, 320, 432, 335, 462, 337, 463, 353, 479, 353, 479, 368, 494, 368,
495, 686, 510, 689, 511, 703, 1040, 703, 1040, 687, 1055, 687, 1055, 448, 1070, 449,
1070, 464, 1087, 465, 1087, 480, 1230, 480, 1230, 511

    };

    External(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 108, _listener, _texture) {}
};

class Bloque1Izq : public Collisions {
public:
    static constexpr int coords[8] = {
        33, 511,
    32, 496,
    46, 496,
    47, 511
    };

    Bloque1Izq(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque2Izq : public Collisions {
public:
    static constexpr int coords[8] = {
        97, 143,
    96, 128,
    111, 129,
    111, 143
    };

    Bloque2Izq(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque1Abajo : public Collisions {
public:
    static constexpr int coords[10] = {
        561, 669,
    560, 656,
    590, 656,
    591, 670,
    570, 670
    };

    Bloque1Abajo(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 10, _listener, _texture) {}
};

class Bloque2Abajo : public Collisions {
public:
    static constexpr int coords[8] = {
        640, 657,
    655, 657,
    655, 672,
    641, 672
    };

    Bloque2Abajo(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque3Abajo : public Collisions {
public:
    static constexpr int coords[8] = {
        720, 640,
    735, 640,
    735, 655,
    720, 655
    };

    Bloque3Abajo(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque1Arriba : public Collisions {
public:
    static constexpr int coords[8] = {
        1056, 48,
    1071, 48,
    1071, 63,
    1056, 63
    };

    Bloque1Arriba(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque2Arriba : public Collisions {
public:
    static constexpr int coords[8] = {
        896, 80,
    911, 80,
    911, 95,
    896, 95
    };

    Bloque2Arriba(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};

class Bloque3Arriba : public Collisions {
public:
    static constexpr int coords[8] = {
        800, 304,
    815, 304,
    816, 319,
    800, 319
    };

    Bloque3Arriba(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture)
        : Collisions(physics, coords, 8, _listener, _texture) {}
};


LevelSetup::LevelSetup(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    ray_on = false;
    sensed = false;
}

LevelSetup::~LevelSetup()
{}

// Load assets
bool LevelSetup::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    App->renderer->camera.x = App->renderer->camera.y = 0;

    

    return ret;
}
// Load assets
bool LevelSetup::CleanUp()
{
    
    return true;
}

// Update: draw background
update_status LevelSetup::Update()
{

    // Prepare for raycast ------------------------------------------------------
    vec2i mouse;
    mouse.x = GetMouseX();
    mouse.y = GetMouseY();
    int ray_hit = ray.DistanceTo(mouse);

    vec2f normal(0.0f, 0.0f);

    // All draw functions ------------------------------------------------------


    for (PhysicEntity* entity : entities)
    {
        entity->Update();
        if (ray_on)
        {
            int hit = entity->RayHit(ray, mouse, normal);
            if (hit >= 0)
            {
                ray_hit = hit;
            }
        }
    }


    // ray -----------------
    if (ray_on == true)
    {
        vec2f destination((float)(mouse.x - ray.x), (float)(mouse.y - ray.y));
        destination.Normalize();
        destination *= (float)ray_hit;

        DrawLine(ray.x, ray.y, (int)(ray.x + destination.x), (int)(ray.y + destination.y), RED);

        if (normal.x != 0.0f)
        {
            DrawLine((int)(ray.x + destination.x), (int)(ray.y + destination.y), (int)(ray.x + destination.x + normal.x * 25.0f), (int)(ray.y + destination.y + normal.y * 25.0f), Color{ 100, 255, 100, 255 });
        }
    }

    return UPDATE_CONTINUE;
}

void LevelSetup::CreateCollisionsAndSensors()
{
    //------------------------------ Collision ----------------------------------------

    entities.emplace_back(new Internal_Collision(App->physics, 0, 0, this, default));
    entities.emplace_back(new Internal_Collision_2(App->physics, 0, 0, this, default));
    entities.emplace_back(new Internal_Collision_3(App->physics, 0, 0, this, default));
    entities.emplace_back(new Internal_Collision_4(App->physics, 0, 0, this, default));
    entities.emplace_back(new Internal_Collision_5(App->physics, 0, 0, this, default));
    entities.emplace_back(new External(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque1Izq(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque2Izq(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque1Abajo(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque2Abajo(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque3Abajo(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque1Arriba(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque2Arriba(App->physics, 0, 0, this, default));
    entities.emplace_back(new Bloque3Arriba(App->physics, 0, 0, this, default));

    //----------------------------- Snow Zone -----------------------------------------
    //                                                width/height 
    entities.emplace_back(new SnowZone_1(App->physics, 100, 252, this, default));
    entities.emplace_back(new SnowZone_2(App->physics, 100, 40, this, default));
    entities.emplace_back(new SnowZone_3(App->physics, 100, 382, this, default));
    entities.emplace_back(new SnowZone_4(App->physics, 62, 135, this, default));
    entities.emplace_back(new SnowZone_5(App->physics, 230, 138, this, default));
    entities.emplace_back(new SnowZone_6(App->physics, 164, 70, this, default));
    entities.emplace_back(new SnowZone_7(App->physics, 72, 250, this, default));
    entities.emplace_back(new SnowZone_8(App->physics, 564, 40, this, default));
    entities.emplace_back(new SnowZone_9(App->physics, 115, 165, this, default));
    entities.emplace_back(new SnowZone_10(App->physics, 52, 320, this, default));
    entities.emplace_back(new SnowZone_11(App->physics, 426, 20, this, default));
    entities.emplace_back(new SnowZone_12(App->physics, 74, 267, this, default));
    entities.emplace_back(new SnowZone_13(App->physics, 136, 137, this, default));
    entities.emplace_back(new SnowZone_14(App->physics, 75, 140, this, default));
    entities.emplace_back(new SnowZone_15(App->physics, 134, 206, this, default));
    entities.emplace_back(new SnowZone_16(App->physics, 94, 70, this, default));
    entities.emplace_back(new SnowZone_17(App->physics, 198, 200, this, default));
    entities.emplace_back(new SnowZone_18(App->physics, 70, 250, this, default));
    entities.emplace_back(new SnowZone_19(App->physics, 80, 374, this, default));
    entities.emplace_back(new SnowZone_20(App->physics, 57, 93, this, default));
    entities.emplace_back(new SnowZone_21(App->physics, 57, 189, this, default));
    entities.emplace_back(new SnowZone_22(App->physics, 240, 118, this, default));
    entities.emplace_back(new SnowZone_23(App->physics, 70, 296, this, default));
    entities.emplace_back(new SnowZone_24(App->physics, 280, 294, this, default));
    entities.emplace_back(new SnowZone_25(App->physics, 246, 20, this, default));
    entities.emplace_back(new SnowZone_26(App->physics, 52, 50, this, default));
    entities.emplace_back(new SnowZone_27(App->physics, 256, 84, this, default));

    //----------------------------- Darkened Snow Zone  -----------------------------------------
    //                                                       width/height 
    entities.emplace_back(new DarkenedSnowZone_1(App->physics, 100, 91, this, default));
    entities.emplace_back(new DarkenedSnowZone_2(App->physics, 60, 137, this, default));
    entities.emplace_back(new DarkenedSnowZone_3(App->physics, 162, 64, this, default));
    entities.emplace_back(new DarkenedSnowZone_4(App->physics, 52, 132, this, default));
    entities.emplace_back(new DarkenedSnowZone_5(App->physics, 168, 64, this, default));
    entities.emplace_back(new DarkenedSnowZone_6(App->physics, 57, 91, this, default));
    entities.emplace_back(new DarkenedSnowZone_7(App->physics, 190, 118, this, default));

    //----------------------------- Checkpoints  -----------------------------------------
    //                                                       width/height 
    entities.emplace_back(new CheckpointSensor(App->physics, 130, 10, this, default));
    entities.emplace_back(new CheckpointSensor_2(App->physics, 140, 10, this, default));
    entities.emplace_back(new CheckpointSensor_3(App->physics, 10, 206, this, default));
    entities.emplace_back(new CheckpointSensor_4(App->physics, 10, 116, this, default));
    entities.emplace_back(new FinishCheckpointSensor(App->physics, 142, 10, this, default));

}

void LevelSetup::RemoveAllCollisionsAndSensors() {
    for (auto entity : entities) {
        if (entity->body != nullptr && entity->body->body != nullptr) {
            App->physics->world->DestroyBody(entity->body->body);
            entity->body->body = nullptr;
        }
        delete entity;
    }
    entities.clear();
}