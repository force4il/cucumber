#include "authmanager.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QByteArray>
#include <QStandardPaths>

AuthManager::AuthManager(QObject *parent) : QObject(parent)
{
    loadUsers();
}

// Из строки получить хэш
QString AuthManager::hashPassword(const QString &password)
{
    QByteArray data = password.toUtf8();

    return QString(QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex());
}

// Загрузка пользователей изи .ini файла
bool AuthManager::loadUsers()
{
    QSettings settings = QSettings(CONFIG_FILE, QSettings::IniFormat);
    
    settings.beginGroup("Users");
    QStringList keys = settings.childKeys();

    for (const QString &key : keys) {
        users[key] = settings.value(key).toString();
    }
    settings.endGroup();

    return !users.isEmpty();
}

// Сохранить пользователей
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

// Проверка связки пользователь-пароль
bool AuthManager::authenticate(const QString &username, const QString &password)
{
    if (!users.contains(username)) {
        return false;
    }

    QString hashedInput = hashPassword(password);
    return users[username] == hashedInput;
}

// Добавить пользователя
bool AuthManager::addUser(const QString &username, const QString &password)
{
    if (username.isEmpty() || password.isEmpty() || users.contains(username)) {
        return false;
    }

    qDebug() << hashPassword(password);

    users[username] = hashPassword(password);
    return saveUsers();
}
