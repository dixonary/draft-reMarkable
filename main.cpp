#include <QtQuick>
//#include <QtGui>
//#include <QtPlugin>
#include "mainview.h"
#include "options.h"
#include "handler.h"
#ifdef RM
Q_IMPORT_PLUGIN(QsgEpaperPlugin)
#endif

int main(int argc, char *argv[])
{
#ifdef RM
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");
#endif

    QGuiApplication app(argc, argv);
    MainView view;

    srand(time(NULL));

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view.setSource(QUrl("qrc:/qml/Main.qml"));
    view.show();

    Options options(&view, &app);

    return app.exec();
}
