#include "Menu.h"
#include <string>
#include <iostream>
#include <filesystem>


Menu::Menu()
{
    menuButtons = {
        GetButton(ButtonType::PlayGame, PLAYGAME_TEXTURE, PLAYGAME_PRESSED_TEXTURE),
        GetButton(ButtonType::Settings, SETTINGS_TEXTURE, SETTINGS_PRESSED_TEXTURE),
        GetButton(ButtonType::About, ABOUT_TEXTURE, ABOUT_PRESSED_TEXTURE),
        GetButton(ButtonType::Maps, MAPS_TEXTURE, MAPS_PRESSED_TEXTURE),
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
                    else if (buttons[i].buttonName == ButtonType::Maps)
                    {
                        b_maps = true;
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
                else if (b_maps)
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

        if (!b_settings && !b_about && !b_maps && i < menuButtons.size())
            window.draw(buttons[i].buttonSprite);
    }

    settings(window);
    about(window);
    maps(window);
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

void Menu::maps(sf::RenderTarget& window)
{
    if (!b_maps)
        return;

    sf::Sprite button;
    sf::Text textMaps;
    sf::Text textPreview;

    const int offset = 20;
    float xPosS1 = 10;
    float yPosS1 = offset;
    float xS1 = SCREEN_WIDTH - offset - offset * 0.75;
    float yS1 = SCREEN_HEIGHT - offset - offset * 0.75;
    float lineSize = 5;

    sf::RectangleShape rectangle1(sf::Vector2f(120.f, 50.f));
    rectangle1.setSize(sf::Vector2f(xS1 - lineSize * 2, yS1 - lineSize * 2));
    rectangle1.setFillColor(sf::Color::White);
    rectangle1.setPosition(xPosS1 + lineSize, yPosS1 + lineSize);
    rectangle1.setOutlineColor(sf::Color::Black);
    rectangle1.setOutlineThickness(lineSize);

    float xPosS2 = xPosS1 + 10 + 20;
    float yPosS2 = yPosS1 + 10 + 40;
    float xS2 = SCREEN_WIDTH - offset - offset * 0.75 - xPosS2 * 1.5;
    float yS2 = SCREEN_HEIGHT - offset - offset * 0.75 - yPosS2;
    sf::RectangleShape rectangle3(sf::Vector2f(120.f, 50.f));
    rectangle3.setSize(sf::Vector2f(xS2 - lineSize * 2, yS2 - lineSize * 2));
    rectangle3.setFillColor(sf::Color::White);
    rectangle3.setPosition(xPosS2 + lineSize, yPosS2 + lineSize);
    rectangle3.setOutlineColor(sf::Color::Black);
    rectangle3.setOutlineThickness(lineSize);

    float xPosS3 = xPosS2 + lineSize;
    float yPosS3 = yPosS2 + lineSize;
    float xS3 = SCREEN_WIDTH - offset - offset * 0.75 - xPosS3 * 1.5;
    float yS3 = SCREEN_HEIGHT - offset - offset * 0.75 - yPosS3;
    sf::RectangleShape rectangle5(sf::Vector2f(120.f, 50.f));
    rectangle5.setSize(sf::Vector2f((xS2 - lineSize * 2) / 4 - lineSize, yS2 - lineSize * 2));
    rectangle5.setFillColor(sf::Color::White);
    rectangle5.setPosition(xPosS3, yPosS3);
    rectangle5.setOutlineColor(sf::Color::Black);
    rectangle5.setOutlineThickness(lineSize);
    sf::RectangleShape rectangle6(sf::Vector2f(120.f, 50.f));
    rectangle6.setSize(sf::Vector2f(lineSize + xS2 - lineSize * 2 - (xS2 - lineSize * 2) / 4 - lineSize, yS2 - lineSize * 2));
    rectangle6.setFillColor(sf::Color::White);
    rectangle6.setPosition(xPosS3 + lineSize + (xS2 - lineSize * 2) / 4 - lineSize, yPosS3);

    textMaps.setFont(*ResourceManager::loadFont(TEXT_FONT));
    textMaps.setCharacterSize(38);
    textMaps.setFillColor(sf::Color::Black);
    textMaps.setPosition(xPosS2 + lineSize * 2, yPosS2 - lineSize * 2 - 38);
    textMaps.setString("Maps");

    textPreview.setFont(*ResourceManager::loadFont(TEXT_FONT));
    textPreview.setCharacterSize(38);
    textPreview.setFillColor(sf::Color::Black);
    textPreview.setPosition(SCREEN_HEIGHT / 2 - (xPosS2 + lineSize) / 6 + 5, yPosS2 - lineSize * 2 - 38);
    textPreview.setString("Preview");

    namespace fs = std::filesystem;
    struct MapObj {
        std::string path;
        std::string preview;
    };
    std::vector<MapObj> objects;
    std::string path = "maps\\";
    for (const auto& entry : fs::directory_iterator(path)) {
        fs::path p = entry.path();
        if (p.string().find(".obj") != std::string::npos) {
            std::string prev = p.string().replace(p.string().find(".obj"), 4, "_preview.jpg");
            struct stat buffer;
            bool is_exist = (stat(prev.c_str(), &buffer) == 0);

            MapObj m = MapObj();
            m.path = p.string();
            m.preview = is_exist ? prev : NOT_FOUND;
            objects.push_back(m);
        }
    }

    // TODO: Add selection
    MapObj o = objects[0];
    rectangle6.setTexture(ResourceManager::loadTexture(o.preview));
    textPreview.setString("Preview: " + o.path);

    window.draw(rectangle1);
    window.draw(rectangle3);
    window.draw(rectangle5);
    window.draw(rectangle6);
    window.draw(textMaps);
    window.draw(textPreview); 

    float sX = xPosS2 + lineSize * 2;
    float sY = yPosS2 - lineSize * 2 - 38;
    float curr = sY;
    float off = 50;
    for (const auto& oobj : objects) {
        sf::Text t;
        t.setFont(*ResourceManager::loadFont(TEXT_FONT));
        t.setCharacterSize(38);
        t.setFillColor(sf::Color::Black);
        curr += off;
        t.setPosition(sX, curr);
        t.setString(oobj.path);
        window.draw(t);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        b_maps = false;
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
