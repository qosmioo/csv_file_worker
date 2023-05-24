#ifndef FILE_ERROR_H
#define FILE_ERROR_H

enum error_type
{
    error_year,
    error_region,
    error_amount_column,
    error_type_data_of_column,
    error_file,
    error_no_appr_metrics
};

void critical_error (error_type i);

#endif // FILE_ERROR_H
