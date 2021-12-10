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
		  Enemies(std::string key, int level, float dice)
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

						  this->hp.first += 2.5*dice;
						  this->hp.second += 2.5*dice;
						  this->mp.first += dice;
						  this->mp.second += dice;
						  this->atk += dice/2;
						  this->def += dice/3;
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
							  this->skills[i].first *= 1.05f;
							  this->skills[i].second *= 1.2f;
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

	sf::Time timer;
	sf::Clock clock;

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

	///Enemies
	std::map<std::string, Enemies*> enemies;

	///Combat Variables
	int combatCount;
	int turnCount;
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
	///Combat functions
	void enemyTurn();
	void levelUP();
	void resetCombat();


	///Begining stages
	void beginTurn();
	void beginCombat();
	void beginDialog(short int key);
	void beginInteraction(short int key);

	///Updating functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);

	///Render functions
	void renderButtons(sf::RenderTarget* target, std::string key);
	void renderDisplayCombat(sf::RenderTarget* target, std::string key);
	void render(sf::RenderTarget* target = nullptr);

};