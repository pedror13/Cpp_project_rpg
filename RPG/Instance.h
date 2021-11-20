#pragma once

#include "Player.h"

class Instance
{
  private:

  protected:
	  //Variables
	  std::stack<Instance*>* instances;
	  sf::RenderWindow* window;
	  std::map<std::string, int>* supportedKeys;
	  std::map<std::string, int> keybinds;
	  bool finish;

	  sf::Vector2i mousePositionWindow;
	  sf::Vector2i mousePositionScreen;
	  sf::Vector2f mousePositionView;

	  //Resources
	  std::map<std::string, sf::Texture> textures;

	  //Protected Functions

	  // Each instance willl have their on keybinds depending of what was passed by supportedKeys
	  virtual void initKeybinds() =0;

  public:

	  //Constructors & Destructors
	  Instance(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<Instance*>* instances);
	  virtual ~Instance();

	  //Functions
	  const bool& getFinish() const;
	  void endInstance(); // Probably will need one for each kind of intance, * see later*

	  ////Pure Virtual for  inheritance
	  virtual void updateMousePositions(); // TO DO LATER sf::View* view
	  virtual void updateInput(const float& dt) = 0;
	  virtual void update(const float& dt) = 0; 
	  virtual void render(sf::RenderTarget* target = nullptr) = 0; //With target i can render to some specific stuff
};

