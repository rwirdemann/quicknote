# quicknote

A tiny macOS menu bar app for jotting down a daily note. Press a global
hotkey (Cmd+E) from anywhere to pop open a window, write, and it's
saved back into your Obsidian-style vault as `YYYY-MM-DD.md`.

Built with Qt 6 (QML) and C++.

## Features

- Global hotkey (Cmd+E) toggles the window from any application
- Loads/creates today's note in your vault directory
  (`YYYY-MM-DD.md`), autosaving on close, hide, or Cmd+S
- Lives in the system tray; click the tray icon to show/hide

## Configuration

The vault directory is currently hardcoded in
`src/dailynote.cpp` to `~/Jottacloud/zettelkasten/Tagebuch`.
Adjust it there to point at your own vault.

## Requirements

- macOS
- CMake >= 3.16
- Qt 6.5+ (Core, Gui, Qml, Quick, QuickControls2)

## Build

```sh
cmake -B build
cmake --build build
```

The resulting app bundle is at `build/quicknote.app`.

## Installing a release build

Release zips are unsigned. After downloading and unzipping, macOS
Gatekeeper will refuse to open the app with "the file is damaged
and should be moved to the Trash" — this just means it's quarantined,
not actually corrupted. Remove the quarantine attribute to fix it:

```sh
xattr -cr /path/to/quicknote.app
```
