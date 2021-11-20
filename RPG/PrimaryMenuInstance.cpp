 #include "PrimaryMenuInstance.h"

/*
----------Private Functions----------
*/

void PrimaryMenuInstance::initVariables()
{
	if (!this->buttonTexture.loadFromFile("Resources/Images/Buttons/Menu_buttons.png"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_BACKGROUND_IMAGE";
	}
}

void PrimaryMenuInstance::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);	
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/PramaryMenuBackground.jpg"))
	{
		throw "ERROR::MENU_INSTANCE::FAILED_TO_LOAD_BACKGROUND_IMAGE"; // TODO CHANGE IT TO INITVARIABLES
	}
	this->background.setTexture(&this->backgroundTexture);
}

void PrimaryMenuInstance::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/lastfontwastingonyou.ttf"))
	{
		throw("ERROR::PrimaryMenuInstance::COULD NOT LOAD FONT");
	}
}

void PrimaryMenuInstance::initKeybinds()
{
	//Maybe later do ifs of existence of the commands, Probably not
	this->keybinds["Exit"] = this->supportedKeys->at("Escape");

}

void PrimaryMenuInstance::initButtons()
{
	this->buttons["GO_TO_GAME_INSTANCE"] = new Button(520, 80, 192, 56,
		&this->font, "New Game", &this->buttonTexture,
		sf::Color::Blue, sf::Color::Red, sf::Color::Transparent);

	this->buttons["Continue"] = new Button(520, 165, 192, 56,
		&this->font, "Continue", &this->buttonTexture,
		sf::Color::Blue, sf::Color::Red, sf::Color::Transparent);
	
	this->buttons["Credits"] = new Button(520, 250, 192, 56,
		&this->font, "Credits", &this->buttonTexture,
		sf::Color::Blue, sf::Color::Red, sf::Color::Transparent);

	this->buttons["EXIT_INSTANCE"] = new Button(520, 400, 192, 56,
		&this->font, "Exit Game", &this->buttonTexture,
		sf::Color::Blue, sf::Color::Red, sf::Color::Transparent);

}

/*
----------Constructors & Destructors----------
*/

PrimaryMenuInstance::PrimaryMenuInstance(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<Instance*>* instances)
	: Instance(window, supportedKeys, instances)
{
	this->initVariables();
	this->initBackground();
	this->InitFonts();
	this->initKeybinds();
	this->initButtons();
}

PrimaryMenuInstance::~PrimaryMenuInstance()
{
	auto it = this->buttons.begin();
	for (it; it != this->buttons.end(); ++it) // tentar so o it
	{
		delete it->second;
	}
}

/*
----------Functions----------
*/

void PrimaryMenuInstance::updateInput(const float & dt)
{

}

void PrimaryMenuInstance::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePositionView);
	}

	//Quit the aplication
	if (this->buttons["EXIT_INSTANCE"]->isPressed())
	{
		this->endInstance();
	}

	//Start the game
	if (this->buttons["GO_TO_GAME_INSTANCE"]->isPressed())
	{
		this->instances->push(new GameInstance(this->window, this->supportedKeys, this->instances));

	}
}

void PrimaryMenuInstance::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	//system("cls");
	//Debug stuff
	//std::cout << "x: " << this->mousePositionView.x 
		      //<< ", y = " << this->mousePositionView.y << std::endl; //TODO REMOVE LATER ( DEBUG )

}

void PrimaryMenuInstance::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void PrimaryMenuInstance::render(sf::RenderTarget* target)
{
	if (!target) // if target is nullpr
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);

	// TODO REMOVE LATER ( DEBUG )
	sf::Text mouseText;
	mouseText.setPosition(this->mousePositionView.x, this->mousePositionView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream ss;
	ss << std::setprecision(4) << this->mousePositionView.x << ", " << this->mousePositionView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
