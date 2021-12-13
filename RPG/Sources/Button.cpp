#include "../Headers/Button.h"

/*
----------Constructors & Destructors----------
*/
Button::Button(float x, float y, float witdth, float height,
	sf::Font* font, std::string text, int textSize,
	sf::Texture* buttonTexture,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->pressed = false;
	this->hover = false;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(witdth, height));
	if (buttonTexture != nullptr)
	{
		this->shape.setTexture(buttonTexture);
	}
	else
	{
		this->shape.setFillColor(sf::Color::Transparent);
	}

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(idleColor);
	this->text.setCharacterSize(textSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

Button::~Button()
{

}

/*
----------Functions----------
*/
sf::Vector2f Button::getPosition()
{
	return this->shape.getPosition();
}

sf::Vector2f Button::getLength()
{
	return sf::Vector2f(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height);
}

void Button::update(const sf::Vector2f mousePosition)
{
	/*
		Main update function for the class,
		will set up the hover/pressed values, check the,
		and if they changed do the respective actions
	*/
	this->hover = false;
	this->pressed = false;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->hover = true;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->pressed = true;
		}
	}
	if (pressed)
	{
		this->text.setFillColor(this->activeColor);
	}
	else if (hover)
	{
		this->text.setFillColor(this->hoverColor);
	}
	else
	{
		this->text.setFillColor(this->idleColor);
	}
}

const bool Button::isPressed() const
{
	return this->pressed;
}

const bool Button::isHovered() const
{
	return this->hover;

}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}