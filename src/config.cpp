#include "config.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

namespace {

const QString kDefaultVaultDir = "~/Dropbox/zettelkasten/Tagebuch";

QString configFilePath()
{
    return QDir::homePath() + "/.config/quicknote.toml";
}

QString expandHome(const QString &path)
{
    if (path.startsWith("~/"))
        return QDir::homePath() + path.mid(1);
    return path;
}

void writeDefaultConfig(const QString &path)
{
    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream(&file)
        << "vault_dir = \"" << kDefaultVaultDir << "\"\n";
}

}

// vaultDir returns the note vault directory configured under the
// vault_dir key. It creates a default config file on first run.
QString Config::vaultDir()
{
    const QString path = configFilePath();

    QFile file(path);
    if (!file.exists())
        writeDefaultConfig(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return expandHome(kDefaultVaultDir);

    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString line = in.readLine().trimmed();
        if (line.startsWith('#') || !line.startsWith("vault_dir"))
            continue;

        const int eq = line.indexOf('=');
        if (eq < 0)
            continue;

        QString value = line.mid(eq + 1).trimmed();
        if (value.startsWith('"') && value.endsWith('"'))
            value = value.mid(1, value.length() - 2);

        return expandHome(value);
    }

    return expandHome(kDefaultVaultDir);
}
