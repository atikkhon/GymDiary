#include "diarymodel.h"

DiaryModel::DiaryModel(QObject *parent)
    : QAbstractListModel{parent}, stringDate(QDate::currentDate().toString("dd.MM.yyyy"))
{
    qDebug() << stringDate;
    rebuildNoticesFromJson();
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

void DiaryModel::saveToJson(const QString &TypeOfExercise, const QString &Weight, const QString &Reps)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);

    QString filePath = path + "/GymDiary.json";

    QFile myFile(filePath);

    if (!myFile.exists())
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
    }

    QJsonObject doc_obj;
    QJsonArray trainings_arr;

    // Загрузка файла
    if (myFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Файл открылся";
        QByteArray Bytes = myFile.readAll();
        myFile.close();

        QJsonParseError JsonError;
        QJsonDocument Document = QJsonDocument::fromJson(Bytes, &JsonError);
        if (JsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "Error in json data: " << JsonError.errorString();
            return;
        }
        else
        {
            qDebug() << "No any errors in Json File";
        }

        if (Document.isObject())
        {
            doc_obj = Document.object();
            trainings_arr = doc_obj.value("trainings").toArray();
        }
    }
    // Данные из параметров
    QString newDate = stringDate;
    QString newExercise = TypeOfExercise;
    QString newWeight = Weight;
    QString newReps = Reps;

    bool trainingFound = false;
    bool exerciseFound = false;

    //Ищем нужную дату
    for (int i = 0; i < trainings_arr.size(); i++)
    {
        qDebug() << "************" << "Цикл по дате №: " << i << "*****************";
        QJsonObject training_obj = trainings_arr[i].toObject();

        qDebug() << "Текущая дата" << training_obj.value("date").toString();
        qDebug() << "Новая дата" << newDate;

        if (training_obj.value("date").toString() == newDate)
        {
            trainingFound = true;

            QJsonArray exercises_arr = training_obj.value("exercises").toArray();
            //Ищем упражнение внутри даты
            for (int j = 0; j < exercises_arr.size(); j++)
            {
                qDebug() << "************" << "Цикл по упражнениям №: " << j << "*****************";
                QJsonObject exercise_obj = exercises_arr[j].toObject();

                qDebug() << "Текущее упражнение" << exercise_obj.value("name").toString();
                qDebug() << "Новое упражнение" << newExercise;

                if (exercise_obj.value("name").toString() == newExercise)
                {
                    exerciseFound = true;

                    QJsonArray sets_arr = exercise_obj.value("sets").toArray();

                    //Добовляем новый подход
                    QJsonObject newSet;
                    newSet["weight"] = newWeight;
                    newSet["reps"] = newReps;
                    sets_arr.append(newSet);
                    exercise_obj["sets"] = sets_arr;
                    exercises_arr[j] = exercise_obj;

                    break;
                }
            }
            qDebug() << "Упражнение найдено?" << exerciseFound;
            // Если упражнение не найдено - создаём
            if(!exerciseFound)
            {
                QJsonObject new_exercise_obj;
                new_exercise_obj["name"] = newExercise;

                QJsonArray sets_arr;

                QJsonObject newSet;

                newSet["weight"] = newWeight;
                newSet["reps"]   = newReps;

                sets_arr.append(newSet);

                new_exercise_obj["sets"] = sets_arr;

                exercises_arr.append(new_exercise_obj);
            }
            training_obj["exercises"] = exercises_arr;
            trainings_arr[i] = training_obj;
            break;
        }
    }
    qDebug() << "Дата найдена?" << trainingFound;
    //Если дата не найдена - создаём новую тренировку
    if (!trainingFound)
    {
        QJsonObject new_training_obj;
        new_training_obj["date"] = newDate;

        QJsonArray exercises_arr;

        QJsonObject new_exercise_obj;
        new_exercise_obj["name"] = newExercise;

        QJsonArray sets_arr;

        QJsonObject newSet;

        newSet["weight"] = newWeight;
        newSet["reps"]   = newReps;

        sets_arr.append(newSet);

        new_exercise_obj["sets"] = sets_arr;

        exercises_arr.append(new_exercise_obj);

        new_training_obj["exercises"] = exercises_arr;
        trainings_arr.append(new_training_obj);
    }

    doc_obj["trainings"] = trainings_arr;
    QJsonDocument newDoc(doc_obj);

    if (myFile.open(QIODevice::WriteOnly))
    {
        myFile.write(newDoc.toJson(QJsonDocument::Indented));
        myFile.close();
        qDebug() << "JSON сохранён";
    }
    rebuildNoticesFromJson();
}

void DiaryModel::rebuildNoticesFromJson()
{
    QVector<Entry> newNotices;

    //Корректное открытие json в режиме чтения
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString filePath = path + "/GymDiary.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray bytes = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject())
        return;

    QJsonObject doc_obj = doc.object();
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
            QStringList sets_for_notice;
            // Добавляем все подходы в sets_for_notice
            for (int k = 0; k < sets.size(); ++k)
            {
                QJsonObject setObj = sets[k].toObject();
                QString weight = setObj.value("weight").toString();
                QString reps   = setObj.value("reps").toString();

                sets_for_notice.append(reps + "(" + weight + ")");
            }
            // Добавляем в структуру подходы
            notice.sets = sets_for_notice;
            // Добавляем запись в вектор записей
            newNotices.append(notice);
        }
    }
    beginResetModel();
    notices = std::move(newNotices);
    endResetModel();
    for (int i = 0; i < notices.size(); ++i) {
        const Entry &e = notices[i];
        qDebug() << i << e.date << e.exercise << e.sets;
    }
}
