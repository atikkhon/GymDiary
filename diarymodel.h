#ifndef DIARYMODEL_H
#define DIARYMODEL_H

#include <qqml.h>
#include <jsondatabase.h>
#include <domain.h>
#include <QObject>
#include <QAbstractListModel>
#include <QStandardPaths>
#include <QtCore>
#include <QDate>

// структура, которая будет в записях
struct Entry {
    QString date;
    QString exercise;
    QStringList sets;
};

class DiaryModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum DiaryRoles
    {
        date = Qt::UserRole + 1,
        exercise,
        sets
    };

    explicit DiaryModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Entry> DiaryNotices;
    void BuildDiaryFromJson();
};

#endif // DIARYMODEL_H
