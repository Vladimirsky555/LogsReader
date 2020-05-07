#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "qregexphighlighter.h"
#include "task_chosen_lines.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QFile fileIn;
    QFile fileOut;
    QRegexpHighlighter *highlighter;
    qint64 countLines;
    qint64 start;
    qint64 end;
    Task_Chosen_Lines *Task_2;
    int task;
    QString file;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void searchTask_keyLine(QString filename);
    void searchTask_Chosen_Lines(QString filename);
    void searchTask_All_Lines(QString filename);
    void refresh();


private slots:
    void on_btnStart_clicked();
    void on_edtPattern_textChanged(const QString &arg1);
    void on_edtPattern_returnPressed();
    void on_btnClear_clicked();

    void Task_Chosen_Lines_launcher(int, qint64, qint64);


    void on_action_1_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
     bool checkRegExp(QRegExp rx);
};

#endif // MAINWINDOW_H
