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
    int placed;
    int position_region;
    double *column;
    func_type func_type;
    std::string all_data;
    std::string region;
    std::string filename;

};

struct entry_point_returning_value {
    int rows_num = 0;
    int last_row_index;
    int placed = 0;
    double max;
    double min;
    double mid;
    std::string file_to_string;
};


entry_point_returning_value entry_point (entry_point_argument data);

#endif // ENTRY_POINT_H
