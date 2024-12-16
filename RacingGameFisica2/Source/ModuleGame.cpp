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
    Cone(ModulePhysics* physics, int x, int y, Module* listener, Texture2D texture, Application* _app)
        : PhysicEntity(physics->CreateStaticCircle(x, y, 5), listener) // Radio del cono = 5
        , texture(texture)
        , app(_app)
    {
    }

    void Update() override
    {
        int x, y;
        body->GetPhysicPosition(x, y);

        float scale = 1.5f;
        DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
            Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
            Vector2{ (float)texture.width -  1, (float)texture.height}, 0.0f, WHITE);
    }

private:
    Texture2D texture;
    Application* app;
};

class Kart : public PhysicEntity {
public:
    Kart(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app)
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
    Kart_Controller(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app)
        : Kart(physics, x, y, _listener, _texture, _app), speed(0.0f), rotation(0.0f), isBoosting(false), isMoving(false) {}

    virtual void HandleInput() {
        
        float currentMaxSpeed = maxSpeed;

        if (speed != 0.0f && !isMoving)
        {
            app->audio->PlayFx(engineSound, -1); // Reproduce en bucle
            isMoving = true;
        }
        else if (speed == 0.0f && isMoving)
        {
            isMoving = false;
        }
        
        // Si se presiona Shift, aumentar la velocidad máxima y reproducir el sonido de boost
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            currentMaxSpeed = boostedMaxSpeed;
            if (!isBoosting) {
                app->audio->PlayFx(boostSound);
                isBoosting = true;
            }
        }
        else {
            
            isBoosting = false;
        }

        if (IsKeyDown(KEY_W)) {
            speed += 0.1f;
            if (speed > currentMaxSpeed) {
                speed = currentMaxSpeed;
            }
        }
        else if (IsKeyDown(KEY_S)) {
            speed -= 0.1f;
            if (speed < -currentMaxSpeed) {
                speed = -currentMaxSpeed;
            }
        }
        else {
            // Deceleración gradual
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

        // Deceleración adicional cuando se deja de pulsar Shift
        if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && speed > maxSpeed) {
            speed -= deceleration;
            if (speed < maxSpeed) {
                speed = maxSpeed;
            }
        }

        if (isBoosting) {
            if (IsKeyDown(KEY_A)) {
                rotation -= 2.0f;
            }
            if (IsKeyDown(KEY_D)) {
                rotation += 2.0f;
            }
        }
        else {
            if (IsKeyDown(KEY_A)) {
                rotation -= 3.0f;
            }
            if (IsKeyDown(KEY_D)) {
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

    virtual void Update() override {
        HandleInput();
        Move();
        Kart::Update();
    }

protected:
    float speed;
    float rotation;
    bool isMoving;
    bool isBoosting;
    const float maxSpeed = 2.5f;
    const float boostedMaxSpeed = 4.5f;
    const float deceleration = 0.05f;
    uint32 boostSound = app->audio->LoadFx("Assets/boost.wav");
	uint32 engineSound = app->audio->LoadFx("Assets/drive.wav");;
};

class Kart_Player_1 : public Kart_Controller {
public:
    Kart_Player_1(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app)
        : Kart_Controller(physics, x, y, _listener, _texture, _app) {}
};

class Kart_Player_2 : public Kart_Controller {
public:
    Kart_Player_2(ModulePhysics* physics, int x, int y, Module* _listener, Texture2D _texture, Application* _app)
        : Kart_Controller(physics, x, y, _listener, _texture, _app) {}
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

    cone = LoadTexture("Assets/cone.png");
    circle = LoadTexture("Assets/wheel.png");
    yellowCar = LoadTexture("Assets/car.png");
    redCar = LoadTexture("Assets/redcar.png");
    rick = LoadTexture("Assets/rick_head.png");
	background = LoadTexture("Assets/Mapa1Racing.png");

    engine_fx = App->audio->LoadFx("Assets/drive.wav");
    boost_fx = App->audio->LoadFx("Assets/boost.wav"); // Cargar el sonido de boost
    bump_fx = App->audio->LoadFx("Assets/Bump.wav");

    bgm = LoadMusicStream("Assets/music.ogg");

    PlayMusicStream(bgm);

    sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

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
	UpdateMusicStream(bgm);

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
        entities.emplace_back(new Kart_Player_1(App->physics, GetMouseX(), GetMouseY(), this, yellowCar, App));
    }
    if (IsKeyPressed(KEY_THREE))
    {
        entities.emplace_back(new Kart_Player_2(App->physics, GetMouseX(), GetMouseY(), this, redCar, App));
    }

    if (IsKeyPressed(KEY_M))
    {
        entities.emplace_back(new Cone(App->physics, GetMouseX(), GetMouseY(), this, cone, App)); // Pasa el puntero a Application y el sonido de boost
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
