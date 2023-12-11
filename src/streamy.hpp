// License:    GPL
// Author:     Brian K Preston
// File Name:  streamy.hpp
// Build Date: Sun Oct  1 09:39:08 PM CDT 2023
// Version:    3.6.7

#ifndef _streamy_HPP
#define _streamy_HPP

#include <string>
#include <vector>
#include <map>
#include <regex>

using std::string;
using std::map;
using std::vector;
using std::pair;


// const string OPEN_CURLY_BRACE;
// const int STATE_BEGIN = 0;
// const int STATE_INITIAL = 9999;
// const int STATE_MATCH_START = 0x2;
// const int STATE_MATCH_FILE_KEYWORD = 0x4;
// const int STATE_MATCH_MODIFIER = 0x8;
// const int STATE_MATCH_FILE_NAME = 0x1000;
// const int STATE_MATCH_VARIABLE = 1;
// const int STATE_MATCH_LITERAL = 0x4;
// const int EVENT_INITIALIZED = 0x1;
// // events
// const int EVENT_MATCHED_CURLY = 0x2;
// const int EVENT_FILE_KEYWORD = 0x4;
// const int EVENT_COMMENT = 0x20;
// const int EVENT_MODIFIER = 0x8;
// const int EVENT_VARIABLE = 0x10;
// const int EVENT_STATIC = 0x40;
// const int EVENT_BEGIN_IF = 0x40;
// const int EVENT_END_IF = 0x80;
// const int EVENT_LITERAL = 0x100;
// const int EVENT_FILE_NAE = 0x200;

class streamy
{
public:
    streamy(const string& template_dir, const string& complie_dir, const string& config_dir, const string& cache_dir);
    string& load_config(const string& path, /* out */ string& s_out);
    void assign(const string& name, const string& val);
    void assign(const string& name, const vector<string>& vec);
    void display(const string& file);
    void clear_all();
    map<string, string>& get_map_vars(/* out */ map<string, string>& vars);
    map<string, string>& get_map_config(/* out */ map<string, string>& config);
    
private:
    // string& read_stream(const string& path, /* out */string& out);
    // int read_bits(const std::smatch& m);
    void find_escaped_text(const string& tmpl, /* out */ vector<pair<int, std::string>>& tokens);
    void lex(const string& tmpl, /* out */ vector<pair<int, std::string>>& tokens);
    void parse(const std::vector<pair<int, string>>& tokens, /* out */ string& html); 
    void parse_tag(const string token, /* out */ string& html); 
    void change_state(int event);

public:
    // maps
    map<string, string> map_config;
    map<string, string> map_vars;
    map<string, vector<string>> map_arrays;
    map<int, string> token_map;
    int state = 0;

    // testing
    typedef vector<pair<int, string>> token_vector;
    //token_vec v;
    // config
    string template_dir;
    string compile_dir;
    string config_dir;
    string cache_dir;
};

#endif



