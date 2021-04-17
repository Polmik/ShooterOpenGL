#include "Button.h"

void Button::selectButton()
{
    if (!isSelected && !isPressed)
    {
        isSelected = true;
        buttonSprite.setTexture(*ButtonPressedTexture);
        buttonSprite.scale({ 1.01f, 1.01f });
    }
}

void Button::unselectButton()
{
    if (isSelected && !isPressed)
    {
        isSelected = false;
        buttonSprite.setTexture(*ButtonTexture);
        buttonSprite.scale({ 1 / 1.01f, 1 / 1.01f });
    }
}

void Button::pressButton()
{
    if (!isPressed)
    {
        isPressed = true;
        buttonSprite.setTexture(*ButtonPressedTexture);
    }
    else
    {
        isPressed = false;
        buttonSprite.setTexture(*ButtonTexture);
    }
}
