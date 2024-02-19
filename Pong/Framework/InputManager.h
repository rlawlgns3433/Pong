#pragma once
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <unordered_map>

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;

	std::list<sf::Keyboard::Key> positives;
	std::list<sf::Keyboard::Key> negatives;

	float sensitive;
	float value;
};

// Ű���� �Է»� �ƴ϶� ���콺 �Է±��� �߰� �ʿ�
class InputManager
{
private:

	//sf::Clock clock;
	//sf::Time currentTime; 
	static std::map<Axis, AxisInfo> axisInfoMap;

	// �̹� �����ӿ� down�� Ű���� ��Ƶδ� ��, ���� Ű�� �ʿ� ��� ��Ƽ� ó�� // �ð������� �����Ͽ� ���� �ֱٿ� ���� Ű�� �������� �����ϰ� �ٲ�� �Ѵ�.
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> downKeyMap;
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> upKeyMap;
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> ingKeyMap;


	static std::list<sf::Keyboard::Key> downKeyList;
	static std::list<sf::Keyboard::Key> upKeyList;
	static std::list<sf::Keyboard::Key> ingKeyList;

	// �� ������ ������ keydown, keyup�� ������ �Ǿ�� �Ѵ�. �ϳ��� ������ ��������!
public:

	static sf::Mouse mouse;
	static void Init();
	static void Update(float dt);

	static void UpdateEvent(const sf::Event& event);
	static void Clear();
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static const sf::Vector2f& GetMousePos(sf::Mouse& mouse);
	static bool GetMouseButtonDown(sf::Mouse::Button mouse);
	static bool GetMouseButtonUp(sf::Mouse::Button mouse);
	static bool GetMouseButton(sf::Mouse::Button mouse);

	static float GetAxisRaw(Axis axis); // -1.f  /  0.f  /  1.f
	static float GetAxis(Axis axis); // -1.f ~ 1.f


	//static int EncryptKey(sf::Keyboard::Key key);
	//static sf::Keyboard::Key DecryptKey(int cipherText);
};