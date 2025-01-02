#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModulePhysics.h"
#include "time.h"

bool raceStarted = false;

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
	TurnDirection GetTurnDirection() const { return turnDirection; }
    KartType GetKartType() const { return kartType; }
	PhysBody* body;

protected:

	Module* listener;
    CollisionType collisionType;
    KartType kartType;
    TurnDirection turnDirection;
};

//------------------------------------------------------------------------------------ Snow Zone -------------------------------------------------------------------------------------

// Clase base
class SnowZone : public PhysicEntity {
public:
    SnowZone(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture)
        : PhysicEntity(physics->CreateRectangleSensor(x, y, width, height), listener), texture(texture) {
        collisionType = SNOW;
    }

    virtual void Update() override {
        int posX, posY;
        body->GetPhysicPosition(posX, posY);
        DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, body->GetRotation() * RAD2DEG, 0.0f, WHITE);
    }

protected:
    Texture2D texture;
};

void InitializeSnowZones(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    // Datos de configuración: x, y, width, height
    struct SnowZoneParams {
        int x;
        int y;
        int width;
        int height;
    };

    std::vector<SnowZoneParams> snowZoneData = {
        {562, 210, 164, 70}, {175, 371, 100, 252}, {175, 607, 100, 40},     // 6 1 2
        {275, 435, 100, 382}, {356, 559, 62, 135}, {365, 175, 230, 138}, // 3 4 5
        {789, 495, 75, 140}, {894, 528, 134, 206}, {704, 460, 94, 70}, // 14 15 16
        {1060, 275, 198, 200}, {925, 300, 70, 250}, {738, 188, 80, 374}, // 17 18 19
        {807, 329, 57, 93}, {807, 97, 57, 189}, {955, 62, 240, 118}, // 20 21 22
        {1245, 279, 70, 296}, {1158, 574, 280, 294}, {895, 692, 246, 20}, // 23 24 25
        {608, 370, 72, 250}, {414, 35, 564, 40}, {75, 98, 115, 165}, // 7 8 9
        {43, 522, 52, 320}, {230, 692, 426, 20}, {480, 570, 74, 267}, // 10 11 12
        {448, 368, 136, 137}, {43, 205, 52, 50}, {644, 663, 256, 84} // 13 26 27
    };

    for (const auto& zone : snowZoneData) {
        entities.emplace_back(DBG_NEW SnowZone(physics, zone.x, zone.y, zone.width, zone.height, listener, defaultTexture));
    }
}

//------------------------------------------------------------------------------------ Darkened Snow Zone -------------------------------------------------------------------------------------

// Clase base 
class DarkenedSnowZone : public PhysicEntity {
public:
    DarkenedSnowZone(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture)
        : PhysicEntity(physics->CreateRectangleSensor(x, y, width, height), listener), texture(texture) {
        collisionType = DARKENED_SNOW;
    }

    virtual void Update() override {
        int posX, posY;
        body->GetPhysicPosition(posX, posY);
        DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, body->GetRotation() * RAD2DEG, 0.0f, WHITE);
    }

protected:
    Texture2D texture;
};

void InitializeDarkenedSnowZones(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    struct DarkenedSnowZoneParams {
        int x;
        int y;
        int width;
        int height;
    };

    std::vector<DarkenedSnowZoneParams> darkenedSnowZoneData = {
        {175, 542, 100, 91}, {220, 176, 60, 137}, {560, 142, 162, 64},
        {43, 296, 52, 132}, {660, 527, 168, 64}, {807, 237, 57, 91},
        {1170, 62, 190, 118}
    };

    // Crear cada zona de DarkenedSnow y añadirla a la lista de entidades
    for (const auto& zone : darkenedSnowZoneData) {
        entities.emplace_back(DBG_NEW DarkenedSnowZone(physics, zone.x, zone.y, zone.width, zone.height, listener, defaultTexture));
    }
}

//------------------------------------------------------------------------------------ CHECKPOINTS -------------------------------------------------------------------------------------

// Clase base 
class CheckpointSensor : public PhysicEntity {
public:
    CheckpointSensor(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture, CollisionType type)
        : PhysicEntity(physics->CreateRectangleSensor(x, y, width, height), listener), texture(texture) {
        collisionType = type;
    }

    virtual void Update() override {
        int posX, posY;
        body->GetPhysicPosition(posX, posY);
        DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, body->GetRotation() * RAD2DEG, 0.0f, YELLOW);
    }

protected:
    Texture2D texture;
};

void InitializeCheckpointSensors(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    struct CheckpointParams {
        int x;
        int y;
        int width;
        int height;
        CollisionType type;
    };

    std::vector<CheckpointParams> checkpointData = {
        




        {135, 260, 240, 10, CHECKPOINT_SENSOR_1},
        {295, 85, 10, 140, CHECKPOINT_SENSOR_2},
        { 535, 95, 10, 160, CHECKPOINT_SENSOR_3},

        {670, 270, 130, 10, CHECKPOINT_SENSOR_4},

        { 760, 400, 10, 130, CHECKPOINT_SENSOR_5 },
        {840, 270, 150, 10, CHECKPOINT_SENSOR_6 },
        {952, 123, 10, 230, CHECKPOINT_SENSOR_7 },
        {1093, 118, 10, 200, CHECKPOINT_SENSOR_8 },

        {1192, 232, 140, 10, CHECKPOINT_SENSOR_9},

        {1062, 350, 10, 200, CHECKPOINT_SENSOR_10 },
        {991, 462, 150, 10, CHECKPOINT_SENSOR_11 },
        {991, 583, 150, 10, CHECKPOINT_SENSOR_12 },
        {904, 664, 10, 80, CHECKPOINT_SENSOR_13 },
        {733, 602, 10, 230, CHECKPOINT_SENSOR_14 },

        {600, 600, 10, 206, CHECKPOINT_SENSOR_15},

        {543, 471, 130, 10, CHECKPOINT_SENSOR_16 },
        {533, 341, 130, 10, CHECKPOINT_SENSOR_17 },
        {440, 261, 10, 150, CHECKPOINT_SENSOR_18 },
        {351, 325, 150, 10, CHECKPOINT_SENSOR_19 },
        {371, 406, 170, 10, CHECKPOINT_SENSOR_20 },
        {385, 504, 190, 10, CHECKPOINT_SENSOR_21 },
        {415, 584, 130, 10, CHECKPOINT_SENSOR_22 },

        {260, 650, 10, 116, CHECKPOINT_SENSOR_23},

        {145, 540, 250, 10, CHECKPOINT_SENSOR_24 }
    };

    for (const auto& checkpoint : checkpointData) {
        entities.emplace_back(DBG_NEW CheckpointSensor(physics, checkpoint.x, checkpoint.y, checkpoint.width, checkpoint.height, listener, defaultTexture, checkpoint.type));
    }
}

class FinishCheckpointSensor : public PhysicEntity {
public:
    FinishCheckpointSensor(ModulePhysics* physics, int coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateRectangleSensor(140, 450, coords, coordCount), _listener)
    {                                               // x    y
        collisionType = FINISH_CHECKPOINT_SENSOR;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 0.0f, YELLOW);
    }
public: 
    int lap = 0;
private:
    Texture2D texture;
};

//------------------------------------------------------------------------------------ IA -------------------------------------------------------------------------------------

class AISensor : public PhysicEntity {
public:
    AISensor(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture, TurnDirection direction)
        : PhysicEntity(physics->CreateRectangleSensor(x, y, width, height), listener), texture(texture) {
        collisionType = IA;
        turnDirection = direction;
    }

    virtual void Update() override {
        int posX, posY;
        body->GetPhysicPosition(posX, posY);
        DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, body->GetRotation() * RAD2DEG, 0.0f, YELLOW);
    }

protected:
    Texture2D texture;
};

struct AISensorParams {
    int x;
        int y;
    int width;
    int height;
    TurnDirection direction;
};

void InitializeAISensors(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    std::vector<AISensorParams> aiSensorData = {
        {95, 240, 180, 10, RIGHT}, {140, 170, 100, 10, LEFT}, {140, 100, 180, 10, RIGHT}, // 1 2 3
        {210, 75, 10, 180, RIGHT}, {650, 82, 10, 180, RIGHT}, {680, 150, 10, 180, RIGHT}, // 4 5 6
        {680, 360, 160, 30, LEFT}, {745, 390, 10, 180, LEFT}, {820, 390, 10, 180, LEFT}, // 7 8 9
        {840, 345, 145, 10, LEFT},{925, 145, 205, 30, RIGHT}, {920, 125, 60, 180, RIGHT},  //10 11 12
        {1150, 125, 10, 180, RIGHT},{1230, 200, 140, 10, RIGHT}, {1185, 370, 200, 10, RIGHT}, // 13 14 15
        {1130, 400, 10, 100, RIGHT}, {1030, 400, 10, 100, LEFT}, {1000, 460, 120, 30, LEFT}, // 16 17 18
        {1000, 620, 100, 10, RIGHT}, {940, 650, 10, 120, RIGHT}, {830, 650, 10, 180, RIGHT}, // 19 20 21
        {800, 580, 210, 10, LEFT}, {590, 590, 20, 210, RIGHT}, {540, 560, 20, 205, RIGHT}, // 22 23 24
        {542, 310, 100, 10, LEFT},{480, 270, 10, 170, LEFT}, {400, 270, 10, 180, LEFT}, // 25 26 27
        {350, 320, 180, 10, LEFT}, {350, 430, 180, 10, LEFT}, {430, 430, 10, 180, RIGHT}, // 28 29 30
        {415, 630, 180, 10, RIGHT}, {370, 653, 10, 180, RIGHT}, {120, 665, 10, 100, RIGHT}, // 31 32 33
        {88, 600, 180, 10, RIGHT} // 34
    };

    // Crear cada sensor IA y añadirlo a la lista de entidades
    for (const auto& sensor : aiSensorData) {
        entities.emplace_back(DBG_NEW AISensor(physics, sensor.x, sensor.y, sensor.width, sensor.height, listener, defaultTexture, sensor.direction));
    }
}

//----------------------------------------------------- BOOST PADS -------------------------------------------------------------------------------------

class BoostPad : public PhysicEntity {
public:
    BoostPad(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture)
        : PhysicEntity(physics->CreateRectangleSensor(x, y, width, height), listener), texture(texture) {
        collisionType = BOOST;
    }

    virtual void Update() override {
        int posX, posY;
        body->GetPhysicPosition(posX, posY);
        DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, body->GetRotation() * RAD2DEG, 0.0f, YELLOW);
    }

protected:
    Texture2D texture;
};

struct BoostSensorParams {
    int x;
    int y;
    int width;
    int height;
};

