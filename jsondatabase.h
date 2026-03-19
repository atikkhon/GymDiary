#ifndef JSONDATABASE_H
#define JSONDATABASE_H

#include <domain.h>
#include <QObject>
#include <QDate>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

class JsonDataBase : public QObject
{
    Q_OBJECT
public:
    explicit JsonDataBase(QObject *parent = nullptr);

    void AddSet(const QString &TypeOfExercise, const QString &Weight, const QString &Reps);
    bool RemoveJson();
    bool ReadJson();
    bool WriteJson();

signals:

private:
    QVector<TrainingDay> m_days;
    QString stringDate;
    bool CreateJson();
    bool OpenJsonReadOnly(QJsonObject & doc_obj);
    bool OpenJsonWriteOnly(QJsonDocument & doc);
};

#endif // JSONDATABASE_H
