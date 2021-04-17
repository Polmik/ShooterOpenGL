#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <SFML/Graphics.hpp>

class Idrawable
{
public:
    virtual ~Idrawable() {};
    virtual void draw(sf::RenderTarget& window) = 0;
};


#endif //IDRAWABLE_H
