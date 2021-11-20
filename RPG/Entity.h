#pragma once
#include "PlayerMovement.h"
#include "PlayerAnimation.h"

class Entity
{
  private:
	  //Private Functions
	  void initVariables();

  protected:
	  //Variables
	  sf::Sprite sprite;

	  sf::Vector2f spritePos;
	  sf::Font font; // Temporary ( DEBUG )

	  PlayerMovement* movementComponent;
	  PlayerAnimation* animationComponent;

  public:
	  //Constructors & Destructors
	  Entity();
	  virtual ~Entity();


	  //Functions
	  void setTexture(sf::Texture& texture);
	  void creatMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
	  void creatAnimationComponent(sf::Texture& textureSheet);
	  const sf::Vector2f& getPos() const;
	  sf::Vector2f updatePosSprite(const float& dt);
	
	  virtual void setPosition(const float x, const float y);
	  virtual void move(const float x, const float y, const float&dt);

	  virtual void update(const float& dt);
	  virtual void render(sf::RenderTarget* target);
};

