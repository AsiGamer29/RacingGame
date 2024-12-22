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
	DARKENED_SNOW
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


public:
	std::vector<PhysicEntity*> entities;

	Texture2D background;
	
	PhysBody* m_body;
	PhysBody* sensor;
	bool sensed;

	Texture2D circle;
	Texture2D box;
	Texture2D rick;
	Texture2D default;

	uint32 bonus_fx;
	uint32 engine_fx;
	uint32 bump_fx;
	uint32 boost_fx;



	vec2<int> ray;
	bool ray_on;
};
