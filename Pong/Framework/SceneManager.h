#pragma once
#include "Singleton.h"

class Scene; 

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	enum class Mod
	{
		NONE = -1,
		SINGLE,
		DUO,
		COUNT,
	};

protected:
	SceneManager(const SceneManager&)			 = delete;
	SceneManager(SceneManager&&)				 = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&)		 = delete;

	std::vector<Scene*> scenes;
	SceneIDs startScene = SceneIDs::SceneGame;
	SceneIDs currentScene = startScene;

	std::vector<std::string> TextureResourceNames = {};
	std::vector<std::string> FontResourceNames = { "Font/DS-DIGI.ttf" };
	std::vector<std::string> SoundResourceNames = {};

public:

	SceneManager() = default;
	virtual ~SceneManager();
	
	void Init(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����
	void Release(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	
	void LoadAllResources();
	void ChangeScene(SceneIDs id);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MANAGER (Singleton<SceneManager>::Instance())