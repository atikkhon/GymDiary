#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <qqml.h>
#include <QObject>
#include <QAbstractTableModel>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    enum TableRoles
    {
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };

public:
    explicit TableModel(QObject *parent = nullptr);

    Q_INVOKABLE void setExerciseType(const QString &text1, const QString &text2, const QString &text3);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
private:
    QVector<QVector<QString>> table;
};

#endif // TABLEMODEL_H
