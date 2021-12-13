#pragma once
#include "../Headers/GameInstance.h"
#include "../Headers/Button.h"

class PrimaryMenuInstance :
	public Instance
{

private:

	//Variables
	///Background variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	///Buttons Variables
	sf::Texture buttonTexture;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	// Private Functions
	void initVariables();
	void initBackground();
	void InitFonts();
	void initKeybinds();
	void initButtons();

public:
	//Constructors & Destructors
	PrimaryMenuInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances);
	virtual ~PrimaryMenuInstance();

	//Functions
	///Update functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);

	///Render functions
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};
