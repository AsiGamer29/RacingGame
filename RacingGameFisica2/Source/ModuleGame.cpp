#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
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
    KartType GetKartType() const { return kartType; }
	PhysBody* body;

protected:

	Module* listener;
    CollisionType collisionType;
    KartType kartType;
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

    Internal_Collision_2(ModulePhysics * physics, int x, int y, Module * _listener, Texture2D _texture)
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

class Circle : public PhysicEntity
{
public:
	Circle(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle(_x, _y, 25), _listener)
		, texture(_texture)
	{

	}

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x, (float)y };
		float scale = 1.0f;
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
		Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f};
		float rotation = 0;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}

private:
	Texture2D texture;

};

class Cone : public PhysicEntity
{
public:
    Cone(ModulePhysics* physics, int x, int y, Module* listener, Texture2D _texture, Application* _app)
        : PhysicEntity(physics->CreateStaticCircle(x, y, 6), listener), texture(_texture), app(_app)
    {
    }

    void Update() override
    {
        int x, y;
        body->GetPhysicPosition(x, y);

        float scale = 2.0f;
        DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
            Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
            Vector2{ (float)texture.width, (float)texture.height }, 0.0f, WHITE);
    }

private:
    Texture2D texture;
    Application* app;
};


class Kart : public PhysicEntity {
public:
    Kart(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type)
        : PhysicEntity(physics->CreateCircle(x, y, 9), _listener), texture(_texture), app(_app) {}

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        float rotationDegrees = body->GetRotation() * RAD2DEG;
        float scale = 1.5f; // Escala de la imagen
        DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
            Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
            Vector2{ (float)texture.width - 1.0f, (float)texture.height - 2.0f }, rotationDegrees, WHITE);

    }

protected:
    Texture2D texture;
    Application* app;
};

class Kart_Controller : public Kart {
public:
    Kart_Controller(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart(physics, x, y, _listener, _texture, _app, type), speed(0.0f), rotation(0.0f), isBoosting(false), isMoving(false), kartType(type), player(player){}


    virtual void HandleInput() {
        
        float currentMaxSpeed;
        float kartRotation;
        float kartAcceleration;

        if (kartType == KARTO) {
            currentMaxSpeed = maxSpeedKa;
        }
        else if (kartType == HAOLIEN) {
			currentMaxSpeed = maxSpeedHa;
		}
		else if (kartType == JOHANA) {
			currentMaxSpeed = maxSpeedJo;
		}
		else if (kartType == TANKETO) {
			currentMaxSpeed = maxSpeedTa;
		}
		else {
			currentMaxSpeed = maxSpeed;
		}

        if (kartType == KARTO) {
            kartRotation = rotationKa;
        }
        else if (kartType == HAOLIEN) {
            kartRotation = rotationHa;
        }
        else if (kartType == JOHANA) {
            kartRotation = rotationJo;
        }
        else if (kartType == TANKETO) {
            kartRotation = rotationTa;
        }
        else {
            kartRotation = rotation;
        }

        if (kartType == KARTO) {
			kartAcceleration = accelerationKa;
        }
		else if (kartType == HAOLIEN) {
			kartAcceleration = accelerationHa;
		}
		else if (kartType == JOHANA) {
			kartAcceleration = accelerationJo;
		}
		else if (kartType == TANKETO) {
			kartAcceleration = accelerationTa;
		}
		else {
			kartAcceleration = acceleration;
		}
        

        if (speed != 0.0f && !isMoving)
        {
            app->audio->PlayFx(engineSound, -1); // Reproduce en bucle
            isMoving = true;
        }
        else if (speed == 0.0f && isMoving)
        {
            isMoving = false;
        }

        if (player == PLAYER1) {
            if (IsKeyDown(KEY_W)) {
                speed += kartAcceleration;
                if (speed > currentMaxSpeed) {
                    speed = currentMaxSpeed;
                }
            }
            else if (IsKeyDown(KEY_S)) {
                speed -= kartAcceleration;
                if (speed < -currentMaxSpeed) {
                    speed = -currentMaxSpeed;
                }
            }
            else {
                // Deceleraci�n gradual
                if (speed > 0.0f) {
                    speed -= deceleration;
                    if (speed < 0.0f) {
                        speed = 0.0f;
                    }
                }
                else if (speed < 0.0f) {
                    speed += deceleration;
                    if (speed > 0.0f) {
                        speed = 0.0f;
                    }
                }
            }
        }
        else if (player == PLAYER2) {
            if (IsKeyDown(KEY_UP)) {
                speed += 0.1f;
                if (speed > currentMaxSpeed) {
                    speed = currentMaxSpeed;
                }
            }
            else if (IsKeyDown(KEY_DOWN)) {
                speed -= 0.1f;
                if (speed < -currentMaxSpeed) {
                    speed = -currentMaxSpeed;
                }
            }
            else {
                // Deceleraci�n gradual
                if (speed > 0.0f) {
                    speed -= deceleration;
                    if (speed < 0.0f) {
                        speed = 0.0f;
                    }
                }
                else if (speed < 0.0f) {
                    speed += deceleration;
                    if (speed > 0.0f) {
                        speed = 0.0f;
                    }
                }
            }
        }
       
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
			isDrifting = true;
        }
        else {
			isDrifting = false;
        }

        if (isDrifting) {
            if (player == PLAYER1) {
                if (IsKeyDown(KEY_A)) {
                    rotation -= kartRotation + 0.5f;
                }
                if (IsKeyDown(KEY_D)) {
                    rotation += kartRotation + 0.5f;
                }
            }
			else if (player == PLAYER2) {
				if (IsKeyDown(KEY_LEFT)) {
					rotation -= kartRotation + 0.5f;
				}
				if (IsKeyDown(KEY_RIGHT)) {
					rotation += kartRotation + 0.5f;
				}
			}
            
		}
		else {
            if (player == PLAYER1) {
				if (IsKeyDown(KEY_A)) {
                    rotation -= kartRotation;
				}
				if (IsKeyDown(KEY_D)) {
                    rotation += kartRotation;
				}
            }
            else if (player == PLAYER2) {
                if (IsKeyDown(KEY_LEFT)) {
					rotation -= kartRotation;
                }
                if (IsKeyDown(KEY_RIGHT)) {
                    rotation += kartRotation;
                }
            }
        }
        
    }
    
