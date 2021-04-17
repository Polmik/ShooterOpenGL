#include "Menu.h"

Menu::Menu()
{
    buttons.assign(7, {});

    buttons[0].buttonName = "PLAYGAME";
    buttons[1].buttonName = "SETTINGS";
    buttons[2].buttonName = "ABOUT";
    buttons[3].buttonName = "QUIT";
    buttons[0].ButtonTexture = ResourceManager::loadTexture(PLAYGAME_TEXTURE);
    buttons[1].ButtonTexture = ResourceManager::loadTexture(SETTINGS_TEXTURE);
    buttons[2].ButtonTexture = ResourceManager::loadTexture(ABOUT_TEXTURE);
    buttons[3].ButtonTexture = ResourceManager::loadTexture(QUIT_TEXTURE);

    buttons[0].ButtonPressedTexture = ResourceManager::loadTexture(PLAYGAME_PRESSED_TEXTURE);
    buttons[1].ButtonPressedTexture = ResourceManager::loadTexture(SETTINGS_PRESSED_TEXTURE);
    buttons[2].ButtonPressedTexture = ResourceManager::loadTexture(ABOUT_PRESSED_TEXTURE);
    buttons[3].ButtonPressedTexture = ResourceManager::loadTexture(QUIT_PRESSED_TEXTURE);

    buttons[4].buttonName = "TEXTURING";
    buttons[5].buttonName = "SMOOTHING";
    buttons[6].buttonName = "COLLISION";
    buttons[4].ButtonTexture = ResourceManager::loadTexture(TEXTURING_SELECT);
    buttons[5].ButtonTexture = ResourceManager::loadTexture(SMOOTHING_SELECT);
    buttons[6].ButtonTexture = ResourceManager::loadTexture(COLLISION_SELECT);

    buttons[4].ButtonPressedTexture = ResourceManager::loadTexture(TEXTURING_SELECT_S);
    buttons[5].ButtonPressedTexture = ResourceManager::loadTexture(SMOOTHING_SELECT_S);
    buttons[6].ButtonPressedTexture = ResourceManager::loadTexture(COLLISION_SELECT_S);

    for (size_t i = 0; i < buttons.size(); i++)
    {
        buttons[i].buttonSprite.setTexture(*buttons[i].ButtonTexture);
        if (i < 4)
            buttons[i].buttonSprite.setPosition((float)SCREEN_WIDTH / 2 - 170, (float)50 + 150 * i);
        else
            buttons[i].buttonSprite.setPosition((float)SCREEN_WIDTH / 2 - 170, (float)50 + 150 * (i - 4));
    }

    if (b_textures)
        buttons[4].pressButton();
    if (b_smooth)
        buttons[5].pressButton();
    if (b_collision)
        buttons[6].pressButton();
}

void Menu::drawMenu(sf::RenderWindow& window, double elapsedTime)
{
    sf::ConvexShape back;
    back.setPointCount(4);
    back.setPoint(0, sf::Vector2f(0, 0));
    back.setPoint(1, sf::Vector2f(SCREEN_WIDTH, 0));
    back.setPoint(2, sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    back.setPoint(3, sf::Vector2f(0, SCREEN_HEIGHT));
    back.setPosition({ 0, 0 });
    back.setFillColor({ 255, 255, 255 });
    window.draw(back);

    float mouseX = (float)sf::Mouse::getPosition(window).x * window.getView().getSize().x / window.getSize().x;
    float mouseY = (float)sf::Mouse::getPosition(window).y * window.getView().getSize().y / window.getSize().y;

    bool b_pressing = sf::Mouse::isButtonPressed(sf::Mouse::Left) && !b_pressed;
    b_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    for (size_t i = 0; i < buttons.size(); i++)
    {
        if (!buttons[i].buttonSprite.getGlobalBounds().contains(mouseX, mouseY))
            buttons[i].unselectButton();
        else
        {
            buttons[i].selectButton();
            if (window.hasFocus() && b_pressing)
            {
                buttons[i].unselectButton();
                if (!b_settings)
                {
                    if (buttons[i].buttonName == "PLAYGAME")
                    {
                        b_pause = false;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == "SETTINGS")
                    {
                        b_settings = true;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == "ABOUT")
                    {
                        b_about = true;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == "QUIT")
                    {
                        window.close();
                        b_pressing = false;
                    }
                }
                else
                {
                    if (buttons[i].buttonName == "TEXTURING")
                    {
                        buttons[i].pressButton();
                        b_textures = buttons[i].isPressed;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == "SMOOTHING")
                    {
                        buttons[i].pressButton();
                        b_smooth = buttons[i].isPressed;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == "COLLISION")
                    {
                        buttons[i].pressButton();
                        b_collision = buttons[i].isPressed;
                        b_pressing = false;
                    }
                }
            }
        }

        if (!b_settings && !b_about && i < 4)
            window.draw(buttons[i].buttonSprite);
    }

    settings(window);
    about(window);
}

void Menu::about(sf::RenderTarget& window)
{
    if (!b_about)
        return;

    sf::Sprite button;
    button.setTexture(*ResourceManager::loadTexture(ABOUT_INFO));

    button.scale((float)SCREEN_WIDTH / 1920, (float)SCREEN_WIDTH / 1920);

    window.draw(button);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        b_about = false;
}

void Menu::settings(sf::RenderTarget& window)
{
    if (!b_settings)
        return;

    for (size_t i = 4; i < buttons.size(); i++)
        window.draw(buttons[i].buttonSprite);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        b_settings = false;
}

bool Menu::isPaused()
{
    return b_pause;
}

void Menu::setPause(bool active)
{
    b_pause = active;
}

bool Menu::isSmooth()
{
    return b_smooth;
}

void Menu::setSmooth(bool active)
{
    b_smooth = active;
}

bool Menu::isCollision()
{
    return b_collision;
}

void Menu::setCollision(bool active)
{
    b_collision = active;
}

bool Menu::isTextures()
{
    return b_textures;
}

void Menu::setTextures(bool active)
{
    b_textures = active;
}
