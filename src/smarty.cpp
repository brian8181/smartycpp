#include <iostream>
#include <regex>
#include <fstream>
#include "regexpr.hpp"
#include "smarty.hpp"

smarty::smarty(const string& template_dir, const string& compile_dir, const string& config_dir, const string& cache_dir)
{
    // todo trim foward slash trim ...
    string s = "test/";
    s = trim(s, '/');

    this->template_dir = template_dir;
    this->compile_dir = compile_dir;
    this->config_dir = config_dir;
    this->cache_dir = cache_dir;

    trim(this->template_dir, '/');
    trim(this->compile_dir, '/');
    trim(this->config_dir, '/');
    trim(this->cache_dir, '/');
}

smarty::~smarty()
{
}

bool smarty::load_config(const string& path)
{
    string src = readfile(path);
    const string name_exp(LOAD_CONFIG_NAME);
    const string value_exp(LOAD_CONFIG_VALUE);
    regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp); 

    auto begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_default);
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
    vars.insert(p);
    return true;
}

// bool assign(const string& name, vector<string>& values)
// {
//     pair<string, vector<string>> p(name, values);
//     var_arrays.insert(p);
//     return true;
// }

bool smarty::display(const string& tmpl)
{
    string src = include(tmpl);
    src = remove_comments(src);
    src = if_sequence(src);
    //src = variable(src);

    //REPLACE VARIABLES
    regex exp = regex(VARIABLE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string& tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        map<string, string>::const_iterator find_iter = vars.find(tag);
        if(find_iter != vars.end())
        {
            output += find_iter->second;
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    // END REPLACE

    output = replace_tag(output, ESCAPE);
    cout << output << endl;
    return true;
}

std::string smarty::include(const string& tmpl)
{
    string path = template_dir + "/" + tmpl;
    //string src = readfile(path);
    string src = fread(path);
    regex exp = regex(INCLUDE, regex::ECMAScript);

    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string& tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        // call include recursively
        output += include(tag);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string smarty::variable(const string& src)
{
    regex exp = regex(VARIABLE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string& tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        map<string, string>::const_iterator find_iter = vars.find(tag);
        if(find_iter != vars.end())
        {
            output += find_iter->second;
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string smarty::replace_tag(string& src, const string& exp_str)
{
    string path = template_dir;
    regex exp = regex(exp_str, regex::ECMAScript);

    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        output += "@* ESCAPE: " + match.str() + " *@"; //testing
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string smarty::remove_comments(const string& src)
{
    regex exp = regex(COMMENT, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int end_pos = match.position();
        // remove comment
        output += src.substr(beg_pos, end_pos-beg_pos);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string smarty::if_sequence(const string& src)
{
    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int end_pos = match.position();
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string& tag = trim(s);
        //HTML
        output += "@IF SEQUENCE@\n";
        output += "@HTML@ " + tag + " @HTML@\n";
        output += "@/IF_SEQUENCE@\n";
        output += src.substr(beg_pos, end_pos-beg_pos);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

std::string smarty::readfile(const string& path)
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
            //src += tp += "\n";
            src += tp;
        }
        file.close(); //close the file object.
    }
    return src;
}

string smarty::fread(string path)
{
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return contents;
}


std::string& smarty::trim(string &s, char c)
{
    if(s.at(s.length()-1) == c)
        s.pop_back();

    return s;
}

std::string& smarty::ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                    [](char c) {
                        return !std::isspace<char>(c, std::locale::classic());
                    });
    s.erase(s.begin(), it);
    return s;
}

std::string& smarty::rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                    [](char c) {
                        return !std::isspace<char>(c, std::locale::classic());
                    });
    s.erase(it.base(), s.end());
    return s;
}

std::string& smarty::trim(std::string &s)
{
    return ltrim(rtrim(s));
}

std::string smarty::lex(const string& tmpl)
{
    string path = template_dir + "/" + tmpl;
    string src = readfile(path);
    regex exp = regex(INCLUDE, regex::ECMAScript);

    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string& tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        output += include(tag);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string smarty::get_conf(string s)
{
    return config[s];
}