#pragma once
#include "Singleton.h"
class InputMgr : public Singleton<InputMgr>
{
	friend Singleton<InputMgr>;
private:
	InputMgr() = default;
	virtual ~InputMgr() override = default;

	std::list<sf::Keyboard::Key> downList;
	std::list<sf::Keyboard::Key> upList;
	std::list<sf::Keyboard::Key> ingList;

public:
	void Clear();
	void Update(const sf::Event& ev);

	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);
};

#define INPUT_MGR (InputMgr::Instance())