#include <QtGui>
#include <QtQuick>
#include <QtPlugin>
Q_IMPORT_PLUGIN(QsgEpaperPlugin)

int main(int argc, char *argv[])
{
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");

    QGuiApplication app(argc, argv);
    QQuickView view;
    // exit gracefully on kill signal
    QObject::connect(view.engine(),SIGNAL(quit()),&app,SLOT(quit()));

    view.engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view.setSource(QDir(DEPLOYMENT_PATH).filePath("qml/Main.qml"));
    view.show();
    return app.exec();
}
