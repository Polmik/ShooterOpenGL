#include "Menu.h"

Menu::Menu()
{
    menuButtons = {
        GetButton(ButtonType::PlayGame, PLAYGAME_TEXTURE, PLAYGAME_PRESSED_TEXTURE),
        GetButton(ButtonType::Settings, SETTINGS_TEXTURE, SETTINGS_PRESSED_TEXTURE),
        GetButton(ButtonType::About, ABOUT_TEXTURE, ABOUT_PRESSED_TEXTURE),
        GetButton(ButtonType::Quit, QUIT_TEXTURE, QUIT_PRESSED_TEXTURE),
    };
    settingButtons = {
        GetButton(ButtonType::Texturing, TEXTURING_SELECT, TEXTURING_SELECT_S, b_textures),
        GetButton(ButtonType::Smoothing, SMOOTHING_SELECT, SMOOTHING_SELECT_S, b_smooth),
        GetButton(ButtonType::Collision, COLLISION_SELECT, COLLISION_SELECT_S, b_collision),
    };
    buttons.insert(buttons.end(), menuButtons.begin(), menuButtons.end());
    buttons.insert(buttons.end(), settingButtons.begin(), settingButtons.end());

    for (size_t i = 0; i < buttons.size(); i++)
    {
        buttons[i].buttonSprite.setTexture(*buttons[i].ButtonTexture);
        int multy = i < menuButtons.size() ? i : i - menuButtons.size();
        buttons[i].buttonSprite.setPosition((float)SCREEN_WIDTH / 2 - 170, (float)50 + 150 * multy);
        if (buttons[i].isInitPressed) {
            buttons[i].pressButton();
        }
    }
}

Button Menu::GetButton(std::string name, std::string texture, std::string pressedTexture, bool isPressed) {
    Button b = Button();
    b.buttonName = name;
    b.ButtonTexture = ResourceManager::loadTexture(texture);
    b.ButtonPressedTexture = ResourceManager::loadTexture(pressedTexture);
    b.isInitPressed = isPressed;
    return b;
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
                    if (buttons[i].buttonName == ButtonType::PlayGame)
                    {
                        b_pause = false;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == ButtonType::Settings)
                    {
                        b_settings = true;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == ButtonType::About)
                    {
                        b_about = true;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == ButtonType::Quit)
                    {
                        window.close();
                        b_pressing = false;
                    }
                }
                else if (b_settings)
                {
                    if (buttons[i].buttonName == ButtonType::Texturing)
                    {
                        buttons[i].pressButton();
                        b_textures = buttons[i].isPressed;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == ButtonType::Smoothing)
                    {
                        buttons[i].pressButton();
                        b_smooth = buttons[i].isPressed;
                        b_pressing = false;
                    }
                    else if (buttons[i].buttonName == ButtonType::Collision)
                    {
                        buttons[i].pressButton();
                        b_collision = buttons[i].isPressed;
                        b_pressing = false;
                    }
                }
            }
        }

        if (!b_settings && !b_about && i < menuButtons.size())
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

    for (size_t i = menuButtons.size(); i < buttons.size(); i++)
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
