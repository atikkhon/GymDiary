#ifndef DOMAIN_H
#define DOMAIN_H
#include <QString>
#include <QVector>

struct Set {
    int id = 0;
    QString weight;
    QString reps;
};

struct Exercise {
    QString name;
    QVector<Set> sets;
};

struct TrainingDay {
    QString date;
    QVector<Exercise> exercises;
};

#endif // DOMAIN_H
