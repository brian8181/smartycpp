// License:    GPL
// Author:     Brian K Preston
// File Name:  streamy.cpp
// Build Date: Thu Dec 21 09:06:55 AM CST 2023
// Version:    0.0.2

#include <iostream>
#include <regex>
#include <sstream>
#include <map>
#include "streamy.hpp"
#include "utility.hpp"
#include "tokens.hpp"
#include "grammer.hpp"
#include "bash_color.h"
#include <filesystem>

using namespace std;

map<string, unsigned int> _token_map = { {"{", ID_OPEN_CURLY_BRACE}, {"}", ID_CLOSE_CURLY_BRACE}, {"#", ID_HASH_MARK}, {"*", ID_ASTERIK}, {"$", ID_DOLLAR_SIGN}, 
                                          {"=", ID_EQUAL}, {"|", ID_VBAR}, {":", ID_COLON}, {"\"", ID_DOUBLE_QUOTE}, {"'", ID_SINGLE_QUOTE}, {".", ID_DOT},
                                          {"+", ID_PLUS}, {"-", ID_MINUS}, {"%", ID_MODULUS}, 
                                          {"[", ID_OPEN_BRACE}, {"]", ID_CLOSE_BRACE}, {";", ID_SEMI_COLON},
                                          {"&&", ID_LOGICAL_AND}, {"||", ID_LOGICAL_OR}, {"!", ID_LOGICAL_NOT},
                                          {"if", ID_IF}, {"ELSEIF", ID_ELSEIF}, {"ELSE", ID_ELSE}, {"foreach", ID_FOREACH}, {"foreachelse", ID_FOREACHELSE},
                                          {"include", ID_BUILTIN_FUNCTION }, {"config_load", ID_BUILTIN_FUNCTION }, {"insert", ID_BUILTIN_FUNCTION},
                                          {"assign", ID_BUILTIN_FUNCTION }, {"fetch", ID_BUILTIN_FUNCTION}, {"capture", ID_BUILTIN_FUNCTION },
                                          {"upper", ID_MODIFIER_UPPER}, {"lower", ID_MODIFIER_LOWER}, {"truncate", ID_MODIFIER_TRUNCATE}, {"capitalize", ID_MODIFIER_CAPATIALIZE},
                                          {"indent", ID_MODIFIER_INDENT} };
unsigned int token_id = 0;

streamy::streamy()
{
    this->template_dir = "../streamy/templates";
    this->compile_dir = "../streamy/compile";
    this->config_dir = "../streamy/config";
    this->cache_dir = "../streamy/cache";
}

streamy::streamy(const string& template_dir, const string& compile_dir, const string& config_dir, const string& cache_dir)
{
    this->template_dir = template_dir;
    this->compile_dir = compile_dir;
    this->config_dir = config_dir;
    this->cache_dir = cache_dir;
}

void streamy::config_load(const string& path)
{
    string s_out;
    read_stream(path, s_out);
    regex rgx = regex(LOAD_CONFIG_PAIR); 

    auto begin = sregex_iterator(s_out.begin(), s_out.end(), rgx, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string symbol_name = match[1].str();
        string value = match[2].str();
        pair<string, string> p(symbol_name, value);
        map_config.insert(p);
    }
}

void streamy::config_load(const string& path, const string& section)
{
    string s_out;
    read_stream(path, s_out);
    regex rgx = regex(LOAD_CONFIG_PAIR); 

    auto begin = sregex_iterator(s_out.begin(), s_out.end(), rgx, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string symbol_name = match[1].str();
        string value = match[2].str();
        pair<string, string> p(symbol_name, value);
        map_config.insert(p);
    }
}

void streamy::display(const string& tmpl)
{
    string _html;
    compile(tmpl, _html);
    // stdout final
    // cout << _html << endl;
}

string& streamy::fetch(const string& tmpl, const string& cache_id, const string& compile_id, /*out*/ string& html)
{
    compile(tmpl, html);
    return html;
}

