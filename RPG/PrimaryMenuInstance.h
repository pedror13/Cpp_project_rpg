#pragma once
#include "GameInstance.h"
#include "Button.h"

class PrimaryMenuInstance :
	public Instance
{

  private:
	  //Variables
	  sf::Texture backgroundTexture;
	  sf::Texture buttonTexture;
	  sf::RectangleShape background;
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
	  void updateInput(const float& dt);
	  void updateButtons();
	  void update(const float& dt);
	  void renderButtons(sf::RenderTarget* target = nullptr);
	  void render(sf::RenderTarget* target = nullptr);
};

