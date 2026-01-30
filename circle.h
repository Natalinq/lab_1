#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPointF>
#include <QPainter>
#include <cmath>

class Circle {
protected:
    double x, y;
    double radius;
    double vx, vy;
    bool isMoving;

public:

    Circle(double x = 100, double y = 100, double radius = 30);
    virtual ~Circle() = default;

    virtual void move(double dt);
    virtual void startMoving();
    virtual void stopMoving();

    virtual void draw(QPainter &painter) const;

    virtual void handleCollision(int width, int height);

    virtual void setPosition(double newX, double newY);
    virtual void setRadius(double newRadius);
    virtual void setSpeed(double newVx, double newVy);

    QPointF getPosition() const { return QPointF(x, y); }
    double getRadius() const { return radius; }
    bool getIsMoving() const { return isMoving; }
};

#endif // CIRCLE_H
