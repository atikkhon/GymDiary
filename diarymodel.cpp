#include "diarymodel.h"

DiaryModel::DiaryModel(QObject *parent)
    : QAbstractListModel{parent}, stringDate(QDate::currentDate().toString("dd.MM.yyyy"))
{
    if (WasJsonExisting())
    {
        qDebug() << "Дсон существовал до вызова WasJsonExisting()";
        BuildNoticeFromJson();
    }
}

void DiaryModel::addingSetToJson(const QString &TypeOfExercise, const QString &Weight, const QString &Reps)
{
    QJsonObject doc_obj;
    if (!OpenJsonReadOnly(doc_obj)) return;

    QJsonArray trainings_arr;
    trainings_arr = doc_obj.value("trainings").toArray();

    bool trainingFound = false;
    bool exerciseFound = false;

    //Ищем нужную дату
    for (int i = 0; i < trainings_arr.size(); i++)
    {
        QJsonObject training_obj = trainings_arr[i].toObject();
        if (training_obj.value("date").toString() == stringDate)
        {
            trainingFound = true;
            QJsonArray exercises_arr = training_obj.value("exercises").toArray();
            //Ищем упражнение внутри даты
            for (int j = 0; j < exercises_arr.size(); j++)
            {
                QJsonObject exercise_obj = exercises_arr[j].toObject();
                if (exercise_obj.value("name").toString() == TypeOfExercise)
                {
                    exerciseFound = true;
                    QJsonArray sets_arr = exercise_obj.value("sets").toArray();
                    //Добовляем новый подход
                    QJsonObject newSet;
                    newSet["weight"] = Weight;
                    newSet["reps"] = Reps;
                    sets_arr.append(newSet);
                    exercise_obj["sets"] = sets_arr;
                    exercises_arr[j] = exercise_obj;
                    break;
                }
            }
            // Если упражнение не найдено - создаём
            if(!exerciseFound)
            {
                QJsonObject new_exercise_obj;
                new_exercise_obj["name"] = TypeOfExercise;
                QJsonArray sets_arr;
                QJsonObject newSet;
                newSet["weight"] = Weight;
                newSet["reps"]   = Reps;
                sets_arr.append(newSet);
                new_exercise_obj["sets"] = sets_arr;
                exercises_arr.append(new_exercise_obj);
            }
            training_obj["exercises"] = exercises_arr;
            trainings_arr[i] = training_obj;
            break;
        }
    }
    //Если дата не найдена - создаём новую тренировку
    if (!trainingFound)
    {
        QJsonObject new_training_obj;
        new_training_obj["date"] = stringDate;
        QJsonArray exercises_arr;
        QJsonObject new_exercise_obj;
        new_exercise_obj["name"] = TypeOfExercise;
        QJsonArray sets_arr;
        QJsonObject newSet;
        newSet["weight"] = Weight;
        newSet["reps"]   = Reps;
        sets_arr.append(newSet);
        new_exercise_obj["sets"] = sets_arr;
        exercises_arr.append(new_exercise_obj);
        new_training_obj["exercises"] = exercises_arr;
        trainings_arr.append(new_training_obj);
    }

    doc_obj["trainings"] = trainings_arr;

    if (!OpenJsonWriteOnly(doc_obj))
        return;
    else
        BuildNoticeFromJson();
}

void DiaryModel::BuildNoticeFromJson()
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
    notices = std::move(newNotices);
    endResetModel();   
}

void DiaryModel::recreateJson()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    file.remove();
    notices.clear();
    QFile templateFile(":/database/GymDiary.json");
    if (templateFile.open(QIODevice::ReadOnly))
    {
        QByteArray data = templateFile.readAll();
        templateFile.close();
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(data);
            file.close();
        }
    }
    BuildNoticeFromJson();
}

Entry DiaryModel::getEntry()
{

}

bool DiaryModel::WasJsonExisting()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QString filePath = path + "/GymDiary.json";
    QFile myFile(filePath);

    if (myFile.exists())
    {
        return true; //Json существовал до вызова WasJsonExisting()
    }
    else
    {
        QFile templateFile(":/database/GymDiary.json");
        if (templateFile.open(QIODevice::ReadOnly))
        {
            QByteArray data = templateFile.readAll();
            templateFile.close();

            if (myFile.open(QIODevice::WriteOnly))
            {
                myFile.write(data);
                myFile.close();
            }
        }
        return false; //Json не существовал до вызова WasJsonExisting()
    }
}

bool DiaryModel::OpenJsonReadOnly(QJsonObject & doc_obj)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QByteArray bytes = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject())
        return false;
    doc_obj = doc.object();
    return true;
}

bool DiaryModel::OpenJsonWriteOnly(QJsonObject & doc_obj)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    QJsonDocument newDoc(doc_obj);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    else
    {
        file.write(newDoc.toJson(QJsonDocument::Indented));
        file.close();
        return true;
    }
}

int DiaryModel::rowCount(const QModelIndex &) const
{
    return notices.size();
}

QVariant DiaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const int row = index.row();
    if (row < 0 || row >= notices.size())
        return {};

    const Entry &e = notices.at(row);

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
