#include <QtGui>
#include <QtQuick>
#include <QtPlugin>
#include "backend.h"
#include "mainview.h"

Q_IMPORT_PLUGIN(QsgEpaperPlugin)

int main(int argc, char *argv[])
{
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");

    QGuiApplication app(argc, argv);
    MainView view;
    // exit gracefully on kill signal
    QObject::connect(view.engine(),SIGNAL(quit()),&app,SLOT(quit()));

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    Backend backend;
    view.rootContext()->setContextProperty("backend", &backend);
    view.engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view.setSource(QDir(DEPLOYMENT_PATH).filePath("qml/Main.qml"));
    view.show();

    qDebug() << "view shown";
    return app.exec();
}
