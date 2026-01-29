#include "wheel.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <cmath>
#include <stdexcept>

// Константа: пи для перевода градусов в радианы
const double DEG_TO_RAD = M_PI / 180.0;

Wheel::Wheel(double initX, double initY, double initRadius, int spokes)
    : Circle(initX, initY, initRadius),  // Вызов конструктора родителя
    angle(0.0),                         // Начальный угол = 0°
    rotationSpeed(90.0),                // Скорость по умолчанию: 90 град/сек
    spokeCount(spokes)                  // Количество спиц
{
    // Валидация количества спиц
    if (spokeCount < 2 || spokeCount > 32) {
        throw std::invalid_argument(
            "Количество спиц должно быть в диапазоне [2, 32]. "
            "Передано: " + std::to_string(spokeCount)
            );
    }
}

void Wheel::move(double dt) {
    // 1. Сначала двигаем колесо как обычный круг (вызываем родительский метод)
    Circle::move(dt);

    // 2. Затем вращаем спицы
    rotate(dt);
}

void Wheel::rotate(double dt) {
    // Изменяем угол: угол += скорость * время
    angle += rotationSpeed * dt;

    // Нормализуем угол в диапазон [0, 360)
    if (angle >= 360.0) {
        angle -= 360.0;
    } else if (angle < 0.0) {
        angle += 360.0;
    }
}

void Wheel::draw(QPainter &painter) const {
    // === ШАГ 1: Рисуем основной круг колеса ===
    painter.setPen(QPen(Qt::black, 3));          // Толстая чёрная обводка
    painter.setBrush(QBrush(Qt::darkGray, Qt::SolidPattern));  // Тёмно-серая заливка
    painter.drawEllipse(QPointF(x, y), radius, radius);

    // === ШАГ 2: Рисуем спицы (вращающиеся элементы) ===
    // Сохраняем текущее состояние трансформации холста
    painter.save();

    // Перемещаем начало координат в центр колеса
    painter.translate(x, y);

    // Поворачиваем холст на текущий угол спиц
    painter.rotate(angle);

    // Рисуем спицы как линии от центра к краю
    painter.setPen(QPen(Qt::yellow, 2));  // Жёлтые спицы

    for (int i = 0; i < spokeCount; ++i) {
        // Рассчитываем угол каждой спицы (равномерно распределяем по кругу)
        double spokeAngle = 360.0 / spokeCount * i;
        double rad = spokeAngle * DEG_TO_RAD;  // Переводим в радианы

        // Конечная точка спицы (на окружности колеса)
        double endX = radius * cos(rad);
        double endY = radius * sin(rad);

        // Рисуем линию от центра (0,0) до конца спицы
        painter.drawLine(0, 0, endX, endY);
    }

    // Восстанавливаем исходное состояние холста (отменяем translate + rotate)
    painter.restore();

    // === ШАГ 3: Рисуем центральную втулку ===
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));  // Красная втулка
    painter.drawEllipse(QPointF(x, y), radius * 0.2, radius * 0.2);
}

void Wheel::startRotating() {
    // Если скорость = 0 — устанавливаем значение по умолчанию
    if (rotationSpeed == 0.0) {
        rotationSpeed = 90.0;  // 90 градусов в секунду
    }
}

void Wheel::stopRotating() {
    rotationSpeed = 0.0;  // Останавливаем вращение
}

void Wheel::setRotationSpeed(double speed) {
    // Валидация: ограничиваем разумный диапазон скорости
    if (speed < -720.0 || speed > 720.0) {
        throw std::invalid_argument(
            "Скорость вращения должна быть в диапазоне [-720, 720] град/сек. "
            "Передано: " + std::to_string(speed)
            );
    }
    rotationSpeed = speed;
}

void Wheel::setSpokeCount(int count) {
    // Валидация количества спиц
    if (count < 2 || count > 32) {
        throw std::invalid_argument(
            "Количество спиц должно быть в диапазоне [2, 32]. "
            "Передано: " + std::to_string(count)
            );
    }
    spokeCount = count;
}