void InitializeBoostSensors(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    std::vector<BoostSensorParams> boostSensorData = {
        {248, 69, 20, 13}, {520, 92, 20, 13}, {1172, 248, 13, 20}, // 1 2 3
        {1073, 343, 13, 20}, {744, 604, 20, 13}, {532, 425, 13, 20}, // 4 5 6
        {242, 645, 20, 13}, {225, 328, 13, 20}
    };

    // Crear cada sensor IA y añadirlo a la lista de entidades
    for (const auto& sensor : boostSensorData) {
        entities.emplace_back(DBG_NEW BoostPad(physics, sensor.x, sensor.y, sensor.width, sensor.height, listener, defaultTexture));
    }
}

//------------------------------------------------------------------------------------ Collisions -------------------------------------------------------------------------------------

class CollisionZone : public PhysicEntity {
public:
    CollisionZone(ModulePhysics* physics, const int* coords, int coordCount, Module* listener, Texture2D texture, CollisionType type)
        : PhysicEntity(physics->CreateChain(0, 0, coords, coordCount), listener), texture(texture) {
        collisionType = type;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 0.0f, WHITE);
    }

protected:
    Texture2D texture;
};

struct CollisionParams {
    const int* coords;
    int coordCount;
    CollisionType type;
};

void InitializeCollisions(ModulePhysics* physics, Module* listener, std::vector<PhysicEntity*>& entities, Texture2D defaultTexture) {
    // Lista de datos para cada colisión
    static constexpr int internalCollisionCoords[] = {
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

    static constexpr int internalCollision2Coords[] = {
        161, 479, 161, 417, 177, 417, 177, 257, 191, 257, 191, 447, 175, 447, 175, 479
    };

    static constexpr int internalCollision3Coords[] = {
        929, 193, 943, 193, 943, 207,929, 207
    };

    static constexpr int internalCollision4Coords[] = {
        1009, 289, 1039, 289,1039, 303, 1009, 303
    };

    static constexpr int internalCollision5Coords[] = {
        1105, 337, 1135, 337, 1135, 351, 1105, 351
    };

    static constexpr int bloque1IzqCoords[] = {
        33, 511,32, 496, 46, 496, 47, 511
    };

    static constexpr int bloque2IzqCoords[] = {
        97, 143, 96, 128, 111, 129, 111, 143
    };

    static constexpr int bloque1AbajoCoords[] = {
        561, 669, 560, 656, 590, 656, 591, 670, 570, 670
    };

    static constexpr int bloque2AbajoCoords[] = {
        640, 657, 655, 657, 655, 672, 641, 672
    };

    static constexpr int bloque3AbajoCoords[] = {
        720, 640, 735, 640,735, 655, 720, 655
    };

    static constexpr int bloque1ArribaCoords[] = {
        1056, 48, 1071, 48, 1071, 63, 1056, 63
    };

    static constexpr int bloque2ArribaCoords[] = {
        896, 80, 911, 80, 911, 95, 896, 95
    };

    static constexpr int bloque3ArribaCoords[] = {
        800, 304, 815, 304, 816, 319, 800, 319
    };

    static constexpr int externalCollisionCoords[] = {
        1263, 509, 1263, 31, 1248, 31, 1247, 15, 784, 15, 782, 30, 768, 31, 767, 334,
        752, 334, 751, 350, 736, 350, 735, 32, 720, 31, 719, 16, 31, 17, 31, 32, 16, 31,
        15, 687, 30, 688, 32, 704, 448, 703, 448, 688, 465, 688, 464, 415, 449, 414,
        448, 399, 433, 399, 431, 383, 416, 383, 415, 367, 400, 366, 400, 337, 416, 337,
        416, 320, 430, 320, 432, 335, 462, 337, 463, 353, 479, 353, 479, 368, 494, 368,
        495, 686, 510, 689, 511, 703, 1040, 703, 1040, 687, 1055, 687, 1055, 448, 1070, 449,
        1070, 464, 1087, 465, 1087, 480, 1230, 480, 1230, 511
    };

    std::vector<CollisionParams> collisionData = {
        {internalCollisionCoords, sizeof(internalCollisionCoords) / sizeof(int), DEFAULT},
        {internalCollision2Coords, sizeof(internalCollision2Coords) / sizeof(int), DEFAULT},
        {internalCollision3Coords, sizeof(internalCollision3Coords) / sizeof(int), DEFAULT},
        {internalCollision4Coords, sizeof(internalCollision4Coords) / sizeof(int), DEFAULT},
        {internalCollision5Coords, sizeof(internalCollision5Coords) / sizeof(int), DEFAULT},
        {bloque1IzqCoords, sizeof(bloque1IzqCoords) / sizeof(int), DEFAULT},
        {bloque2IzqCoords, sizeof(bloque2IzqCoords) / sizeof(int), DEFAULT},
        {bloque1AbajoCoords, sizeof(bloque1AbajoCoords) / sizeof(int), DEFAULT},
        {bloque2AbajoCoords, sizeof(bloque2AbajoCoords) / sizeof(int), DEFAULT},
        {bloque3AbajoCoords, sizeof(bloque3AbajoCoords) / sizeof(int), DEFAULT},
        {bloque1ArribaCoords, sizeof(bloque1ArribaCoords) / sizeof(int), DEFAULT},
        {bloque2ArribaCoords, sizeof(bloque2ArribaCoords) / sizeof(int), DEFAULT}, 
        {bloque3ArribaCoords, sizeof(bloque3ArribaCoords) / sizeof(int), DEFAULT},
        {externalCollisionCoords, sizeof(externalCollisionCoords) / sizeof(int), DEFAULT} 
    };

    for (const auto& collision : collisionData) {
        entities.emplace_back(DBG_NEW CollisionZone(physics, collision.coords, collision.coordCount, listener, defaultTexture, collision.type));
    }
}

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
        : PhysicEntity(physics->CreateCircle(x, y, 9), _listener), texture(_texture), app(_app) 
    {
        currentCheckpoint = 0;
    }

    virtual void Update() override {
        int x, y;
        body->GetPhysicPosition(x, y);
        float rotationDegrees = body->GetRotation() * RAD2DEG;
        float scale = 1.5f; // Escala de la imagen
        DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
            Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
            Vector2{ (float)texture.width - 1.0f, (float)texture.height - 2.0f }, rotationDegrees, WHITE);

    }

    int CurrentRank;
    int currentCheckpoint;
    int CountSensor = 0;
    int isActivated_1 = false;
    int isActivated_2 = false;
    int isActivated_3 = false;
    int isActivated_4 = false;
    int isActivated_5 = false;
    int isActivated_6 = false;
    int isActivated_7 = false;
    int isActivated_8 = false;
    int isActivated_9 = false;
    int isActivated_10 = false;
    int isActivated_11 = false;
    int isActivated_12 = false;
    int isActivated_13 = false;
    int isActivated_14 = false;
    int isActivated_15 = false;
    int isActivated_16 = false;
    int isActivated_17 = false;
    int isActivated_18 = false;
    int isActivated_19 = false;
    int isActivated_20 = false;
    int isActivated_21 = false;
    int isActivated_22 = false;
    int isActivated_23 = false;
    int isActivated_24 = false;

protected:
    Texture2D texture;
    Application* app;
};

struct KartInfo {
    Kart* kart;
    float distanceToCP;
};

