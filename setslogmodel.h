#ifndef SETSLOGMODEL_H
#define SETSLOGMODEL_H

#include <qqml.h>
#include <jsondatabase.h>
#include <domain.h>
#include <QObject>
#include <QAbstractListModel>
#include <algorithm>

class SetsLogModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(JsonDataBase* db READ db WRITE setDb NOTIFY dbChanged FINAL);
public:
    explicit SetsLogModel(QObject *parent = nullptr);

    enum LogRoles
    {
        date = Qt::UserRole + 1,
        exercise,
        lastset
    };
    JsonDataBase* db();

    void setDb(JsonDataBase* db);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void dbChanged();

private slots:
    void RebuildLogFromDb();

private:
    struct LogNotice {
        QString date;
        QString exercise;
        QString set;
        int set_id = 0;
    };
    QVector<LogNotice> LogNotices;
    JsonDataBase *m_db = nullptr;
};

#endif // SETSLOGMODEL_H
