#include "mainwindow.h"
#include <QLabel>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

    consoleOutput = new QTextEdit();
    consoleOutput->setReadOnly(true);
    consoleOutput->setFont(QFont("Courier New", 14));
    consoleOutput->setMinimumHeight(400);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(project1Btn);
    mainLayout->addWidget(project2Btn);
    mainLayout->addWidget(project3Btn);
    mainLayout->addWidget(new QLabel("Вывод консоли:"));
    mainLayout->addWidget(consoleOutput);

    connect(project1Btn, &QPushButton::clicked, this, &MainWindow::runProject1);
    connect(project2Btn, &QPushButton::clicked, this, &MainWindow::runProject2);
    connect(project3Btn, &QPushButton::clicked, this, &MainWindow::runProject3);

    currentProcess = new QProcess(this);
    connect(currentProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::readProcessOutput);
    connect(currentProcess, &QProcess::readyReadStandardError, this, &MainWindow::readProcessOutput);
    connect(currentProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &MainWindow::processFinished);

    setWindowTitle("Выбор проекта");
    resize(500, 400);
}

QPushButton* MainWindow::createProjectButton(const QString &name, const QString &color)
{
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

void MainWindow::runProject1()
{
    consoleOutput->clear();

    QString program = "./bin/calculator";
    currentProcess->start(program);
}

void MainWindow::runProject2()
{
    consoleOutput->clear();

    QString program = "./bin/stack";     
    currentProcess->start(program);
}

void MainWindow::runProject3()
{
    consoleOutput->clear();

    QString program = "./bin/queue";     
    currentProcess->start(program);
}

void MainWindow::readProcessOutput()
{
    QByteArray output = currentProcess->readAllStandardOutput();
    QByteArray error = currentProcess->readAllStandardError();

    if (!output.isEmpty()) {
        consoleOutput->append(QString::fromLocal8Bit(output));
    }
    if (!error.isEmpty()) {
        consoleOutput->append("<font color='red'>" + QString::fromLocal8Bit(error) + "</font>");
    }
}

void MainWindow::processFinished()
{
    consoleOutput->append("\n<font color='green'>Процесс завершен</font>");
}

MainWindow::~MainWindow()
{
    if (currentProcess->state() == QProcess::Running) {
        currentProcess->terminate();
        currentProcess->waitForFinished(3000);
    }
}
