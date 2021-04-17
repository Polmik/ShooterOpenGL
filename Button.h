#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

struct Button
{
    sf::Texture* T_Texture;
    sf::Texture* T_PressedTexture;
    sf::Sprite button;
    std::string name;

    bool selected = false;
    bool pressed = false;

    void select();
    void unSelect();
    void press();
};


#endif //BUTTON_H