#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QQuickView>
#include <QKeyEvent>
#include <QMouseEvent>
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
};

#endif // MAINVIEW_H
