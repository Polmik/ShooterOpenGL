#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Camera.h"
#include "Button.h"
#include "ButtonType.h"

class Menu
{
private:
    std::vector<Button> buttons;
    std::vector<Button> menuButtons;
    std::vector<Button> settingButtons;

    bool b_pause = true;

    bool b_settings = false;
    bool b_about = false;
    bool b_maps = false;

    bool b_textures = true;
    bool b_smooth = false;
    bool b_collision = true;
    double lastTime = 0;

    bool b_pressed = false;

    Button GetButton(std::string name, std::string texture, std::string pressedTexture, bool isPressed = false);
public:
    Menu();

    void drawMenu(sf::RenderWindow& window, double elapsedTime);
    void settings(sf::RenderTarget& window);
    void about(sf::RenderTarget& window);
    void maps(sf::RenderTarget& window);

    bool isPaused();
    void setPause(bool active = true);

    bool isSmooth();
    void setSmooth(bool active);
    bool isCollision();
    void setCollision(bool active);
    bool isTextures();
    void setTextures(bool active);
};


#endif //MENU_H
