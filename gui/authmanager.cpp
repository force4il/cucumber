#include "authmanager.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QByteArray>


AuthManager::AuthManager(QObject *parent) : QObject(parent)
{
    loadUsers();

    if (users.isEmpty()) {
        // empty
    }
}

QByteArray AuthManager::generateSalt(int length)
{
    QByteArray salt;
    salt.resize(length);

    for (int i = 0; i < length; ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::global()->generate() % 256);
    }

    return salt;
}

QString AuthManager::hashPassword(const QString &password)
{
    QByteArray salt = generateSalt();
    QByteArray data = password.toUtf8() + salt;

    return QString(QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex());
}

bool AuthManager::loadUsers()
{
    QSettings settings(CONFIG_FILE, QSettings::IniFormat);

    settings.beginGroup("Users");
    QStringList keys = settings.childKeys();

    for (const QString &key : keys) {
        users[key] = settings.value(key).toString();
    }
    settings.endGroup();

    return !users.isEmpty();
}

bool AuthManager::saveUsers()
{
    QSettings settings(CONFIG_FILE, QSettings::IniFormat);

    settings.beginGroup("Users");
    QMap<QString, QString>::const_iterator i = users.constBegin();
    while (i != users.constEnd()) {
        settings.setValue(i.key(), i.value());
        ++i;
    }
    settings.endGroup();
    settings.sync();

    return true;
}

bool AuthManager::authenticate(const QString &username, const QString &password)
{
    if (!users.contains(username)) {
        return false;
    }

    QString hashedInput = hashPassword(password);
    return users[username] == hashedInput;
}

bool AuthManager::addUser(const QString &username, const QString &password)
{
    if (username.isEmpty() || password.isEmpty() || users.contains(username)) {
        return false;
    }

    users[username] = hashPassword(password);
    return saveUsers();
}

bool AuthManager::removeUser(const QString &username)
{
    if (!users.contains(username)) {
        return false;
    }

    users.remove(username);
    return saveUsers();
}

QStringList AuthManager::getUsers() const
{
    return users.keys();
}
