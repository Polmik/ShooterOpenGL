#ifndef CIRCLE2D_H
#define CIRCLE2D_H

#include "Object2D.h"
#include "settings.h"

class Circle2D : public Object2D
{
private:
    double d_radius = 0;

public:
    explicit Circle2D(double radius = 0.5, Point2D position = { 0, 0 }, double height = 1, const std::string& texture = COLUMN_TEXTURE, int convexNumber = CIRCLE_CONVEX_NUMBER);

    ObjectType getType() override;

    // Check the intersection of the ray with this circle.
    // Returns true if ray intersects with this circle, false otherwise.
    // wall - hitted wall.
    // point - hit point.
    // uv - distance from the beginning of wall to the hit point.
    bool isCross(const std::pair<Point2D, Point2D>& ray, std::pair<Point2D, Point2D>& wall, Point2D& point, double& uv) override;
};


#endif //CIRCLE2D_H
