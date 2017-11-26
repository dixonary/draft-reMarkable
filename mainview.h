#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QQuickView>
#include <QDebug>

class MainView : public QQuickView
{
public:
    MainView();
public slots:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* me);
    void mousePressEvent(QMouseEvent* me);
    void mouseReleaseEvent(QMouseEvent* me);
    void tabletEvent(QTabletEvent* te);
    void touchEvent(QTouchEvent* te);
};

#endif // MAINVIEW_H
