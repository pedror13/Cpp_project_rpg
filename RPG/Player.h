#pragma once
#include "Entity.h"
class Player :
	public Entity
{
  private:
	  //Variables
	  sf::Vector2f playerPos;

	  //Private Functions
	  void initVariables();
	  void initComponents();

  public:
	  //Constructors & Destructors
	  Player(float x, float y, sf::Texture& textureSheet);
	  virtual ~Player();

	  //Functions
	  sf::Vector2f getPlayerPos();
	  virtual void update(const float& dt);
};

