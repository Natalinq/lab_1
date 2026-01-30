#include "wheel.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <cmath>
#include <stdexcept>

const double DEG_TO_RAD = M_PI / 180.0;

Wheel::Wheel(double initX, double initY, double initRadius, int spokes)
    : Circle(initX, initY, initRadius),
    angle(0.0),
    rotationSpeed(90.0),
    spokeCount(spokes)
{
    if (spokeCount < 2 || spokeCount > 32) {
        throw std::invalid_argument(
            "Количество спиц должно быть в диапазоне [2, 32]. "
            "Передано: " + std::to_string(spokeCount)
            );
    }
}

void Wheel::move(double dt) {
    Circle::move(dt);

    rotate(dt);
}

void Wheel::rotate(double dt) {
    angle += rotationSpeed * dt;

    if (angle >= 360.0) {
        angle -= 360.0;
    } else if (angle < 0.0) {
        angle += 360.0;
    }
}

void Wheel::draw(QPainter &painter) const {
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(Qt::darkGray, Qt::SolidPattern));
    painter.drawEllipse(QPointF(x, y), radius, radius);

    painter.save();

    painter.translate(x, y);

    painter.rotate(angle);

    painter.setPen(QPen(Qt::yellow, 2));

    for (int i = 0; i < spokeCount; ++i) {
        double spokeAngle = 360.0 / spokeCount * i;
        double rad = spokeAngle * DEG_TO_RAD;

        double endX = radius * cos(rad);
        double endY = radius * sin(rad);

        painter.drawLine(0, 0, endX, endY);
    }

    painter.restore();

    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(QPointF(x, y), radius * 0.2, radius * 0.2);
}

void Wheel::startRotating() {
    if (rotationSpeed == 0.0) {
        rotationSpeed = 90.0;
    }
}

void Wheel::stopRotating() {
    rotationSpeed = 0.0;
}

void Wheel::setRotationSpeed(double speed) {
    if (speed < -720.0 || speed > 720.0) {
        throw std::invalid_argument(
            "Скорость вращения должна быть в диапазоне [-720, 720] град/сек. "
            "Передано: " + std::to_string(speed)
            );
    }
    rotationSpeed = speed;
}

void Wheel::setSpokeCount(int count) {
    if (count < 2 || count > 32) {
        throw std::invalid_argument(
            "Количество спиц должно быть в диапазоне [2, 32]. "
            "Передано: " + std::to_string(count)
            );
    }
    spokeCount = count;
}
