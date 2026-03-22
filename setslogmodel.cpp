#include "setslogmodel.h"

SetsLogModel::SetsLogModel(QObject *parent)
    : QAbstractListModel{parent}
{}

JsonDataBase *SetsLogModel::db()
{
    return m_db;
}

void SetsLogModel::setDb(JsonDataBase *db)
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
                this, &SetsLogModel::RebuildLogFromDb);
    }

    emit dbChanged();

    // сразу построим модель (чтобы не ждать следующего dataChanged)
    RebuildLogFromDb();
}

int SetsLogModel::rowCount(const QModelIndex &) const
{
    return LogNotices.size();
}

QVariant SetsLogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const int row = index.row();
    if (row < 0 || row >= LogNotices.size())
        return {};

    const LogNotice &notice = LogNotices[row];

    switch (role) {
    case date:
        return notice.date;       // QString упакуется в QVariant автоматически
    case exercise:
        return notice.exercise;   // QString
    case lastset:
        return notice.set;       // QStringList тоже упакуется в QVariant
    default:
        return {};
    }
}

QHash<int, QByteArray> SetsLogModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(date, "date");
    roles.insert(exercise, "exercise");
    roles.insert(lastset, "lastset");
    return roles;
}

void SetsLogModel::RebuildLogFromDb()
{
    QVector<LogNotice> newNotices;

    if (m_db) {
        const auto &days = m_db->Get_m_days();
        for (int i = 0; i < days.size(); ++i) {
            const TrainingDay &day = days[i];
            for (int j = 0; j < day.exercises.size(); ++j) {
                const Exercise &ex = day.exercises[j];
                for (int k = 0; k < ex.sets.size(); ++k) {
                    LogNotice row;
                    const Set &s = ex.sets[k];
                    row.set_id = s.id;
                    row.set = s.reps + "(" + s.weight + ")";
                    row.date = day.date;
                    row.exercise = ex.name;
                    newNotices.append(row);
                }
            }
        }
    }
    std::sort(newNotices.begin(), newNotices.end(), [](const LogNotice &a, const LogNotice &b) { return a.set_id < b.set_id; });
    beginResetModel();
    LogNotices = std::move(newNotices);
    endResetModel();
}
