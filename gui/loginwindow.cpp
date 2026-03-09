#include "loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <QDebug>

QString get_time() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    authManager = new AuthManager(this);
    setupUI();
}

void LoginWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 20, 20);

    // Заголовок
    QLabel *titleLabel = new QLabel("Авторизация");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Поля ввода
    loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин");
    loginEdit->setMinimumHeight(30);

    passwordEdit = new QLineEdit();
   passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(30);

    showPasswordCheck = new QCheckBox("Показать пароль");

    loginButton = new QPushButton("Войти");
    loginButton->setMinimumHeight(35);
    loginButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        );

    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(loginEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(showPasswordCheck);
    layout->addSpacing(10);
    layout->addWidget(loginButton);

    // Подключение сигналов
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(showPasswordCheck, &QCheckBox::toggled, this, &LoginWindow::togglePasswordVisibility);
    connect(loginEdit, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);

    setWindowTitle("Вход в систему");
    resize(350, 250);

    loginEdit->setFocus();
}

void LoginWindow::togglePasswordVisibility(bool checked)
{
    if (checked) {
        passwordEdit->setEchoMode(QLineEdit::Normal);
    } else {
        passwordEdit->setEchoMode(QLineEdit::Password);
    }
}

void LoginWindow::handleLogin()
{
    QString username = loginEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль");
        qDebug() << "Неудачная попытка входа" << get_time();
        return;
    }

    if (authManager->authenticate(username, password)) {
        qDebug() << "Успешный вход пользователя :" << username << get_time();

        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
        passwordEdit->clear();
        passwordEdit->setFocus();

        qDebug() << "Неудачная попытка входа для пользователя:" << username  << get_time();
    }
}

LoginWindow::~LoginWindow() {}
