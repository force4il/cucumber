#include "loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Вход в систему");
    titleLabel->setAlignment(Qt::AlignCenter);

    loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин");

    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Войти");

    layout->addWidget(titleLabel);
    layout->addWidget(loginEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);

    setWindowTitle("Авторизация");
    resize(300, 200);
}

// Функция проверки пароля
void LoginWindow::handleLogin()
{
    if (loginEdit->text() == "admin" && passwordEdit->text() == "123") {
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
    }
}

LoginWindow::~LoginWindow() {}