string& streamy::compile(const string& tmpl, /* out */ string& html)
{
    // open file the call parse function ...
    string full_path = this->template_dir + "/" + tmpl;
    // find escape sequences
    vector<std::pair<int, vector<std::string>>> escapes;
    find_escapes(full_path, escapes);



    int len = escapes.size();
    for(int i = 0; i < len; ++i)
    {
        cout << escapes[i].second[0];
    }
    // lex_escapes(escapes, tokens);
    // parse the tokens appling agrammer rules
    // parse(tokens, html);

    return html;
}

void streamy::assign(const string& symbol_name, const string& val)
{
    pair<string, string> p(symbol_name, val);
    map_vars.insert(p);
}

void streamy::assign(const string& symbol_name, const vector<string>& vec)
{
    pair<string, vector<string>> p(symbol_name, vec);
    map_arrays.insert(p);
}

void streamy::find_escapes(const string& tmpl, /* out*/ std::vector<pair<int, vector<string>>>& escapes)
{
    string s;
    read_stream(tmpl, s);
    regex exp = regex(ESCAPE, std::regex::ECMAScript);
    smatch match;
    while(std::regex_search(s, match, exp, std::regex_constants::match_default))
    {
        std::string fmt_match_beg = match.format("$`");
        std::string fmt_match = match.format("$&");
        vector<string> begin_text = {fmt_match_beg};
        escapes.push_back(pair(TEXT, begin_text));
        //cout << fmt_match_beg;
        vector<string> tag_match = {fmt_match};
        escapes.push_back(pair(TAG, tag_match));
        vector<vector<string>> tokens;
        lex_escapes(escapes, tokens);
       
        // vector<string> tok_line;
        // lex(fmt_match, tok_line);
        // vector<vector<string>> dummy_one_line_vector = { tok_line };
        // string html;
        // parse(dummy_one_line_vector, html);
        // // puke out the html        
        // cout << html;

        s = match.format("$'");
    }
    //escapes.push_back(pair(TEXT, s));
    cout << s;
}

void streamy::lex_escapes(vector<pair<int, vector<string>>>& escapes, /* out */ vector<vector<string>>& tokens)
{
    int len = escapes.size();
    for(int i = 0; i < len; ++i)
    {
        pair<int, vector<std::string>> p = escapes[i];
        switch(p.first)
        {
            case TEXT:
                break;
            case TAG:
                vector<string> tok_line;
                lex(p.second, tok_line);
                //tokens.push_back(tok_line);
                p.second = tok_line;
                break;
        }
    }
}

void streamy::lex(const vector<string>& s, /* out */ vector<string>& tokens)
{
    string end_of_string = s[0];
    regex exp = regex(HEX_LITERAL + "|" + FLOAT_LITERAL + "|" + LOGICAL_OPERATORS + "|" + OPERATORS, std::regex::ECMAScript); 
    smatch match;

    while(std::regex_search(end_of_string, match, exp, std::regex_constants::match_default))
    {
        std::string fmt_match_beg = match.format("$`");
        std::string fmt_match = match.format("$&");
        if(fmt_match_beg.size() > 0)
            tokens.push_back(fmt_match_beg);
        if(!std::isspace(fmt_match[0]))    
            tokens.push_back(fmt_match);

        end_of_string = match.format("$'");
        if(fmt_match == "*" || fmt_match == "#" || fmt_match == "\"" || fmt_match == "'")
        {
            int pos = end_of_string.find_first_of("*#\"'");
            tokens.push_back(end_of_string.substr(0, pos));
            tokens.push_back(end_of_string.substr(pos, 1));
            end_of_string = end_of_string.substr(pos+1, 1);
        }
    }
}

