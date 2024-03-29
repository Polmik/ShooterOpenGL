#include "Player.h"

Player::Player(Point2D position, double vPos, double height, double health, std::string texture)
    : Circle2D(COLLISION_DISTANCE, position, height, texture, 4), d_vPos(vPos), d_health(health)
{
}

ObjectType Player::getType()
{
    return ObjectType::Player;
}

bool Player::isCross(const std::pair<Point2D, Point2D>& ray, std::pair<Point2D, Point2D>& wall, Point2D& point, double& uv)
{
    return Object2D::isCross(ray, wall, point, uv);
}

double Player::vPos() const
{
    return d_vPos;
}

void Player::setVPos(double vPos)
{
    d_vPos = vPos;
}

double Player::health() const
{
    return d_health;
}

void Player::fullHealth()
{
    d_health = 100;
}

void Player::setHealth(double h)
{
    d_health = h;
}

bool Player::reduceHealth(double damage)
{
    d_health -= damage;
    if (d_health > 100)
        d_health = 100;
    return d_health <= 0;
}
