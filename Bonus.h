#ifndef BONUS_H
#define BONUS_H

#include "Object2D.h"
#include "settings.h"

enum class BonusType
{
    Heal,
    Ammo,
    Speed,
    Vision,
};

class Bonus : public Object2D
{
private:
    BonusType bonusType;

public:
    explicit Bonus(Point2D position = { 0, 0 }, BonusType bType = BonusType::Heal, const std::string texture = HEALTH_TEXTURE);

    ObjectType getType() override;

    [[nodiscard]] BonusType getBonusType() const { return bonusType; }
};


#endif //BONUS_H