void streamy::parse(vector<vector<string>>& tokens, /* out */ string& html)
{
    //int ilen = tokens.size();
    string symbol_name;
    //for(int i = 0; i < ilen; ++i)
    //{
        int jlen = tokens[0].size();
        for(int j = 0; j < jlen; ++j)
        {
            string token = tokens[0][j];
            //if(token.size() == 1)
            {
                switch(_token_map[token])
                {
                    case ID_OPEN_CURLY_BRACE:
                    case ID_CLOSE_CURLY_BRACE:
                        break;
                    case ID_DOLLAR_SIGN:
                    {
                        //vector<vector<string>>::iterator iter = tokens.begin();
                        symbol_name = tokens[0][j+1];
                        string value = map_vars[symbol_name];
                        html = value;
                        vector<string> line_vec = { value };
                        //tokens.erase(iter+i);
                        //tokens.insert(iter+i, line_vec); 
                        break;
                    }
                    case ID_HASH_MARK:
                    {
                        //vector<vector<string>>::iterator iter = tokens.begin();
                        symbol_name = tokens[0][j+1];
                        string value = map_config[symbol_name];
                        html = value;
                        vector<string> line_vec = { value };
                        //tokens.erase(iter+i);
                        //tokens.insert(iter+i, line_vec); 
                        break;
                    }
                    case ID_ASTERIK:       
                    {
                        //vector<vector<string>>::iterator iter = tokens.begin();
                        //html = ""; do nothing, comment are just not displayed
                        //tokens.erase(iter+i);
                        break;
                    }
                    case ID_MODULUS:
                    case ID_LOGICAL_AND:
                    case ID_LOGICAL_OR:
                    case ID_LOGICAL_NOT:
                    case ID_LESS_THAN:
                    case ID_GREATER_THAN:
                    case ID_DOUBLE_QUOTE:
                    case ID_SINGLE_QUOTE:
                    case ID_PLUS:
                    case ID_MINUS:
                    case ID_VBAR:
                    case ID_DOT:
                    case ID_COLON:
                    case ID_SEMI_COLON:
                    case ID_OPEN_PAREN:
                    case ID_CLOSE_PAREN:
                    case ID_OPEN_BRACE:
                    case ID_CLOSE_BRACE:
                    case ID_EQUAL:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                    case ID_IF:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                    case ID_ELSE:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                    case ID_FOREACH:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                    case ID_FOREACHELSE:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                    
                    case ID_BUILTIN_FUNCTION:
                    {
                        cout << FMT_FG_YELLOW << "todo: built in fucntion: " << FMT_RESET << FMT_FG_MAGENTA << token << FMT_RESET << endl; 
                        break;
                    }
                   default:
                   {
                        cout << FMT_FG_RED << "error " << FMT_RESET << FMT_BOLD << "unknown token: " 
                            << FMT_FG_BLUE << token << FMT_RESET << endl;
                        break;
                   }
                }
            }
        }
    //}
}

vector<pair<string, string>>& streamy::get_registered_object(string object_name, /*out*/ vector<pair<string, string>>& registered_object)
{
    return registered_object;
}

void streamy::clear_cache()
{
    // delete cache
    filesystem::path p = cache_dir;
}

std::map<string, string>& streamy::get_map_config()
{
    return map_config;
}

std::map<string, string>& streamy::get_map_vars()
{
    return map_vars;
}

map<string, vector<string>>& streamy::get_map_arrays()
{
    return map_arrays;
}

void streamy::clear_config()
{
    map_config.clear();
}

void streamy::clear_config(string symbol_name)
{
    map_config.erase(symbol_name);
}

void streamy::clear_assign()
{
    map_vars.clear();
}

void streamy::clear_assign(string symbol_name)
{
    map_vars.erase(symbol_name);
}

void streamy::clear_all()
{
    map_config.clear();
    map_vars.clear();
    map_arrays.clear();
}

string smarty_prefilter_name(const string& src, const string& smarty)
{
    return "";
}

string smarty_postfilter_name(const string& src, const string& smarty)
{
    return "";
}

unsigned int streamy::get_state()
{
    return state;
}
