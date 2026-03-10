#include "repsmodel.h"

RepsModel::RepsModel(QObject *parent) : QObject{parent}
{
    items = {"8", "9", "10", "11", "12", "13", "14", "15"};
}

QStringList RepsModel::visibleItems() const
{
    QStringList result;
    for(int i = 0; i < 4; i++)
    {
        int idx = index + i;
        if(idx < items.size())
            result << items[idx];
        else
            result << "";
    }
    return result;
}

void RepsModel::next()
{
    if(index + 4 < items.size())
    {
        index += 1;
        emit visibleItemsChanged();
    }
}

void RepsModel::prev()
{
    if(index > 0)
    {
        index -= 1;
        emit visibleItemsChanged();
    }
}

