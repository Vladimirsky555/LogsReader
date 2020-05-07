#ifndef TASK_CHOSEN_LINES_H
#define TASK_CHOSEN_LINES_H

#include <QWidget>

namespace Ui {
class Task_Chosen_Lines;
}

class Task_Chosen_Lines : public QWidget
{
    Q_OBJECT

    qint64 start;
    qint64 end;
    int task;

public:
    explicit Task_Chosen_Lines(QWidget *parent = 0);
    ~Task_Chosen_Lines();

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

signals:
    void Task_Chosen_Lines_launcher(int, qint64, qint64);

private:
    Ui::Task_Chosen_Lines *ui;
};

#endif // TASK_CHOSEN_LINES_H
