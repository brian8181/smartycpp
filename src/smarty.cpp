#include <iostream>
#include <regex>
#include <fstream>
#include "smarty.h"

smarty::smarty(const string& template_dir, const string& complie_dir, const string& config_dir, const string& cache_dir)
{
    this->template_dir = template_dir;
    this->compile_dir = compile_dir;
    this->config_dir = config_dir;
    this->cache_dir = cache_dir;
}

smarty::~smarty()
{
}

bool smarty::load_config(const string& path)
{
    string src = readfile(path);
    string name_exp = "([A-Za-z]+\\w*)";
    string value_exp = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
    regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp); 
                    
    auto begin = sregex_iterator(src.begin(), src.end(), src_exp);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string name = match[1].str();
        string value = match[3].str() + match[5].str() + match[7].str();
        pair<string, string> p(name, value);
        config.insert(p);
    }
    return true;
}

bool smarty::assign(const string& name, const string& val)
{
    pair<string, string> p(name, val);
    symbols.insert(p);
    return true;
}

bool smarty::display(const string& tmpl)
{
    string src = readfile(tmpl);
    regex exp = regex("\\{\\$(.*?)\\}", regex::ECMAScript);
            
    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), exp);
    auto end = sregex_iterator(); 
    
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        string tag = trim(sub.str());
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        map<string, string>::const_iterator find_iter = symbols.find(tag);
        if(find_iter != symbols.end())
        {
            output += find_iter->second;
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    cout << output << endl;

    return true;
}

string smarty::readfile(const string& path)
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

std::string smarty::ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string smarty::rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string smarty::trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

// std::string& ltrim(std::string &s)
// {
//     auto it = std::find_if(s.begin(), s.end(),
//                     [](char c) {
//                         return !std::isspace<char>(c, std::locale::classic());
//                     });
//     s.erase(s.begin(), it);
//     return s;
// }
 
// std::string& rtrim(std::string &s)
// {
//     auto it = std::find_if(s.rbegin(), s.rend(),
//                     [](char c) {
//                         return !std::isspace<char>(c, std::locale::classic());
//                     });
//     s.erase(it.base(), s.end());
//     return s;
// }
 
// std::string& trim(std::string &s)
// {
//     return ltrim(rtrim(s));
// }