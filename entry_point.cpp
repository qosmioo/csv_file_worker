#include "entry_point.h"

entry_point_returning_value get_files_data(entry_point_argument data)
{

    std::fstream fin;
    std::string last_read_region;
    entry_point_returning_value result;
    result.file_to_string = "";
    result.rows_count = 0;
    std::string tmp_region;

    fin.open(data.filename);
    if(fin.is_open())
    {
        while(getline(fin, last_read_region))
        {
            std::stringstream stream(last_read_region);


            for (int i = 0; i <= data.position_region; ++i) getline(stream, tmp_region, ',');

            if (tmp_region == data.region || data.region == "" || result.rows_count == 0) {
                result.file_to_string += last_read_region + "\n" ;
                ++result.rows_count;
            }
        }

    }
    return result;
}

entry_point_returning_value get_metrics (entry_point_argument data) {
    entry_point_returning_value result;
    result.amount_of_appr_metrics = data.rows_num;
    sort_array(data.column, data.rows_num);
    result.max = data.column[data.rows_num - 1];
    result.min = data.column[0];
    if (data.rows_num % 2 == 0) {
        result.mediana = (data.column[data.rows_num/2 - 1] + data.column[data.rows_num/2])/2;
    } else {
        result.mediana = data.column[(data.rows_num - 1)/2];
    }
    return result;
}

entry_point_returning_value entry_point (entry_point_argument data) {
    entry_point_returning_value result;
    switch (data.func_type) {
    case func_type::get_data:
        result = get_files_data(data);
        break;

    case func_type::calculate_metrics:
        result = get_metrics(data);
        break;
    default:
        result.error = 1;
    }
    return result;
}
