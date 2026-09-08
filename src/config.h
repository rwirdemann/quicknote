#pragma once

#include <QString>

// Config reads user settings from $HOME/.config/quicknote.toml. If
// the file is missing, it is created with default values.
namespace Config
{

QString vaultDir();

}