class Kart_Controller : public Kart {
public:
    Kart_Controller(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart(physics, x, y, _listener, _texture, _app, type), speed(0.0f), rotation(0.0f), isBoosting(false), isMoving(false), kartType(type), player(player)
    {
        timeToBoost.Start();
    }


    virtual void HandleInput() {
        
        float currentMaxSpeed;
        float kartRotation;
        float kartAcceleration;

        if (kartType == KARTO) {
            if (isBoosting) {
                currentMaxSpeed = boostedMaxSpeedKa;
            }
			else {
				currentMaxSpeed = maxSpeedKa;
			}
        }
        else if (kartType == HAOLIEN) {
            if (isBoosting)
            {
                currentMaxSpeed = boostedMaxSpeedHa;
            }
            else {
				currentMaxSpeed = maxSpeedHa;
            }
		}
		else if (kartType == JOHANA) {
			if (isBoosting) {
				currentMaxSpeed = boostedMaxSpeedJo;
			}
            else {
                currentMaxSpeed = maxSpeedJo;
            }
		}
		else if (kartType == TANKETO) {
			if (isBoosting) {
				currentMaxSpeed = boostedMaxSpeedTa;
			}
            else {
                currentMaxSpeed = maxSpeedTa;
            }
		}
		else {
            if (isBoosting) {
				currentMaxSpeed = boostedMaxSpeed;
            }
            else {
                currentMaxSpeed = maxSpeed;
            }
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
                speed += kartAcceleration;
                if (speed > currentMaxSpeed) {
                    speed = currentMaxSpeed;
                }
            }
            else if (IsKeyDown(KEY_DOWN)) {
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
       
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
			isDrifting = true;
        }
        else {
			isDrifting = false;
        }


        if (isDrifting) {
            if (player == PLAYER1) {
                if (IsKeyDown(KEY_A)) {
                    if (isBoosting) {
                        rotation -= kartRotation - 0.75f;
                    }
					else {
						rotation -= kartRotation;
					}
                }
                if (IsKeyDown(KEY_D)) {
					if (isBoosting) {
						rotation += kartRotation - 0.75f;
					}
                    else {
                        rotation += kartRotation;
                    }
                }
            }
			else if (player == PLAYER2) {
				if (IsKeyDown(KEY_LEFT)) {
                    if (isBoosting) {
                        rotation -= kartRotation - 0.75f;
                    }
                    else {
                        rotation -= kartRotation;
                    }
				}
				if (IsKeyDown(KEY_RIGHT)) {
                    if (isBoosting) {
                        rotation += kartRotation - 0.75f;
                    }
                    else {
                        rotation += kartRotation;
                    }
				}
			}
            
		}
		else {
            if (player == PLAYER1) {
				if (IsKeyDown(KEY_A)) {
                    if (isBoosting) {
                        rotation -= 1.25f;
                    }
                    else {
                        rotation -= kartRotation;
                    }
				}
				if (IsKeyDown(KEY_D)) {
                    if (isBoosting) {
                        rotation += 1.25f;
                    }
                    else {
                        rotation += kartRotation;
                    }
				}
            }
            else if (player == PLAYER2) {
                if (IsKeyDown(KEY_LEFT)) {
                    if (isBoosting) {
                        rotation -= 1.25f;
                    }
                    else {
                        rotation -= kartRotation;
                    }
                }
                if (IsKeyDown(KEY_RIGHT)) {
                    if (isBoosting) {
                        rotation += 1.25f;
                    }
                    else {
                        rotation += kartRotation;
                    }
                }
            }
        }
        

        if (isBoosting && timeToBoost.ReadSec() >= boostTime) {
            isBoosting = false;
            timeToBoost.Start();
            boostTime = 1;
        }

    }
    
    

    void Move()
    {
        float rad = rotation * DEG2RAD;
        body->body->SetLinearVelocity(b2Vec2(speed * sin(rad), -speed * cos(rad)));
        body->body->SetTransform(body->body->GetPosition(), rad);
    }

    virtual void Update() override {
        if (raceStarted == true) {
            HandleInput();
            Move();
        }
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
    float boostedMaxSpeedTa = 5.25f;
    float boostedMaxSpeedHa = 5.0f;

	// Rotations for each kart
	float rotationKa = 2.25f;
	float rotationTa = 2.75f;
    float rotationHa = 1.25f;
	float rotationJo = 2.0f;

	float maxSpeed = 2.0f;
    float acceleration = 1.0f;
	float rotationDefault = 2.0f;
	float boostedMaxSpeed = 4.0f;

    bool isBoosting = false;

    bool inSnowZone = false;
    bool inDarkenedSnowZone = false;
    int snowZoneCount = 0;
    int DarkenedsnowZoneCount = 0;

    Timer timeToBoost;
    int boostTime = 1;

    int CurrentLap;

    KartType kartType;

protected:
    
	Player player;
    std::vector<PhysicEntity*> entities;
    float speed;
    float rotation;
    bool isMoving;
    bool isDrifting;
    const float deceleration = 0.05f;
	uint32 engineSound = app->audio->LoadFx("Assets/drive.wav");
};

class Kart_NPC : public Kart {
public:
    Kart_NPC(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type)
		: Kart(physics, x, y, _listener, _texture, _app, type), speed(0.0f), rotation(0.0f), isBoosting(false), isMoving(false), kartType(type)
    {
        rotationTimer.Start();
    }


    virtual void MovingLogic() {

        float currentMaxSpeed;

        if (isBoosting) {
            currentMaxSpeed = boostedMaxSpeed;
        }
        else {
            currentMaxSpeed = maxSpeed;
        }

        if (speed != 0.0f && !isMoving)
        {
            isMoving = true;
        }
        else if (speed == 0.0f && isMoving)
        {
            isMoving = false;
        }

        speed += acceleration;
        if (speed > currentMaxSpeed) {
            speed = currentMaxSpeed;
        }

        if (rotationTimer.ReadSec() >= waitTime) {
            if (left == true) {
                rotation -= 45.0f;
                left = false;
            }
            else if (right == true) {
                rotation += 45.0f;
                right = false;
            }
            rotationTimer.Start();
            waitTime = 0;
        }

        if (isBoosting && timeToBoost.ReadSec() >= boostTime) {
            isBoosting = false;
            timeToBoost.Start();
            boostTime = 1;
        }
    }

    void Move()
    {
        float rad = rotation * DEG2RAD;
        body->body->SetLinearVelocity(b2Vec2(speed * sin(rad), -speed * cos(rad)));
        body->body->SetTransform(body->body->GetPosition(), rad);
    }

    virtual void Update() override {
        if (raceStarted == true) {
            MovingLogic();
            Move();
        }
        Kart::Update();
    }

public:
    int waitTime = 1;
	float timeToRotate = 0.75f;
    float maxSpeed = 2.5f;
    float acceleration = 1.0f;
    float boostedMaxSpeed = 5.0f;

    float rotation;

	bool left = false;
	bool right = false;

    bool inSnowZone = false;
    bool inDarkenedSnowZone = false;
    int snowZoneCount = 0;
    int DarkenedsnowZoneCount = 0;
    KartType kartType;

    int CurrentLap;
    bool isBoosting;

    Timer timeToBoost;
    int boostTime = 1;


protected:
    
    std::vector<PhysicEntity*> entities;
    float speed;
    bool isMoving;
    
    Timer rotationTimer;
    float deceleration = 0.05f;
};

class Kart_Player_1 : public Kart_Controller {
public:
    Kart_Player_1(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart_Controller(physics, x, y, _listener, _texture, _app, type, player)
    {
        CurrentRank = 4;
        CurrentLap = 0;

    }

public:
};

class Kart_Player_2 : public Kart_Controller {
public:
    Kart_Player_2(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type, Player player)
        : Kart_Controller(physics, x, y, _listener, _texture, _app, type, player) 
    {
        CurrentRank = 3;
        CurrentLap = 0;
    }
    
public:
};

class Kart_Player_3 : public Kart_NPC {
public:
    Kart_Player_3(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type)
        : Kart_NPC(physics, x, y, _listener, _texture, _app, type) 
    {
		CurrentRank = 2;
        CurrentLap = 0;
    }

public:
};

class Kart_Player_4 : public Kart_NPC {
public:
    Kart_Player_4(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app, KartType type)
        : Kart_NPC(physics, x, y, _listener, _texture, _app, type) 
    {
		CurrentRank = 1;
        CurrentLap = 0;
    }

public:
};

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    srand(time(NULL));
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

    InitializeSnowZones(App->physics, this, entities, default);  
    InitializeDarkenedSnowZones(App->physics, this, entities, default); 
    InitializeCheckpointSensors(App->physics, this, entities, default); 
    InitializeCollisions(App->physics, this, entities, default); 
    InitializeAISensors(App->physics, this, entities, default); 

    App->renderer->camera.x = App->renderer->camera.y = 0;

    lap_time = 0.0f;
    best_lap_time = 0.0f;

    cone = LoadTexture("Assets/cone.png");
    yellowCar = LoadTexture("Assets/yellow.png");
    redCar = LoadTexture("Assets/red.png");
    greenCar = LoadTexture("Assets/green.png");
    blueCar = LoadTexture("Assets/blue.png");
	npc1 = LoadTexture("Assets/npc1.png");
	npc2 = LoadTexture("Assets/npc2.png");
	npc3 = LoadTexture("Assets/npc3.png");
	npc4 = LoadTexture("Assets/npc4.png");

	three = LoadTexture("Assets/three.png");
	two = LoadTexture("Assets/two.png");
	one = LoadTexture("Assets/one.png");
	go = LoadTexture("Assets/go.png");

	kaWin = LoadTexture("Assets/kartoWin.png");
	haWin = LoadTexture("Assets/haolienWin.png");
	joWin = LoadTexture("Assets/johanaWin.png");
	taWin = LoadTexture("Assets/tanketoWin.png");
	npcWin = LoadTexture("Assets/npcWin.png");

	mainScreen = LoadTexture("Assets/mainScreen.png");
    player1Select = LoadTexture("Assets/player1select.png");
	player2Select = LoadTexture("Assets/player2select.png");
	background = LoadTexture("Assets/Mapa1Racing.png");

    engine_fx = App->audio->LoadFx("Assets/drive.wav");
    boost_fx = App->audio->LoadFx("Assets/boost.wav"); 
    bump_fx = App->audio->LoadFx("Assets/Bump.wav");

	showStage = App->audio->LoadFx("Assets/show.wav");
	countdown = App->audio->LoadFx("Assets/start.wav");

    bgm = LoadMusicStream("Assets/music.ogg");
	playerSelect = LoadMusicStream("Assets/playerselect.ogg");
	title = LoadMusicStream("Assets/title.ogg");
	win = LoadMusicStream("Assets/win.ogg");
	loss = LoadMusicStream("Assets/loss.ogg");

    App->fontsModule->LoadFontTexture("Assets/fuente32_16.png", ' ', 32);

    PlayMusicStream(title);
	PlayMusicStream(playerSelect);
    PlayMusicStream(bgm);
	PlayMusicStream(win);
	PlayMusicStream(loss);

    return ret;
}
// Load assets
bool ModuleGame::CleanUp()
{
    LOG("Unloading Intro scene");
	RemoveAllCollisionsAndSensors();
	UnloadTexture(cone);
	UnloadTexture(yellowCar);
	UnloadTexture(redCar);
	UnloadTexture(greenCar);
	UnloadTexture(blueCar);
	UnloadTexture(mainScreen);
	UnloadTexture(background);
	UnloadMusicStream(bgm);
	UnloadMusicStream(title);
	UnloadMusicStream(playerSelect);
	UnloadMusicStream(win);
	UnloadMusicStream(loss);
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
            if (hasStarted == false) {
                hasStarted = true;
                hasDeleted = false;
            }
            chosenKartop2 = true;
            hasChosenPlayer2 = true;
            gameState = NPCSELECTION;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            if (hasStarted == false) {
                hasStarted = true;
                hasDeleted = false;
            }
            chosenHaolienp2 = true;
            hasChosenPlayer2 = true;
            gameState = NPCSELECTION;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            if (hasStarted == false) {
                hasStarted = true;
                hasDeleted = false;
            }
            chosenJohanap2 = true;
            hasChosenPlayer2 = true;
            gameState = NPCSELECTION;
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            if (hasStarted == false) {
                hasStarted = true;
                hasDeleted = false;
            }
            chosenTanketop2 = true;
            hasChosenPlayer2 = true;
            gameState = NPCSELECTION;
        }
        break;

    case NPCSELECTION:
        int type[2];
        Texture2D kartTexture[2];
        type[0] = randomKart();
        type[1] = randomKart();
        for (int i = 0; i < 2; ++i) {

            switch (type[i]) {
            case 0:
                kartTexture[i] = npc1;
                break;
            case 1:
                kartTexture[i] = npc2;
                break;
            case 2:
                kartTexture[i] = npc3;
                break;
            case 3:
                kartTexture[i] = npc4;
                break;
            default:
                kartTexture[i] = npc1;
            }

            if (i == 0) {
                entities.emplace_back(DBG_NEW Kart_Player_3(App->physics, 86, 474, this, kartTexture[i], App, DEFAULT_KART));
            }
            else {
                entities.emplace_back(DBG_NEW Kart_Player_4(App->physics, 109, 484, this, kartTexture[i], App, DEFAULT_KART));
                gameState = SHOWSTAGE;
                break; 
            }
        }
	case SHOWSTAGE:
		if (hasShownStage == false) {
			showStageTimer.Start();
            App->audio->PlayFx(showStage);
            CreateCollisionsAndSensors();
			hasShownStage = true;
		}
        DrawTexture(background, 0, 0, WHITE);
        if (showStageTimer.ReadSec() >= 12) {
            gameState = COUNTDOWN;
            hasShownStage = false;
        }
        if (chosenKartop1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(DBG_NEW Kart_Player_1(App->physics, 109, 510, this, blueCar, App, KARTO, PLAYER1));
            hasChosenPlayer1 = false;
        }
        else if (chosenHaolienp1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(DBG_NEW Kart_Player_1(App->physics, 109, 510, this, yellowCar, App, HAOLIEN, PLAYER1));
            hasChosenPlayer1 = false;
        }
        else if (chosenJohanap1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(DBG_NEW Kart_Player_1(App->physics, 109, 510, this, greenCar, App, JOHANA, PLAYER1));
            hasChosenPlayer1 = false;
        }
        else if (chosenTanketop1 == true && hasChosenPlayer1 == true)
        {
            entities.emplace_back(DBG_NEW Kart_Player_1(App->physics, 109, 510, this, redCar, App, TANKETO, PLAYER1));
            hasChosenPlayer1 = false;
        }

        if (chosenKartop2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(DBG_NEW Kart_Player_2(App->physics, 86, 500, this, blueCar, App, KARTO, PLAYER2));
            hasChosenPlayer2 = false;
        }
        else if (chosenHaolienp2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(DBG_NEW Kart_Player_2(App->physics, 86, 500, this, yellowCar, App, HAOLIEN, PLAYER2));
            hasChosenPlayer2 = false;
        }
        else if (chosenJohanap2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(DBG_NEW Kart_Player_2(App->physics, 86, 500, this, greenCar, App, JOHANA, PLAYER2));
            hasChosenPlayer2 = false;
        }
        else if (chosenTanketop2 == true && hasChosenPlayer2 == true) {
            entities.emplace_back(DBG_NEW Kart_Player_2(App->physics, 86, 500, this, redCar, App, TANKETO, PLAYER2));
            hasChosenPlayer2 = false;
        }
		break;

    case COUNTDOWN:
		if (hasShownCountdown == false) {
			countdownTimer.Start();
            App->audio->PlayFx(countdown);
			hasShownCountdown = true;
		}
        DrawTexture(background, 0, 0, WHITE);
        if (countdownTimer.ReadSec() >= 0) {
			DrawTexture(three, 500, 250, WHITE);
        }
		if (countdownTimer.ReadSec() >= 1) {
			DrawTexture(two, 500, 250, WHITE);
		}
        if (countdownTimer.ReadSec() >= 2) {
            DrawTexture(one, 500, 250, WHITE);
        }
		if (countdownTimer.ReadSec() >= 3) {
			DrawTexture(go, 500, 250, WHITE);
		}
		if (countdownTimer.ReadSec() >= countdownTime) {
			gameState = PLAYING;
            countdownTimer.Start();
			hasShownCountdown = false;
            lap_start_time = GetTime();
		}
        break;

    case PLAYING:
		raceStarted = true;
        DrawTexture(background, 0, 0, WHITE);
        lap_time = GetTime() - lap_start_time;
        App->fontsModule->DrawText(1060, 848, TextFormat("BEST: %.2f", best_lap_time), 16, WHITE);
        App->fontsModule->DrawText(1093, 777, TextFormat("%.2f", lap_time ), 20, WHITE);

        UpdateRanking();

            for (PhysicEntity* entity : entities)
        {
            if (FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entity))
            {
                App->fontsModule->DrawText(27, 770, TextFormat("LAP:%d", finish->lap), 20, WHITE);
            } 
            if (Kart_Player_1* kart_1 = dynamic_cast<Kart_Player_1*>(entity))
            {
                if (kart_1->CurrentRank == 1) {
                    App->fontsModule->DrawText(469, 789, TextFormat("KART 1"), 20, WHITE);     
                }
                else if (kart_1->CurrentRank == 2) {
					App->fontsModule->DrawText(680, 789, TextFormat("KART 1"), 20, WHITE); // 469, 825
                }
				else if (kart_1->CurrentRank == 3) {
					App->fontsModule->DrawText(469, 825, TextFormat("KART 1"), 20, WHITE);
				}
				else if (kart_1->CurrentRank == 4) {
					App->fontsModule->DrawText(680, 825, TextFormat("KART 1"), 20, WHITE);
				}
            }
            if (Kart_Player_2* kart_2 = dynamic_cast<Kart_Player_2*>(entity))
            {
                if (kart_2->CurrentRank == 1) {
                    App->fontsModule->DrawText(469, 789, TextFormat("KART 2"), 20, WHITE);
                }
                else if (kart_2->CurrentRank == 2) {
                    App->fontsModule->DrawText(680, 789, TextFormat("KART 2"), 20, WHITE);
                }
                else if (kart_2->CurrentRank == 3) {
                    App->fontsModule->DrawText(469, 825, TextFormat("KART 2"), 20, WHITE);
                }
				else if (kart_2->CurrentRank == 4) {
					App->fontsModule->DrawText(680, 825, TextFormat("KART 2"), 20, WHITE);
				}
            }
            if (Kart_Player_3* kart_3 = dynamic_cast<Kart_Player_3*>(entity))
            {
                if (kart_3->CurrentRank == 1) {
                    App->fontsModule->DrawText(469, 789, TextFormat("KART 3"), 20, WHITE);
                }
                else if (kart_3->CurrentRank == 2) {
                    App->fontsModule->DrawText(680, 789, TextFormat("KART 3"), 20, WHITE);
                }
                else if (kart_3->CurrentRank == 3) {
                    App->fontsModule->DrawText(469, 825, TextFormat("KART 3"), 20, WHITE);
                }
                else if (kart_3->CurrentRank == 4) {
                    App->fontsModule->DrawText(680, 825, TextFormat("KART 3"), 20, WHITE);
                }
            }
            if (Kart_Player_4* kart_4 = dynamic_cast<Kart_Player_4*>(entity))
            {
                if (kart_4->CurrentRank == 1) {
                    App->fontsModule->DrawText(469, 789, TextFormat("KART 4"), 20, WHITE);
                }
                else if (kart_4->CurrentRank == 2) {
                    App->fontsModule->DrawText(680, 789, TextFormat("KART 4"), 20, WHITE);
                }
                else if (kart_4->CurrentRank == 3) {
                    App->fontsModule->DrawText(469, 825, TextFormat("KART 4"), 20, WHITE);
                }
                else if (kart_4->CurrentRank == 4) {
                    App->fontsModule->DrawText(680, 825, TextFormat("KART 4"), 20, WHITE);
                }
            }

            entity->Update();
        }
        UpdateMusicStream(bgm);
       
