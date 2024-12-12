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


protected:
	PhysBody* body;
	Module* listener;
    CollisionType collisionType;
};

class Collisions : public PhysicEntity {
public:
    Collisions(ModulePhysics* physics, const int* coords, int coordCount, Module* _listener, Texture2D _texture)
        : PhysicEntity(physics->CreateChain(0, 0, coords, coordCount), _listener)
        , texture(_texture)
    {
        collisionType = DEFAULT; // Inicializa con el tipo de colisión por defecto
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

    entities.emplace_back(new Internal_Collision(App->physics, 0, 0, this, default));
    entities.emplace_back(new Internal_Collision_2(App->physics, 0, 0, this, default));

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
