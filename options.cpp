#include "options.h"
#include "handler.h"
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include <QtQuick>
#include <algorithm>


//TODO: do not hard code
const std::string configDir = "/home/root/.draft/";

// Create options and add them to the screen.
Options::Options(MainView* mainView, QGuiApplication* app) :
    mainView(mainView),
    optionsView(mainView->rootObject()->findChild<QQuickItem*>("optionsArea")),
    app(app)
{

    std::vector<std::string> filenames;

    // If the config directory doesn't exist,
    // then print an error and stop.
    if(!Options::read_directory(configDir, filenames)) {
        Options::error("Failed to read directory - it does not exist.> " + configDir);
        return;
    }

    std::sort(filenames.begin(), filenames.end());

    for(std::string f : filenames) {

        std::cout << "parsing file " << f << std::endl;
        QFile file((configDir + "/" + f).c_str());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Options::error("Couldn't find the file " + f + ".");
            break;
        }

        QTextStream in(&file);

        OptionItem opt;

        while (!in.atEnd()) {
            std::string line = in.readLine().toStdString();
            if(line.length() > 0) {
                size_t sep = line.find("=");
                if(sep != line.npos) {
                    std::string lhs = line.substr(0,sep);
                    std::string rhs = line.substr(sep+1);

                    if     (lhs == "name")     opt.name    = rhs;
                    else if(lhs == "desc")     opt.desc    = rhs;
                    else if(lhs == "imgFile")  opt.imgFile = rhs;
                    else if(lhs == "call")     opt.call    = rhs;
                    else if(lhs == "term")     opt.term    = rhs;
                    else std::cout << "ignoring unknown parameter \"" << line
                                   << "\" in file \"" << f << "\"" << std::endl;
                }
            }
            else {
                std::cout << "ignoring malformed line \"" << line
                          << "\" in file \"" << f << "\"" << std::endl;
            }
        }

        if(opt.call == "" || opt.term == "") continue;
        createOption(opt, optionList.size());
        optionList.push_back(opt);

    }

}

void Options::createOption(OptionItem &option, int index) {

    QQuickView* opt  = new QQuickView();
    opt->setSource(QUrl("qrc:/qml/MenuItem.qml"));
    opt->show();

    QQuickItem* root = opt->rootObject();
    root->setProperty("itemNumber", index);
    root->setParentItem(optionsView);

    root->setProperty("t_name",QVariant(option.name.c_str()));
    root->setProperty("t_desc",QVariant(option.desc.c_str()));
    root->setProperty("t_imgFile",QVariant(("file://"+configDir+"/icons/"+option.imgFile+".png").c_str()));

    QObject* mouseArea = root->children().at(0);
    Handler* handler = new Handler(option.call, option.term, app, mainView, mouseArea);
    root->children().at(0)->installEventFilter(handler);

    option.object = opt;
    option.handler = handler;
}

void Options::error(std::string text) {
    std::cout << "!! Error: " << text << std::endl;
}


// Stolen shamelessly from Martin Broadhurst
bool Options::read_directory(const std::string name,
                             std::vector<std::string>& filenames)
{
	//todo: use QDir
    DIR* dirp = opendir(name.c_str());
    if(dirp == nullptr) {
        return false;
    }

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::string dn = dp->d_name;

        if(dn == "." || dn == ".."|| dn == "icons") continue;

        filenames.push_back(dn);
    }
    closedir(dirp);
    return true;
}
