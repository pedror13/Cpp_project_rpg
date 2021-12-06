#include "Scenario.h"
#include <map>

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

}

/*
----------Private Functions----------
*/
void Scenario::initObjects()
{
	if (this->key == "CENTRAL_MAP")
	{
		std::ifstream file("Config/Scenarios/Scenario_0/scenario_0_objects.ini");
		if (file.is_open())
		{
			file >> this->numberObjs;
			this->objects = new sf::RectangleShape[numberObjs];
			for (int i = 0; i < numberObjs; i++)
			{
				file >> this->coordenates.x >> this->coordenates.y >> this->size.x >> this->size.y;

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
				this->objects[i].setOutlineThickness(-1.f);
				this->objects[i].setOutlineColor(sf::Color::Red);
			}
		}
		file.close();

		std::ifstream file2("Config/Scenarios/Scenario_0/scenario_0_NPCs.ini");
		if (file2.is_open())
		{
			file2 >> this->numberNPCs;
			this ->dialogSize.resize(this->numberNPCs);
			this->npc = new sf::RectangleShape[this->numberNPCs];
			
			for (int i = 0; i < numberNPCs; i++)
			{

				file2 >> this->dialogSize[i] >> this->coordenates.x >> this->coordenates.y >> this->size.x >> this->size.y;

				this->npc[i].setPosition(
					static_cast<float>(this->coordenates.x),
					static_cast<float>(this->coordenates.y)
				);

				this->npc[i].setSize(sf::Vector2f
				(
					static_cast<float>(this->size.x),
					static_cast<float>(this->size.y)
				)
				);
				this->npc[i].setOutlineThickness(-1.f);
				//(DEBUG)
				this->npc[i].setFillColor(sf::Color::Transparent);
				this->npc[i].setOutlineColor(sf::Color::Yellow);
				
			}
		}
		file2.close();

		std::ifstream file3("Config/Scenarios/Scenario_0/scenario_0_interactive_objects.ini");
		if (file3.is_open())
		{
			file3 >> this->numberInteractiveObj;

			this->interactiveObjSize.resize(this->numberInteractiveObj);
			this->interactiveObjects = new sf::RectangleShape[numberInteractiveObj];

			for (int i = 0; i < numberInteractiveObj; i++)
			{
				file3 >> interactiveObjSize[i] >> this->coordenates.x >> this->coordenates.y >> this->size.x >> this->size.y;

				this->interactiveObjects[i].setPosition(
					static_cast<float>(this->coordenates.x),
					static_cast<float>(this->coordenates.y)
				);

				this->interactiveObjects[i].setSize(sf::Vector2f
				(
					static_cast<float>(this->size.x),
					static_cast<float>(this->size.y)
				)
				);
				this->interactiveObjects[i].setOutlineThickness(-1.f);
				//(DEBUG)
				this->interactiveObjects[i].setFillColor(sf::Color::Transparent);
				this->interactiveObjects[i].setOutlineColor(sf::Color::Blue);
			}
		}
		file3.close();
	}
}

sf::RectangleShape * Scenario::getObjects()
{
	return this->objects;
}

sf::RectangleShape * Scenario::getNPCs()
{
	return this->npc;
}

sf::RectangleShape * Scenario::getInteractiveObj()
{
	return this->interactiveObjects;
}

int Scenario::getNumObjs()
{
	return this->numberObjs;
}

int Scenario::getNumNPC()
{
	return this->numberNPCs;
}

int Scenario::getNumInteractObj()
{
	return this->numberInteractiveObj;
}

std::vector<short int> & Scenario::GetSizeDialog()
{
	return this->dialogSize;
}

std::vector<short int> & Scenario::GetKeyInteractiveObj()
{
	return this->interactiveObjSize;
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

	//(Debug) - keep track of all information of the NPCs and interactive Objects
	//for (int i = 0; i < 2; i++) {
	//	std::cout << std::endl << "dialogSize NPC : " << this->dialogSize[i];
	//	std::cout << std::endl << "npc.x, npc.y :" << this->npc[i].getPosition().x << ", " << this->npc[i].getPosition().y;
	//	std::cout << std::endl << "key intobj : " << this->interactiveObjKey[i];
	//	std::cout << std::endl << "intobj.x,intobj.y :" << this->interactiveObjects[i].getPosition().x << ", " << this->interactiveObjects[i].getPosition().y;
	//	std::cout << std::endl;
	//}

}

void Scenario::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	//(Debug) - Draw the objects hitbox for interaction
	//for (int i = 0; i < this->numberObjs; i++)
	//{
	//	target->draw(this->objects[i]);
	//}
	/*for (int i = 0; i < this->numberNPCs; i++)
	{
		target->draw(this->npc[i]);
	}
	for (int i = 0; i < this->numberInteractiveObj; i++)
	{
		target->draw(this->interactiveObjects[i]);
	}*/
}
