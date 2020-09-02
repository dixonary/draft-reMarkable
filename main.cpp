#include <QtQuick>
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


void suspend() {
    qDebug() << "Suspending";
    system("systemctl suspend");
    gotEvents+=1;
}


void restoreSuspendBanner() {
    QQuickItem* root = VIEW->rootObject();
    root->setProperty(
        "suspend_banner_text",
        QVariant("")
    );
}


void suspendIfInactive() {
    qDebug() << "Checking if it should suspend...";
    QQuickItem* root = VIEW->rootObject();
    if (gotEvents != 0) {
        root->setProperty(
            "suspend_banner_text",
            QVariant("")
        );
        gotEvents = 0;
        qDebug() << "Not suspending!";
        return;
     }

    qDebug() << "Suspending!";
    root->setProperty(
        "suspend_banner_text",
        QVariant("Suspended, press any button to continue.")
    );
    // Give it time to show the banner
    qDebug() << "waiting for the banner to appear...";
    qSize = 1-(qSize-1403)+1403;
    root->setProperty("width",QVariant(qSize));
    QTimer *wait_for_timer = new QTimer();
    // Give it time to show the banner
    wait_for_timer->singleShot(
        1000,
        VIEW,
        QOverload<>::of(suspend)
    );
    wait_for_timer->singleShot(
        2000,
        VIEW,
        QOverload<>::of(restoreSuspendBanner)
    );
    // after returning from sleep, refresh the battery
    wait_for_timer->singleShot(
        3000,
        VIEW,
        QOverload<>::of(setBatteryLevel)
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

    QTimer *battery_timer = new QTimer();
    battery_timer->connect(
        battery_timer,
        &QTimer::timeout,
        VIEW,
        QOverload<>::of(setBatteryLevel)
    );
    // update the battery level every 10min
    battery_timer->start(600000);

    QTimer *suspend_timer = new QTimer();
    suspend_timer->connect(
        suspend_timer,
        &QTimer::timeout,
        VIEW,
        QOverload<>::of(suspendIfInactive)
    );
    // check if we should suspend every 20 min
    suspend_timer->start(1200000);

    view.show();
    return app.exec();
}
