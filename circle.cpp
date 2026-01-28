#include "circle.h"
#include <QPen>
#include <QBrush>
#include <QMessageBox>

Circle::Circle(double initX, double initY, double initRadius)
    : x(initX), y(initY), radius(initRadius), vx(0), vy(0), isMoving(false)
{
    if (radius <= 0 || radius > 1000) {
        throw std::invalid_argument("Радиус должен быть в диапазоне (0, 1000]");
    }
    if (std::isnan(x) || std::isnan(y)) {
        throw std::invalid_argument("Координаты не могут быть NaN");
    }
}

void Circle::move(double dt) {
    if (!isMoving) return;
    x += vx * dt;
    y += vy * dt;
}

void Circle::startMoving() {
    if (vx == 0 && vy == 0) {
        vx = 80.0;
        vy = 50.0;
    }
    isMoving = true;
}

void Circle::stopMoving() {
    isMoving = false;
}

void Circle::draw(QPainter &painter) const {
    painter.setPen(QPen(Qt::blue, 2));
    painter.setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
    painter.drawEllipse(QPointF(x, y), radius, radius);

    painter.setPen(QPen(Qt::red, 4));
    painter.drawPoint(QPointF(x, y));
}

void Circle::handleCollision(int width, int height) {
    if (x - radius < 0) {
        x = radius;
        vx = std::abs(vx);
    } else if (x + radius > width) {
        x = width - radius;
        vx = -std::abs(vx);
    }

    if (y - radius < 0) {
        y = radius;
        vy = std::abs(vy);
    } else if (y + radius > height) {
        y = height - radius;
        vy = -std::abs(vy);
    }
}

void Circle::setPosition(double newX, double newY) {
    if (std::isnan(newX) || std::isnan(newY)) {
        throw std::invalid_argument("Координаты не могут быть NaN");
    }
    x = newX;
    y = newY;
}

void Circle::setRadius(double newRadius) {
    if (newRadius <= 0 || newRadius > 1000) {
        throw std::invalid_argument("Радиус должен быть в диапазоне (0, 1000]");
    }
    radius = newRadius;
}

void Circle::setSpeed(double newVx, double newVy) {
    vx = newVx;
    vy = newVy;
}
