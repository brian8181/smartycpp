#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        string src = fstream_read(path);
        cout << src << endl;
    }
}