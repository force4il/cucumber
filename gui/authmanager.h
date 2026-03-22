#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QCryptographicHash>
#include <QSettings>

// Класс для управления аутентификацией пользователей
class AuthManager : public QObject
{
    Q_OBJECT

public:
    // Конструктор, который загружает пользователей при инициализации
    explicit AuthManager(QObject *parent = nullptr) : QObject(parent) {
        loadUsers();
    }

    // Проверка связки пользователь-пароль
    bool authenticate(const QString &username, const QString &password)
    {
        if (!users.contains(username)) {
            return false;
        }

        const QString hashedInput = hashPassword(password);
        return users[username] == hashedInput;
    }

private:
    // Из строки получить хэш
    QString hashPassword(const QString &password)
    {
        const QByteArray data = password.toUtf8();

        return QString{QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex()};
    }

    // Загрузка пользователей изи .ini файла
    bool loadUsers()
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

    // Словарь для хранения пользователей и их хэшей паролей
    QMap<QString, QString> users;
    const QString CONFIG_FILE = "users.ini";
};

#endif // AUTHMANAGER_H