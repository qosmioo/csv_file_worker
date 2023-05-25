#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include "./ui_mainwindow.h"
#include "entry_point.h"
#include "table_work.h"
#include "file_error.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string filename;
    int rows_num = 0;
    int cols_num = 0;
    int position_region = -1;
private slots:
    void on_btn_load_data_clicked();
    void on_pbt_open_file_clicked();
    void on_btn_calc_metrics_clicked();
private:
    entry_point_argument get_column ();
    void set_text_to_label(entry_point_returning_value tmp);
    void clear_table();
    void clear_metric();
    int find_position_region (QStringList header);
    void adapt_tabel(entry_point_returning_value arg);
    void filling_table(int counter, entry_point_returning_value arg);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
