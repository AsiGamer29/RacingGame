#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;

enum CollisionType
{
	DEFAULT,
	SNOW,
	DARKENED_SNOW,
	CHECKPOINT_SENSOR_1,
	CHECKPOINT_SENSOR_2,
	CHECKPOINT_SENSOR_3,
	CHECKPOINT_SENSOR_4,
	FINISH_CHECKPOINT_SENSOR
};

enum KartType
{
	KARTO,
	HAOLIEN,
	JOHANA,
	TANKETO,
	DEFAULT_KART
};

enum Player {
	PLAYER1,
	PLAYER2,
	NPC
};

enum GameState {
	TITLESCREEN,
	PLAYER1SELECT,
	PLAYER2SELECT,
	PLAYING
};

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void OnCollisionExit(PhysBody* bodyA, PhysBody* bodyB) override;
	void CreateCollisionsAndSensors();
	void RemoveAllCollisionsAndSensors();

public:
	std::vector<PhysicEntity*> entities;

	Texture2D mainScreen;
	Texture2D player1Select;
	Texture2D player2Select;
	Texture2D background;
	
	PhysBody* m_body;
	PhysBody* sensor;
	bool sensed;

	Texture2D circle;
	Texture2D yellowCar;
	Texture2D redCar;
	Texture2D blueCar;
	Texture2D greenCar;
	Texture2D rick;
	Texture2D cone;
	Texture2D default;

	uint32 bonus_fx;
	uint32 engine_fx;
	uint32 bump_fx;
	uint32 boost_fx;
	uint32 horn_fx;

	Music bgm;
	Music playerSelect;
	Music title;

	bool chosenKartop1 = false;
	bool chosenHaolienp1 = false;
	bool chosenJohanap1 = false;
	bool chosenTanketop1 = false;

	bool chosenKartop2 = false;
	bool chosenHaolienp2 = false;
	bool chosenJohanap2 = false;
	bool chosenTanketop2 = false;

	bool hasChosenPlayer1 = false;
	bool hasChosenPlayer2 = false;

	bool hasSpawnedPlayer1Car = false;
	bool hasSpawnedPlayer2Car = false;

	bool hasStarted = false;
	bool hasDeleted = false;
	GameState gameState;

	vec2<int> ray;
	bool ray_on;
};
