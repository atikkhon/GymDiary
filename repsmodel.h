#ifndef REPSMODEL_H
#define REPSMODEL_H

#include <QObject>
#include <QStringList>

class RepsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList visibleItems READ visibleItems NOTIFY visibleItemsChanged FINAL);
public:
    explicit RepsModel(QObject *parent = nullptr);

    QStringList visibleItems() const;

    Q_INVOKABLE void next();
    Q_INVOKABLE void prev();

signals:
    void visibleItemsChanged();

private:
    QStringList items;
    int index = 0;
};

#endif // REPSMODEL_H
