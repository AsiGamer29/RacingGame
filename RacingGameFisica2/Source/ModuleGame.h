#pragma once

#include "Globals.h"
#include "Module.h"
#include "Timer.h"
#include "p2Point.h"

#include <algorithm>
#include "cmath"
#include "raylib.h"
#include <vector>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

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
	CHECKPOINT_SENSOR_5,
	CHECKPOINT_SENSOR_6,
	CHECKPOINT_SENSOR_7,
	CHECKPOINT_SENSOR_8,
	CHECKPOINT_SENSOR_9,
	CHECKPOINT_SENSOR_10,
	CHECKPOINT_SENSOR_11,
	CHECKPOINT_SENSOR_12,
	CHECKPOINT_SENSOR_13,
	CHECKPOINT_SENSOR_14,
	CHECKPOINT_SENSOR_15,
	CHECKPOINT_SENSOR_16,
	CHECKPOINT_SENSOR_17,
	CHECKPOINT_SENSOR_18,
	CHECKPOINT_SENSOR_19,
	CHECKPOINT_SENSOR_20,
	CHECKPOINT_SENSOR_21,
	CHECKPOINT_SENSOR_22,
	CHECKPOINT_SENSOR_23,
	CHECKPOINT_SENSOR_24,
	FINISH_CHECKPOINT_SENSOR,
	IA,
	BOOST
};

enum KartType
{
	KARTO,
	HAOLIEN,
	JOHANA,
	TANKETO,
	DEFAULT_KART
};

enum TurnDirection
{
	LEFT,
	RIGHT,
	NONE
};

enum Player {
	PLAYER1,
	PLAYER2
};

enum GameState {
	TITLESCREEN,
	PLAYER1SELECT,
	PLAYER2SELECT,
	NPCSELECTION,
	PLAYING,
	SHOWSTAGE,
	COUNTDOWN,
	WINSCREEN,
	LOSSSCREEN
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
	Texture2D getCarTexture(KartType kartType);
	void UpdateRanking();
	void UpdateKartCheckpoints(int checkpointID);
	int randomKart();

public:
	std::vector<PhysicEntity*> entities;

	Texture2D mainScreen;
	Texture2D player1Select;
	Texture2D player2Select;
	Texture2D background;
	Texture2D leaderboard;
	Texture2D stats;
	Texture2D bestTimes;

	Texture2D three;
	Texture2D two;
	Texture2D one;
	Texture2D go;

	Texture2D kaWin;
	Texture2D haWin;
	Texture2D joWin;
	Texture2D taWin;
	Texture2D npcWin;
	
	PhysBody* m_body;
	PhysBody* sensor;
	bool sensed;

	Texture2D circle;
	Texture2D yellowCar;
	Texture2D redCar;
	Texture2D blueCar;
	Texture2D greenCar;
	Texture2D npc1;
	Texture2D npc2;
	Texture2D npc3;
	Texture2D npc4;
	Texture2D cone;
	Texture2D default;

	uint32 bonus_fx;
	uint32 engine_fx;
	uint32 bump_fx;
	uint32 boost_fx;
	uint32 horn_fx;

	uint32 finishLine;
	uint32 showStage;
	uint32 countdown;

	Music bgm;
	Music playerSelect;
	Music title;
	Music win;
	Music loss;
	
	Timer endMusicTimer;
	Timer showStageTimer;
	Timer countdownTimer;

	bool hasPlayedFinish = false;

	bool hasShownStage = false;
	bool hasShownCountdown = false;

	int stageTime = 13;
	int countdownTime = 4;

	float lap_time1 = 0.0f;
	float lap_time2 = 0.0f;
	float best_lap_time = 0.0f;
	float best_lap_time2 = 0.0f;
	float best_time = 0.0f;
	float lap_start_time = 0.0f;
	float lap_start_time2 = 0.0f;
	
	
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

	bool player1Won = false;
	bool player2Won = false;
	bool npcWon = false;

	bool hasStarted = false;
	bool hasDeleted = false;

	bool lapUpdated = false;

	int FPS_inGame;

	GameState gameState;

	vec2<int> ray;
	bool ray_on;
};
