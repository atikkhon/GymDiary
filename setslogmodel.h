#ifndef SETSLOGMODEL_H
#define SETSLOGMODEL_H

#include <qqml.h>
#include <jsondatabase.h>
#include <domain.h>
#include <QObject>
#include <QAbstractListModel>

class SetsLogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SetsLogModel(QObject *parent = nullptr);

signals:

private:
    QVector<Entry> SetsLogNotices;
    void BuildSetsLogFromJson();
};

#endif // SETSLOGMODEL_H
