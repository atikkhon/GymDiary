#include "repsmodel.h"

RepsModel::RepsModel(QObject *parent) : QObject{parent}
{
    m_reps = {"8", "9", "10", "11", "12", "13", "14", "15"};
    m_weights = {"5 кг", "10 кг", "12.5 кг", "16 кг", "24 кг", "32 кг"};
}

QStringList RepsModel::makeVisibleItems(const QStringList &type, int index) const
{
    QStringList result;
    for(int i = 0; i < 4; i++)
    {
        int idx = index + i;
        if(idx < type.size())
            result << type[idx];
        else
            result << "";
    }
    return result;
}

QStringList RepsModel::repsVisibleItems() const
{
    return makeVisibleItems(m_reps, m_reps_i);
}

QStringList RepsModel::weightsVisibleItems() const
{
    return makeVisibleItems(m_weights, m_weights_i);
}

void RepsModel::reps_next()
{
    if(m_reps_i + 4 < m_reps.size())
    {
        m_reps_i += 1;
        emit repsVisibleItemsChanged();
    }
}

void RepsModel::reps_prev()
{
    if(m_reps_i > 0)
    {
        m_reps_i -= 1;
        emit repsVisibleItemsChanged();
    }
}

void RepsModel::weights_next()
{
    if(m_weights_i + 4 < m_weights.size())
    {
        m_weights_i += 1;
        emit weightsVisibleItemsChanged();
    }
}

void RepsModel::weights_prev()
{
    if(m_weights_i > 0)
    {
        m_weights_i -= 1;
        emit weightsVisibleItemsChanged();
    }
}


