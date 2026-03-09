#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QMap>
#include <QCryptographicHash>
#include <QSettings>
#include <QFile>

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);
    bool authenticate(const QString &username, const QString &password);
    bool addUser(const QString &username, const QString &password);
    bool removeUser(const QString &username);
    QStringList getUsers() const;

private:
    QByteArray generateSalt(int length = 16);
    QString hashPassword(const QString &password);
    bool loadUsers();
    bool saveUsers();

    QMap<QString, QString> users; // username -> hashed_password
    const QString CONFIG_FILE = "users.ini";
};

#endif
