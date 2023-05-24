#include "mainwindow.h"

void MainWindow::set_text_to_label(entry_point_returning_value tmp) {
    ui->lbl_min_res->setText(QString::number(tmp.min, 'g', 15));
    ui->lbl_mid_res->setText(QString::number(tmp.mediana, 'g', 15));
    ui->lbl_max_res->setText(QString::number(tmp.max, 'g', 15));
}

void MainWindow::clear_table() {
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->line_region->setText("");
}

void MainWindow::clear_metric() {
    ui->lbl_min_res->setText("");
    ui->lbl_mid_res->setText("");
    ui->lbl_max_res->setText("");
}

int MainWindow::find_position_region(QStringList header) {
    for (int i = 0; i < header.size(); ++i) {
        if (header[i] == "region") return i;
    }
    return 0;
}

entry_point_argument MainWindow::get_column () {
    int column_index = ui->line_cols_num->text().toInt() - 1;
    entry_point_argument result;
    result.rows_num = 0;
    result.column = (double*)malloc(sizeof(double));
    if (result.column != NULL) {
        for (int i = 0; i < rows_num - 1; ++i) {
            QString tmp = ui->tableWidget->item(i, column_index)->text();
            if (tmp != "" && tmp.toDouble()) {
                result.rows_num++;
                result.column = (double*)realloc(result.column,sizeof(double)*(result.rows_num + 1));
                if (result.column != NULL) {
                    result.column[result.rows_num - 1] = tmp.toDouble();
                } else {
                    result.amount_of_metrics = 0;
                    break;
                }
            }
        }
    }
    return result;
}



