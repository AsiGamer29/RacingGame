#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;

enum CollisionType {
	SNOW,
	DARKENED_SNOW,
	CHECKPOINT_SENSOR_1,
	CHECKPOINT_SENSOR_2,
	CHECKPOINT_SENSOR_3,
	CHECKPOINT_SENSOR_4,
	FINISH_CHECKPOINT_SENSOR,
	DEFAULT
};

class LevelSetup : public Module
{
public:
	LevelSetup(Application* app, bool start_enabled = true);
	~LevelSetup();

	bool Start();
	update_status Update();
	bool CleanUp();

	void CreateCollisionsAndSensors();
	void RemoveAllCollisionsAndSensors();

public:
	std::vector<PhysicEntity*> entities;

	PhysBody* m_body;
	PhysBody* sensor;
	bool sensed;

	vec2<int> ray;
	bool ray_on;
};
