#include "diarymodel.h"

DiaryModel::DiaryModel(QObject *parent)
    : QAbstractListModel{parent}
{

}


void DiaryModel::BuildDiaryFromJson()
{
    QVector<Entry> newNotices;
    QJsonObject doc_obj;

    //Корректное открытие json в режиме чтения
    if (!OpenJsonReadOnly(doc_obj)) return;

    QJsonArray trainings = doc_obj.value("trainings").toArray();
    // Проходим по датам
    for (int i = 0; i < trainings.size(); ++i)
    {
        QJsonObject training_obj = trainings[i].toObject();
        QString date = training_obj.value("date").toString();
        QJsonArray exercises = training_obj.value("exercises").toArray();
        // Проходим по упражнениям
        for (int j = 0; j < exercises.size(); ++j)
        {
            // Объект структуры - хранит запись
            Entry notice;
            QJsonObject exercise_obj = exercises[j].toObject();
            QString exercise = exercise_obj.value("name").toString();
            // Добавляем дату в структуру
            notice.date = date;
            //Добавляем имя упражнения в структуру
            notice.exercise = exercise;
            QJsonArray sets = exercise_obj.value("sets").toArray();
            for (int k = 0; k < sets.size(); ++k)
            {
                QJsonObject setObj = sets[k].toObject();
                QString weight = setObj.value("weight").toString();
                QString reps   = setObj.value("reps").toString();
                //Добавляем подходы в структуру
                notice.sets.append(reps + "(" + weight + ")");
            }
            // Добавляем запись в вектор записей
            newNotices.append(notice);
        }
    }
    beginResetModel();
    DiaryNotices = std::move(newNotices);
    endResetModel();   
}

int DiaryModel::rowCount(const QModelIndex &) const
{
    return DiaryNotices.size();
}

QVariant DiaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const int row = index.row();
    if (row < 0 || row >= DiaryNotices.size())
        return {};

    const Entry &e = DiaryNotices.at(row);

    switch (role) {
    case date:
        return e.date;       // QString упакуется в QVariant автоматически
    case exercise:
        return e.exercise;   // QString
    case sets:
        return e.sets;       // QStringList тоже упакуется в QVariant
    default:
        return {};
    }
}

QHash<int, QByteArray> DiaryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(date, "date");
    roles.insert(exercise, "exercise");
    roles.insert(sets, "sets");
    return roles;
}
