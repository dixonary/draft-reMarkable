#include "handler.h"
#include "mainview.h"
#include <QtQuick>
#include <QString>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

time_t lastReturn;
int qSize = 1404;

Handler::Handler(std::string lT, std::string term, QGuiApplication* app, MainView* mainView, QObject* obj)
    : link(lT), term(term), ef(obj), app(app), mainView(mainView){

    time(&lastReturn);

}

bool Handler::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        obj->parent()->setProperty("color", QVariant("#22000000"));
        return true;
    }

    else if (event->type() == QEvent::MouseButtonRelease) {
        obj->parent()->setProperty("color", QVariant("white"));
        time_t tim;
        time(&tim);
        // 1 second cooldown before opening again!
        if(difftime(tim, lastReturn) > 1) {
            handleEvent();
        }
        return true;
    }
    else
        return false;
}

void Handler::handleEvent() {

    std::cout << "Setting termfile /etc/draft/.terminate" << std::endl;
    std::ofstream termfile;
    termfile.open("/etc/draft/.terminate");
    termfile << term << std::endl;

    std::cout << "Running command " << link << "..." << std::endl;
    system((link).c_str());

    // Don't exit any more - just head back to the launcher!
    std::cout << "Running again" << std::endl;

    // Yes, this is an exceptionally hacky way of repainting the screen
    qSize = 1-(qSize-1403)+1403;

    usleep(500000);

    mainView->rootObject()->setProperty("width",QVariant(qSize));

    // Cooldown
    time(&lastReturn);

}

Handler::~Handler() {
    ef->removeEventFilter(this);
}
