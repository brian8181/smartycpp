// License:    GPL
// Author:     Brian K Preston
// File Name:  streamy.cpp
// Build Date: Sun Oct  1 09:39:08 PM CDT 2023
// Version:    3.6.7

#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include "bash_color.h"
#include "symbols.hpp"
#include "streamy.hpp"

using namespace std;

//vector<string> KEYWORDS_REGEX { VARIABLE, ARRAY, OBJECT, STATIC_VARIABLE, INCLUDE, CONFIG_LOAD, COMMENT };

streamy::streamy(const string& template_dir, const string& compile_dir, const string& config_dir, const string& cache_dir)
{
    this->template_dir = template_dir;
    this->compile_dir = compile_dir;
    this->config_dir = config_dir;
    this->cache_dir = cache_dir;
}

string& streamy::load_config(const string& path, /* out */ string& s_out)
{
    s_out = read_stream(path, s_out);
    regex rgx = regex(LOAD_CONFIG_PAIR); 

    auto begin = sregex_iterator(s_out.begin(), s_out.end(), rgx, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string name = match[1].str();
        string value = match[2].str();
        pair<string, string> p(name, value);
        map_config.insert(p);
    }
    return s_out;
}

bool streamy::assign(const string& name, const string& val)
{
    pair<string, string> p(name, val);
    map_vars.insert(p);
    return true;
}

bool streamy::assign(const string& name, const vector<string>& vec)
{
    pair<string, vector<string>> p(name, vec);
    var_arrays.insert(p);
    return true;
}

void streamy::display(const string& file)
{
    // open file the call parse function ...
    string full_path = this->template_dir + "/" + file;
    std::vector<pair<int, std::string>> tokens;
    lex(file, tokens);
    string _html;
    parse(tokens, _html); 
    cout << _html << endl;
}

bool streamy::lex(const string& tmpl, /* out */ std::vector<pair<int, std::string>>& tokens)
{
    string full_path = this->template_dir + "/" + tmpl;
    string s;
    read_stream(full_path, s);
    tokens.clear(); // clear tokens

    regex exp = regex(ESCAPE, std::regex::ECMAScript); // match
    smatch match;
    while(std::regex_search(s, match, exp, std::regex_constants::match_default))
    {
        std::string fmt_match_beg = match.format("$`");
        std::string fmt_match = match.format("$&");

        tokens.push_back(pair(TEXT, fmt_match_beg));
        tokens.push_back(pair(TAG, fmt_match));
        s = match.format("$'");

        // lex tag
        string token_str = s;;
        regex exp_toks = regex(TOKENS,  std::regex::ECMAScript); // match
        smatch tok_match;
        while(std::regex_search(token_str, match, exp_toks, std::regex_constants::match_default))
        {
            std::string fmt_match_beg = match.format("$`");
            std::string fmt_match = match.format("$&");

            // int TOKEN_TYPE; // set value from bits
            //tokens.push_back(pair(TEXT, fmt_match_beg));
            tokens.push_back(pair(TOKEN, fmt_match));
            token_str = match.format("$'");
        }
        tokens.push_back(pair(TOKEN,token_str ));
    }
    tokens.push_back(pair(1, s));
    return true;
}

bool streamy::parse(const std::vector<pair<int, std::string>>& tokens, /* out */ string& html)
{
    stringstream ss;
    stringstream estream;

    estream     << "(" 
                << EXPR_ARRAY 
                << ")|("
                << EXPR_ACTION_FILE 
                << ")|("  
                << EXPR_STATIC_VARIABLE 
                << ")|(" 
                << EXPR_VARIABLE 
                << ")|("
                << EXPR_COMMENT 
                << ")";
 
    int len = tokens.size();
    for(int i = 0; i < len; ++i)
    {
        switch(tokens[i].first)
        {
            case TEXT:
                ss << tokens[i].second;
                break;
            case TAG:

                string expression_stream = estream.str();
                regex exp = regex(expression_stream, regex::ECMAScript); // match
                smatch m;
                std::regex_search(tokens[i].second, m, exp);

                int bits = read_bits(m);
           
                if (!m.empty())
                {
                    if(m[ESC_REG_VAR].matched || m[ESC_STATIC_VAR].matched || m[ESC_ARRAY_VAR].matched || m[ESC_COMMENT].matched || m[ESC_INCLUDE].matched)
                    {
                        ss << FMT_FG_GREEN << "MATCH( " << FMT_RESET << FMT_FG_BLUE << FMT_UNDERLINE << tokens[i].second
                            << FMT_RESET_UNDERLINE << FMT_RESET << FMT_FG_GREEN << " )" << FMT_RESET << " : " << std::oct << bits;
                        break;
                    }
                }
                ss << FMT_FG_RED << "ERROR( " << FMT_RESET << FMT_FG_LIGHT_CYAN << tokens[i].second << FMT_RESET << FMT_FG_RED << " )" << FMT_RESET;
                break;
        }
    }
    html = ss.str();
    return true;
}

bool streamy::parse_tag(const string token, /* out */ string& html)
{
    // regex exp = regex(INCLUDE, regex::ECMAScript); // match
    // std::regex_search(tokens[i].second, m, exp);
    // if (!m.empty())
    // {
    //     sub_match sm = m[1];
    //     map<string, string>::const_iterator find_iter = config.find(sm.str());
    //     if(find_iter != config.end())
    //     {
    //         ss << find_iter->second;
    //         break;
    //     }
    // }
    return true;
}

std::map<string, string>& streamy::get_map_config(/* out */ std::map<string, string>& config)
 {
    config = map_config;
    return config;
 }

 std::map<string, string>& streamy::get_map_vars(/* out */ std::map<string, string>& vars)
 {
    vars = map_vars;
    return vars;
 }

int streamy::read_bits(const smatch& m)
{
    int len = m.size();
    unsigned int bits = 0;
    for(int i = 0; i < len && i < 32; ++i)
    {
        bits |= (int(m[i].matched) << i);
    }
    return bits;
}

string& streamy::read_stream(const string& path, /* out */ string& s_out)
{
    std::ifstream ifstrm(path);
    std::string output((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
    s_out = output;
    return s_out;
}

// string& streamy::include(const string& tmpl, /* out */ string& s_out)
// {
//     string path = template_dir + "/" + tmpl;
//     string src;
//     read_stream(path, src);

//     regex exp = regex(INCLUDE, regex::ECMAScript);
//     auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
//     auto end = sregex_iterator(); 
//     int beg_pos = 0;
//     for (sregex_iterator iter = begin; iter != end; ++iter)
//     {
//         smatch match = *iter;
//         std::ssub_match sub = match[1];
//         string s(sub.str());
//         string& tag = trim(s);
        
//         int end_pos = match.position();
//         s_out += src.substr(beg_pos, end_pos-beg_pos);
//         // call include recursively
//         s_out += include(tag, s_out);
//         beg_pos = end_pos + match.length();
//     }
//     s_out += src.substr(beg_pos);
//     return s_out;
// }
