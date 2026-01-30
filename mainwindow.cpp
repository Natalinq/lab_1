#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
#include "wheel.h"
#include <QTimer>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , drawingWidget(nullptr)
    , animationTimer(new QTimer(this))
    , isAnimating(false)
{
    ui->setupUi(this);

    drawingWidget = new DrawingWidget(ui->drawingArea);

    QVBoxLayout *drawingLayout = new QVBoxLayout(ui->drawingArea);
    drawingLayout->setContentsMargins(0, 0, 0, 0);
    drawingLayout->addWidget(drawingWidget);

    connect(animationTimer, &QTimer::timeout, drawingWidget, &DrawingWidget::animate);

    ui->editX->setValidator(new QDoubleValidator(0, 1000, 2, this));
    ui->editY->setValidator(new QDoubleValidator(0, 1000, 2, this));
    ui->editRadius->setValidator(new QDoubleValidator(5, 200, 2, this));
    ui->editVx->setValidator(new QDoubleValidator(-500, 500, 2, this));
    ui->editVy->setValidator(new QDoubleValidator(-500, 500, 2, this));
    ui->editSpokes->setValidator(new QIntValidator(2, 32, this));
    ui->editRotationSpeed->setValidator(new QDoubleValidator(-720, 720, 2, this));

    connect(ui->btnCreateCircle, &QPushButton::clicked, this, &MainWindow::onCreateCircle);
    connect(ui->btnCreateWheel, &QPushButton::clicked, this, &MainWindow::onCreateWheel);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartAnimation);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStopAnimation);

    ui->btnStop->setEnabled(false);

    statusBar()->showMessage("Готово: создайте круг или колесо");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateCircle()
{
    try {
        double x = ui->editX->text().toDouble();
        double y = ui->editY->text().toDouble();
        double r = ui->editRadius->text().toDouble();

        if (r <= 0 || r > 200) {
            throw std::invalid_argument("Радиус должен быть от 5 до 200");
        }

        Circle *circle = new Circle(x, y, r);
        circle->setSpeed(ui->editVx->text().toDouble(), ui->editVy->text().toDouble());

        drawingWidget->setObject(circle, false);

        if (isAnimating) {
            onStopAnimation();
        }

        statusBar()->showMessage(QString("Создан круг: (%1, %2), радиус %3").arg(x).arg(y).arg(r));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка ввода", QString::fromStdString(e.what()));
    }
}

void MainWindow::onCreateWheel()
{
    try {
        double x = ui->editX->text().toDouble();
        double y = ui->editY->text().toDouble();
        double r = ui->editRadius->text().toDouble();
        int spokes = ui->editSpokes->text().toInt();
        double rotSpeed = ui->editRotationSpeed->text().toDouble();

        if (r <= 0 || r > 200) {
            throw std::invalid_argument("Радиус должен быть от 5 до 200");
        }
        if (spokes < 2 || spokes > 32) {
            throw std::invalid_argument("Количество спиц должно быть от 2 до 32");
        }

        Wheel *wheel = new Wheel(x, y, r, spokes);
        wheel->setSpeed(ui->editVx->text().toDouble(), ui->editVy->text().toDouble());
        wheel->setRotationSpeed(rotSpeed);

        drawingWidget->setObject(wheel, true);

        if (isAnimating) {
            onStopAnimation();
        }

        statusBar()->showMessage(QString("Создано колесо: (%1, %2), %3 спиц").arg(x).arg(y).arg(spokes));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка ввода", QString::fromStdString(e.what()));
    }
}

void MainWindow::onStartAnimation()
{
    if (!drawingWidget->getCurrentObject()) {
        QMessageBox::warning(this, "Внимание", "Сначала создайте объект (круг или колесо)");
        return;
    }

    drawingWidget->getCurrentObject()->startMoving();

    animationTimer->start(50);
    isAnimating = true;

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);

    statusBar()->showMessage("Анимация запущена");
}

void MainWindow::onStopAnimation()
{
    if (isAnimating) {
        animationTimer->stop();
        isAnimating = false;

        if (drawingWidget->getCurrentObject()) {
            drawingWidget->getCurrentObject()->stopMoving();
        }

        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);

        statusBar()->showMessage("Анимация остановлена");
    }
}
