#include "globalhotkey.h"

#include <Carbon/Carbon.h>

namespace {

GlobalHotkey *g_activeHotkey = nullptr;

OSStatus handleHotKeyEvent(EventHandlerCallRef, EventRef, void *)
{
    if (g_activeHotkey)
        g_activeHotkey->trigger();
    return noErr;
}

}

GlobalHotkey::GlobalHotkey(QObject *parent)
    : QObject(parent)
{
    g_activeHotkey = this;

    EventTypeSpec eventType;
    eventType.eventClass = kEventClassKeyboard;
    eventType.eventKind = kEventHotKeyPressed;

    EventHandlerRef handlerRef = nullptr;
    InstallApplicationEventHandler(&handleHotKeyEvent, 1, &eventType,
                                    nullptr, &handlerRef);
    m_eventHandlerRef = handlerRef;

    EventHotKeyID hotKeyID;
    hotKeyID.signature = 'osqk';
    hotKeyID.id = 1;

    EventHotKeyRef hotKeyRef = nullptr;
    RegisterEventHotKey(kVK_ANSI_E, cmdKey, hotKeyID,
                         GetApplicationEventTarget(), 0, &hotKeyRef);
    m_hotKeyRef = hotKeyRef;
}

GlobalHotkey::~GlobalHotkey()
{
    if (m_hotKeyRef)
        UnregisterEventHotKey(static_cast<EventHotKeyRef>(m_hotKeyRef));
    if (m_eventHandlerRef)
        RemoveEventHandler(static_cast<EventHandlerRef>(m_eventHandlerRef));
    if (g_activeHotkey == this)
        g_activeHotkey = nullptr;
}

void GlobalHotkey::trigger()
{
    emit activated();
}
