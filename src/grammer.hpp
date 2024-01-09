// License:    None
// Author:     Brian K Preston
// File Name:  grammer.hpp
// Build Date: Thu Jan  4 07:56:02 PM CST 2024
// Version:    0.0.1

#ifndef _GRAMMER_HPP
#define _GRAMMER_HPP

#include <string>

using std::string;


enum token_id : unsigned long
{
    ID_IF                 = 0x1ul,
    ID_ELSE               = 0x2ul,
    ID_ELSEIF             = 0x4ul,
    ID_FOREACH            = 0x8ul,
    ID_DOUBLE_QUOTE       = 0x10ul,
    ID_SINGLE_QUOTE       = 0x20ul,
    ID_OPEN_BRACE         = 0x40ul,
    ID_CLOSE_BRACE        = 0x80ul,
    ID_FOREACHELSE        = 0x100ul,
    ID_LITERAL            = 0x200ul,
    ID_OPEN_CURLY_BRACE   = 0x400ul,
    ID_CLOSE_CURLY_BRACE  = 0x800ul,
    ID_ASTERIK            = 0x1000ul,
    ID_HASH_MARK          = 0x2000ul,
    ID_DOLLAR_SIGN        = 0x4000ul,
    ID_DOT                = 0x8000ul,
    ID_EQUAL              = 0x10000ul,
    ID_BUILTIN_FUNCTION   = 0x20000ul,
    ID_VBAR               = 0x40000ul,
    ID_COLON              = 0x80000ul,
    ID_SEMI_COLON         = 0x100000ul,
    ID_LOGICAL_NOT        = 0x200000ul,
    ID_LESS_THAN          = 0x400000ul,
    ID_GREATER_THAN       = 0x800000ul,
    ID_MINUS              = 0x1000000ul,
    ID_PLUS               = 0x2000000ul,
    ID_OPEN_PAREN         = 0x4000000ul,
    ID_CLOSE_PAREN        = 0x8000000ul,
    ID_MODULUS            = 0x10000000ul,
    ID_LOGICAL_AND        = 0x20000000ul,
    ID_LOGICAL_OR         = 0x40000000ul,
    ID_DIVIDE_OR          = 0x80000000ul,
    ID_MULTIPLY           = 0x100000000ul,
    ID_LOGICAL_EQUAL      = 0x200000000ul,
    ID_MODIFIER_CAPATIALIZE = 0x400000000ul,
    ID_MODIFIER_INDENT      = 0x600000000ul,
    ID_MODIFIER_LOWER       = 0x800000000ul,
    ID_MODIFIER_UPPER       = 0x1000000000ul,
    ID_MODIFIER_TRUNCATE    = 0x2000000000ul,
    ID_MODIFIER_SPACIFY     = 0x4000000000ul,
    ID_MODIFIER_STRINGF_FORMAT = 0x8000000000ul,
    ID_MODIFIER_DATE_FORMAT    = 0x10000000000ul,
    ID_MODIFIER_ESCAPE         = 0x20000000000ul
};




// const string VALID_ESC_CHARS = "[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,()]";
// const string VALID_SYMBOL_CHARS = "[A-Za-z0-9_]";
// const string VALID_FILE_CHARS = "[A-Za-z0-9_.]";

// const string SYMBOL_NAME = "\\$?_*[A-Za-z]" + VALID_SYMBOL_CHARS + "*";
// const string VARIABLE_TOKEN = "\\$(" + SYMBOL_NAME + ")";
// const string COMMENT_TOKEN = "\\*\\s*" + VALID_SYMBOL_CHARS + "*\\s*\\*";
// const string STATIC_VARIABLE_TOKEN = "\\s*#(" + SYMBOL_NAME + ")#\\s*";

// //const string LITERAL_TEXT = "\\\"(" + VALID_ESC_CHARS + ")\\\"";
// const string LITERAL_NUMERIC = "[0-9]*.?[0-9]*";
// //const string LITERAL_COMMENT = "\\*(" + VALID_SYMBOL_CHARS + ")\\*";
// const string WHITE_SPACE = "[:[space]:]";

// const string ACTION_TOKEN = "(insert)|(include)|(config_load)";
// // const string MATH = "(abs)|(ceil)|(cos)|(exp)|(floor)|(log)|(log10)|(max)|(min)|(pi)|(pow)|(rand)|(round)|(sin)|(sqrt)|(srans)|(tan)";
// const string KEY_WORDS = "(if)|(else)|(elseif)|(foreach)|(foreachelse)|(literal)|(section)|(strip)|(assign)|(counter)|(cycle)|(debug)|(eval)|(fetch)|(html_checkboxes)";

// const string MATCHED_OPEN_CURLY = "(" + VARIABLE_TOKEN 
//                                     + ")|("
//                                     + COMMENT_TOKEN
//                                     + ")|("
//                                     + ACTION_TOKEN
//                                     + ")}("
//                                     + STATIC_VARIABLE_TOKEN
//                                     + ")";
// const string VAR_MODIFIER = "(capitalize)|(indent)|(lower)|(spacify)|(string_format)|(truncate)|(date_format)|(escape)";
// const string CONFIG_PAIR = "([A-Za-z]" + VALID_SYMBOL_CHARS + "*)=(" + VALID_SYMBOL_CHARS + "*);";

// const string EXPR_VARIABLE = "\\$(" + SYMBOL_NAME + ")(\\|" + VAR_MODIFIER +  ")?";
// const string EXPR_OBJECT =  "\\{\\s*\\$(" + SYMBOL_NAME + ")(?:\\.)|(?:->)" + SYMBOL_NAME + "(\\(\\))*\\s*\\}";
// const string EXPR_ARRAY = "\\$(" + SYMBOL_NAME + ")\\[([0-9]+)\\]";
// const string EXPR_STATIC_VARIABLE = "\\s*#(" + SYMBOL_NAME + ")#\\s*";
// const string EXPR_ACTION_FILE = ACTION_TOKEN + " file=\"" + VALID_FILE_CHARS + "+\"";
// const string EXPR_COMMENT = "\\*\\s*" + VALID_SYMBOL_CHARS + "*\\s*\\*";

// // lexing
// const string ESCAPE = "\\{" + VALID_ESC_CHARS + "*\\}";
// const string TOKENS = "(" + EXPR_VARIABLE + ")|(" + ACTION_TOKEN + ")";


#endif