#include <QtQuick>
//#include <QtGui>
//#include <QtPlugin>
#include "mainview.h"

Q_IMPORT_PLUGIN(QsgEpaperPlugin)

int main(int argc, char *argv[])
{
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
//    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "/dev/input/event1");
//    qputenv("QT_QPA_EGLFS_NO_LIBINPUT", "1");

    QGuiApplication app(argc, argv);
    MainView view;

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view.engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view.setSource(QDir(DEPLOYMENT_PATH).filePath("qml/Main.qml"));
    view.show();

    qDebug() << "view shown";
    return app.exec();
}
