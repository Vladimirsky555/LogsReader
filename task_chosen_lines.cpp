#include "task_chosen_lines.h"
#include "ui_task_chosen_lines.h"

Task_Chosen_Lines::Task_Chosen_Lines(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task_Chosen_Lines)
{
    ui->setupUi(this);
}

Task_Chosen_Lines::~Task_Chosen_Lines()
{
    delete ui;
}



void Task_Chosen_Lines::on_btnOK_clicked()
{
    start = ui->line_start->text().toInt();
    end = ui->line_end->text().toInt();

    if(ui->isAll->isChecked()){
        task = 3;
    } else {
        task = 2;
    }

    emit Task_Chosen_Lines_launcher(task, start, end);

    close();
}

void Task_Chosen_Lines::on_btnCancel_clicked()
{
    close();
}
