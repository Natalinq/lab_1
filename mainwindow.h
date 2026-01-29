#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "circle.h"
#include "wheel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    Circle *testCircle;
    Wheel *testWheel;
};
#endif // MAINWINDOW_H
