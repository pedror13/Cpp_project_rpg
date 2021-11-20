#pragma once
#include "Instance.h"
class GameInstance :
	public Instance
{
  private:

	  //CameraView variables
	  sf::View* playerView;
	  sf::RenderTexture renderTexture;
	  sf::Sprite renderSprite;

	  Player* player; 
	  sf::Vector2f playerPos;
      //sf::RectangleShape gameScenarios; //TODO CREATE A FUNCTION TO MAKE THE MAPS OBJECTS
	  sf::Texture scenarioTexture; // TODO CREAT THIS BETTER
	  sf::Sprite scenario;

	  // Private Functions
	  void initView();
	  void initKeybinds();
	  void initTextures();
	  void initPlayers();
	  void initScenarios();

  public:
	  //Constructors & Destructors
	  GameInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances);
	  virtual ~GameInstance();

	  //Functions
	  void updateView(const float& dt);
	  void updateInput(const float& dt);
	  void update(const float& dt);
	  void render(sf::RenderTarget* target = nullptr);

};

 