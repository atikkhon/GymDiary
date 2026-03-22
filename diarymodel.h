#ifndef DIARYMODEL_H
#define DIARYMODEL_H

#include <jsondatabase.h>
#include <domain.h>
#include <QObject>
#include <QAbstractListModel>

class DiaryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(JsonDataBase* db READ db WRITE setDb NOTIFY dbChanged FINAL);

public:

    enum DiaryRoles
    {
        date = Qt::UserRole + 1,
        exercise,
        sets
    };

    explicit DiaryModel(QObject *parent = nullptr);

    JsonDataBase* db();

    void setDb(JsonDataBase* db);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void dbChanged();

private slots:
    void RebuildDiaryFromDb();

private:
    struct DiaryNotice {
        QString date;
        QString exercise;
        QStringList sets;
    };
    QVector<DiaryNotice> DiaryNotices;
    JsonDataBase *m_db = nullptr;
};

#endif // DIARYMODEL_H
