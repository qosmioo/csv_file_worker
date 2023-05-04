#include "entry_point.h"

std::string get_files_data(std::string region, std::string file_name, int& count)
{
    std::fstream fin;
    std::string last_read_region;
    std::string tmp;
    std::string tmp_region;
    count = 0;

    fin.open(file_name);
    if(fin.is_open())
    {
        while(getline(fin, last_read_region))
        {
            std::stringstream stream(last_read_region);
            getline(stream, tmp_region, ',');
            getline(stream, tmp_region, ',');
            if (tmp_region == region || region == "" || count == 0) {
                tmp += last_read_region + "\n" ;
                ++count;
            }
        }

    }
    std::cout<<tmp<<std::endl;
    return tmp;
}
