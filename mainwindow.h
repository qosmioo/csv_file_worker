#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>

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
private slots:
    void on_btn_load_data_clicked();

    void on_pbt_open_file_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
