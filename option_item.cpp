#include "option_item.h"

bool OptionItem::ok() {
    return ! (_name.isEmpty() && _call.isEmpty());
}

void OptionItem::execute()
{
    system(_call.toUtf8());
}
