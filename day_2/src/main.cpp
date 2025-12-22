#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

/* CONSTANTS */
const std::string PATH {R"(C:\Sandbox\aoc\day_2\inputs\input.txt)"};

/* GLOBALS */
volatile int64_t sum = 0;

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

    while(std::getline(file, text, ','))
    {
        vec.push_back(text);
    }

    file.close();

    return vec;
}

void sum_invalid_id(int64_t n)
{
    sum += n;
}

bool is_invalid(std::string n)
{
    std::string pattern;
    bool id_invalid = false;
    int size        = n.size();
    int cnt         = 0;    

    for (int idx = 1; idx < size; idx++)
    {
        if (size % idx == 0)
        {
            int jdx = idx;
            pattern = n.substr(0,idx);
            
            while (pattern.compare(n.substr(jdx,idx)) == 0)
            {
                jdx += idx;
                
                if (jdx >= n.length())
                {
                    id_invalid = true;
                    sum += std::stoll(n);
                    std::cout << "Invalid: " << n << " Sum: " << sum << std::endl;
                    return id_invalid;
                }
            }
        }
    }

    return id_invalid;
}

int get_invalids(const std::string str)
{
    int8_t pos;
    int64_t sum = 0;
    int64_t min, max;

    pos = str.find('-');
    min = stoll(str.substr(0,pos));
    max = stoll(str.substr(pos+1,str.length()));

    for (int64_t idx = min; idx <= max; idx++)
    {
        is_invalid(std::to_string(idx));
    }

    return 0;
}

int main()
{   
    std::vector<std::string> vec = file_2_vector(PATH);

    for (auto v : vec)
    {
        get_invalids(v);
    }

    std::cout << sum << std::endl;

    return 0;
}