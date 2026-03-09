#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    table.append({"Дата", "Упражнение", "Доп. вес", "Повторы"});

}

void TableModel::setExerciseType(const QString &text1, const QString &text2, const QString &text3)
{
    int newRow = table.size();

    beginInsertRows(QModelIndex(), newRow, newRow);
    table.append({"10.11", text1, text2, text3});
    endInsertRows();
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size(); //number of rows
}

int TableModel::columnCount(const QModelIndex &) const
{
    return table.at(0).size(); //number of columns
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case TableDataRole:
        {
            return table.at(index.row()).at(index.column());
        }
        case HeadingRole:
        {
            if (index.row()==0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        default:
            break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}
