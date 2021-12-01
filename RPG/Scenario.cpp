#include "Scenario.h"

Scenario::Scenario(
	float x, float y, float witdth, float height,
	sf::Texture* scenarioTexture,
	std::string key)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(witdth, height));
	this->shape.setTexture(scenarioTexture);
	this->key = key;

	initObjects();
}

Scenario::~Scenario()
{
	delete[] this->objects;
}

/*
----------Private Functions----------
*/
void Scenario::initObjects()
{
	if (this->key == "CENTRAL_MAP")
	{
		std::ifstream ifs("Config/scenarioObj.ini");
		if (ifs.is_open())
		{
			ifs >> this->numberObjs;
			this->objects = new sf::RectangleShape[numberObjs];
			for (int i = 0; i < numberObjs; i++)
			{
				ifs >> this->coordenates.x >> this->coordenates.y >> this->size.x >> this->size.y;

				objects[i].setPosition(
					static_cast<float>(this->coordenates.x),
					static_cast<float>(this->coordenates.y)
				);

				this->objects[i].setSize(sf::Vector2f
				(
					static_cast<float>(this->size.x),
					static_cast<float>(this->size.y)
				)
				);
				this->objects[i].setFillColor(sf::Color::Transparent);
				this->objects[i].setOutlineThickness(1.f);
				this->objects[i].setOutlineColor(sf::Color::Red);
			}
		}

		ifs.close();
	}
}

sf::RectangleShape * Scenario::getObjects()
{
	return this->objects;
}

int Scenario::getNumObjs()
{
	return this->numberObjs;
}

void Scenario::updateCollision(Entity * entity)
{
	//World BOUNDS
	if (entity->getPos().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPos().y);
	}
	else if (entity->getPos().x > static_cast<float>(this->shape.getGlobalBounds().width) - entity->getSize().x)
	{
		entity->setPosition(static_cast<float>(this->shape.getGlobalBounds().width - entity->getSize().x), entity->getPos().y); // for now
	}
	else if (entity->getPos().y < -4.f) // 4.f Size of the texture image
	{
		entity->setPosition(entity->getPos().x, -4.f);
	}
	else if (entity->getPos().y > static_cast<float>(this->shape.getGlobalBounds().height) - entity->getSize().y + 2.f)
	{
		entity->setPosition(entity->getPos().x, static_cast<float>(this->shape.getGlobalBounds().height) - entity->getSize().y + 2.f);
	}


}

void Scenario::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	//(Debug)
	for (int i = 0; i < this->numberObjs; i++)
	{
		target->draw(this->objects[i]);
	}
}
