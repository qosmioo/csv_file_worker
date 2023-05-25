#include "entry_point.h"

entry_point_returning_value get_files_data(entry_point_argument arg);
entry_point_returning_value get_metrics (entry_point_argument column);

entry_point_returning_value get_files_data(entry_point_argument data) {
    std::fstream fin;
    std::string last_read_region;
    std::string to_check_suitable_data;
    entry_point_returning_value suitable_regions;
    fin.open(data.filename);
    if(fin.is_open()){
        getline(fin, suitable_regions.file_to_string);
        while(getline(fin, last_read_region) && suitable_regions.rows_num != 100){
            if(suitable_regions.placed >= data.placed){
                std::stringstream tmp_stream(last_read_region);
                for(int i = 0; i <= data.position_region; i++)
                    getline(tmp_stream, to_check_suitable_data, ',');
                if(to_check_suitable_data == data.region || data.region == "") {
                    suitable_regions.file_to_string += "\n" + last_read_region;
                    suitable_regions.rows_num += 1;
                }
            }
            suitable_regions.placed++;
        }
        fin.close();
    }
    return suitable_regions;
}

entry_point_returning_value get_metrics (entry_point_argument data) {
    entry_point_returning_value result;
    result.rows_num = data.rows_num;
    sort_array(data.column, data.rows_num);
    result.max = data.column[data.rows_num - 1];
    result.min = data.column[0];
    if (data.rows_num % 2 == 0) {
        result.mid = (data.column[data.rows_num/2 - 1] + data.column[data.rows_num/2])/2;
    } else {
        result.mid = data.column[(data.rows_num - 1)/2];
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
    }
    return result;
}
