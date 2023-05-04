#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entry_point.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_load_data_clicked()
{
    int count = 0;
    std::string str = get_files_data(ui->line_region->text().toStdString(), filename, count);

    std::stringstream stream(str);
    std::string line;
    getline(stream, line);

    QStringList header = QString::fromStdString(line).split(',');
    ui->tableWidget->setColumnCount(header.size());
    ui->tableWidget->setRowCount(count - 1);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    std::string tmp1;
    for(int j = 0; j < count; j++)
    {
        getline(stream, line, '\n');
        std::stringstream stream2(line);
        for(int i = 0; i < header.size(); i++)
        {
            getline(stream2, tmp1, ',');
            ui->tableWidget->setItem(j, i, new QTableWidgetItem(QString::fromStdString(tmp1)));
        }
    }
}

void MainWindow::on_pbt_open_file_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "как дела", "C://Users/UseR/Downloads", "Image Files (*.csv)").toStdString();

}
