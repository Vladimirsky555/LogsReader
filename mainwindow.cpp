#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Logs Reader");

    countLines = 0;
    ui->lineEdit->setText(QString::number(countLines));
    task = 1;

    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->textBrowser->document());
    highlighter->setPattern(ui->edtPattern->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    countLines = 0;
    ui->lineEdit->setText(QString::number(countLines));
}


void MainWindow::searchTask_keyLine(QString filename)
{
    if (filename == ""){
        QMessageBox b;
        b.setText("Выберите файл для поиска!");
        b.exec();
        return;
    }

    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);
    fileOut.setFileName(filename + "_" +
                        ui->edtPattern->text() + ".txt");
    fileOut.open(QIODevice::WriteOnly);

    int count = 0;
    int c = 0;
    for(int i = 0; i < countLines; i++){
    QByteArray arr = fileIn.readLine();

    c++;
    ui->countLinecurrent->setText("Lines: " + QString::number(c));

    int cnt = 0;

    QRegExp rx(ui->edtPattern->text());
    if(!checkRegExp(rx))return;
    int pos = 0;
    while((pos = rx.indexIn(QString::fromUtf8(arr), pos)) != -1){
        pos += rx.matchedLength();
        cnt++;
        count++;
    }

    if(cnt != 0){
        QString temp = QString::fromUtf8(arr);
        ui->textBrowser->append(QString::number(i + 1)+ ": " + temp);
        fileOut.write(arr);
    }
  }

    ui->textBrowser->append(" ");
    ui->textBrowser->append(" ");
    ui->textBrowser->append(" ");

    ui->textBrowser->append("Количество повторений: " +
                            QString::number(count));

    QString result = "Total: " + QString::number(count);
    QByteArray arr = result.toUtf8();
    fileOut.write(arr);

    ui->textBrowser->append(" ");
    ui->textBrowser->append("Лог находится в файле " + file + "_" +
                            ui->edtPattern->text() + ".txt");

    fileIn.close();
    fileOut.close();
    refresh();
}


void MainWindow::searchTask_Chosen_Lines(QString filename)
{
    if (filename == ""){
        QMessageBox b;
        b.setText("Выберите файл для поиска!");
        b.exec();
        return;
    }

    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);
    fileOut.setFileName(filename + "_lines_" + QString::number(start) +
                        "-" + QString::number(end) + "_" +
                        ui->edtPattern->text() + ".txt");
    fileOut.open(QIODevice::WriteOnly);

    int count = 0;
    int c = 0;
    countLines = 5000000;
    for(int i = 0; i < countLines; i++){

        if(i == end)break;

        QByteArray arr = fileIn.readLine();

        c++;
        ui->countLinecurrent->setText("Lines: " + QString::number(c));

        int cnt = 0;

        QRegExp rx(ui->edtPattern->text());
        if(!checkRegExp(rx))return;
        int pos = 0;
        while((pos = rx.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx.matchedLength();
            cnt++;
            if(i >= start)count++;
        }

        if(cnt != 0 && i >= start && i <= end){
            QString temp = QString::fromUtf8(arr);
            ui->textBrowser->append(QString::number(i + 1)+ ": " + temp);
            fileOut.write(arr);
        }
    }

    ui->textBrowser->append(" ");
    ui->textBrowser->append(" ");
    ui->textBrowser->append(" ");

    ui->textBrowser->append("Количество повторений: " +
                            QString::number(count));

    QString result = "Total: " + QString::number(count);
    QByteArray arr = result.toUtf8();
    fileOut.write(arr);

    ui->textBrowser->append(" ");
    ui->textBrowser->append("Лог с " + QString::number(start) + " по " +
                            QString::number(end) +
                            " строчку находится в файле " + file +
                            "_lines_" + QString::number(start) +
                            "-" + QString::number(end) + "_" +
                            ui->edtPattern->text() +  ".txt");

    fileIn.close();
    fileOut.close();
    refresh();
}

void MainWindow::searchTask_All_Lines(QString filename)
{
    if (filename == ""){
        QMessageBox b;
        b.setText("Выберите файл для логирования!");
        b.exec();
        return;
    }


    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);
    fileOut.setFileName(filename + "_lines_" + QString::number(start) +
                        "-" + QString::number(end) + ".txt");
    fileOut.open(QIODevice::WriteOnly);

    int c = 0;
    countLines = 5000000;
    for(int i = 0; i < countLines; i++){

        if(i == end)break;

        QByteArray arr = fileIn.readLine();

        c++;
        ui->countLinecurrent->setText("Lines: " + QString::number(c));

        if(i >= start && i <= end){
            fileOut.write(arr);
        }
    }

    ui->textBrowser->append(" ");
    ui->textBrowser->append("Лог с " + QString::number(start) + " по " +
                            QString::number(end) +
                            " строчку находится в файле " + file +
                            "_lines_" + QString::number(start) +
                            "-" + QString::number(end) + ".txt");

    fileIn.close();
    fileOut.close();
    refresh();
}






void MainWindow::on_edtPattern_textChanged(const QString &arg1)
{
    highlighter->setPattern(arg1);
    highlighter->rehighlight();
}


bool MainWindow::checkRegExp(QRegExp rx)
{
    if(rx.isValid() && !rx.isEmpty() && !rx.exactMatch("")){
        return true;
    }else{
        QMessageBox::information(this,
                                 "Информсообщение",
                                 trUtf8("Некорректный шаблон регулярного выражения!"));
        return false;
    }
}



void MainWindow::on_btnClear_clicked()
{
    task = 1;
    ui->textBrowser->clear();
}


void MainWindow::Task_Chosen_Lines_launcher(int task, qint64 start, qint64 end)
{
    this->task = task;
    this->start = start;
    this->end = end;
}


void MainWindow::on_btnStart_clicked()
{
    if(task == 1){

        QMessageBox b;
        b.setText("Поиск по всему логу займёт какое-то время!");
        b.exec();

        searchTask_keyLine(file);
    } else if(task == 2){
        searchTask_Chosen_Lines(file);
    } else if(task == 3){
        searchTask_All_Lines(file);
    }
}

void MainWindow::on_edtPattern_returnPressed()
{
    if(task == 1){

        QMessageBox b;
        b.setText("Поиск по всему логу займёт какое-то время!");
        b.exec();

        searchTask_keyLine(file);
    } else if(task == 2){
        searchTask_Chosen_Lines(file);
    } else if(task == 3){
        searchTask_All_Lines(file);
    }
}

void MainWindow::on_action_1_triggered()
{
    QFileDialog dialog;
    file = dialog.getOpenFileName();
}

void MainWindow::on_action_2_triggered()
{
    Task_2 = new Task_Chosen_Lines();

    connect(Task_2, SIGNAL(Task_Chosen_Lines_launcher(int,qint64,qint64)),
            this, SLOT(Task_Chosen_Lines_launcher(int,qint64,qint64)));

    Task_2->show();

}

void MainWindow::on_action_3_triggered()
{
    QMessageBox b;
    b.setText("Версия 1.0.0");
    b.setText("Программа на C++ (Qt Creator)");
    b.exec();
}





void MainWindow::on_lineEdit_editingFinished()
{
    countLines = ui->lineEdit->text().toInt();
}
