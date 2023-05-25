#include "mainwindow.h"

void MainWindow::adapt_tabel(entry_point_returning_value str) {
    std::stringstream stream(str.file_to_string);
    std::string line;
    getline(stream, line);
    QStringList header = QString::fromStdString(line).split(',');
    position_region = find_position_region(header);
    cols_num = header.size();
    ui->tableWidget->setColumnCount(header.size());
    ui->tableWidget->setRowCount(rows_num);
    ui->tableWidget->setHorizontalHeaderLabels(header);
}

void MainWindow::filling_table(int counter, entry_point_returning_value str) {
    std::stringstream stream(str.file_to_string);
    std::string line;
    std::string tmp;
    for(int j = counter *100 - 1; j <= rows_num; j++)
    {
        getline(stream, line, '\n');
        std::stringstream stream2(line);
        for(int i = 0; i < cols_num; i++)
        {
            getline(stream2, tmp, ',');
            ui->tableWidget->setItem(j, i, new QTableWidgetItem(QString::fromStdString(tmp)));
        }
    }
}
void MainWindow::set_text_to_label(entry_point_returning_value tmp) {
    ui->lbl_min_res->setText(QString::number(tmp.min, 'g', 15));
    ui->lbl_mid_res->setText(QString::number(tmp.mid, 'g', 15));
    ui->lbl_max_res->setText(QString::number(tmp.max, 'g', 15));
}

void MainWindow::clear_table() {
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->line_region->setText("");
    ui->line_cols_num->setText("");
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
    return -1;
}

entry_point_argument MainWindow::get_column () {
    int column_index = ui->line_cols_num->text().toInt() - 1;
    entry_point_argument result;
    result.rows_num = 0;
    result.column = (double*)malloc(sizeof(double));
    if (result.column != NULL) {
        for (int i = 0; i < rows_num; ++i) {
            QString tmp = ui->tableWidget->item(i, column_index)->text();
            if (tmp != "" && tmp.toDouble()) {
                result.rows_num++;
                result.column = (double*)realloc(result.column,sizeof(double)*(result.rows_num + 1));
                if (result.column != NULL) {
                    result.column[result.rows_num - 1] = tmp.toDouble();
                } else {
                    result.rows_num = 0;
                    break;
                }
            }
        }
    }
    return result;
}



