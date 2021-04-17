#include "Bonus.h"

Bonus::Bonus(Point2D position, BonusType bType, const std::string texture) : Object2D(position, {{-0.3, -0.3}, {0.3, -0.3}, {0.3, 0.3}, {-0.3, 0.3}}, 0.5, texture), bonusType(bType) {

}

ObjectType Bonus::type() {
    return ObjectType::Bonus;
}