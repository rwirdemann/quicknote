#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>

// DailyNote loads and saves the current day's note file from an
// Obsidian-style vault directory, using the YYYY-MM-DD.md naming
// convention. It creates an empty file for today if none exists.
class DailyNote : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY
                   contentChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged)
    Q_PROPERTY(bool dirty READ dirty NOTIFY dirtyChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
    explicit DailyNote(QObject *parent = nullptr);

    QString content() const;
    void setContent(const QString &content);

    QString filePath() const;
    bool dirty() const;
    QString status() const;

    Q_INVOKABLE void save();

signals:
    void contentChanged();
    void filePathChanged();
    void dirtyChanged();
    void statusChanged();

private:
    void load();
    void setStatus(const QString &status);

    QString m_vaultDir;
    QString m_filePath;
    QString m_content;
    bool m_dirty = false;
    QString m_status;
};