    // La logica para boostear esta en los commits anteriores

    void Move()
    {
        float rad = rotation * DEG2RAD;
        body->body->SetLinearVelocity(b2Vec2(speed * sin(rad), -speed * cos(rad)));
        body->body->SetTransform(body->body->GetPosition(), rad);
    }

    virtual void Update() override {
        HandleInput();
        Move();
        Kart::Update();
		
    }
public:
    // Accelerations
	float accelerationKa = 0.1f;
	float accelerationJo = 0.1f;
	float accelerationTa = 0.25f;
    float accelerationHa = 0.25f;
	
    // Max speeds for each kart
	float maxSpeedKa = 2.5f;
    float maxSpeedTa = 1.5f;
	float maxSpeedHa = 3.0f;
	float maxSpeedJo = 1.0f;

	// Max boosted speed for each kart
    float boostedMaxSpeedKa = 4.0f;
    float boostedMaxSpeedJo = 3.0f;
    float boostedMaxSpeedTa = 6.0f;
    float boostedMaxSpeedHa = 5.0f;

	// Rotations for each kart
	float rotationKa = 2.0f;
	float rotationTa = 2.25f;
    float rotationHa = 1.0f;
	float rotationJo = 1.5f;

	float maxSpeed = 2.0f;
    float acceleration = 1.0f;
	float rotationDefault = 2.0f;
	float boostedMaxSpeed = 4.0f;

    bool inSnowZone = false;
    bool inDarkenedSnowZone = false;
    int snowZoneCount = 0;
    int DarkenedsnowZoneCount = 0;


    KartType kartType;

protected:
	Player player;
    std::vector<PhysicEntity*> entities;
    float speed;
    float rotation;
    bool isMoving;
    bool isBoosting;
    bool isDrifting;
    const float deceleration = 0.05f;
    uint32 boostSound = app->audio->LoadFx("Assets/boost.wav");
	uint32 engineSound = app->audio->LoadFx("Assets/drive.wav");
};

