#include <iostream>
#include "scanner.h"

Scanner::Scanner(string input)
{
    _inputString = input;
    _index = 0;
    _size = input.length();
    _lineIndex = 1;
    _columnIndex = 1;
    _errorCount = 0;
    cout << "input size: " << _size << endl; 
}

void Scanner::begin_scan()
{   
    while (_index < _size)
    {
        get_token();
    }
    cout << "INFO SCAN - Completed with " << _errorCount << " errors" << endl;
    _index = 0;
    _lineIndex = 1;
    _columnIndex = 1;
    _errorCount = 0;
}

Token Scanner::get_token()
{
begin:
    char next;
    token tempTokenType;
    Token tempToken;
    tempToken._type = token::TOKEN_EOF;
    // skip initial white space if any
    while (_index < _size && ((next = _inputString[_index])  == ' ' || 
                              next == '\t'))
    {
        updateIndex(1);
    }

    // EOF reached
    if (_index >= _size) {
        cout << "EOF reached..." << endl;
        return tempToken;
    }
    // check string
    switch (next)
    {
    case '\n':
        _index++;
        _lineIndex++;
        _columnIndex = 1;
        goto begin;
    case '{':
        debug_scan("TOKEN_OPEN_BLOCK - [ [ ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_OPEN_SQR_BRACKET;
        break;
    case '}':
        debug_scan("TOKEN_CLOSE_BLOCK - [ ] ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_CLOSE_SQR_BRACKET;
        break;
    case '(':
        debug_scan("TOKEN_OPEN_BRCKT - [ ( ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_OPEN_BRCKT;
        break;
    case ')':
        debug_scan("TOKEN_CLOSE_BRCKT - [ ) ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_CLOSE_BRCKT;
        break;
    case '+':
        debug_scan("TOKEN_PLUS - [ + ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_PLUS;
        break;
    case '-':
        if (_inputString[_index + 1] == '>')
        {
            debug_scan("TOKEN_ARROW - [ -> ]");
            updateIndex(1);
            tempToken._type = token::TOKEN_ARROW;
            break;
        }
        debug_scan("TOKEN_MINUS - [ - ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_MINUS;
        break;
    case '*':
        debug_scan("TOKEN_MUL - [ * ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_MUL;
        break;
    case '%':
        debug_scan("TOKEN_MOD - [ % ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_MOD;
        break;
    case '<':
        if (_inputString[_index + 1] == '=')
        {
            debug_scan("TOKEN_LESSTEQUAL - [ <= ]");
            updateIndex(1);
            tempToken._type = token::TOKEN_LESSTEQUAL;
            break;
        }
        debug_scan("TOKEN_LESST - [ < ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_LESST;
        break;
    case '>':
        if (_inputString[_index + 1] == '=')
        {
            debug_scan("TOKEN_GREATERTEQUAL - [ >= ]");
            updateIndex(1);
            tempToken._type = token::TOKEN_GREATERTEQUAL;
            break;
        }
        debug_scan("TOKEN_GREATERT - [ > ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_GREATERT;
        break;
    case '/':
        if (_inputString[_index + 1] == '/')
        {
            debug_scan("TOKEN_DOUBLE_SLASH - [ // ]");
            updateIndex(1);
            tempToken._type = token::TOKEN_DOUBLE_SLASH;
            break;
        }
        /*
        else {
           debug_scan("TOKEN_DIV - [ / ]");
           updateIndex(1);
           tempToken._type = token::TOKEN_DIV;
           break; 
        }*/

    case '#':
        updateIndex(2);
        _tempIndex = _index; // if closing comment is not found
        while(_index < _size && (_tempStr = _inputString.substr(_index,1)) != "\n"){
            updateIndex(1);
        }
        goto begin;        
    case '=':
        if (_inputString[_index + 1] == '=')
        {
            debug_scan("TOKEN_EQUAL - [ == ]");
            updateIndex(2);
            tempToken._type = token::TOKEN_EQUAL;
            _tempIndex = _index;
            break;
        }
        else {
           debug_scan("TOKEN_ASSIGN - [ = ]");
           updateIndex(1);
           tempToken._type = token::TOKEN_ASSIGN;
           break;
        }
    case '!':
        if (_inputString[_index + 1] == '=')
        {
            debug_scan("TOKEN_NEQUAL - [ != ]");
            updateIndex(2);
            tempToken._type = token::TOKEN_NEQUAL;
            _tempIndex = _index;
            break;
        }
    case ',':
        debug_scan("TOKEN_COMMA - [ , ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_COMMA;
        break;
    case ':':
        debug_scan("TOKEN_COLON - [ : ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_COLON;
        break;
    case '.':
        debug_scan("TOKEN_POINT - [ . ]");
        updateIndex(1);
        tempToken._type = token::TOKEN_POINT;
        break;
    case '"':
        _tempStr = "";
        updateIndex(1);
        while(_index < _size && (next = _inputString[_index])  != '"'){
            _tempStr += next;
            updateIndex(1);
        }
        debug_scan("TOKEN_STR_VAL - [ "+_tempStr+" ]");
        tempToken._type = token::TOKEN_STR_VAL;
        tempToken._value = _tempStr;
        updateIndex(1);
        break;       

    default:
        _tempStr = "";
        if (isdigit(next)) // scan number
        {
            while (_index < _size && 
                  (next == '0' || next == '1' || next == '2' || next == '3' ||
                    next == '4' || next == '5' || next == '6' || next == '7' ||
                    next == '8' || next == '9'))
            {
                _tempStr += next;
                updateIndex(1);
                next = _inputString[_index];
            }
            debug_scan("TOKEN_INT_VAL - [ "+_tempStr+" ]");
            tempToken._type = token::TOKEN_INT_VAL;
            tempToken._value = _tempStr;
            break;
        }
        else if (isalpha(next)) // scan ID
        {
            _tempStr += next;
            while (++_index < _size && 
                    (isalnum((next = _inputString[_index])) || next=='_'))
            {
                _tempStr += next;
                if ((_tempIndex = getReservedIndex(_tempStr)) != -1 &&
                     (_inputString[_index+1] == ' ' || _inputString[_index+1] == '\t' ||
                      _inputString[_index+1] == '\n' || _inputString[_index+1] == '(' ||
                      _inputString[_index+1] == ')' || _inputString[_index+1] == '"'))
                {
                    _tempReserved = reserved[_tempIndex];
                    tempToken._type = getTokenReserved(_tempIndex);
                    tempToken._value = _tempStr;
                    transform(_tempReserved.begin(), _tempReserved.end(),
                              _tempReserved.begin(), ::toupper);
                    debug_scan(_tempReserved+"_STMNT - [ "+reserved[_tempIndex]+" ]");
                    updateIndex(1);
                    goto theEnd;        
                }
            }
            debug_scan("TOKEN_ID - [ "+_tempStr+" ]");
            tempToken._type = token::TOKEN_ID;
            tempToken._value = _tempStr;
            break;
        } 
        else {
            _errorCount++;
            cout << "ERROR(Symbol not in language) - [ " << next << " ]" << " found at: (" << _lineIndex << ":" << _columnIndex << ")" << endl;
        }
        updateIndex(1);
        goto begin;
    }
theEnd:;
    return tempToken;
}

void Scanner::updateIndex(int n)
{
    _index += n;
    _columnIndex += n;
}

int Scanner::getReservedIndex(string str)
{
    auto it = find(reserved.begin(), reserved.end(), str);
    if (it != reserved.end())
    {
        int index = it - reserved.begin();
        return index;
    }
    else{
        return -1;
    }
}

string Scanner::isReserved(string str)
{
    return "";
}

void Scanner::debug_scan(string msg)
{
    cout << msg << " found at: (" << _lineIndex << ":" << _columnIndex << ")" << endl;
}



char Scanner::peek_char()
{
    _tempIndex = _index+1;
    char next;
    while (_tempIndex < _size && ((next = _inputString[_tempIndex])  == ' ' || 
                              next == '\t'))
    {
        _tempIndex++;
    }
    switch (next)
    {
        case '\n':
            _tempIndex++;
            break;
        case '/':
            if (_inputString[_tempIndex + 1] == '*')
            {
                _tempIndex += 2;
                while(_tempIndex < _size && (_tempStr = _inputString.substr(_tempIndex,2)) != "*/")
                    _tempIndex++;
                _tempIndex += 2;           
                break;        
            }
            break;
    }
    return _inputString[_tempIndex];
}

token Scanner::peek_token()
{
    cout << "just peeking... ";
    int tempIndex = _index;
    int tempColumn = _columnIndex;
    Token tempToken = get_token();
    _index = tempIndex;
    _columnIndex = tempColumn;
    return tempToken._type;
}

token Scanner::getTokenReserved(int res)
{
    switch (res)
    {
    case 0:
        return token::TOKEN_BOOL_FALSE_VAL;
        break;  
    case 1:
        return token::TOKEN_NONE_VAL;
        break;
    case 2:
        return token::TOKEN_BOOL_TRUE_VAL;
        break;
    case 3:
        return token::TOKEN_AND;
        break;
    case 4:
        return token::TOKEN_AS;
        break;
    case 5:
        return token::TOKEN_ASSERT;
        break;
    case 6:
        return token::TOKEN_ASYNC;
        break;
    case 7:
        return token::TOKEN_AWAIT;
        break;
    case 8:
        return token::TOKEN_BREAK;
        break;
    case 9:
        return token::TOKEN_CLASS_TYPE;
        break;
    case 10:
        return token::TOKEN_CONTINUE;
        break;
    case 11:
        return token::TOKEN_DEF;
        break;
    case 12:
        return token::TOKEN_DEL;
        break;
    case 13:
        return token::TOKEN_ELIF;
        break;
    case 14:
        return token::TOKEN_ELSE;
        break;
    case 15:
        return token::TOKEN_EXCEPT;
        break;
    case 16:
        return token::TOKEN_FINALLY;
        break;
    case 17:
        return token::TOKEN_FOR;
        break;
    case 18:
        return token::TOKEN_FROM;
        break;
    case 19:
        return token::TOKEN_GLOBAL;
        break;
    case 20:
        return token::TOKEN_IF;
        break;
    case 21:
        return token::TOKEN_IMPORT;
        break;
    case 22:
        return token::TOKEN_IN;
        break;
    case 23:
        return token::TOKEN_IS;
        break;
    case 24:
        return token::TOKEN_LAMBDA;
        break;
    case 25:
        return token::TOKEN_NONLOCAL;
        break;
    case 26:
        return token::TOKEN_NOT;
        break;
    case 27:
        return token::TOKEN_OR;
        break;
    case 28:
        return token::TOKEN_PASS;
        break;
    case 29:
        return token::TOKEN_RAISE;
        break;
    case 30:
        return token::TOKEN_RETURN;
        break;
    case 31:
        return token::TOKEN_TRY;
        break;
    case 32:
        return token::TOKEN_WHILE;
        break;
    case 33:
        return token::TOKEN_WITH;
        break;
    case 34:
        return token::TOKEN_YIELD;
        break;
    }
}

void Scanner::print_token(token token)
{
    switch (token)
    {
    case token::TOKEN_EOF:
        cout << "TOKEN_EOF" << endl;
        break;
    case token::TOKEN_OPEN_BLOCK:
        cout << "TOKEN_OPEN_BLOCK" << endl;
        break;
    case token::TOKEN_CLOSE_BLOCK:
        cout << "TOKEN_CLOSE_BLOCK" << endl;
        break;
    case token::TOKEN_OPEN_BRCKT:
        cout << "TOKEN_OPEN_BRCKT" << endl;
        break;
    case token::TOKEN_CLOSE_BRCKT:
        cout << "TOKEN_CLOSE_BRCKT" << endl;
        break;
    case token::TOKEN_PRINT_STMNT:
        cout << "TOKEN_PRINT_STMNT" << endl;
        break;
    case token::TOKEN_WHILE_STMNT:
        cout << "TOKEN_WHILE_STMNT" << endl;
        break;
    case token::TOKEN_IF_STMNT:
        cout << "TOKEN_IF_STMNT" << endl;
        break;
    case token::TOKEN_ASSIGN:
        cout << "TOKEN_ASSIGN" << endl;
        break;
    case token::TOKEN_PLUS:
        cout << "TOKEN_PLUS" << endl;
        break;
    case token::TOKEN_MINUS:
        cout << "TOKEN_MINUS" << endl;
        break;
    case token::TOKEN_MUL:
        cout << "TOKEN_MUL" << endl;
        break;
    case token::TOKEN_DIV:
        cout << "TOKEN_DIV" << endl;
        break;
    case token::TOKEN_INT_VAL:
        cout << "TOKEN_INT_VAL" << endl;
        break;
    case token::TOKEN_STR_VAL:
        cout << "TOKEN_STR_VAL" << endl;
        break;
    case token::TOKEN_BOOL_TRUE_VAL:
        cout << "TOKEN_BOOL_TRUE_VAL" << endl;
        break;
    case token::TOKEN_BOOL_FALSE_VAL:
        cout << "TOKEN_BOOL_FALSE_VAL" << endl;
        break;
    case token::TOKEN_ID:
        cout << "TOKEN_ID" << endl;
        break;
    case token::TOKEN_INT_TYPE:
        cout << "TOKEN_INT_TYPE" << endl;
        break;
    case token::TOKEN_STR_TYPE:
        cout << "TOKEN_STR_TYPE" << endl;
        break;
    case token::TOKEN_BOOL_TYPE:
        cout << "TOKEN_BOOL_TYPE" << endl;
        break;
    case token::TOKEN_EQUAL:
        cout << "TOKEN_EQUAL" << endl;
        break;
    case token::TOKEN_NEQUAL:
        cout << "TOKEN_NEQUAL" << endl;
        break;
    default:
        break;
    }
}

string Scanner::get_line_col()
{
    string tmp = to_string(_lineIndex) + ":" + to_string(_columnIndex);
    return tmp;
}

Scanner::~Scanner()
{
}