#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ResourceManager
{
    // Unloads all currently loaded textures.
    void unloadTextures();
    void unloadSoundBuffers();
    void unloadAllResources();
    void unloadFonts();

    // Try to load texture from file.
    // If success returns pointer to texture.
    // Otherwise returns nullptr.
    sf::Texture* loadTexture(const std::string& filename);
    sf::Font* loadFont(const std::string& filename);
    sf::SoundBuffer* loadSoundBuffer(const std::string& filename);
};


#endif //RESOURCEMANAGER_H