class Kart_Player_1 : public Kart_Controller {
public:
    Kart_Player_1(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart_Controller(physics, x, y, _listener, _texture, _app, type, player) {}

public:
    int CurrentRank = 1;
};

class Kart_Player_2 : public Kart_Controller {
public:
    Kart_Player_2(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart_Controller(physics, x, y, _listener, _texture, _app, type, player) {
    }
    
public:
    int CurrentRank = 2;
};



ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    ray_on = false;
    sensed = false;
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

	gameState = TITLESCREEN;

    App->renderer->camera.x = App->renderer->camera.y = 0;

    cone = LoadTexture("Assets/cone.png");
    yellowCar = LoadTexture("Assets/yellow.png");
    redCar = LoadTexture("Assets/red.png");
    greenCar = LoadTexture("Assets/green.png");
    blueCar = LoadTexture("Assets/blue.png");

	mainScreen = LoadTexture("Assets/mainScreen.png");
    player1Select = LoadTexture("Assets/player1select.png");
	player2Select = LoadTexture("Assets/player2select.png");
	background = LoadTexture("Assets/Mapa1Racing.png");

    engine_fx = App->audio->LoadFx("Assets/drive.wav");
    boost_fx = App->audio->LoadFx("Assets/boost.wav"); // Cargar el sonido de boost
    bump_fx = App->audio->LoadFx("Assets/Bump.wav");

    bgm = LoadMusicStream("Assets/music.ogg");
	playerSelect = LoadMusicStream("Assets/playerselect.ogg");
	title = LoadMusicStream("Assets/title.ogg");

    PlayMusicStream(title);
	PlayMusicStream(playerSelect);
    PlayMusicStream(bgm);

