#include "options.h"
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QSet>
#include <QDebug>
#include "version.h"

QList<QObject*> Options::getOptions(){

    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QList<QObject*> result;
    // If the config directory doesn't exist,
    // then print an error and stop.
    QDir directory(configDir);
    if (!directory.exists() || configDir.isEmpty())
    {
        qCritical() << "Failed to read directory - it does not exist.> " << configDir;
        return result;
    }


    directory.setFilter( QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    auto images = directory.entryInfoList(QDir::NoFilter,QDir::SortFlag::Name);
    foreach(QFileInfo fi, images) {
        auto f = fi.absoluteFilePath();

        qDebug() << "parsing file " << f;

        QFile file(fi.absoluteFilePath());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCritical() << "Couldn't find the file " << f;
            continue;
        }

        QTextStream in(&file);

        OptionItem *opt= new OptionItem();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("=");
            if(parts.length() != 2){
                qWarning() << "wrong format on " << line;
                continue;
            }
            QString lhs= parts.at(0);
            QString rhs= parts.at(1);
            QSet<QString> known = {"name","desc","call"};
            if (known.contains(lhs)){
                opt->setProperty(lhs.toUtf8(), rhs);
            }
        }
        if(opt->ok())
            result.append(opt);
    }
    return result;
}

QString Options::getVersion()
{
    return VERSION;
}


