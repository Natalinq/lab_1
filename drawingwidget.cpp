#include "drawingwidget.h"
#include "wheel.h"
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
    , currentObject(nullptr)
    , currentIsWheel(false)
{
    setAttribute(Qt::WA_StaticContents);

    setMinimumSize(600, 400);
}

DrawingWidget::~DrawingWidget()
{
    if (currentObject) {
        if (currentIsWheel) {
            delete static_cast<Wheel*>(currentObject);
        } else {
            delete currentObject;
        }
    }
}

void DrawingWidget::setObject(Circle *obj, bool isWheel)
{
    if (currentObject) {
        if (currentIsWheel) {
            delete static_cast<Wheel*>(currentObject);
        } else {
            delete currentObject;
        }
    }

    currentObject = obj;
    currentIsWheel = isWheel;

    update();

    qDebug() << "DrawingWidget: объект установлен"
             << (isWheel ? "Wheel" : "Circle");
}

void DrawingWidget::animate()
{
    if (!currentObject || !currentObject->getIsMoving()) {
        return;
    }

    currentObject->move(0.05);

    currentObject->handleCollision(width(), height());

    update();
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    for (int x = 50; x < width(); x += 50) {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = 50; y < height(); y += 50) {
        painter.drawLine(0, y, width(), y);
    }

    if (currentObject) {
        currentObject->draw(painter);
    }

    if (currentObject) {
        painter.setPen(QPen(Qt::black, 1));
        QPointF pos = currentObject->getPosition();
        painter.drawText(10, 20,
                         QString("Позиция: (%1, %2)  Радиус: %3")
                             .arg(pos.x(), 0, 'f', 1)
                             .arg(pos.y(), 0, 'f', 1)
                             .arg(currentObject->getRadius(), 0, 'f', 1));
    }
}

void DrawingWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update();
}