    return ret;
}
// Load assets
bool ModuleGame::CleanUp()
{
    LOG("Unloading Intro scene");
	UnloadTexture(cone);
	UnloadTexture(yellowCar);
	UnloadTexture(redCar);
	UnloadTexture(greenCar);
	UnloadTexture(blueCar);
	UnloadTexture(mainScreen);
	UnloadTexture(background);
	UnloadMusicStream(bgm);
	UnloadMusicStream(title);
    return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
    switch (gameState) {
    case TITLESCREEN:
        
        UpdateMusicStream(title);
        DrawTexture(mainScreen, 0, 0, WHITE);
        if (IsKeyPressed(KEY_SPACE)) {
            gameState = PLAYER1SELECT;
        }
        break;
    case PLAYER1SELECT:
        UpdateMusicStream(playerSelect);
        DrawTexture(player1Select, 0, 0, WHITE);
        
        if (IsKeyPressed(KEY_ONE)) {
            chosenKartop1 = true;
            hasChosenPlayer1 = true;
            gameState = PLAYER2SELECT;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            chosenHaolienp1 = true;
			hasChosenPlayer1 = true;
            gameState = PLAYER2SELECT;
        }
		else if (IsKeyPressed(KEY_THREE))
		{
			chosenJohanap1 = true;
			hasChosenPlayer1 = true;
            gameState = PLAYER2SELECT;
		}
		else if (IsKeyPressed(KEY_FOUR))
		{
			chosenTanketop1 = true;
			hasChosenPlayer1 = true;
            gameState = PLAYER2SELECT;
		}
        break;

    case PLAYER2SELECT:
        UpdateMusicStream(playerSelect);
        DrawTexture(player2Select, 0, 0, WHITE);
        if (IsKeyPressed(KEY_ONE)) {
            chosenKartop2 = true;
            hasChosenPlayer2 = true;
            if (hasStarted == false) {
                CreateCollisionsAndSensors();
                hasStarted = true;
                hasDeleted = false;
            }
            gameState = PLAYING;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            chosenHaolienp2 = true;
            hasChosenPlayer2 = true;
            if (hasStarted == false) {
                CreateCollisionsAndSensors();
                hasStarted = true;
                hasDeleted = false;
            }
            gameState = PLAYING;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            chosenJohanap2 = true;
            hasChosenPlayer2 = true;
            if (hasStarted == false) {
                CreateCollisionsAndSensors();
                hasStarted = true;
                hasDeleted = false;
            }
            gameState = PLAYING;
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            chosenTanketop2 = true;
            hasChosenPlayer2 = true;
            if (hasStarted == false) {
                CreateCollisionsAndSensors();
                hasStarted = true;
                hasDeleted = false;
            }
            gameState = PLAYING;
        }
        break;

    case PLAYING:
        DrawTexture(background, 0, 0, WHITE);
            for (PhysicEntity* entity : entities)
        {
            if (FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entity))
            {
                DrawText(TextFormat("Lap: %d", finish->lap), 1080, 500, 20, RED);
                //printf("Lap: %d\n", finish->lap);
            }
            if (Kart_Player_1* kart_1 = dynamic_cast<Kart_Player_1*>(entity))
            {
                if(kart_1->CurrentRank == 1) DrawText(TextFormat("Kart 1 - Top: %d", kart_1->CurrentRank), 1080, 530, 20, RED);
                else DrawText(TextFormat("Kart 1 - Top: %d", kart_1->CurrentRank), 1080, 560, 20, RED);
                //printf("Top: %d\n", kart_1->CurrentRank);
            }
            if (Kart_Player_2* kart_2 = dynamic_cast<Kart_Player_2*>(entity))
            {
                if(kart_2->CurrentRank == 1) DrawText(TextFormat("Kart 2 - Top: %d", kart_2->CurrentRank), 1080, 530, 20, RED);
                else DrawText(TextFormat("Kart 2 - Top: %d", kart_2->CurrentRank), 1080, 560, 20, RED);
                /*printf("Top: %d\n", kart_2->CurrentRank);*/
            }

            entity->Update();
        }
        UpdateMusicStream(bgm);
       
        if (IsKeyPressed(KEY_Z)) {
            if (hasDeleted == false) {
                RemoveAllCollisionsAndSensors();
				hasDeleted = true;
                hasStarted = false;

                chosenKartop1 = false;
                chosenHaolienp1 = false;
                chosenJohanap1 = false;
                chosenTanketop1 = false;

                chosenKartop2 = false;
                chosenHaolienp2 = false;
                chosenJohanap2 = false;
                chosenTanketop2 = false;

                hasChosenPlayer1 = false;
                hasChosenPlayer2 = false;

                hasSpawnedPlayer1Car = false;
                hasSpawnedPlayer2Car = false;
            }
            gameState = TITLESCREEN;
            
        }
        break;
    }

    
    if (gameState == PLAYING) {
        if (IsKeyPressed(KEY_SPACE))
        {
            ray_on = !ray_on;
            ray.x = GetMouseX();
            ray.y = GetMouseY();
        }

        if (chosenKartop1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(new Kart_Player_1(App->physics, 81, 458, this, blueCar, App, KARTO, PLAYER1));
			hasChosenPlayer1 = false;
		}
        else if (chosenHaolienp1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(new Kart_Player_1(App->physics, 81, 458, this, yellowCar, App, HAOLIEN, PLAYER1));
            hasChosenPlayer1 = false;
        }
        else if (chosenJohanap1 == true && hasChosenPlayer1 == true)
        {
			entities.emplace_back(new Kart_Player_1(App->physics, 81, 458, this, greenCar, App, JOHANA, PLAYER1));
            hasChosenPlayer1 = false;
        }
        else if (chosenTanketop1 == true && hasChosenPlayer1 == true)
        {
			entities.emplace_back(new Kart_Player_1(App->physics, 81, 458, this, redCar, App, TANKETO, PLAYER1));
            hasChosenPlayer1 = false;
        }

        if (chosenKartop2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(new Kart_Player_2(App->physics, 104, 470, this, blueCar, App, KARTO, PLAYER2));
			hasChosenPlayer2 = false;
		}
		else if (chosenHaolienp2 == true && hasChosenPlayer2 == true) {
			entities.emplace_back(new Kart_Player_2(App->physics, 104, 470, this, yellowCar, App, HAOLIEN, PLAYER2));
			hasChosenPlayer2 = false;
		}
		else if (chosenJohanap2 == true && hasChosenPlayer2 == true) {
			entities.emplace_back(new Kart_Player_2(App->physics, 104, 470, this, greenCar, App, JOHANA, PLAYER2));
			hasChosenPlayer2 = false;
		}
        else if (chosenTanketop2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(new Kart_Player_2(App->physics, 104, 470, this, redCar, App, TANKETO, PLAYER2));
            hasChosenPlayer2 = false;
        }

        if (IsKeyPressed(KEY_M))
        {
            entities.emplace_back(new Cone(App->physics, GetMouseX(), GetMouseY(), this, cone, App)); // Pasa el puntero a Application y el sonido de boost
        }
    }

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

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {
    int length = entities.size();
    for (int i = 0; i < length; ++i) {
        if (bodyA == entities[i]->body) {
            Kart_Controller* kart = dynamic_cast<Kart_Controller*>(entities[i]);
            FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entities[i]);
            if (kart) {
                for (int j = 0; j < length; ++j) {
                    //SNOW ZONE
                    if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == SNOW) {
                        if (kart->snowZoneCount == 0) {
                            printf("Kart entered snow zone.\n");
                            kart->inSnowZone = true;
                            if (kart->kartType == KARTO) {
								kart->maxSpeedKa = 1.5f;
								kart->boostedMaxSpeedKa = 3.0f;
							}
                            else if (kart->kartType == HAOLIEN) {
                                kart->maxSpeedHa = 1.5f;
                                kart->boostedMaxSpeedHa = 2.5f;
                            }
							else if (kart->kartType == JOHANA) {
								kart->maxSpeedJo = 2.5f;
								kart->boostedMaxSpeedJo = 4.0f;
							}
							else if (kart->kartType == TANKETO) {
								kart->maxSpeedTa = 1.5f;
								kart->boostedMaxSpeedTa = 6.0f;
							}
                            
                        }
                        kart->snowZoneCount++;
                        return;
                    }
                    //DARKENED SNOW ZONE
                    if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == DARKENED_SNOW) {
                        if (kart->DarkenedsnowZoneCount == 0) {
                            printf("Kart entered darkened snow zone.\n");
                            kart->inDarkenedSnowZone = true;
                            if (kart->kartType == KARTO) {
                                kart->maxSpeedKa = 1.0f;
                                kart->boostedMaxSpeedKa = 2.5f;
                            }
                            else if (kart->kartType == HAOLIEN) {
                                kart->maxSpeedHa = 1.0f;
                                kart->boostedMaxSpeedHa = 2.0f;
                            }
                            else if (kart->kartType == JOHANA) {
                                kart->maxSpeedJo = 2.5f;
                                kart->boostedMaxSpeedJo = 4.0f;
                            }
                            else if (kart->kartType == TANKETO) {
                                kart->maxSpeedTa = 1.5f;
                                kart->boostedMaxSpeedTa = 6.0f;
                            }
                        }
                        kart->DarkenedsnowZoneCount++;
                        return;
                    }
                    //------------------------------------  CHECKPOINTS  --------------------------------------
                    // CHECKPOINT 
                    for (PhysicEntity* entity : entities)
                    {
                        if (FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entity))
                        {

                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_1 && finish->isActivated_1 == false) {
                                Kart_Player_1* kart_1 = nullptr;
                                Kart_Player_2* kart_2 = nullptr;

                                for (PhysicEntity* entity : entities) { // search karts
                                    if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                                    if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                                    if (kart_1 && kart_2) break; 
                                }
                                if (kart_1 && kart_2) {
                                    if (kart_1->body == bodyA) { //first kart_1
                                        if (kart_1->CurrentRank > kart_2->CurrentRank) {
                                            kart_1->CurrentRank = 1;
                                            kart_2->CurrentRank = 2;
                                        }
                                    }
                                    else if (kart_2->body == bodyA) { //first kart_2
                                        if (kart_2->CurrentRank > kart_1->CurrentRank) {
                                            kart_2->CurrentRank = 1;
                                            kart_1->CurrentRank = 2;
                                        }
                                    }
                                }

                                finish->CountSensor++;
                                finish->isActivated_1 = true;
                                printf("Checkpoint %d", finish->CountSensor);
                                return;
                            }
                            // CHECKPOINT 2
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_2 && finish->isActivated_1 == true && finish->isActivated_2 == false) {
                                Kart_Player_1* kart_1 = nullptr;
                                Kart_Player_2* kart_2 = nullptr;

                                for (PhysicEntity* entity : entities) { // search karts
                                    if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                                    if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                                    if (kart_1 && kart_2) break;
                                }
                                if (kart_1 && kart_2) {
                                    if (kart_1->body == bodyA) { //first kart_1
                                        if (kart_1->CurrentRank > kart_2->CurrentRank) {
                                            kart_1->CurrentRank = 1;
                                            kart_2->CurrentRank = 2;
                                        }
                                    }
                                    else if (kart_2->body == bodyA) { //first kart_2
                                        if (kart_2->CurrentRank > kart_1->CurrentRank) {
                                            kart_2->CurrentRank = 1;
                                            kart_1->CurrentRank = 2;
                                        }
                                    }
                                }
                                finish->CountSensor++;
                                finish->isActivated_2 = true;
                                printf("Checkpoint %d", finish->CountSensor);
                                return;
                            }
                            // CHECKPOINT 3
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_3 && finish->isActivated_2 == true && finish->isActivated_3 == false) {
                                Kart_Player_1* kart_1 = nullptr;
                                Kart_Player_2* kart_2 = nullptr;

                                for (PhysicEntity* entity : entities) { // search karts
                                    if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                                    if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                                    if (kart_1 && kart_2) break;
                                }
                                if (kart_1 && kart_2) {
                                    if (kart_1->body == bodyA) { //first kart_1
                                        if (kart_1->CurrentRank > kart_2->CurrentRank) {
                                            kart_1->CurrentRank = 1;
                                            kart_2->CurrentRank = 2;
                                        }
                                    }
                                    else if (kart_2->body == bodyA) { //first kart_2
                                        if (kart_2->CurrentRank > kart_1->CurrentRank) {
                                            kart_2->CurrentRank = 1;
                                            kart_1->CurrentRank = 2;
                                        }
                                    }
                                }
                                finish->CountSensor++;
                                finish->isActivated_3 = true;
                                printf("Checkpoint %d", finish->CountSensor);
                                return;
                            }
                            // CHECKPOINT 4
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_4 && finish->isActivated_3 == true && finish->isActivated_4 == false) {
                                
                                Kart_Player_1* kart_1 = nullptr;
                                Kart_Player_2* kart_2 = nullptr;

                                for (PhysicEntity* entity : entities) { // search karts
                                    if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                                    if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                                    if (kart_1 && kart_2) break;
                                }
                                if (kart_1 && kart_2) {
                                    if (kart_1->body == bodyA) { //first kart_1
                                        if (kart_1->CurrentRank > kart_2->CurrentRank) {
                                            kart_1->CurrentRank = 1;
                                            kart_2->CurrentRank = 2;
                                        }
                                    }
                                    else if (kart_2->body == bodyA) { //first kart_2
                                        if (kart_2->CurrentRank > kart_1->CurrentRank) {
                                            kart_2->CurrentRank = 1;
                                            kart_1->CurrentRank = 2;
                                        }
                                    }
                                }
                                finish->CountSensor++;
                                finish->isActivated_4 = true;
                                printf("Checkpoint %d", finish->CountSensor);
                                return;
                            }
                            // FINISH CHECKPOINT
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == FINISH_CHECKPOINT_SENSOR && finish->isActivated_4 == true && finish->CountSensor == 4) {

                                Kart_Player_1* kart_1 = nullptr;
                                Kart_Player_2* kart_2 = nullptr;

                                for (PhysicEntity* entity : entities) { // search karts
                                    if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                                    if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                                    if (kart_1 && kart_2) break;
                                }
                                if (kart_1 && kart_2) {
                                    if (kart_1->body == bodyA) { //first kart_1
                                        if (kart_1->CurrentRank > kart_2->CurrentRank) {
                                            kart_1->CurrentRank = 1;
                                            kart_2->CurrentRank = 2;
                                        }
                                    }
                                    else if (kart_2->body == bodyA) { //first kart_2
                                        if (kart_2->CurrentRank > kart_1->CurrentRank) {
                                            kart_2->CurrentRank = 1;
                                            kart_1->CurrentRank = 2;
                                        }
                                    }
                                }
                                finish->CountSensor = 0;
                                finish->lap++;
                                finish->isActivated_1 = false;
                                finish->isActivated_2 = false;
                                finish->isActivated_3 = false;
                                finish->isActivated_4 = false;

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}


