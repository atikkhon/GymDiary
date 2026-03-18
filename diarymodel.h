#ifndef DIARYMODEL_H
#define DIARYMODEL_H

#include <qqml.h>
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

    Q_INVOKABLE void addingSetToJson(const QString &TypeOfExercise, const QString &Weight, const QString &Reps);

    Q_INVOKABLE void recreateJson();

    Q_INVOKABLE Entry getEntry();

private:
    QVector<Entry> notices;
    QString stringDate;
    bool WasJsonExisting();
    bool OpenJsonReadOnly(QJsonObject & doc_obj);
    bool OpenJsonWriteOnly(QJsonObject & doc_obj);
    void BuildNoticeFromJson();
};

#endif // DIARYMODEL_H