        if (IsKeyPressed(KEY_R)) {
            if (hasDeleted == false) {
				raceStarted = false;
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

        if (IsKeyPressed(KEY_I))
        {
            player1Won = true;
            gameState = WINSCREEN;
        }
        if (IsKeyPressed(KEY_O))
        {
            player2Won = true;
            gameState = WINSCREEN;
        }
        if (IsKeyPressed(KEY_P))
        {
            npcWon = true;
            gameState = LOSSSCREEN;
        }

        break;
	case WINSCREEN:
        raceStarted = false;
		UpdateMusicStream(win);
        RemoveAllCollisionsAndSensors();
        hasDeleted = true;
        hasStarted = false;
        if (player1Won == true) {
            if (chosenKartop1 == true) {
                DrawTexture(kaWin, 0, 0, WHITE);
            }
            else if (chosenHaolienp1 == true) {
                DrawTexture(haWin, 0, 0, WHITE);
            }
            else if (chosenJohanap1 == true) {
                DrawTexture(joWin, 0, 0, WHITE);
            }
            else if (chosenTanketop1 == true) {
                DrawTexture(taWin, 0, 0, WHITE);
            }
        }
        else if (player2Won == true) {
            if (chosenKartop2 == true) {
                DrawTexture(kaWin, 0, 0, WHITE);
            }
            else if (chosenHaolienp2 == true) {
                DrawTexture(haWin, 0, 0, WHITE);
            }
            else if (chosenJohanap2 == true) {
                DrawTexture(joWin, 0, 0, WHITE);
            }
            else if (chosenTanketop2 == true) {
                DrawTexture(taWin, 0, 0, WHITE);
            }
        }
		else if (npcWon == true) {
			gameState = LOSSSCREEN;
		}
		if (IsKeyPressed(KEY_R)) {
			gameState = TITLESCREEN;
			player1Won = false;
			player2Won = false;
		}
		break;
	case LOSSSCREEN:
        raceStarted = false;
		UpdateMusicStream(loss);
        RemoveAllCollisionsAndSensors();
        hasDeleted = true;
        hasStarted = false;
		DrawTexture(npcWin, 0, 0, WHITE);
        if (IsKeyPressed(KEY_R)) {
            gameState = TITLESCREEN;
            npcWon = false;
        }
    }
    
    if (IsKeyPressed(KEY_SPACE))
    {
        ray_on = !ray_on;
        ray.x = GetMouseX();
        ray.y = GetMouseY();
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
            Kart_NPC* kartNPC = dynamic_cast<Kart_NPC*>(entities[i]);
            Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(entities[i]);
            Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(entities[i]);
            FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entities[i]);
           
            // NPC KART AI MANAGEMENT
            if (kart3) {
                for (int k = 0; k < length; k++)
                {
                    if (bodyB == entities[k]->body && entities[k]->GetCollisionType() == IA && entities[k]->GetTurnDirection() == LEFT) {
                        kart3->left = true;
                        kart3->right = false;
                        return;
                    }
                    else if (bodyB == entities[k]->body && entities[k]->GetCollisionType() == IA && entities[k]->GetTurnDirection() == RIGHT)
                    {
                        kart3->right = true;
                        kart3->left = false;
                        return;
                    }
                }
            }
            if (kart4) {
                for (int l = 0; l < length; l++)
                {
                    if (bodyB == entities[l]->body && entities[l]->GetCollisionType() == IA && entities[l]->GetTurnDirection() == LEFT) {
                        kart4->left = true;
                        kart4->right = false;
                        return;
                    }
                    else if (bodyB == entities[l]->body && entities[l]->GetCollisionType() == IA && entities[l]->GetTurnDirection() == RIGHT)
                    {
                        kart4->left = false;
                        kart4->right = true;
                        return;
                    }
                }
            }

            // PLAYABLE KARTS COLLISION DETECTION

            if (kart || kartNPC) {
                for (int j = 0; j < length; ++j) {
                    // SNOW ZONE
                    if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == SNOW) {
                        if (kart && kart->snowZoneCount == 0) {
                            printf("Kart entered snow zone.\n");
                            kart->inSnowZone = true;
                            switch (kart->kartType) {
                            case KARTO:
                                kart->maxSpeedKa = 1.5f;
                                kart->boostedMaxSpeedKa = 3.0f;
                                break;
                            case HAOLIEN:
                                kart->maxSpeedHa = 1.5f;
                                kart->boostedMaxSpeedHa = 2.5f;
                                break;
                            case JOHANA:
                                kart->maxSpeedJo = 2.5f;
                                kart->boostedMaxSpeedJo = 4.0f;
                                break;
                            case TANKETO:
                                kart->maxSpeedTa = 1.5f;
                                kart->boostedMaxSpeedTa = 6.0f;
                                break;
                            default:
                                kart->maxSpeed = 1.5f;
                                kart->boostedMaxSpeed = 3.0f;
                                break;
                            }
                        }
                        if (kartNPC && kartNPC->snowZoneCount == 0) {
                            printf("Kart_NPC entered snow zone.\n");
                            kartNPC->inSnowZone = true;
                            switch (kartNPC->kartType) {
                            case KARTO:
                                kartNPC->maxSpeed = 1.5f;
                                kartNPC->boostedMaxSpeed = 3.0f;
                                break;
                            case HAOLIEN:
                                kartNPC->maxSpeed = 1.5f;
                                kartNPC->boostedMaxSpeed = 2.5f;
                                break;
                            case JOHANA:
                                kartNPC->maxSpeed = 2.5f;
                                kartNPC->boostedMaxSpeed = 4.0f;
                                break;
                            case TANKETO:
                                kartNPC->maxSpeed = 1.5f;
                                kartNPC->boostedMaxSpeed = 6.0f;
                                break;
                            default:
                                kartNPC->maxSpeed = 1.5f;
                                kartNPC->boostedMaxSpeed = 3.0f;
                                break;
                            }
                        }
                        if (kart) kart->snowZoneCount++;
                        if (kartNPC) kartNPC->snowZoneCount++;
                        return;
                    }
                    // DARKENED SNOW ZONE
                    if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == DARKENED_SNOW) {
                        if (kart && kart->DarkenedsnowZoneCount == 0) {
                            printf("Kart entered darkened snow zone.\n");
                            kart->inDarkenedSnowZone = true;
                            switch (kart->kartType) {
                            case KARTO:
                                kart->maxSpeedKa = 1.0f;
                                kart->boostedMaxSpeedKa = 2.5f;
                                break;
                            case HAOLIEN:
                                kart->maxSpeedHa = 1.0f;
                                kart->boostedMaxSpeedHa = 2.0f;
                                break;
                            case JOHANA:
                                kart->maxSpeedJo = 2.5f;
                                kart->boostedMaxSpeedJo = 4.0f;
                                break;
                            case TANKETO:
                                kart->maxSpeedTa = 1.5f;
                                kart->boostedMaxSpeedTa = 6.0f;
                                break;
                            default:
                                kart->maxSpeed = 1.0f;
                                kart->boostedMaxSpeed = 2.5f;
                                break;
                            }
                        }
                        if (kartNPC && kartNPC->DarkenedsnowZoneCount == 0) {
                            printf("Kart_NPC entered darkened snow zone.\n");
                            kartNPC->inDarkenedSnowZone = true;
                            switch (kartNPC->kartType) {
                            case KARTO:
                                kartNPC->maxSpeed = 1.0f;
                                kartNPC->boostedMaxSpeed = 2.5f;
                                break;
                            case HAOLIEN:
                                kartNPC->maxSpeed = 1.0f;
                                kartNPC->boostedMaxSpeed = 2.0f;
                                break;
                            case JOHANA:
                                kartNPC->maxSpeed = 2.5f;
                                kartNPC->boostedMaxSpeed = 4.0f;
                                break;
                            case TANKETO:
                                kartNPC->maxSpeed = 1.5f;
                                kartNPC->boostedMaxSpeed = 6.0f;
                                break;
                            default:
                                kartNPC->maxSpeed = 1.0f;
                                kartNPC->boostedMaxSpeed = 2.5f;
                                break;
                            }
                        }
                        if (kart) kart->DarkenedsnowZoneCount++;
                        if (kartNPC) kartNPC->DarkenedsnowZoneCount++;
                        return;
                    }
                    //------------------------------------ BOOSTERS -------------------------------------------
                    if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == BOOST) {
                        printf("Kart entered booster.\n");
                        if (kart && !kart->isBoosting) {
                            kart->isBoosting = true;
                            kart->timeToBoost.Start();
                            App->audio->PlayFx(boost_fx);
                        }
                        if (kartNPC && !kartNPC->isBoosting) {
                            kartNPC->isBoosting = true;
                            kartNPC->timeToBoost.Start();
                            App->audio->PlayFx(boost_fx);
                        }

                        return;
                    }