void ModuleGame::OnCollisionExit(PhysBody* bodyA, PhysBody* bodyB) {
    int length = entities.size();
    for (int i = 0; i < length; ++i) {
        if (bodyA == entities[i]->body) {
            Kart_Controller* kart = dynamic_cast<Kart_Controller*>(entities[i]);
            if (kart) {
                for (int j = 0; j < length; ++j) {
                    if (bodyB == entities[j]->body) {
                        // SNOW ZONE
                        if (entities[j]->GetCollisionType() == SNOW) {
                            kart->snowZoneCount--;
                            if (kart->snowZoneCount == 0 && kart->DarkenedsnowZoneCount == 0) {
                                printf("Kart exited snow zone.\n");
                                kart->inSnowZone = false;
                                kart->inDarkenedSnowZone = false;
                                if (kart->kartType == KARTO) {
                                    kart->maxSpeedKa = 2.5f;
                                    kart->boostedMaxSpeedKa = 4.0f;
                                }
                                else if (kart->kartType == HAOLIEN) {
                                    kart->maxSpeedHa = 3.0f;
                                    kart->boostedMaxSpeedHa = 5.0f;
                                }
                                else if (kart->kartType == JOHANA) {
                                    kart->maxSpeedJo = 1.0f;
                                    kart->boostedMaxSpeedJo = 3.0f;
                                }
                                else if (kart->kartType == TANKETO) {
                                    kart->maxSpeedTa = 1.5f;
                                    kart->boostedMaxSpeedTa = 6.0f;
                                }
                            }
                        }
                        //DARKENED SNOW ZONE
                        if (entities[j]->GetCollisionType() == DARKENED_SNOW) {
                            kart->DarkenedsnowZoneCount--;
                            if (kart->DarkenedsnowZoneCount == 0 && kart->snowZoneCount == 0) {
                                printf("Kart exited darkened snow zone.\n");
                                kart->inSnowZone = false;
                                kart->inDarkenedSnowZone = false;
                                if (kart->kartType == KARTO) {
                                    kart->maxSpeedKa = 2.5f;
                                    kart->boostedMaxSpeedKa = 4.0f;
                                }
                                else if (kart->kartType == HAOLIEN) {
                                    kart->maxSpeedHa = 3.0f;
                                    kart->boostedMaxSpeedHa = 5.0f;
                                }
                                else if (kart->kartType == JOHANA) {
                                    kart->maxSpeedJo = 1.0f;
                                    kart->boostedMaxSpeedJo = 3.0f;
                                }
                                else if (kart->kartType == TANKETO) {
                                    kart->maxSpeedTa = 1.5f;
                                    kart->boostedMaxSpeedTa = 6.0f;
                                }
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
}

void ModuleGame::CreateCollisionsAndSensors()
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

void ModuleGame::RemoveAllCollisionsAndSensors() {
    for (auto entity : entities) {
        if (entity->body != nullptr && entity->body->body != nullptr) {
            App->physics->world->DestroyBody(entity->body->body);
            entity->body->body = nullptr;
        }
        delete entity;
    }
    entities.clear();
}

PhysicEntity* ModuleGame::GetEntityByBody(PhysBody* body) {
    for (PhysicEntity* entity : entities) {
        if (entity->body == body) {
            return entity;
        }
    }
    return nullptr;
}