#include <QtQuick>
#include "options.h"
#ifdef RM
#include <QtPlugin>
Q_IMPORT_PLUGIN(QsgEpaperPlugin)
#endif

int main(int argc, char *argv[])
{
#ifdef RM
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");
    qputenv("QT_QPA_GENERIC_PLUGINS", "evdevtablet");
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine view;
    Options controller;
    qmlRegisterType<OptionItem>();
    qmlRegisterType<Options>();
    QList<QObject*> list = controller.GetOptions();

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view.rootContext()->setContextProperty("options", QVariant::fromValue(list));
    view.rootContext()->setContextProperty("controller", &controller);

    view.load(QUrl("qrc:/Main.qml"));

    return app.exec();
}
