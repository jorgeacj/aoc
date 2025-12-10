#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

/* CONSTANTS */
const int DIAL_START = 50;
const std::string PATH {R"(C:\Boeing\aoc\day_1\inputs\test.txt)"};

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

void inc_zeros(void)
{
    std::cout << "inc" << std::endl;
    password++;
}

int get_password(void)
{
    return password;
}

int sub_constrained(int a, int b)
{
    int ret = 0;

    if (b > 99)
    {
        b = b % 100;
        for (int i = 0; i < (b / 100); i++)
        {
            inc_zeros();
        }
    }
    if (a >= b)  
    {
        ret = a - b;
    }
    else
    {
        ret = 100 + a - b;
        inc_zeros();
    }

    return ret;
}

int add_constrained(int a, int b)
{
    int ret = 0;

    if (b > 99)
    {
        b = b % 100;
        for (int i = 0; i < (b / 100); i++)
        {
            inc_zeros();
        }
    }
    if (a + b < 100)
    {
        ret = a + b;
    }
    else if (a + b == 100)
    {
        ret = 0;
    }
    else
    {
        ret = a + b - 100; 
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
        next_dial = sub_constrained(initial_dial, cnts);
    }
    else if (dir.compare("R") == 0)
    {
        next_dial = add_constrained(initial_dial, cnts);
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
        std::cout << v << " " << dial << std::endl;
        if (dial == 0)
        {
            inc_zeros();
        }
    }

    std::cout << password << std::endl;

    return 0;
}