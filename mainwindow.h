#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateCircle();
    void onCreateWheel();
    void onStartAnimation();
    void onStopAnimation();

private:
    Ui::MainWindow *ui;
    DrawingWidget *drawingWidget;
    QTimer *animationTimer;
    bool isAnimating;
};

#endif // MAINWINDOW_H
