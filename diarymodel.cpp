#include "diarymodel.h"

DiaryModel::DiaryModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

JsonDataBase *DiaryModel::db()
{
    return m_db;
}

void DiaryModel::setDb(JsonDataBase *db)
{
    if (m_db == db)
        return;

    // если раньше была база — отцепимся
    if (m_db != nullptr) {
        disconnect(m_db, nullptr, this, nullptr);
    }

    m_db = db;

    // если база есть — подписываемся на изменения
    if (m_db != nullptr) {
        connect(m_db, &JsonDataBase::dataChanged,
                this, &DiaryModel::RebuildDiaryFromDb);
    }

    emit dbChanged();

    // сразу построим модель (чтобы не ждать следующего dataChanged)
    RebuildDiaryFromDb();
}


void DiaryModel::RebuildDiaryFromDb()
{
    QVector<DiaryNotice> newNotices;

    if (m_db) {
        const auto &days = m_db->Get_m_days();
        for (int i = 0; i < days.size(); ++i) {
            const TrainingDay &day = days[i];
            for (int j = 0; j < day.exercises.size(); ++j) {
                const Exercise &ex = day.exercises[j];

                DiaryNotice row;
                row.date = day.date;
                row.exercise = ex.name;

                for (int k = 0; k < ex.sets.size(); ++k) {
                    const Set &s = ex.sets[k];
                    row.sets.append(s.reps + "(" + s.weight + ")");
                }

                newNotices.append(std::move(row));
            }
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

    const DiaryNotice &notice = DiaryNotices[row];

    switch (role) {
    case date:
        return notice.date;       // QString упакуется в QVariant автоматически
    case exercise:
        return notice.exercise;   // QString
    case sets:
        return notice.sets;       // QStringList тоже упакуется в QVariant
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
