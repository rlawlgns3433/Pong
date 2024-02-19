#include "pch.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "TextGo.h";

SceneGame::SceneGame(SceneIDs id) 
    : Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
    lives = 3;

	bat = new Bat("bat");
	ball = new Ball(*bat, sf::FloatRect({ 0,0 }, {1920, 1080}));

	AddGameObject(bat);
	AddGameObject(ball);

    textScore = new TextGo("Score");
    textLives = new TextGo("Lives");

    textScore->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "SCORE:" + std::to_string(score), 50, sf::Color::White);
    textScore->SetOrigin(Origins::TL);
    textScore->SetPosition(0, 0);
    std::cout << textScore->GetText() << std::endl;
    AddGameObject(textScore);

    textLives->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "Lives:" + std::to_string(lives), 50, sf::Color::White);
    textLives->SetOrigin(Origins::TL);
    textLives->SetPosition(200, 0);
    std::cout << textLives->GetText() << std::endl;
    AddGameObject(textLives);

    for (GameObject* obj : gameObjects)
    {
        obj->Init();
    }
}

void SceneGame::Release()
{
	Scene::Release();
    textScore = nullptr;
    textLives = nullptr;
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);
    sf::Vector2f mousePos = InputManager::GetMousePos(InputManager::mouse);

    std::cout.precision(8);
    std::cout << mousePos.x << ", " << mousePos.y << std::endl;


    bat->Update(dt);

    if (!isBallActive && InputManager::GetKeyDown(sf::Keyboard::Space))
    {
        ball->Fire({1.f, -1.f}, 200.f);
        isBallActive = true;
    }

    if (ball->IsDead())
    {
        isBallActive = true;
        ball->Fire({ 0.f, 0.f }, 0.f);
        FRAMEWORK.SetTimeScale(0.f);
        // 게임 오버
        // 게임 재시작
    }
    else // bound bat 인 경우
    {
        score += 1;
        // 점수 추가
    }

    ball->Update(dt);

    InputManager::Update(dt);
    if (!isBallActive)
    {
        ball->GetShape().setPosition(bat->shape.getPosition());
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(GameStatus newStatus)
{
    GameStatus prevStatus = status;

    status = newStatus;

    switch (status)
    {
    case GameStatus::Awake:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    case GameStatus::Game:
        FRAMEWORK.SetTimeScale(1.f);
        break;
    case GameStatus::GameOver:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    case GameStatus::Pause:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    }
}
