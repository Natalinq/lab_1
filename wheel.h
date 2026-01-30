#ifndef WHEEL_H
#define WHEEL_H

#include "circle.h"

class Wheel : public Circle {
private:
    double angle;
    double rotationSpeed;
    int spokeCount;

public:

    Wheel(double x = 150, double y = 150, double radius = 40, int spokes = 8);

    void move(double dt) override;
    void draw(QPainter &painter) const override;

    void rotate(double dt);
    void startRotating();
    void stopRotating();

    void setRotationSpeed(double speed);
    void setSpokeCount(int count);

    double getAngle() const { return angle; }
    double getRotationSpeed() const { return rotationSpeed; }
    int getSpokeCount() const { return spokeCount; }
};

#endif // WHEEL_H
