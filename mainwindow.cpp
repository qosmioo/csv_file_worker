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


void MainWindow::on_btn_load_data_clicked() {
    clear_metric();
    if(filename == "") {
        critical_error(error_file);
    } else {
        entry_point_argument arg;
        arg.position_region = position_region;
        arg.filename = filename;
        arg.region = ui->line_region->text().toStdString();
        arg.func_type = get_data;
        arg.placed = 0;

        entry_point_returning_value str;
        rows_num = 0;

        int counter = 0;
        do {
            str = entry_point(arg);
            if(str.rows_num == 0){
                critical_error(error_region);
                break;
            }
            arg.placed = str.placed;
            rows_num += str.rows_num;
            adapt_tabel(str);
            filling_table(counter, str);
            counter++;
        } while(str.rows_num == 100);
    }
    ui->line_cols_num->setText("");
}

void MainWindow::on_pbt_open_file_clicked() {
    clear_table();
    clear_metric();
    filename = QFileDialog::getOpenFileName(this, "", "C://Users/UseR/Downloads", "Image Files (*.csv)").toStdString();
    ui->lbl_path->setText(QString::fromStdString(filename));
    if (filename != "") {
        on_btn_load_data_clicked();
    }

}

void MainWindow::on_btn_calc_metrics_clicked() {
    if (ui->line_cols_num->text().toInt() && ui->line_cols_num->text().toInt() > 0
            && ui->line_cols_num->text().toInt() <= cols_num) {
        entry_point_argument tmp = get_column();
        tmp.position_region = position_region;
        if (tmp.rows_num != 0) {
            tmp.func_type = calculate_metrics;
            entry_point_returning_value metrics = entry_point(tmp);
            set_text_to_label(metrics);
            free(tmp.column);
        } else {
            critical_error(error_metrics);
            ui->line_cols_num->setText("");
            clear_metric();
        }
    } else {
        critical_error(error_type_data_of_column);
        ui->line_cols_num->setText("");
        clear_metric();
    }

}
