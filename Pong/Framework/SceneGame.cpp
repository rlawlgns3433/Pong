#include "pch.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "TextGo.h";

SceneGame::SceneGame(SceneIDs id) 
    : Scene(id)
{
    windowX = FRAMEWORK.GetWindowSize().x;
    windowY = FRAMEWORK.GetWindowSize().y;
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	bat = new Bat("bat");
	ball = new Ball(*bat, sf::FloatRect({ 0,0 }, { windowX, windowY }));

	AddGameObject(bat);
	AddGameObject(ball);

    textScore = new TextGo("Score");
    textLives = new TextGo("Lives");
    textGameover = new TextGo("Gameover");
    textMessage = new TextGo("Tutorial");

    textScore->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "SCORE:" + std::to_string(SCENE_MANAGER.GetScore()), 50, sf::Color::White);
    textScore->SetOrigin(Origins::TL);
    textScore->SetPosition(0, 0);
    AddGameObject(textScore);

    textLives->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "Lives:" + std::to_string(SCENE_MANAGER.GetLives()), 50, sf::Color::White);
    textLives->SetOrigin(Origins::TL);
    textLives->SetPosition(400, 0);
    AddGameObject(textLives);

    textGameover->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "Gameover ^.^\n Try Again\nPRESS ENTER TO RESTART", 50, sf::Color::White);
    textGameover->SetOrigin(Origins::MC);
    textGameover->SetPosition(windowX / 2, windowY / 2);
    textGameover->SetActive(false);
    AddGameObject(textGameover);

    textMessage->Set(*FONT_MANAGER.GetResource("Font/DS-DIGI.ttf"), "Use (Left and Right) OR (A and D) to move sliding bar", 50, sf::Color::White);
    textMessage->SetOrigin(Origins::MC);
    textMessage->SetPosition(windowX / 2, windowY / 2);
    textMessage->SetActive(true);
    AddGameObject(textMessage);

    for (GameObject* obj : gameObjects)
    {
        obj->Init();
    }
}

void SceneGame::Release()
{
	Scene::Release();
    bat = nullptr;
    ball = nullptr;
    textScore = nullptr;
    textLives = nullptr;
    textGameover = nullptr;
    textMessage = nullptr;
}

void SceneGame::Reset()
{
    InputManager::Clear();

    isGameover = false;
    textGameover->SetActive(false);
    SCENE_MANAGER.SetScore(0);
    SCENE_MANAGER.SetLives(3);
    textScore->SetText("SCORE:" + std::to_string(SCENE_MANAGER.GetScore()));
    textLives->SetText("Lives:" + std::to_string(SCENE_MANAGER.GetLives()));
    FRAMEWORK.SetTimeScale(1.f);
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
    SetStatus(status);

    switch (status)
    {
    case GameStatus::Awake:
        UpdateAwake(dt);
        break;
    case GameStatus::Game:
        UpdateGame(dt);
        break;
    case GameStatus::GameOver:
        UpdateGameover(dt);
        break;
    case GameStatus::Pause:
        UpdatePause(dt);
        break;
    default:
        break;
    }
}

void SceneGame::UpdateAwake(float dt)
{
    textMessage->SetActive(true);

    if (InputManager::GetKeyDown(sf::Keyboard::Enter))
    {
        status = GameStatus::Game;
        textMessage->SetActive(false);
    }
}

void SceneGame::UpdateGame(float dt)
{

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Pause;
    }

    bat->Update(dt);

    if (!isBallActive && InputManager::GetKeyDown(sf::Keyboard::Space))
    {
        ball->Fire({ 1.f, -1.f }, 500.f);
        isBallActive = true;
    }

    if (ball->IsDead())
    {
        SCENE_MANAGER.SetLives(SCENE_MANAGER.GetLives() - 1);
        if (SCENE_MANAGER.GetLives() <= 0)
        {
            textGameover->SetActive(true);
            status = GameStatus::GameOver;
        }
        isBallActive = false;
        ball->Fire({ 0.f, 0.f }, 0.f);
    }

    ball->Update(dt);
    InputManager::Update(dt);

    if (!isBallActive)
    {
        ball->GetShape().setPosition(bat->shape.getPosition());
    }

    textLives->SetText("Lives:" + std::to_string(SCENE_MANAGER.GetLives()));
    textScore->SetText("SCORE:" + std::to_string(SCENE_MANAGER.GetScore()));
}

void SceneGame::UpdateGameover(float dt)
{
    if (InputManager::GetKeyDown(sf::Keyboard::Enter))
    {
        Reset();
        status = GameStatus::Game;
    }
}

void SceneGame::UpdatePause(float dt)
{
    textMessage->SetText("Pause");
    textMessage->SetActive(true);

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Game;
        textMessage->SetActive(false);
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
