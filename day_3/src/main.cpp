#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <typeinfo>

/* CONSTANTS */
const std::string PATH {R"(C:\Sandbox\aoc\day_3\inputs\input.txt)"};

/* GLOBALS */
int sum = 0;

/* FUNCTIONS */
std::vector<std::string> file_2_vector(const std::string path)
{
    std::string text;
    std::ifstream file(path);
    std::vector<std::string> vec;

    if(!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    while(std::getline(file, text))
    {
        vec.push_back(text);
    }

    file.close();

    return vec;
}

int char_to_int(char c)
{
    int n = (int) c - 48;
    return n;
}


void find_battery(std::string str)
{
    int battery = 0;
    int batt_1  = 0;
    int batt_2  = 0;
    
    for (int idx = 0; idx < str.size(); idx++)
    {
        int n = char_to_int(str.at(idx));
        if ( (n > batt_1) && (idx < (str.size()-1)) )
        {
            batt_1 = n;
            batt_2 = 0;
            continue;
        }
        else if (n > batt_2)
        {
            batt_2 = n;
            continue;
        }
    }

    battery = 10 * batt_1 + batt_2;
    std::cout << "Battery: " << battery << std::endl;
    sum += battery;
}

int main()
{   
    std::vector<std::string> vec = file_2_vector(PATH);

    for (auto v : vec)
    {
        find_battery(v);
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}