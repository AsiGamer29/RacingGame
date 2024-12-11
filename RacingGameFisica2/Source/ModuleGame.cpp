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

protected:
	PhysBody* body;
	Module* listener;
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

class Kart : public PhysicEntity
{
public:
    Kart(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, int _engineSound, int _boostSound, Application* _app)
        : PhysicEntity(physics->CreateRectangle(_x, _y, 9, 16), _listener)
        , texture(_texture)
        , speed(0.0f)
        , rotation(0.0f)
        , engineSound(_engineSound)
        , boostSound(_boostSound) // Añadir el sonido de boost
        , isMoving(false)
        , isBoosting(false) // Añadir estado de boost
        , app(_app) // Almacena el puntero a Application
    {
    }

    void Update() override
    {
        HandleInput();
        Move();

        int x, y;
        body->GetPhysicPosition(x, y);
        float rotationDegrees = body->GetRotation() * RAD2DEG;
        float scale = 1.5f; // Escala de la imagen
        DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
            Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
            Vector2{ (float)texture.width - 1.0f, (float)texture.height - 2.0f}, rotationDegrees, WHITE);

        // Mostrar la velocidad del coche
        DrawText(TextFormat("SPEED: %.2f", speed), 10, 40, 20, RED);

        // Reproduce el sonido del motor si el kart se está moviendo
        if (speed != 0.0f && !isMoving)
        {
            app->audio->PlayFx(engineSound, -1); // Reproduce en bucle
            isMoving = true;
        }
        else if (speed == 0.0f && isMoving)
        {
            isMoving = false;
        }
    }

    void HandleInput()
    {
        float currentMaxSpeed = maxSpeed;

        // Si se presiona Shift, aumentar la velocidad máxima y reproducir el sonido de boost
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            currentMaxSpeed = boostedMaxSpeed;
            if (!isBoosting)
            {
                app->audio->PlayFx(boostSound);
                isBoosting = true;
            }
        }
        else
        {
            isBoosting = false;
        }

        if (IsKeyDown(KEY_W))
        {
            speed += 0.1f;
            if (speed > currentMaxSpeed)
            {
                speed = currentMaxSpeed;
            }
        }
        else if (IsKeyDown(KEY_S))
        {
            speed -= 0.1f;
            if (speed < -currentMaxSpeed)
            {
                speed = -currentMaxSpeed;
            }
        }
        else
        {
            // Deceleración gradual
            if (speed > 0.0f)
            {
                speed -= deceleration;
                if (speed < 0.0f)
                {
                    speed = 0.0f;
                }
            }
            else if (speed < 0.0f)
            {
                speed += deceleration;
                if (speed > 0.0f)
                {
                    speed = 0.0f;
                }
            }
        }

        // Deceleración adicional cuando se deja de pulsar Shift
        if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && speed > maxSpeed)
        {
            speed -= deceleration;
            if (speed < maxSpeed)
            {
                speed = maxSpeed;
            }
        }

        if (isBoosting) {
            if (IsKeyDown(KEY_A))
            {
                rotation -= 2.0f;
            }
            if (IsKeyDown(KEY_D))
            {
                rotation += 2.0f;
            }
		}
		else {
			if (IsKeyDown(KEY_A))
			{
				rotation -= 3.0f;
			}
			if (IsKeyDown(KEY_D))
			{
				rotation += 3.0f;
			}
		}
    }


    void Move()
    {
        float rad = rotation * DEG2RAD;
        body->body->SetLinearVelocity(b2Vec2(speed * sin(rad), -speed * cos(rad)));
        body->body->SetTransform(body->body->GetPosition(), rad);
    }

    int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
    {
        return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
    }

private:
    Texture2D texture;
    float speed;
    float rotation;
    const float maxSpeed = 2.5f;
    const float boostedMaxSpeed = 4.5f; // Nueva velocidad máxima cuando se presiona Shift
    const float deceleration = 0.05f; // Valor de deceleración
    int engineSound;
    int boostSound; // Añadir variable para el sonido de boost
    bool isMoving;
    bool isBoosting; // Añadir estado de boost
    Application* app; // Puntero a Application
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

    App->renderer->camera.x = App->renderer->camera.y = 0;

    circle = LoadTexture("Assets/wheel.png");
    box = LoadTexture("Assets/car.png");
    rick = LoadTexture("Assets/rick_head.png");
	background = LoadTexture("Assets/Mapa1Racing.png");

    bonus_fx = App->audio->LoadFx("Assets/bonus.wav");
    engine_fx = App->audio->LoadFx("Assets/drive.wav");
    boost_fx = App->audio->LoadFx("Assets/boost.wav"); // Cargar el sonido de boost
    bump_fx = App->audio->LoadFx("Assets/Bump.wav");

    sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

    return ret;
}
// Load assets
bool ModuleGame::CleanUp()
{
    LOG("Unloading Intro scene");

    return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
    DrawTexture(background, 0, 0, WHITE);

    if (IsKeyPressed(KEY_SPACE))
    {
        ray_on = !ray_on;
        ray.x = GetMouseX();
        ray.y = GetMouseY();
    }

    if (IsKeyPressed(KEY_ONE))
    {
        entities.emplace_back(new Circle(App->physics, GetMouseX(), GetMouseY(), this, circle));

    }
    if (IsKeyPressed(KEY_TWO))
    {
        entities.emplace_back(new Kart(App->physics, GetMouseX(), GetMouseY(), this, box, engine_fx, boost_fx, App)); // Pasa el puntero a Application y el sonido de boost
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

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
    App->audio->PlayFx(bump_fx);
}
