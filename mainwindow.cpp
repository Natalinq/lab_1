#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circle.h"
#include "wheel.h"
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , testCircle(nullptr)
    , testWheel(nullptr)
{
    ui->setupUi(this);

    try {
        testCircle = new Circle(200, 150, 40);
        testCircle->setSpeed(80, 50);
        testCircle->startMoving();

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            if (testCircle) {
                testCircle->move(0.05);
                testCircle->handleCollision(this->width(), this->height());
                this->update();
            }
        });
        timer->start(50);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", QString("Не удалось создать круг: %1").arg(e.what()));
    }

    try {
        testWheel = new Wheel(300, 200, 50, 12);
        testWheel->setSpeed(60, -40);
        testWheel->setRotationSpeed(180);
        testWheel->startMoving();

        QTimer *wheelTimer = new QTimer(this);
        connect(wheelTimer, &QTimer::timeout, this, [this]() {
            if (testWheel) {  // ← Проверка на nullptr
                testWheel->move(0.05);
                testWheel->handleCollision(this->width(), this->height());
                this->update();
            }
        });
        wheelTimer->start(50);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", QString("Не удалось создать колесо: %1").arg(e.what()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete testCircle;
    delete testWheel;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    if (testCircle) {
        testCircle->draw(painter);
    }

    if (testWheel) {
        testWheel->draw(painter);
    }
}
