#include <string>
#include <vector>
#include <map>
#include <set>

// std::vector<std::string> split(std::string str, std::string delimeter);











std::vector<std::string> split(std::string str, std::string delimeter)
{
    std::vector<std::string> reslust_v_str;

    if (str.empty())
    {
        reslust_v_str.clear();
        return reslust_v_str;
    }
        
    
    int index = 0, head = index;

    while (index < str.length())
    {
        while (index < str.length() && str[index] != delimeter[0]) 
            ++ index;
        
        if (str.substr(index, delimeter.length()) == delimeter)
        {
            reslust_v_str.push_back(str.substr(head, index - head));
            index += delimeter.length();
            head = index;  
            continue;
        }
        ++ index;
    }

    reslust_v_str.push_back(str.substr(head, index - head));

    return reslust_v_str;
}