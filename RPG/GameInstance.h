#pragma once
#include "Instance.h"
#include "Scenario.h"
#include "Button.h"
#include "PlayerHitbox.h"

class GameInstance :
	public Instance
{
private:
	//Variables

	///CameraView variables
	sf::View* playerView;
	sf::View* view;

	///Player's variables
	Player* player;
	sf::Vector2f playerPos;

	///Colision system variables
	bool invalidMove;
	sf::Vector2f topLeftCord;
	sf::Vector2f topRightCord;
	sf::Vector2f bottomLeftCord;
	sf::Vector2f bottomRightCord;


	///Scenario's Variables
	std::map<std::string, Scenario*> scenario;
	sf::RectangleShape* objects;
	//sf::RectangleShape* npc;
	//sf::RectangleShape* interactiveObjects;
	//std::vector<std::string>  npcKey;
	//std::vector<std::string>  interactiveObjKey;

	///Interact windows variables
	//std::map<std::string, Button*> buttons;
	//short int dialogSize;
	//std::string dialogText;

	//sf::Font font;
	//sf::Texture buttonTexture;



	// Private Functions
	///Initializer functions

	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initScenarios();
	//void InitFonts();
	void initVariables(); // TAVA SEM MAS VOU DEIXAR POR ENQUANTI'


public:
	//Constructors & Destructors
	GameInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances);
	virtual ~GameInstance();

	//Functions
	/*void initializeObjEvent(std::string key);
	void initializeDialog(std::string key);*/


	void updateView(const float& dt);
	void updateInput(const float& dt);
	//void updateButtons();
	void update(const float& dt);

	//void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);

};