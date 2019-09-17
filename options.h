#pragma once

#include <QObject>
#include <stdlib.h>
#include "option_item.h"

class Options
{
public:
    Options();
    QList<QObject*> GetOptions();
private:
    bool read_directory(const std::string name, std::vector<std::string>& files);
    void error(std::string text);
    void createOption(OptionItem &option, int index);
};
