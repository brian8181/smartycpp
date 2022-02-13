#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include "utility.hpp"

string fstream_readlines(string path)
{
    string src;
    fstream file;
    file.open(path, ios::in); //open a file to perform read operation using file object
    if (file.is_open())
    {   
        //checking whether the file is open
        string tp;
        while(getline(file, tp))
        { 
            //read data from file object and put it into string.
            src += tp += "\n";
        }
        file.close(); //close the file object.
    }

    return src;
}

string ifstream_readlines(string path)
{
    string src;
    ifstream file;
    file.open(path, ios::in); //open a file to perform read operation using file object

    if (file.is_open())
    {   
        //checking whether the file is open
        string tp;
        while(getline(file, tp))
        { 
            //read data from file object and put it into string.
            src += tp += "\n";
        }
        file.close(); //close the file object.
    }
    return src;
}

string fstream_read(string path)
{
    string str;
    fstream file;
    file.open(path, ios::in); //open a file to perform read operation using file object
    if (file.is_open())
    {   
        //checking whether the file is open
        char c[256];
        while(file.read(c, 256))
        { 
            //read data from file object and put it into string.
            str.append(c);
            //str.append("\n");
        }
        file.close(); //close the file object.
    }
    return str;
}

bool load_config(string path, map<string, string>& config)
{
    string src = fstream_readlines(path);

    string name_exp = "([A-Za-z]+\\w*)";
    string value_exp = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
    regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp); 
                    
    auto begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_not_null);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string name = match[1].str();
        string value = match[3].str() + match[5].str() + match[7].str();
        cout << "Match: --> " << match.str() <<  "; Name: --> " << match[1].str() << "; Value: --> " << value << endl;
        pair<string, string> p(name, value);
        config.insert(p);
    }
    return true;
}

void ParseCommand(string command)
{

    //string command = "(config_load|include|insert)\\sfile='(.*)'";
    regex exp = regex(command);

    auto begin = sregex_iterator(command.begin(), command.end(), exp, std::regex_constants::match_not_null);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
    }
}

// map sub matches
void MapSubs()
{
    
}

void assign(string name, string val, map<string, string>& symbols)
{
    pair<string, string> p(name, val);
    symbols.insert(p);
}

string display(string name)
{
    return fstream_readlines(name);
}
