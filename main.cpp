#include <QtQuick>
//#include <QtGui>
//#include <QtPlugin>
#include "mainview.h"
#include "options.h"
#include "handler.h"

Q_IMPORT_PLUGIN(QsgEpaperPlugin)

int main(int argc, char *argv[])
{
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");

    system("systemctl start button-capture");

    QGuiApplication app(argc, argv);
    MainView view;

    srand(time(NULL));

    view.rootContext()->setContextProperty("screenGeometry", app.primaryScreen()->geometry());
    view.engine()->addImportPath(QStringLiteral(DEPLOYMENT_PATH));
    view.setSource(QDir(DEPLOYMENT_PATH).filePath("qml/Main.qml"));
    view.show();

    Options options(&view, &app);

    return app.exec();
}
