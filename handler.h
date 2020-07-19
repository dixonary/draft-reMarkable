#pragma once

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <QtGui>
#include "mainview.h"
#include <time.h>

extern time_t lastReturn;
extern int gotEvents;
extern int qSize;

class Handler : public QObject
{
    Q_OBJECT
public:
    Handler(std::string lT, std::string term, QGuiApplication* app, MainView* mainView, QObject* obj);
    ~Handler();
    bool eventFilter(QObject* obj, QEvent* event);
    void handleEvent();

private:
    std::string link;
    std::string term;
    QObject* ef;
    QGuiApplication* app;
    MainView* mainView;
};
