#include <QtQuick>
#include <stdio.h>
#include <cstdlib>
//#include <QtGui>
//#include <QtPlugin>
#include <QTimer>
#include <QDebug>
#include "mainview.h"
#include "options.h"
#include "handler.h"

Q_IMPORT_PLUGIN(QsgEpaperPlugin)

MainView *VIEW;
int _qSize = 1404;


int readInt(std::string path) {

    QFile file(path.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Couldn't find the file " << path.c_str();
        return 0;
    }
    QTextStream in(&file);
    std::string text = in.readLine().toStdString();
    int number = std::stoi(text);

    return number;
}


std::string getBatteryLevel() {
    int charge_now = readInt(
        "/sys/class/power_supply/bq27441-0/charge_now"
    );
    int charge_full = readInt(
        "/sys/class/power_supply/bq27441-0/charge_full_design"
    );

    int battery_level = 100;
    if (charge_now < charge_full) {
        battery_level = (charge_now * 100/ charge_full);
    }
    qDebug() << "Got battery level " << battery_level;
    return std::to_string(battery_level) + "%";
}


void setBatteryLevel() {
    std::string battery_level = getBatteryLevel();
    QQuickItem*          root = VIEW->rootObject();
    root->setProperty(
        "battery_level",
        QVariant(getBatteryLevel().c_str())
    );
}


int main(int argc, char *argv[])
{
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");

    system("/usr/bin/button-capture &");


    srand(time(NULL));
    QGuiApplication app(argc, argv);
    MainView view;
    VIEW = &view;

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view.engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view.setSource(QDir(DEPLOYMENT_PATH).filePath("qml/Main.qml"));

    Options options(VIEW, &app);

    QQuickItem*    root = view.rootObject();
    root->setProperty("battery_icon",QVariant(("file://"+configDir+"/icons/batteryIcon.png").c_str()));
    setBatteryLevel();

    QTimer *timer = new QTimer();
    timer->connect(
        timer,
        &QTimer::timeout,
        VIEW,
        QOverload<>::of(setBatteryLevel)
    );
    // update the battery level every 10min
    timer->start(5000);

    view.show();
    return app.exec();
}