                    //------------------------------------  CHECKPOINTS  --------------------------------------
                    // CHECKPOINT 
                    Kart_Player_1* kart_1 = nullptr;
                    Kart_Player_2* kart_2 = nullptr;
                    Kart_Player_3* kart_3 = nullptr;
                    Kart_Player_4* kart_4 = nullptr;

                    for (PhysicEntity* entity : entities) { // search karts
                        if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
                        if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
                        if (!kart_3) kart_3 = dynamic_cast<Kart_Player_3*>(entity);
                        if (!kart_4) kart_4 = dynamic_cast<Kart_Player_4*>(entity);
                        if (kart_1 && kart_2 && kart_3 && kart_4) break;
                    }
                    for (PhysicEntity* entity : entities)
                    {
                        if (FinishCheckpointSensor* finish = dynamic_cast<FinishCheckpointSensor*>(entity))
                        {
                            // CHECKPOINT 1
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_1) {

                                if (kart_1->CurrentRank == 1 || kart_2->CurrentRank == 1 ||
                                    kart_3->CurrentRank == 1 || kart_4->CurrentRank == 1) {
                                    lapUpdated = false;
                                }

                                if (bodyA == kart_1->body && !kart_1->isActivated_1) {
                                    kart_1->currentCheckpoint = 1;
                                    kart_1->isActivated_1 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_1) {
                                    kart_2->currentCheckpoint = 1;
                                    kart_2->isActivated_1 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_1) {
                                    kart_3->currentCheckpoint = 1;
                                    kart_3->isActivated_1 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_1) {
                                    kart_4->currentCheckpoint = 1;
                                    kart_4->isActivated_1 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                                // CHECKPOINT 2
                                if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_2) {
                                    if (bodyA == kart_1->body && !kart_1->isActivated_2 && kart_1->currentCheckpoint == 1) {
                                        kart_1->currentCheckpoint = 2;
                                        kart_1->isActivated_2 = true;
                                        kart_1->CountSensor++;
                                        printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                    }
                                    else if (bodyA == kart_2->body && !kart_2->isActivated_2 && kart_2->currentCheckpoint == 1) {
                                        kart_2->currentCheckpoint = 2;
                                        kart_2->isActivated_2 = true;
                                        kart_2->CountSensor++;
                                        printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                    }
                                    else if (bodyA == kart_3->body && !kart_3->isActivated_2 && kart_3->currentCheckpoint == 1) {
                                        kart_3->currentCheckpoint = 2;
                                        kart_3->isActivated_2 = true;
                                        kart_3->CountSensor++;
                                        printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                    }
                                    else if (bodyA == kart_4->body && !kart_4->isActivated_2 && kart_4->currentCheckpoint == 1) {
                                        kart_4->currentCheckpoint = 2;
                                        kart_4->isActivated_2 = true;
                                        kart_4->CountSensor++;
                                        printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                    }
                                    return;
                                }

                            // CHECKPOINT 3
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_3) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_3 && kart_1->currentCheckpoint == 2) {
                                    kart_1->currentCheckpoint = 3;
                                    kart_1->isActivated_3 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_3 && kart_2->currentCheckpoint == 2) {
                                    kart_2->currentCheckpoint = 3;
                                    kart_2->isActivated_3 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_3 && kart_3->currentCheckpoint == 2) {
                                    kart_3->currentCheckpoint = 3;
                                    kart_3->isActivated_3 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_4 && kart_4->currentCheckpoint == 2) {
                                    kart_4->currentCheckpoint = 3;
                                    kart_4->isActivated_3 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 4
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_4) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_4 && kart_1->currentCheckpoint == 3) {
                                    kart_1->currentCheckpoint = 4;
                                    kart_1->isActivated_4 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_4 && kart_2->currentCheckpoint == 3) {
                                    kart_2->currentCheckpoint = 4;
                                    kart_2->isActivated_4 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_4 && kart_3->currentCheckpoint == 3) {
                                    kart_3->currentCheckpoint = 4;
                                    kart_3->isActivated_4 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_4 && kart_4->currentCheckpoint == 3) {
                                    kart_4->currentCheckpoint = 4;
                                    kart_4->isActivated_4 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }


                            // CHECKPOINT 5
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_5) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_5 && kart_1->currentCheckpoint == 4) {
                                    kart_1->currentCheckpoint = 5;
                                    kart_1->isActivated_5 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_5 && kart_2->currentCheckpoint == 4) {
                                    kart_2->currentCheckpoint = 5;
                                    kart_2->isActivated_5 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_5 && kart_3->currentCheckpoint == 4) {
                                    kart_3->currentCheckpoint = 5;
                                    kart_3->isActivated_5 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_5 && kart_4->currentCheckpoint == 4) {
                                    kart_4->currentCheckpoint = 5;
                                    kart_4->isActivated_5 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 6
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_6) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_6 && kart_1->currentCheckpoint == 5) {
                                    kart_1->currentCheckpoint = 6;
                                    kart_1->isActivated_6 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_6 && kart_2->currentCheckpoint == 5) {
                                    kart_2->currentCheckpoint = 6;
                                    kart_2->isActivated_6 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_6 && kart_3->currentCheckpoint == 5) {
                                    kart_3->currentCheckpoint = 6;
                                    kart_3->isActivated_6 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_6 && kart_4->currentCheckpoint == 5) {
                                    kart_4->currentCheckpoint = 6;
                                    kart_4->isActivated_6 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 7
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_7) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_7 && kart_1->currentCheckpoint == 6) {
                                    kart_1->currentCheckpoint = 7;
                                    kart_1->isActivated_7 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_7 && kart_2->currentCheckpoint == 6) {
                                    kart_2->currentCheckpoint = 7;
                                    kart_2->isActivated_7 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_7 && kart_3->currentCheckpoint == 6) {
                                    kart_3->currentCheckpoint = 7;
                                    kart_3->isActivated_7 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_7 && kart_4->currentCheckpoint == 6) {
                                    kart_4->currentCheckpoint = 7;
                                    kart_4->isActivated_7 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 8
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_8) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_8 && kart_1->currentCheckpoint == 7) {
                                    kart_1->currentCheckpoint = 8;
                                    kart_1->isActivated_8 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_8 && kart_2->currentCheckpoint == 7) {
                                    kart_2->currentCheckpoint = 8;
                                    kart_2->isActivated_8 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_8 && kart_3->currentCheckpoint == 7) {
                                    kart_3->currentCheckpoint = 8;
                                    kart_3->isActivated_8 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_8 && kart_4->currentCheckpoint == 7) {
                                    kart_4->currentCheckpoint = 8;
                                    kart_4->isActivated_8 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 9
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_9) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_9 && kart_1->currentCheckpoint == 8) {
                                    kart_1->currentCheckpoint = 9;
                                    kart_1->isActivated_9 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_9 && kart_2->currentCheckpoint == 8) {
                                    kart_2->currentCheckpoint = 9;
                                    kart_2->isActivated_9 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_9 && kart_3->currentCheckpoint == 8) {
                                    kart_3->currentCheckpoint = 9;
                                    kart_3->isActivated_9 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_9 && kart_4->currentCheckpoint == 8) {
                                    kart_4->currentCheckpoint = 9;
                                    kart_4->isActivated_9 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 10
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_10) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_10 && kart_1->currentCheckpoint == 9) {
                                    kart_1->currentCheckpoint = 10;
                                    kart_1->isActivated_10 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_10 && kart_2->currentCheckpoint == 9) {
                                    kart_2->currentCheckpoint = 10;
                                    kart_2->isActivated_10 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_10 && kart_3->currentCheckpoint == 9) {
                                    kart_3->currentCheckpoint = 10;
                                    kart_3->isActivated_10 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_10 && kart_4->currentCheckpoint == 9) {
                                    kart_4->currentCheckpoint = 10;
                                    kart_4->isActivated_10 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 11
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_11) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_11 && kart_1->currentCheckpoint == 10) {
                                    kart_1->currentCheckpoint = 11;
                                    kart_1->isActivated_11 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_11 && kart_2->currentCheckpoint == 10) {
                                    kart_2->currentCheckpoint = 11;
                                    kart_2->isActivated_11 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_11 && kart_3->currentCheckpoint == 10) {
                                    kart_3->currentCheckpoint = 11;
                                    kart_3->isActivated_11 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_11 && kart_4->currentCheckpoint == 10) {
                                    kart_4->currentCheckpoint = 11;
                                    kart_4->isActivated_11 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 12
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_12) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_12 && kart_1->currentCheckpoint == 11) {
                                    kart_1->currentCheckpoint = 12;
                                    kart_1->isActivated_12 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_12 && kart_2->currentCheckpoint == 11) {
                                    kart_2->currentCheckpoint = 12;
                                    kart_2->isActivated_12 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_12 && kart_3->currentCheckpoint == 11) {
                                    kart_3->currentCheckpoint = 12;
                                    kart_3->isActivated_12 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_12 && kart_4->currentCheckpoint == 11) {
                                    kart_4->currentCheckpoint = 12;
                                    kart_4->isActivated_12 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 13
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_13) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_13 && kart_1->currentCheckpoint == 12) {
                                    kart_1->currentCheckpoint = 13;
                                    kart_1->isActivated_13 = true;

                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_13 && kart_2->currentCheckpoint == 12) {
                                    kart_2->currentCheckpoint = 13;
                                    kart_2->isActivated_13 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_13 && kart_3->currentCheckpoint == 12) {
                                    kart_3->currentCheckpoint = 13;
                                    kart_3->isActivated_13 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_13 && kart_4->currentCheckpoint == 12) {
                                    kart_4->currentCheckpoint = 13;
                                    kart_4->isActivated_13 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 14
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_14) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_14 && kart_1->currentCheckpoint == 13) {
                                    kart_1->currentCheckpoint = 14;
                                    kart_1->isActivated_14 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_14 && kart_2->currentCheckpoint == 13) {
                                    kart_2->currentCheckpoint = 14;
                                    kart_2->isActivated_14 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_14 && kart_3->currentCheckpoint == 13) {
                                    kart_3->currentCheckpoint = 14;
                                    kart_3->isActivated_14 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_14 && kart_4->currentCheckpoint == 13) {
                                    kart_4->currentCheckpoint = 14;
                                    kart_4->isActivated_14 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 15
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_15) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_15 && kart_1->currentCheckpoint == 14) {
                                    kart_1->currentCheckpoint = 15;
                                    kart_1->isActivated_15 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_15 && kart_2->currentCheckpoint == 14) {
                                    kart_2->currentCheckpoint = 15;
                                    kart_2->isActivated_15 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_15 && kart_3->currentCheckpoint == 14) {
                                    kart_3->currentCheckpoint = 15;
                                    kart_3->isActivated_15 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_15 && kart_4->currentCheckpoint == 14) {
                                    kart_4->currentCheckpoint = 15;
                                    kart_4->isActivated_15 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }


                            // CHECKPOINT 16
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_16) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_16 && kart_1->currentCheckpoint == 15) {
                                    kart_1->currentCheckpoint = 16;
                                    kart_1->isActivated_16 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_16 && kart_2->currentCheckpoint == 15) {
                                    kart_2->currentCheckpoint = 16;
                                    kart_2->isActivated_16 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_16 && kart_3->currentCheckpoint == 15) {
                                    kart_3->currentCheckpoint = 16;
                                    kart_3->isActivated_16 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_16 && kart_4->currentCheckpoint == 15) {
                                    kart_4->currentCheckpoint = 16;
                                    kart_4->isActivated_16 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 17
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_17) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_17 && kart_1->currentCheckpoint == 16) {
                                    kart_1->currentCheckpoint = 17;
                                    kart_1->isActivated_17 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_17 && kart_2->currentCheckpoint == 16) {
                                    kart_2->currentCheckpoint = 17;
                                    kart_2->isActivated_17 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_17 && kart_3->currentCheckpoint == 16) {
                                    kart_3->currentCheckpoint = 17;
                                    kart_3->isActivated_17 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_17 && kart_4->currentCheckpoint == 16) {
                                    kart_4->currentCheckpoint = 17;
                                    kart_4->isActivated_17 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 18
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_18) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_18 && kart_1->currentCheckpoint == 17) {
                                    kart_1->currentCheckpoint = 18;
                                    kart_1->isActivated_18 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_18 && kart_2->currentCheckpoint == 17) {
                                    kart_2->currentCheckpoint = 18;
                                    kart_2->isActivated_18 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_18 && kart_3->currentCheckpoint == 17) {
                                    kart_3->currentCheckpoint = 18;
                                    kart_3->isActivated_18 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_18 && kart_4->currentCheckpoint == 17) {
                                    kart_4->currentCheckpoint = 18;
                                    kart_4->isActivated_18 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 19
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_19) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_19 && kart_1->currentCheckpoint == 18) {
                                    kart_1->currentCheckpoint = 19;
                                    kart_1->isActivated_19 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_19 && kart_2->currentCheckpoint == 18) {
                                    kart_2->currentCheckpoint = 19;
                                    kart_2->isActivated_19 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_19 && kart_3->currentCheckpoint == 18) {
                                    kart_3->currentCheckpoint = 19;
                                    kart_3->isActivated_19 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_19 && kart_4->currentCheckpoint == 18) {
                                    kart_4->currentCheckpoint = 19;
                                    kart_4->isActivated_19 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 20
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_20) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_20 && kart_1->currentCheckpoint == 19) {
                                    kart_1->currentCheckpoint = 20;
                                    kart_1->isActivated_20 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_20 && kart_2->currentCheckpoint == 19) {
                                    kart_2->currentCheckpoint = 20;
                                    kart_2->isActivated_20 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_20 && kart_3->currentCheckpoint == 19) {
                                    kart_3->currentCheckpoint = 20;
                                    kart_3->isActivated_20 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_20 && kart_4->currentCheckpoint == 19) {
                                    kart_4->currentCheckpoint = 20;
                                    kart_4->isActivated_20 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 21
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_21) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_21 && kart_1->currentCheckpoint == 20) {
                                    kart_1->currentCheckpoint = 21;
                                    kart_1->isActivated_21 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_21 && kart_2->currentCheckpoint == 20) {
                                    kart_2->currentCheckpoint = 21;
                                    kart_2->isActivated_21 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_21 && kart_3->currentCheckpoint == 20) {
                                    kart_3->currentCheckpoint = 21;
                                    kart_3->isActivated_21 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_21 && kart_4->currentCheckpoint == 20) {
                                    kart_4->currentCheckpoint = 21;
                                    kart_4->isActivated_21 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 22
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_22) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_22 && kart_1->currentCheckpoint == 21) {
                                    kart_1->currentCheckpoint = 22;
                                    kart_1->isActivated_22 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_22 && kart_2->currentCheckpoint == 21) {
                                    kart_2->currentCheckpoint = 22;
                                    kart_2->isActivated_22 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_22 && kart_3->currentCheckpoint == 21) {
                                    kart_3->currentCheckpoint = 22;
                                    kart_3->isActivated_22 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_22 && kart_4->currentCheckpoint == 21) {
                                    kart_4->currentCheckpoint = 22;
                                    kart_4->isActivated_22 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 23
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_23) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_23 && kart_1->currentCheckpoint == 22) {
                                    kart_1->currentCheckpoint = 23;
                                    kart_1->isActivated_23 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_23 && kart_2->currentCheckpoint == 22) {
                                    kart_2->currentCheckpoint = 23;
                                    kart_2->isActivated_23 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_23 && kart_3->currentCheckpoint == 22) {
                                    kart_3->currentCheckpoint = 23;
                                    kart_3->isActivated_23 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_23 && kart_4->currentCheckpoint == 22) {
                                    kart_4->currentCheckpoint = 23;
                                    kart_4->isActivated_23 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }

                            // CHECKPOINT 24
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == CHECKPOINT_SENSOR_24) {
                                if (bodyA == kart_1->body && !kart_1->isActivated_24 && kart_1->currentCheckpoint == 23) {
                                    kart_1->currentCheckpoint = 24;
                                    kart_1->isActivated_24 = true;
                                    kart_1->CountSensor++;
                                    printf("Kart 1 - Checkpoint: %d\n", kart_1->CountSensor);
                                }
                                else if (bodyA == kart_2->body && !kart_2->isActivated_24 && kart_2->currentCheckpoint == 23) {
                                    kart_2->currentCheckpoint = 24;
                                    kart_2->isActivated_24 = true;
                                    kart_2->CountSensor++;
                                    printf("Kart 2 - Checkpoint: %d\n", kart_2->CountSensor);
                                }
                                else if (bodyA == kart_3->body && !kart_3->isActivated_24 && kart_3->currentCheckpoint == 23) {
                                    kart_3->currentCheckpoint = 24;
                                    kart_3->isActivated_24 = true;
                                    kart_3->CountSensor++;
                                    printf("Kart 3 - Checkpoint: %d\n", kart_3->CountSensor);
                                }
                                else if (bodyA == kart_4->body && !kart_4->isActivated_24 && kart_4->currentCheckpoint == 23) {
                                    kart_4->currentCheckpoint = 24;
                                    kart_4->isActivated_24 = true;
                                    kart_4->CountSensor++;
                                    printf("Kart 4 - Checkpoint: %d\n", kart_4->CountSensor);
                                }
                                return;
                            }
                            // FINISH CHECKPOINT
                            if (bodyB == entities[j]->body && entities[j]->GetCollisionType() == FINISH_CHECKPOINT_SENSOR) {
                                if (bodyA == kart_1->body && kart_1->currentCheckpoint == 24) {
                                    kart_1->currentCheckpoint = 0;
                                    kart_1->CurrentLap++;

                                    kart_1->isActivated_1 = false;
                                    kart_1->isActivated_2 = false;
                                    kart_1->isActivated_3 = false;
                                    kart_1->isActivated_4 = false;
                                    kart_1->isActivated_5 = false;
                                    kart_1->isActivated_6 = false;
                                    kart_1->isActivated_7 = false;
                                    kart_1->isActivated_8 = false;
                                    kart_1->isActivated_9 = false;
                                    kart_1->isActivated_10 = false;
                                    kart_1->isActivated_11 = false;
                                    kart_1->isActivated_12 = false;
                                    kart_1->isActivated_13 = false;
                                    kart_1->isActivated_14 = false;
                                    kart_1->isActivated_15 = false;
                                    kart_1->isActivated_16 = false;
                                    kart_1->isActivated_17 = false;
                                    kart_1->isActivated_18 = false;
                                    kart_1->isActivated_19 = false;
                                    kart_1->isActivated_20 = false;
                                    kart_1->isActivated_21 = false;
                                    kart_1->isActivated_22 = false;
                                    kart_1->isActivated_23 = false;
                                    kart_1->isActivated_24 = false;
                                    kart_1->CountSensor = 0;

                                    if (kart_1->CurrentRank == 1 && !lapUpdated) {
                                        finish->lap++;
                                        lapUpdated = true; 

                                        best_lap_time = lap_time;
                                        lap_time = 0;
                                        lap_start_time = GetTime();
                                    }

                                    printf("Kart 1 completed lap: %d\n", kart_1->CurrentLap);
                                }
                                else if (bodyA == kart_2->body && kart_2->currentCheckpoint == 24) {
                                    kart_2->currentCheckpoint = 0;
                                    kart_2->CurrentLap++;

                                    kart_2->isActivated_1 = false;
                                    kart_2->isActivated_2 = false;
                                    kart_2->isActivated_3 = false;
                                    kart_2->isActivated_4 = false;
                                    kart_2->isActivated_5 = false;
                                    kart_2->isActivated_6 = false;
                                    kart_2->isActivated_7 = false;
                                    kart_2->isActivated_8 = false;
                                    kart_2->isActivated_9 = false;
                                    kart_2->isActivated_10 = false;
                                    kart_2->isActivated_11 = false;
                                    kart_2->isActivated_12 = false;
                                    kart_2->isActivated_13 = false;
                                    kart_2->isActivated_14 = false;
                                    kart_2->isActivated_15 = false;
                                    kart_2->isActivated_16 = false;
                                    kart_2->isActivated_17 = false;
                                    kart_2->isActivated_18 = false;
                                    kart_2->isActivated_19 = false;
                                    kart_2->isActivated_20 = false;
                                    kart_2->isActivated_21 = false;
                                    kart_2->isActivated_22 = false;
                                    kart_2->isActivated_23 = false;
                                    kart_2->isActivated_24 = false;
                                    kart_2->CountSensor = 0;

                                    if (kart_2->CurrentRank == 1 && !lapUpdated) {
                                        finish->lap++;
                                        lapUpdated = true; 

                                        best_lap_time = lap_time;
                                        lap_time = 0;
                                        lap_start_time = GetTime();

                                    }

                                    printf("Kart 2 completed lap: %d\n", kart_2->CurrentLap);
                                }
                                else if (bodyA == kart_3->body && kart_3->currentCheckpoint == 24) {
                                    kart_3->currentCheckpoint = 0;
                                    kart_3->CurrentLap++;

                                    kart_3->isActivated_1 = false;
                                    kart_3->isActivated_2 = false;
                                    kart_3->isActivated_3 = false;
                                    kart_3->isActivated_4 = false;
                                    kart_3->isActivated_5 = false;
                                    kart_3->isActivated_6 = false;
                                    kart_3->isActivated_7 = false;
                                    kart_3->isActivated_8 = false;
                                    kart_3->isActivated_9 = false;
                                    kart_3->isActivated_10 = false;
                                    kart_3->isActivated_11 = false;
                                    kart_3->isActivated_12 = false;
                                    kart_3->isActivated_13 = false;
                                    kart_3->isActivated_14 = false;
                                    kart_3->isActivated_15 = false;
                                    kart_3->isActivated_16 = false;
                                    kart_3->isActivated_17 = false;
                                    kart_3->isActivated_18 = false;
                                    kart_3->isActivated_19 = false;
                                    kart_3->isActivated_20 = false;
                                    kart_3->isActivated_21 = false;
                                    kart_3->isActivated_22 = false;
                                    kart_3->isActivated_23 = false;
                                    kart_3->isActivated_24 = false;

                                    kart_3->CountSensor = 0;

                                    if (kart_3->CurrentRank == 1 && !lapUpdated) {

                                        finish->lap++;
                                        lapUpdated = true;

                                        best_lap_time = lap_time;
                                        lap_time = 0;
                                        lap_start_time = GetTime();
                                    }

                                    printf("Kart 3 completed lap: %d\n", kart_3->CurrentLap);
                                }
                                else if (bodyA == kart_4->body && kart_4->currentCheckpoint == 24) {
                                    kart_4->currentCheckpoint = 0;
                                    kart_4->CurrentLap++;

                                    kart_4->isActivated_1 = false;
                                    kart_4->isActivated_2 = false;
                                    kart_4->isActivated_3 = false;
                                    kart_4->isActivated_4 = false;
                                    kart_4->isActivated_5 = false;
                                    kart_4->isActivated_6 = false;
                                    kart_4->isActivated_7 = false;
                                    kart_4->isActivated_8 = false;
                                    kart_4->isActivated_9 = false;
                                    kart_4->isActivated_10 = false;
                                    kart_4->isActivated_11 = false;
                                    kart_4->isActivated_12 = false;
                                    kart_4->isActivated_13 = false;
                                    kart_4->isActivated_14 = false;
                                    kart_4->isActivated_15 = false;
                                    kart_4->isActivated_16 = false;
                                    kart_4->isActivated_17 = false;
                                    kart_4->isActivated_18 = false;
                                    kart_4->isActivated_19 = false;
                                    kart_4->isActivated_20 = false;
                                    kart_4->isActivated_21 = false;
                                    kart_4->isActivated_22 = false;
                                    kart_4->isActivated_23 = false;
                                    kart_4->isActivated_24 = false;

                                    kart_4->CountSensor = 0;

                                    if (kart_4->CurrentRank == 1 && !lapUpdated) {

                                        finish->lap++;
                                        lapUpdated = true;

                                        best_lap_time = lap_time;
                                        lap_time = 0;
                                        lap_start_time = GetTime();
                                    }

                                    printf("Kart 4 completed lap: %d\n", kart_4->CurrentLap);
                                }

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
            Kart_NPC* kartNPC = dynamic_cast<Kart_NPC*>(entities[i]);
            if (kart || kartNPC) {
                for (int j = 0; j < length; ++j) {
                    if (bodyB == entities[j]->body) {
                        // SNOW ZONE
                        if (entities[j]->GetCollisionType() == SNOW) {
                            if (kart) kart->snowZoneCount--;
                            if (kartNPC) kartNPC->snowZoneCount--;

                            if ((kart && kart->snowZoneCount == 0 && kart->DarkenedsnowZoneCount == 0) ||
                                (kartNPC && kartNPC->snowZoneCount == 0 && kartNPC->DarkenedsnowZoneCount == 0)) {
                                printf("Kart exited snow zone.\n");
                                if (kart) kart->inSnowZone = false;
                                if (kartNPC) kartNPC->inSnowZone = false;

                                if (kart) {
                                    switch (kart->kartType) {
                                    case KARTO:
                                        kart->maxSpeedKa = 2.5f;
                                        kart->boostedMaxSpeedKa = 4.0f;
                                        break;
                                    case HAOLIEN:
                                        kart->maxSpeedHa = 3.0f;
                                        kart->boostedMaxSpeedHa = 5.0f;
                                        break;
                                    case JOHANA:
                                        kart->maxSpeedJo = 1.0f;
                                        kart->boostedMaxSpeedJo = 3.0f;
                                        break;
                                    case TANKETO:
                                        kart->maxSpeedTa = 1.5f;
                                        kart->boostedMaxSpeedTa = 6.0f;
                                        break;
                                    default:
                                        kart->maxSpeed = 2.0f;
                                        kart->boostedMaxSpeed = 4.0f;
                                        break;
                                    }
                                }

                                if (kartNPC) {
                                    switch (kartNPC->kartType) {
                                    case KARTO:
                                        kartNPC->maxSpeed = 2.5f;
                                        kartNPC->boostedMaxSpeed = 4.0f;
                                        break;
                                    case HAOLIEN:
                                        kartNPC->maxSpeed = 3.0f;
                                        kartNPC->boostedMaxSpeed = 5.0f;
                                        break;
                                    case JOHANA:
                                        kartNPC->maxSpeed = 1.0f;
                                        kartNPC->boostedMaxSpeed = 3.0f;
                                        break;
                                    case TANKETO:
                                        kartNPC->maxSpeed = 1.5f;
                                        kartNPC->boostedMaxSpeed = 6.0f;
                                        break;
                                    default:
                                        kartNPC->maxSpeed = 2.0f;
                                        kartNPC->boostedMaxSpeed = 4.0f;
                                        break;
                                    }
                                }
                            }
                            return;
                        }

                        // DARKENED SNOW ZONE
                        if (entities[j]->GetCollisionType() == DARKENED_SNOW) {
                            if (kart) kart->DarkenedsnowZoneCount--;
                            if (kartNPC) kartNPC->DarkenedsnowZoneCount--;

                            if ((kart && kart->DarkenedsnowZoneCount == 0 && kart->snowZoneCount == 0) ||
                                (kartNPC && kartNPC->DarkenedsnowZoneCount == 0 && kartNPC->snowZoneCount == 0)) {
                                printf("Kart exited darkened snow zone.\n");
                                if (kart) kart->inDarkenedSnowZone = false;
                                if (kartNPC) kartNPC->inDarkenedSnowZone = false;

                                if (kart) {
                                    switch (kart->kartType) {
                                    case KARTO:
                                        kart->maxSpeedKa = 2.5f;
                                        kart->boostedMaxSpeedKa = 4.0f;
                                        break;
                                    case HAOLIEN:
                                        kart->maxSpeedHa = 3.0f;
                                        kart->boostedMaxSpeedHa = 5.0f;
                                        break;
                                    case JOHANA:
                                        kart->maxSpeedJo = 1.0f;
                                        kart->boostedMaxSpeedJo = 3.0f;
                                        break;
                                    case TANKETO:
                                        kart->maxSpeedTa = 1.5f;
                                        kart->boostedMaxSpeedTa = 6.0f;
                                        break;
                                    default:
                                        kart->maxSpeed = 2.0f;
                                        kart->boostedMaxSpeed = 4.0f;
                                        break;
                                    }
                                }

                                if (kartNPC) {
                                    switch (kartNPC->kartType) {
                                    case KARTO:
                                        kartNPC->maxSpeed = 2.5f;
                                        kartNPC->boostedMaxSpeed = 4.0f;
                                        break;
                                    case HAOLIEN:
                                        kartNPC->maxSpeed = 3.0f;
                                        kartNPC->boostedMaxSpeed = 5.0f;
                                        break;
                                    case JOHANA:
                                        kartNPC->maxSpeed = 1.0f;
                                        kartNPC->boostedMaxSpeed = 3.0f;
                                        break;
                                    case TANKETO:
                                        kartNPC->maxSpeed = 1.5f;
                                        kartNPC->boostedMaxSpeed = 6.0f;
                                        break;
                                    default:
                                        kartNPC->maxSpeed = 2.0f;
                                        kartNPC->boostedMaxSpeed = 4.0f;
                                        break;
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
}

float CalculateDistance(int x1, int y1, int x2, int y2) {
    return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

void ModuleGame::UpdateRanking() {
    std::vector<KartInfo> kartDistances;

    // Lista de checkpoints
    std::vector<std::pair<int, int>> checkpoints = {
        {135, 260}, // CHECKPOINT_SENSOR_1
        {295, 85},  // CHECKPOINT_SENSOR_2
        {535, 95},  // CHECKPOINT_SENSOR_3
        {670, 270}, // CHECKPOINT_SENSOR_4
        {760, 400}, // CHECKPOINT_SENSOR_5
        {840, 270}, // CHECKPOINT_SENSOR_6
        {952, 123}, // CHECKPOINT_SENSOR_7
        {1093, 118}, // CHECKPOINT_SENSOR_8
        {1192, 232}, // CHECKPOINT_SENSOR_9
        {1062, 350}, // CHECKPOINT_SENSOR_10
        {991, 462},  // CHECKPOINT_SENSOR_11
        {991, 583},  // CHECKPOINT_SENSOR_12
        {904, 664},  // CHECKPOINT_SENSOR_13
        {733, 602},  // CHECKPOINT_SENSOR_14
        {600, 600},  // CHECKPOINT_SENSOR_15
        {543, 471},  // CHECKPOINT_SENSOR_16
        {533, 341},  // CHECKPOINT_SENSOR_17
        {440, 261},  // CHECKPOINT_SENSOR_18
        {351, 325},  // CHECKPOINT_SENSOR_19
        {371, 406},  // CHECKPOINT_SENSOR_20
        {385, 504},  // CHECKPOINT_SENSOR_21
        {415, 584},  // CHECKPOINT_SENSOR_22
        {260, 650},  // CHECKPOINT_SENSOR_23
        {145, 540}   // CHECKPOINT_SENSOR_24
    };

    const int totalCheckpoints = checkpoints.size();

    // Encontrar el kart que va más adelantado
    Kart* leaderKart = nullptr;
    int maxProgress = -1;

    for (PhysicEntity* entity : entities) {
        // Comprobar cada tipo específico de kart
        if (Kart_Player_1* kart1 = dynamic_cast<Kart_Player_1*>(entity)) {
            int kartProgress = (kart1->CurrentLap * totalCheckpoints) + kart1->currentCheckpoint;
            if (kartProgress > maxProgress) {
                maxProgress = kartProgress;
                leaderKart = kart1;
            }
        }
        else if (Kart_Player_2* kart2 = dynamic_cast<Kart_Player_2*>(entity)) {
            int kartProgress = (kart2->CurrentLap * totalCheckpoints) + kart2->currentCheckpoint;
            if (kartProgress > maxProgress) {
                maxProgress = kartProgress;
                leaderKart = kart2;
            }
        }
        else if (Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(entity)) {
            int kartProgress = (kart3->CurrentLap * totalCheckpoints) + kart3->currentCheckpoint;
            if (kartProgress > maxProgress) {
                maxProgress = kartProgress;
                leaderKart = kart3;
            }
        }
        else if (Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(entity)) {
            int kartProgress = (kart4->CurrentLap * totalCheckpoints) + kart4->currentCheckpoint;
            if (kartProgress > maxProgress) {
                maxProgress = kartProgress;
                leaderKart = kart4;
            }
        }
    }

    if (leaderKart) {
        int leaderCheckpoint = leaderKart->currentCheckpoint % checkpoints.size();
        int checkpointX = checkpoints[leaderCheckpoint].first;
        int checkpointY = checkpoints[leaderCheckpoint].second;

        // Recolectar información de todos los karts específicos
        for (PhysicEntity* entity : entities) {
            int kartX, kartY;
            if (Kart_Player_1* kart1 = dynamic_cast<Kart_Player_1*>(entity)) {
                kart1->body->GetPhysicPosition(kartX, kartY);
                float distance = CalculateDistance(kartX, kartY, checkpointX, checkpointY);
                kartDistances.push_back({ kart1, distance });
            }
            else if (Kart_Player_2* kart2 = dynamic_cast<Kart_Player_2*>(entity)) {
                kart2->body->GetPhysicPosition(kartX, kartY);
                float distance = CalculateDistance(kartX, kartY, checkpointX, checkpointY);
                kartDistances.push_back({ kart2, distance });
            }
            else if (Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(entity)) {
                kart3->body->GetPhysicPosition(kartX, kartY);
                float distance = CalculateDistance(kartX, kartY, checkpointX, checkpointY);
                kartDistances.push_back({ kart3, distance });
            }
            else if (Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(entity)) {
                kart4->body->GetPhysicPosition(kartX, kartY);
                float distance = CalculateDistance(kartX, kartY, checkpointX, checkpointY);
                kartDistances.push_back({ kart4, distance });
            }
        }

        // Ordenar los karts considerando progreso real y distancia
        std::sort(kartDistances.begin(), kartDistances.end(),
            [totalCheckpoints](const KartInfo& a, const KartInfo& b) {
                int progressA = 0;
                int progressB = 0;
                int lapA = 0;
                int lapB = 0;
                int checkpointA = 0;
                int checkpointB = 0;

                // Obtener progreso para kart A
                if (Kart_Player_1* kart1 = dynamic_cast<Kart_Player_1*>(a.kart)) {
                    progressA = (kart1->CurrentLap * totalCheckpoints) + kart1->currentCheckpoint;
                    lapA = kart1->CurrentLap;
                    checkpointA = kart1->currentCheckpoint;
                }
                else if (Kart_Player_2* kart2 = dynamic_cast<Kart_Player_2*>(a.kart)) {
                    progressA = (kart2->CurrentLap * totalCheckpoints) + kart2->currentCheckpoint;
                    lapA = kart2->CurrentLap;
                    checkpointA = kart2->currentCheckpoint;
                }
                else if (Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(a.kart)) {
                    progressA = (kart3->CurrentLap * totalCheckpoints) + kart3->currentCheckpoint;
                    lapA = kart3->CurrentLap;
                    checkpointA = kart3->currentCheckpoint;
                }
                else if (Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(a.kart)) {
                    progressA = (kart4->CurrentLap * totalCheckpoints) + kart4->currentCheckpoint;
                    lapA = kart4->CurrentLap;
                    checkpointA = kart4->currentCheckpoint;
                }

                // Obtener progreso para kart B
                if (Kart_Player_1* kart1 = dynamic_cast<Kart_Player_1*>(b.kart)) {
                    progressB = (kart1->CurrentLap * totalCheckpoints) + kart1->currentCheckpoint;
                    lapB = kart1->CurrentLap;
                    checkpointB = kart1->currentCheckpoint;
                }
                else if (Kart_Player_2* kart2 = dynamic_cast<Kart_Player_2*>(b.kart)) {
                    progressB = (kart2->CurrentLap * totalCheckpoints) + kart2->currentCheckpoint;
                    lapB = kart2->CurrentLap;
                    checkpointB = kart2->currentCheckpoint;
                }
                else if (Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(b.kart)) {
                    progressB = (kart3->CurrentLap * totalCheckpoints) + kart3->currentCheckpoint;
                    lapB = kart3->CurrentLap;
                    checkpointB = kart3->currentCheckpoint;
                }
                else if (Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(b.kart)) {
                    progressB = (kart4->CurrentLap * totalCheckpoints) + kart4->currentCheckpoint;
                    lapB = kart4->CurrentLap;
                    checkpointB = kart4->currentCheckpoint;
                }

                // Comparar progreso total
                if (progressA != progressB) {
                    return progressA > progressB;
                }

                // Si están en la misma vuelta y mismo checkpoint, usar distancia
                if (lapA == lapB && checkpointA == checkpointB) {
                    return a.distanceToCP < b.distanceToCP;
                }

                return false;
            });

        // Actualizar las posiciones
        int rank = 1;
        for (const KartInfo& info : kartDistances) {
            if (Kart_Player_1* kart1 = dynamic_cast<Kart_Player_1*>(info.kart)) {
                kart1->CurrentRank = rank;
            }
            else if (Kart_Player_2* kart2 = dynamic_cast<Kart_Player_2*>(info.kart)) {
                kart2->CurrentRank = rank;
            }
            else if (Kart_Player_3* kart3 = dynamic_cast<Kart_Player_3*>(info.kart)) {
                kart3->CurrentRank = rank;
            }
            else if (Kart_Player_4* kart4 = dynamic_cast<Kart_Player_4*>(info.kart)) {
                kart4->CurrentRank = rank;
            }
            ++rank;
        }
    }
}

void ModuleGame::UpdateKartCheckpoints(int checkpointID)
{
    // Encuentra todos los karts
    Kart_Player_1* kart_1 = nullptr;
    Kart_Player_2* kart_2 = nullptr;
    Kart_Player_3* kart_3 = nullptr;
    Kart_Player_4* kart_4 = nullptr;

    for (PhysicEntity* entity : entities) {
        if (!kart_1) kart_1 = dynamic_cast<Kart_Player_1*>(entity);
        if (!kart_2) kart_2 = dynamic_cast<Kart_Player_2*>(entity);
        if (!kart_3) kart_3 = dynamic_cast<Kart_Player_3*>(entity);
        if (!kart_4) kart_4 = dynamic_cast<Kart_Player_4*>(entity);
        if (kart_1 && kart_2 && kart_3 && kart_4) break;
    }

    // Actualiza el checkpoint de cada kart
    if (kart_1 && kart_1->currentCheckpoint == checkpointID - 1) {
        kart_1->currentCheckpoint = checkpointID;
    }
    if (kart_2 && kart_2->currentCheckpoint == checkpointID - 1) {
        kart_2->currentCheckpoint = checkpointID;
    }
    if (kart_3 && kart_3->currentCheckpoint == checkpointID - 1) {
        kart_3->currentCheckpoint = checkpointID;
    }
    if (kart_4 && kart_4->currentCheckpoint == checkpointID - 1) {
        kart_4->currentCheckpoint = checkpointID;
    }
}

void ModuleGame::CreateCollisionsAndSensors()
{
    //------------------------------ SLOW ZONES ----------------------------------------
    InitializeSnowZones(App->physics, this, entities, default);
    InitializeDarkenedSnowZones(App->physics, this, entities, default);
    //------------------------------ SENSORS ----------------------------------------
	InitializeBoostSensors(App->physics, this, entities, default);
    InitializeCheckpointSensors(App->physics, this, entities, default);
    InitializeAISensors(App->physics, this, entities, default);
    entities.emplace_back(DBG_NEW FinishCheckpointSensor(App->physics, 250, 10, this, default));
    //------------------------------ COLLISIONS ----------------------------------------
    InitializeCollisions(App->physics, this, entities, default);

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

Texture2D ModuleGame::getCarTexture(KartType kartType) {
    switch (kartType) {
    case KARTO: return blueCar;
    case HAOLIEN: return yellowCar;
    case JOHANA: return greenCar;
    case TANKETO: return redCar;
    default: return blueCar;
    }
}

int ModuleGame::randomKart() {
    int kart = rand() % 4;
    return kart;
}