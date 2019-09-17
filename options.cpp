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
            std::string line = in.readLine().toStdString();
            if(line.length() > 0) {
                size_t sep = line.find("=");
                if(sep != line.npos) {
                    std::string lhs = line.substr(0,sep);
                    std::string rhs = line.substr(sep+1);

                    if     (lhs == "name")     {
                        if (rhs == ""){
                            continue;
                        }
                                opt->setProperty("name", rhs.c_str());
                    }
                    else if(lhs == "desc")  opt->setProperty("desc", rhs.c_str());
                    else if(lhs == "call")  opt->setProperty("call", rhs.c_str());

                    else std::cout << "ignoring unknown parameter \"" << line
                                   << "\" in file \"" << f << "\"" << std::endl;
                }
            }
            else {
                std::cout << "ignoring malformed line \"" << line
                          << "\" in file \"" << f << "\"" << std::endl;
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


