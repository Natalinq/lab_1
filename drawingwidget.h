#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include "circle.h"

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    ~DrawingWidget() override;


    void setObject(Circle *obj, bool isWheel = false);

    void animate();

    Circle* getCurrentObject() const { return currentObject; }
    bool isCurrentObjectWheel() const { return currentIsWheel; }

protected:

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Circle *currentObject;
    bool currentIsWheel;
};

#endif // DRAWINGWIDGET_H
