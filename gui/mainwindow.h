#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void runProject1();
    void runProject2();
    void runProject3();

private:
    QPushButton *createProjectButton(const QString &name, const QString &color);

    // Пути к исполняемым файлам проектов
    QVector<QString> projects = {
        "./bin/calculator",
        "./bin/stack",
        "./bin/queue"
    };
};

#endif
