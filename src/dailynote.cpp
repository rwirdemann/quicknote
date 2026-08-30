#include "dailynote.h"

#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QTextStream>

DailyNote::DailyNote(QObject *parent)
    : QObject(parent)
    , m_vaultDir(QDir::homePath() +
                 "/Jottacloud/zettelkasten/Tagebuch")
{
    load();
}

QString DailyNote::content() const
{
    return m_content;
}

void DailyNote::setContent(const QString &content)
{
    if (m_content == content)
        return;

    m_content = content;
    m_dirty = true;
    emit contentChanged();
    emit dirtyChanged();
}

QString DailyNote::filePath() const
{
    return m_filePath;
}

bool DailyNote::dirty() const
{
    return m_dirty;
}

QString DailyNote::status() const
{
    return m_status;
}

void DailyNote::setStatus(const QString &status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged();
}

// reload re-reads the note for the current date, picking up edits
// made outside the app and rolling over to a new file if the date
// has changed.
void DailyNote::reload()
{
    load();
}

void DailyNote::load()
{
    QDir dir(m_vaultDir);
    if (!dir.exists()) {
        setStatus("Vault-Ordner nicht gefunden: " + m_vaultDir);
        return;
    }

    const QString fileName =
        QDate::currentDate().toString("yyyy-MM-dd") + ".md";
    m_filePath = dir.filePath(fileName);
    emit filePathChanged();

    QFile file(m_filePath);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_content = QTextStream(&file).readAll();
            file.close();
        } else {
            setStatus("Konnte Datei nicht lesen: " + m_filePath);
        }
    } else {
        m_content.clear();
        save();
    }

    emit contentChanged();
    m_dirty = false;
    emit dirtyChanged();
}

void DailyNote::save()
{
    if (m_filePath.isEmpty())
        return;

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        setStatus("Speichern fehlgeschlagen: " + m_filePath);
        return;
    }

    QTextStream(&file) << m_content;
    file.close();

    m_dirty = false;
    emit dirtyChanged();
    setStatus("Gespeichert " +
              QDateTime::currentDateTime().toString("HH:mm:ss"));
}
