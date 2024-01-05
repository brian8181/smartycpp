// License:    None
// Author:     Brian K Preston
// File Name:  ./token.hpp
// Build Date: Thu Dec 21 09:06:55 AM CST 2023
// Version:    0.0.2

#ifndef _TOKENS_HPP
#define _TOKENS_HPP

#include <string>

using std::string;

// tokens
const string INTEGER_LITERAL = "([0-9]+)";
const string FLOAT_LITERAL = "([0-9]*\\.[0-9]+)";
const string HEX_LITERAL = "(0x[0-9A-Fa-f]+)";
const string LOGICAL_OPERATORS = "((->)|(=>)|(==)|(!=)|(<=)|(>=)|(===))";
const string OPERATORS = "([\\s,/'\"$*#=+-:!%<>|.(){}\\]\\[])";
const string OPEN_CURLY_BRACE = "\\{";
const string CLOSE_CURLY_BRACE = "\\}";
const string FORWARD_SLASH = "/";
const string ASTERIK = "\\*";
const string HASH_MARK = "#";
const string DOLLAR_SIGN = "\\$";
const string QUOTE_MARK = "\"";
const string UNDERSCORE = "_";
const string MINUS_SIGN = "-";
const string EQUALS = "=";
const string EQUALS_LOGICAL = "==";
const string LESS_THAN_OPERATOR = "<";
const string GREATER_THAN_OPERATOR = ">";
const string NOT_OPERATOR = "!";
const string LESS_THAN_EQUAL_OPERATOR = "<=";
const string GREATER_THAN_EQUAL_OPERATOR = ">=";
const string NOT_EQUAL_OPERATOR = "!=";
const string VARIABLE_OFFSETS = "[*#$]";
//const string LITERAL_TEXT = "\\\"(" + VALID_ESC_CHARS + ")\\\"";
const string LITERAL_NUMERIC = "[0-9]*.?[0-9]*";
//const string LITERAL_COMMENT = "\\*(" + VALID_SYMBOL_CHARS + ")\\*";
const string WHITE_SPACE = "[:[space]:]";
const string ACTION_TOKEN = "(insert)|(include)|(config_load)";
// const string MATH = "(abs)|(ceil)|(cos)|(exp)|(floor)|(log)|(log10)|(max)|(min)|(pi)|(pow)|(rand)|(round)|(sin)|(sqrt)|(srans)|(tan)";
const string KEY_WORDS = "(if)|(else)|(elseif)|(foreach)|(foreachelse)|(literal)|(section)|(strip)|(assign)|(counter)|(cycle)|(debug)|(eval)|(fetch)|(html_checkboxes)";
const string REGEXP_TOKENS = "(" + VARIABLE_OFFSETS + ")|(" + ACTION_TOKEN + ")|(" + KEY_WORDS + ")";
const string VALID_ESC_CHARS = "[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,()]";
const string VALID_SYMBOL_CHARS = "[A-Za-z0-9_]";
const string VALID_FILE_CHARS = "[A-Za-z0-9_.]";
const string VAR_MODIFIER = "(capitalize)|(indent)|(lower)|(spacify)|(string_format)|(truncate)|(date_format)|(escape)";
const string LOAD_CONFIG_PAIR = "([A-Za-z]" + VALID_SYMBOL_CHARS + "*)=(" + VALID_SYMBOL_CHARS + "*);";
const string SYMBOL_NAME = "\\$?_*[A-Za-z]" + VALID_SYMBOL_CHARS + "*";
const string EXPR_VARIABLE = "\\$(" + SYMBOL_NAME + ")(\\|" + VAR_MODIFIER +  ")?";
// lexing
const string ESCAPE = "\\{" + VALID_ESC_CHARS + "*\\}";
const string TOKENS = "(" + EXPR_VARIABLE + ")|(" + ACTION_TOKEN + ")";

#endif