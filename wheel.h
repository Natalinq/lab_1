#ifndef WHEEL_H
#define WHEEL_H

#include "circle.h"

/**
 * @brief Класс колеса — расширяет движущийся круг вращающимися спицами
 *
 * Наследует все свойства Circle (координаты, радиус, скорость движения)
 * Добавляет новые свойства: угол поворота, скорость вращения, количество спиц
 */
class Wheel : public Circle {
private:
    double angle;
    double rotationSpeed;
    int spokeCount;

public:
    /**
     * @brief Конструктор колеса
     * @param x Координата X центра
     * @param y Координата Y центра
     * @param radius Радиус колеса
     * @param spokes Количество спиц (по умолчанию 8)
     *
     * Вызывает конструктор родителя Circle для инициализации базовых свойств
     */
    Wheel(double x = 150, double y = 150, double radius = 40, int spokes = 8);

    // Переопределённые методы родителя
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
