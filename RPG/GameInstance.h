#pragma once
#include "Instance.h"
class GameInstance :
	public Instance
{
  private:
	  //Caracters be here maybe 

  public:
	  //Constructors & Destructors
	  GameInstance(sf::RenderWindow* window);
	  virtual ~GameInstance();

	  //Functions
	  void endInstance();
	  void update(const float& dt);
	  void render(sf::RenderTarget* target = nullptr);


};

