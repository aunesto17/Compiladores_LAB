#pragma once
/*
 * scanner.h
*/

#ifndef SCANNER_H_
#define SCANNER_H_

#include "helper.h"

class Scanner
{
private:
    string _inputString;
    int _index;
    int _size;
    int _tempIndex;
    int _lineIndex;
    int _columnIndex;
    int _errorCount;
    string _tempStr,_tempReserved;
    /*
    vector<string> reserved = {"print", "read", "while", "if", "int", "string", 
                               "boolean", "false", "true"};*/
    vector<string> reserved = {"False", "None", "True", "and", "as", "assert",
                                "async", "await", "break", "class", "continue",
                                "def", "del", "elif", "else", "except", "finally",
                                "for", "from", "global", "if", "import", "in", "is",
                                "lambda", "nonlocal", "not", "or", "pass", "raise",
                                "return", "try", "while", "with", "yield"};

    void updateIndex(int);
    int getReservedIndex(string);
    token getTokenReserved(int);
    string isReserved(string);
    void debug_scan(string);
public:
    Scanner(string input);
    void begin_scan();
    Token get_token();
    char peek_char();
    token peek_token();
    void print_token(token);
    string get_line_col();
    

    ~Scanner();
};






#endif


