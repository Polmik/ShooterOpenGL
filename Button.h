#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

struct Button
{
    sf::Texture* ButtonTexture;
    sf::Texture* ButtonPressedTexture;
    sf::Sprite buttonSprite;
    std::string buttonName;

    bool isSelected = false;
    bool isPressed = false;
    bool isInitPressed = false;

    void selectButton();
    void unselectButton();
    void pressButton();
};


#endif //BUTTON_H
