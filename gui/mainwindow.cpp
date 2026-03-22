#include "mainwindow.h"
#include <QLabel>
#include <QDir>
#include <QApplication>

// Конструктор главного окна
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Выберите проект для запуска");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    titleLabel->setFont(font);

    QPushButton *project1Btn = createProjectButton("Проект 1 - Калькулятор больших чисел", "#4CAF50");
    QPushButton *project2Btn = createProjectButton("Проект 2 - Тест стека", "#2196F3");
    QPushButton *project3Btn = createProjectButton("Проект 3 - Тест очереди", "#FF9800");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(project1Btn);
    mainLayout->addWidget(project2Btn);
    mainLayout->addWidget(project3Btn);

    connect(project1Btn, &QPushButton::clicked, this, &MainWindow::runProject1);
    connect(project2Btn, &QPushButton::clicked, this, &MainWindow::runProject2);
    connect(project3Btn, &QPushButton::clicked, this, &MainWindow::runProject3);

    setWindowTitle("Выбор проекта");
    resize(500, 160);
}

// Функция для создания кнопки проекта с заданным именем и цветом
QPushButton* MainWindow::createProjectButton(const QString &name, const QString &color) {
    QPushButton *button = new QPushButton(name);
    button->setStyleSheet(QString(
                              "QPushButton {"
                              "   background-color: %1;"
                              "   color: white;"
                              "   border: none;"
                              "   padding: 10px;"
                              "   font-size: 14px;"
                              "   border-radius: 5px;"
                              "}"
                              "QPushButton:hover {"
                              "   background-color: %2;"
                              "}"
                              ).arg(color).arg(color + "80"));
    return button;
}

void runProgram(const QString &program) {
#ifdef Q_OS_LINUX
    QStringList args;
    args << "-e" << "sh" << "-c" << program + "; exec sh";
    QProcess::startDetached("xterm", args);

#elif defined(Q_OS_MAC)
    QStringList args;
    args << "-a" << "Terminal" << program;
    QProcess::startDetached("open", args);

#elif defined(Q_OS_WIN)
    QProcess::startDetached("cmd", QStringList() << "/c" << "start" << program);

#endif
}

// Слоты для запуска каждого проекта
void MainWindow::runProject1(){
    runProgram(projects.at(0));
}

void MainWindow::runProject2() {
    runProgram(projects.at(1));
}

void MainWindow::runProject3(){
    runProgram(projects.at(2));
}
