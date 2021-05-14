#include "Button.h"

void Button::selectButton()
{
    if (!isSelected && !isPressed)
    {
        buttonSprite.setTexture(*ButtonPressedTexture);
        buttonSprite.scale({ 1.01f, 1.01f });
        isSelected = !isSelected;
    }
}

void Button::unselectButton()
{
    if (isSelected && !isPressed)
    {
        buttonSprite.setTexture(*ButtonTexture);
        buttonSprite.scale({ 1 / 1.01f, 1 / 1.01f });
        isSelected = !isSelected;
    }
}

void Button::pressButton()
{
    sf::Texture texture = isPressed ? *ButtonTexture : *ButtonPressedTexture;
    isPressed = !isPressed;
    buttonSprite.setTexture(texture);
}
