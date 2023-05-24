#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "sort.h"

enum func_type
{
    get_data,
    calculate_metrics
};

struct entry_point_argument{
    int rows_num;
    double *column;
    int position_region;
    std::string region;
    std::string filename;
    func_type func_type;
    int amount_of_metrics;
};

struct entry_point_returning_value {
    double max;
    double min;
    double mediana;
    int amount_of_appr_metrics;
    std::string file_to_string;
    int rows_count;
    int error = 0;
};

entry_point_returning_value get_files_data(entry_point_argument arg);
entry_point_returning_value get_metrics (entry_point_argument column);
entry_point_returning_value entry_point (entry_point_argument data);

#endif // ENTRY_POINT_H
