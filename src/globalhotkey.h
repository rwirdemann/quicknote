#pragma once

#include <QObject>
#include <QQmlEngine>

// GlobalHotkey registers a system-wide keyboard shortcut (Cmd+E on
// macOS) that fires regardless of which application is focused, and
// emits activated() when it is pressed.
class GlobalHotkey : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit GlobalHotkey(QObject *parent = nullptr);
    ~GlobalHotkey() override;

    void trigger();

signals:
    void activated();

private:
    void *m_hotKeyRef = nullptr;
    void *m_eventHandlerRef = nullptr;
};
