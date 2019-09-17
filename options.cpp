#include "options.h"
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QSet>
#include <QDebug>

// Create options and add them to the screen.
Options::Options()
{
}

QList<QObject*> Options::GetOptions(){
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    std::vector<std::string> filenames;
    QList<QObject*> result;
    // If the config directory doesn't exist,
    // then print an error and stop.


    QDir directory(configDir);
    if (!directory.exists() || configDir.isEmpty())
    {
        Options::error("Failed to read directory - it does not exist.> " + configDir.toStdString());
        return result;
    }


    directory.setFilter( QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    auto images = directory.entryInfoList(QDir::NoFilter,QDir::SortFlag::Name);
    foreach(QFileInfo fi, images) {
        auto f = fi.absoluteFilePath().toStdString();

        std::cout << "parsing file " << f << std::endl;

        QFile file(fi.absoluteFilePath());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Options::error("Couldn't find the file " + f+ ".");
            continue;
        }

        QTextStream in(&file);

        OptionItem *opt= new OptionItem();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("=");
            if(parts.length() != 2){
                qDebug() << "wrong format on " << line;
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



void Options::error(std::string text) {
    std::cerr << "!! Error: " << text << std::endl;
}


