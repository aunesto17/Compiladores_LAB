//#pragma once
/*
 * helper.h
*/

#ifndef HELPER_H_
#define HELPER_H_

#include <string>
#include <map>
#include <ctype.h>
#include <vector>
#include <algorithm>

using namespace std;

enum class token
{
    // end of file
    TOKEN_EOF = -1,
    // block terminals
    TOKEN_OPEN_SQR_BRACKET,
    TOKEN_CLOSE_SQR_BRACKET,
    // bracket terminals
    TOKEN_OPEN_BRCKT,
    TOKEN_CLOSE_BRCKT,
    // statements
    // control structures
    TOKEN_WHILE_STMNT,
    TOKEN_IF_STMNT,
    // operators & delimitadores
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_ARROW,
    TOKEN_MOD,
    TOKEN_LESSTEQUAL,
    TOKEN_LESST,
    TOKEN_GREATERTEQUAL,
    TOKEN_GREATERT,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_POINT,
    // values
    TOKEN_INT_VAL,
    TOKEN_STR_VAL,
    TOKEN_BOOL_TRUE_VAL,
    TOKEN_BOOL_FALSE_VAL,
    TOKEN_NONE_VAL,
    // connector
    TOKEN_AND,
    TOKEN_AS,
    TOKEN_ASSERT,
    TOKEN_ASYNC,
    TOKEN_AWAIT,
    TOKEN_BREAK,
    TOKEN_CLASS_TYPE,
    TOKEN_CONTINUE,
    TOKEN_DEF,
    TOKEN_DEL,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_EXCEPT,
    TOKEN_FINALLY,
    TOKEN_FOR,
    TOKEN_FROM,
    TOKEN_GLOBAL,
    TOKEN_IF,
    TOKEN_IMPORT,
    TOKEN_IN,
    TOKEN_IS,
    TOKEN_LAMBDA,
    TOKEN_NONLOCAL,
    TOKEN_NOT,
    TOKEN_OR,
    TOKEN_PASS,
    TOKEN_RAISE,
    TOKEN_RETURN,
    TOKEN_TRY,
    TOKEN_WHILE,
    TOKEN_WITH,
    TOKEN_YIELD,
    // identifier
    TOKEN_ID,
    // types
    TOKEN_INT_TYPE,
    TOKEN_STR_TYPE,
    TOKEN_BOOL_TYPE,
    // compare operator
    TOKEN_EQUAL,
    TOKEN_NEQUAL,
    TOKEN_DOUBLE_SLASH,
};

struct Token
{
    token _type;
    string _value;
    Token(token t, string val):_type(t), _value(val){}
    Token(token t):_type(t),_value("0"){}
    Token(){};
    ~Token(){};
};

/*
Token create_token(token t, string val){
    Token tempToken;
    tempToken._type = t;
    tempToken._value = val;
    return tempToken;
}
*/


string read_file(const char * path);

#endif


