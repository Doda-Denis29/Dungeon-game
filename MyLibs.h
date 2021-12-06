// This is where I have most of my libs that I will be using and some functions

//These are the colours for system(colours);
/*0-Black
* 1-Blue
* 2-Green
* 3-Aqua
* 4-Red
* 5-Purple
* 6-Yellow
* 7-White
* 8-Gray
* 9-LightBlue
* A-Light Green
* B-Light Aqua
* C-Light Red
* D-Light Purple
* E-Light Yellow
* F-Bright White
*/

#include <fstream>
#include <time.h>
#include <vector>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef MyLibs
#define MyLibs

void delay(float number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void mapINIT(std::vector <short>& a)
{
    //0 means nothing, 1 means fight, 2 means decision, 3 means deadend, 4 means boss fight.
    for (auto in = 0; in < 26; in++)
    {
        if (in % 3 == 0 && in != 24 && in != 0)
        {
            a.push_back(1);
        }
        else if (in == 5 || in == 8 || in == 13 || in == 24)
        {
            a.push_back(2);
        }
        else if (in == 25)
        {
            a.push_back(4);
        }
        else
        {
            a.push_back(0);
        }
    }
}

int getMax(int numb, int& max)
{
    if (numb > max)
    {
        max = numb;
    }
    return max;
}

void logdetailsINIT(char (*t)[97], size_t rows) //This was the hardest thing to do
{
    std::ifstream file("log.txt");
    char c{};
    auto in = 0;
    while (!file.eof())
    {
        file.get(c);
        if (c != '\n')
        {
            t[in / 97][in % 97] = c;
        }
        in++;
    }
    file.close();
}

int SkellyA()
{
    size_t atc = rand();
    if (atc % 2 == 0)
    {
        return 0;
    }
    else if (atc % 2 != 0)
    {
        return 1;
    }
}

int DemonicoA()
{
    size_t atc = rand();
    if (atc % 2 == 0)
    {
        return 0;
    }
    else if (atc % 5 == 0)
    {
        return 1;
    }
    else if (atc % 3 == 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

#endif