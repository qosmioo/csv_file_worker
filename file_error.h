#ifndef FILE_ERROR_H
#define FILE_ERROR_H

enum error_type
{
    error_region,
    error_metrics,
    error_type_data_of_column,
    error_file,
};

void critical_error (error_type i);

#endif // FILE_ERROR_H
