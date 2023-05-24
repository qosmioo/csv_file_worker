#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entry_point.h"
#include "file_error.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_load_data_clicked()
{
    entry_point_argument arg;
    arg.position_region = position_region;
    arg.filename = filename;
    arg.region = ui->line_region->text().toStdString();
    arg.func_type = get_data;
    entry_point_returning_value str = entry_point(arg);
    rows_num = str.rows_count;
    std::stringstream stream(str.file_to_string);
    std::string line;
    getline(stream, line);

    QStringList header = QString::fromStdString(line).split(',');
    position_region = find_position_region(header);
    cols_num = header.size();
    ui->tableWidget->setColumnCount(header.size());
    ui->tableWidget->setRowCount(str.rows_count - 1);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    std::string tmp1;
    for(int j = 0; j < str.rows_count; j++)
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
    clear_table();
    clear_metric();
    filename = QFileDialog::getOpenFileName(this, "", "C://Users/UseR/Downloads", "Image Files (*.csv)").toStdString();
    ui->lbl_path->setText(QString::fromStdString(filename));
    if (filename != "") {
        on_btn_load_data_clicked();
    }

}

void MainWindow::on_btn_calc_metrics_clicked()
{
    if (ui->line_cols_num->text().toInt() && ui->line_cols_num->text().toInt() > 0
            && ui->line_cols_num->text().toInt() <= cols_num) {
        entry_point_argument tmp = get_column();
        tmp.position_region = position_region;
        if (tmp.amount_of_metrics != 0) {
            tmp.func_type = calculate_metrics;
            entry_point_returning_value metrics = entry_point(tmp);
            if (metrics.amount_of_appr_metrics == 0) {
                critical_error(error_no_appr_metrics);
            } else {
                set_text_to_label(metrics);
            }

            free(tmp.column);
        } else {
            critical_error(error_amount_column);
        }
    } else {
        critical_error(error_type_data_of_column);
    }
}
