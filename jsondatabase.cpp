#include "jsondatabase.h"

JsonDataBase::JsonDataBase(QObject *parent)
    : QObject{parent}, stringDate(QDate::currentDate().toString("dd.MM.yyyy"))
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    if (!file.exists())
        CreateJson();
    else
        ReadJson();
}

bool JsonDataBase::ReadJson()
{
    m_days.clear();
    QJsonObject doc_obj;

    //Корректное открытие json в режиме чтения
    if (!OpenJsonReadOnly(doc_obj)) return false;

    QJsonArray trainings = doc_obj.value("trainings").toArray();
    for (int i = 0; i < trainings.size(); ++i)
    {
        QJsonObject training_obj = trainings[i].toObject();
        QString date = training_obj.value("date").toString();

        TrainingDay training_day;// Гарантирует заполнение одной датой этого объекта
        training_day.date = date;

        QJsonArray exercises = training_obj.value("exercises").toArray();
        for (int j = 0; j < exercises.size(); ++j)
        {
            QJsonObject exercise_obj = exercises[j].toObject();
            QString exercise = exercise_obj.value("name").toString();

            Exercise domain_exercise;
            domain_exercise.name = exercise;//

            QJsonArray sets = exercise_obj.value("sets").toArray();
            for (int k = 0; k < sets.size(); ++k)
            {
                QJsonObject setObj = sets[k].toObject();
                QString weight = setObj.value("weight").toString();
                QString reps   = setObj.value("reps").toString();

                Set domain_set;// В одном урпажнении несколько подходов могут быть
                domain_set.weight = weight;
                domain_set.reps = reps;
                domain_exercise.sets.append(domain_set);
            }
            training_day.exercises.append(domain_exercise);
        }
        m_days.append(training_day);
    }
    return true;
}

void JsonDataBase::AddSet(const QString &typeOfExercise, const QString &weight, const QString &reps)
{
    const QString date = stringDate; // или передавай date параметром

    // 1) Найти день (или создать)
    int dayIndex = -1;
    for (int i = 0; i < m_days.size(); ++i) {
        if (m_days[i].date == date) {
            dayIndex = i;
            break;
        }
    }

    if (dayIndex == -1) {
        TrainingDay newDay;
        newDay.date = date;
        m_days.append(newDay);
        dayIndex = m_days.size() - 1;
    }

    // 2) Найти упражнение в этом дне (или создать)
    auto &exercises = m_days[dayIndex].exercises;

    int exIndex = -1;
    for (int j = 0; j < exercises.size(); ++j) {
        if (exercises[j].name == typeOfExercise) {
            exIndex = j;
            break;
        }
    }

    if (exIndex == -1) {
        Exercise newExercise;
        newExercise.name = typeOfExercise;
        exercises.append(newExercise);
        exIndex = exercises.size() - 1;
    }

    // 3) Добавить подход
    Set s;
    s.weight = weight;
    s.reps   = reps;
    exercises[exIndex].sets.append(s);

    //if (WriteJson()) НАДО СДЕЛАТЬ ОБНОВЛЕНИЕ МОДЕЛЕЙ или емит сигнала

}

bool JsonDataBase::WriteJson()
{
    QJsonArray trainingsArr;

    for (int i = 0; i < m_days.size(); ++i) {
        TrainingDay &day = m_days[i];

        QJsonObject trainingObj;
        trainingObj["date"] = day.date;

        QJsonArray exercisesArr;
        for (int j = 0; j < day.exercises.size(); ++j) {
            Exercise &ex = day.exercises[j];

            QJsonObject exerciseObj;
            exerciseObj["name"] = ex.name;

            QJsonArray setsArr;
            for (int k = 0; k < ex.sets.size(); ++k) {
                Set &s = ex.sets[k];

                QJsonObject setObj;
                setObj["weight"] = s.weight;
                setObj["reps"]   = s.reps;
                setsArr.append(setObj);
            }

            exerciseObj["sets"] = setsArr;
            exercisesArr.append(exerciseObj);
        }

        trainingObj["exercises"] = exercisesArr;
        trainingsArr.append(trainingObj);
    }
    QJsonObject doc_obj;
    doc_obj["trainings"] = trainingsArr;

    QJsonDocument doc(doc_obj);

    if (!OpenJsonWriteOnly(doc))
        return false;
    else
        return true;
}

bool JsonDataBase::CreateJson()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    QFile templateFile(":/database/GymDiary.json");
    if(!templateFile.open(QIODevice::ReadOnly))
        return false;
    else
    {
        QByteArray data = templateFile.readAll();
        templateFile.close();

        if (!file.open(QIODevice::WriteOnly))
            return false;
        else
        {
            file.write(data);
            file.close();
        }
    }
    return true;
}

bool JsonDataBase::RemoveJson()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    if (file.exists())
    {
        file.remove();
        return true;
    }
    else
    {
        return false;
    }
}

bool JsonDataBase::OpenJsonReadOnly(QJsonObject &doc_obj)
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

bool JsonDataBase::OpenJsonWriteOnly(QJsonDocument &doc)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    else
    {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        return true;
    }
}
