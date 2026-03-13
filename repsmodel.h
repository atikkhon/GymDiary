#ifndef REPSMODEL_H
#define REPSMODEL_H

#include <QObject>
#include <QStringList>

class RepsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList repsVisibleItems READ repsVisibleItems NOTIFY repsVisibleItemsChanged FINAL)
    Q_PROPERTY(QStringList weightsVisibleItems READ weightsVisibleItems NOTIFY weightsVisibleItemsChanged FINAL)
public:
    explicit RepsModel(QObject *parent = nullptr);

    QStringList repsVisibleItems() const;
    QStringList weightsVisibleItems() const;

    Q_INVOKABLE void reps_next();
    Q_INVOKABLE void reps_prev();

    Q_INVOKABLE void weights_next();
    Q_INVOKABLE void weights_prev();

signals:
    void repsVisibleItemsChanged();
    void weightsVisibleItemsChanged();

private:
    QStringList makeVisibleItems(const QStringList &type, int index) const;
    QStringList m_reps;
    QStringList m_weights;
    int m_reps_i = 0;
    int m_weights_i = 0;
};

#endif // REPSMODEL_H
