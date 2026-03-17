#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent), stringDate(QDate::currentDate().toString("dd.MM.yyyy")) {
    table.append({"Дата", "Упражнение", "Доп. вес", "Повторы"});
    qDebug() << stringDate;
}

void TableModel::setExerciseType(const QString &text1, const QString &text2, const QString &text3)
{
    int newRow = table.size();

    beginInsertRows(QModelIndex(), newRow, newRow);
    table.append({stringDate, text1, text2, text3});
    endInsertRows();
    saveToJson({stringDate ,text1, text2, text3});
}

void TableModel::rebuildTableFromJson()
{
    table1.clear();

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

    QJsonObject rootObj = doc.object();
    QJsonArray trainings = rootObj.value("trainings").toArray();

    // Проходим по датам
    for (int i = 0; i < trainings.size(); ++i)
    {
        QJsonObject trainingObj = trainings[i].toObject();
        QString date = trainingObj.value("date").toString();

        QJsonArray exercises = trainingObj.value("exercises").toArray();

        // Проходим по упражнениям
        for (int j = 0; j < exercises.size(); ++j)
        {
            QJsonObject exerciseObj = exercises[j].toObject();
            QString exerciseName = exerciseObj.value("name").toString();

            QJsonArray sets = exerciseObj.value("sets").toArray();

            QVector<QString> row;

            // Первая строка дня содержит дату
            if (j == 0)
                row.append(date);
            else
                row.append("");

            row.append(exerciseName);

            // Добавляем все подходы
            for (int k = 0; k < sets.size(); ++k)
            {
                QJsonObject setObj = sets[k].toObject();
                QString weight = setObj.value("weight").toString();
                QString reps   = setObj.value("reps").toString();

                row.append(weight + " " + reps);
            }

            table1.append(row);
        }
    }

    qDebug() << "Таблица пересобрана:";
    qDebug() << table1;

    beginResetModel();
    endResetModel();
    emit getTableChanged();
}

QVariantList TableModel::getTable()
{
    QVariantList outerList;

    for (const auto &row : table1)
    {
        QVariantList innerList;
        for (const auto &cell : row)
        {
            innerList.append(cell);
        }
        outerList.append(innerList);
    }

    return outerList;
}

void TableModel::saveToJson(const QStringList &text)
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
//18d1
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
    QString newDate = text[0];
    QString newExercise = text[1];
    QString newWeight = text[2];
    QString newReps = text[3];

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
    rebuildTableFromJson();
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size(); //number of rows
}

int TableModel::columnCount(const QModelIndex &) const
{
    return table.at(0).size(); //number of columns
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case TableDataRole:
        {
            return table.at(index.row()).at(index.column());
        }
        case HeadingRole:
        {
            if (index.row()==0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        default:
            break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}
