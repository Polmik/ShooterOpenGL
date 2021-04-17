#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Audio.hpp>
#include "Idrawable.h"
#include "settings.h"

class Weapon : virtual public Idrawable
{
private:
    double d_elapsedTime = 0;

    sf::Sprite S_weapon_trunk;
    sf::Sprite S_weapon_arm;
    sf::Sprite S_weapon_handle;

    sf::Sprite S_fire;
    sf::Sprite S_aim;

    sf::SoundBuffer fireSoundBuffer;
    sf::Sound fireSound;

    int i_damage = 0;
    double d_speed = 1;
    int i_amount = 0;

    double d_fireAnimTime = 0;
    double d_lastFireTime = 0;
    double d_amplitude = 100;
    double fireShift = 0;

public:
    Weapon(int amount);
    Weapon(const Weapon& weapon);

    void draw(sf::RenderTarget& window) override;

    double getSpeed() const;
    int getDamage() const;

    int getAmmo() const;

    void choiceWeapon(std::string name);
    bool isFire();

    void addAmmo(double ammo) {
        i_amount += ammo;
    }
};


#endif //WEAPON_H
