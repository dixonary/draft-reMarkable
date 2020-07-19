#pragma once

#include <QObject>
#include <QQuickView>
#include <QDebug>
#include <QGuiApplication>
#include "mainview.h"

const extern std::string configDir;

struct OptionItem {
    std::string name;
    std::string desc;
    std::string call;
    std::string term;
    std::string imgFile;
    QObject*    object;
    QObject*    handler;
};

class Options
{
public:
    Options(MainView* mainView, QGuiApplication* app);
    bool read_directory(const std::string name, std::vector<std::string>& files);
private:
    void error(std::string text);
    void createOption(OptionItem &option, size_t index);

    MainView* mainView;
    QQuickItem* optionsView;
    std::vector<OptionItem> optionList;
    QGuiApplication* app;
};
