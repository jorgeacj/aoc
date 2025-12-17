#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>

/* CONSTANTS */
const int DIAL_START = 50;
const std::string PATH {R"(C:\Boeing\aoc\day_1\inputs\input.txt)"};

/* GLOBALS */
int password = 0;

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

void inc_count(void)
{
    password++;
}

int sub_and_count(int a, int b)
{
    int ret = 0;
    std::div_t res = std::div(b,100);

    for (int i = 0; i < res.quot; i++)
    {
        inc_count();
    }

    if (a > res.rem)
    {
        ret = a - res.rem;
    }
    else if (a == res.rem)
    {
        inc_count();
        ret = 0;
    }
    else if (a < res.rem)
    {
        if (a == 0)
        {
            ret = 100 - res.rem;
        }
        else
        {
            ret = 100 + a - res.rem;
            inc_count();
        }
    }

    return ret;
}

int add_and_count(int a, int b)
{
    int ret = 0;
    std::div_t res = std::div(b,100);

    for (int i = 0; i < res.quot; i++)
    {
        inc_count();
    }

    if (a + res.rem < 100)
    {
        ret = a + res.rem;
    }
    else
    {
        ret = a + res.rem - 100;
        inc_count();
    }

    return ret;
}

int calculate_dial(int initial_dial, std::string pwd)
{
    int next_dial;

    int cnts = std::stoi(pwd.substr(1));    
    std::string dir = pwd.substr(0,1);

    if (dir.compare("L") == 0)
    {
        next_dial = sub_and_count(initial_dial, cnts);
    }
    else if (dir.compare("R") == 0)
    {
        next_dial = add_and_count(initial_dial, cnts);
    }

    return next_dial;
}

int main()
{   
    std::vector<std::string> vec = file_2_vector(PATH);
    int dial = DIAL_START;
    int pwd = 0;

    for (auto v : vec)
    {
        dial = calculate_dial(dial, v);
    }
    std::cout << password << std::endl;

    return 0;
}