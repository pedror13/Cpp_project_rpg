#pragma once
#include "Instance.h"
#include "Scenario.h"
#include "Button.h"
#include "PlayerHitbox.h"

class GameInstance :
	public Instance
{
private:
	class Enemies
	{
	  private:
	  public:
		  //Variables
		  int level;
		  float atk;
		  float def;

		  /// For HP & MP
		  /// frist -> current value
		  /// secont -> max value
		  std::pair<float, float> hp;
		  std::pair<float, float> mp;

		  /// For Skills
		  /// frist -> damage multiplier value
		  /// secont -> mp cost
		  int numberSkills;
		  std::pair<float, float>* skills;
	
		  //Constructor & Destructor
		  Enemies(std::string key, int level)
		  {
			  this->level = level;

			  if (key == "Goblin")
			  {
				  std::ifstream enemieStats("Config/Scenarios/Scenario_0/Enemies/Goblin/goblin_stats.ini");
				  if (enemieStats.is_open())
				  {
					  enemieStats >> this->hp.first  >> this->hp.second;
					  enemieStats >> this->mp.first >> this->mp.second;
					  enemieStats >> this->atk >> this->def;
					  if (level > 1)
					  {
						  this->hp.first *= (1 + static_cast<float>(level) / 2);
						  this->hp.second *= (1 + static_cast<float>(level) / 2);
						  this->mp.first *= (1 + static_cast<float>(level) / 3);
						  this->mp.second *= (1 + static_cast<float>(level) / 3);
						  this->atk *= (1 + static_cast<float>(level) * 2.f);
						  this->def *= (1 + static_cast<float>(level) * 2.f);
					  }

					  enemieStats.close();
				  }

				  std::ifstream enemieSkills("Config/Scenarios/Scenario_0/Enemies/Goblin/goblin_skills.ini");
				  if (enemieSkills.is_open())
				  {
					  enemieSkills >> this->numberSkills;
					  this->skills = new std::pair<float, float>[this->numberSkills];
					  for (int i = 0; i < this->numberSkills; i++)
					  {
						  enemieSkills >> this->skills[i].first >> this->skills[i].second;
						  if (level > 1)
						  {
							  this->skills[i].second *= (1 + float(level) / 3);
						  }
					  }

					  enemieSkills.close();
				  }
			  }
			  
		  }
		  ~Enemies()
		  {
			  delete[] this->skills;
		  }

		  //Functions
		  bool checkIfDefeated()
		  {
			  if (this->hp.first <= 0)
			  {
				  return true;
			  }
			  return false;
		  }

	};
	//Variables

	///CameraView variables
	sf::View* playerView;
	sf::View* view;

	///Player's variables
	Player* player;
	sf::Vector2f playerPos;

	///Player's Combat stats
	int playerLevel;
	float playerAtk;
	float playerDef;
	std::pair<float, float> playerHP;
	std::pair<float, float> playerMP;
	std::vector<std::pair<float, float>> playerSkills;

	///Player's States Aux
	bool playerOnInteraction;
	bool playerOnCombat;

	///Colision system variables
	sf::Vector2f topLeftCord;
	sf::Vector2f topRightCord;
	sf::Vector2f bottomLeftCord;
	sf::Vector2f bottomRightCord;


	///Scenario's Variables
	std::map<std::string, Scenario*> scenario;
	sf::RectangleShape* objects;
	sf::RectangleShape* npc;
	sf::RectangleShape* interactiveObjects;


	///Interact windows variables
	std::map<std::string, Button*> buttons;
	sf::Font font;
	sf::Texture buttonTexture;
	std::vector<short int> dialogSize;
	std::vector<short int> InteractionsSize;
	std::string atualDialog;
	int dialogCount;

	bool interactionDelay;
	float interactionTimer;

	///Enemies
	std::map<std::string, Enemies*> enemies;

	///Combat Variables
	int combatCount;
	sf::RectangleShape actionsMenu;
	sf::RectangleShape combatDisplay;
	sf::Font font1;
	sf::Font font2;

	// Private Functions
	///Initializer functions

	void initVariables();	
	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initScenarios();
    void InitFonts();
	void initButtons();
	void initCombatWindows();



public:
	//Constructors & Destructors
	GameInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances);
	virtual ~GameInstance();

	//Functions
	void enemyTurn();
	void levelUP();

	void initializeCombat();
	void initializeDialog(short int key);
	void initializeInteraction(short int key);

	void updateView(const float& dt);
	void updateInput(const float& dt);
	bool updateInputDelay(const float& dt);
	void updateButtons();
	void update(const float& dt);

	void renderButtons(sf::RenderTarget* target, std::string key);
	void renderDisplayCombat(sf::RenderTarget* target, std::string key);
	void render(sf::RenderTarget* target = nullptr);

};