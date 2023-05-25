#include "file_error.h"
#include <QMessageBox>

void critical_error (error_type i) {
    switch (i) {
    case error_metrics:
        QMessageBox::critical(0, "Error message", "column has no correct valid values");
        break;
    case error_type_data_of_column:
        QMessageBox::critical(0, "Error message", "select correct column");
        break;
    case error_region:
        QMessageBox::critical(0, "Error message", "select correct data");
        break;
    case error_file:
        QMessageBox::critical(0, "Error message", "select file");
    }
}
