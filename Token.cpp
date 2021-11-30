//
// Created by Drake Ford on 10/1/2021.
//

#include "Token.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

Token::Token(string s)
{
    set(s);
}

Token::Token(int a)
{
    type = Integer;
    stringstream ss;
    ss << a;
    token = ss.str();
    priority = -1;
}

//Defualt constructor. Sets each variable per instructions
Token::Token()
{
    type = INVALID;
    token = "";
    priority = -1;
}

//Private function to convert enum Token_type to outputable string
string Token::type_to_string(Token_type t) const {
    if(t == Integer)
        return "Integer";
    else if(t == Identifier)
        return "Identifier";
    else if(t == Operators)
        return "Operators";
    else if(t == EqualSign)
        return "Equal sign";
    else if(t == OpenBrace)
        return "Open Brace";
    else if(t == CloseBrace)
        return "Close Brace";
    else if(t == INVALID)
        return "INVALID";
}

//Getter for the priority variable
int Token::get_priority() const {
    return priority;
}

//Getter for the token variable
string Token::get_token() const {
    return token;
}

//Getter for the type variable
Token::Token_type Token::get_type() const {
    return type;
}

//Set the type of the token
void Token::setType(string s) {
    //Our other tests don't work for an empty string. We need to set this manually.
    if(s == "")
    {
        type = INVALID;
        return;
    }
    //Case - INTEGER
    bool isInteger = true;
    //For every character in the string
    if(s[0] == '0'&& s.length() > 1)
        isInteger = false;
    for(int i = 0; i < s.length(); i++)
    {
        //If it is not a digit, then it is not an integer
        if(!isdigit(s[i]))
        {
            isInteger = false;
            break;
        }
    }
    //If it is an integer, then type = integer and exit the function
    if(isInteger)
    {
        type = Integer;
        return;
    }

    //To see if it is a valid identifier, we need to know if the string
    //is either ('A' - 'Z') or ('a' - 'z') or ('1' - '9') [The first character cannot be a digit]
    bool isIdentifier = true;
    //The first character cannot be a digit
    if(isdigit(s[0]))
        isIdentifier = false;
    //For every character in the string
    for(int i = 0; i < s.length(); i++)
    {
        //If it is not a letter or number, it is invalid
        if(!isalnum(s[i]))
        {
            isIdentifier = false;
            break;
        }
    }
    //If type is identifier, then type = identifier and exit function.
    if(isIdentifier)
    {
        type = Identifier;
        return;
    }

    //If it is comfirmed to be an integer, set type to integer and exit function (Return nothing)
    if(isInteger)
    {
        type = Integer; return;
    }

    //Case OPERATORS - If it is an operator, type = operators and return nothing (exit function)
    if(s == "+" || s == "/" || s == "*" || s == "-"){
        type = Operators; return;
    }

    //Case EQUALS SIGN - If it is the equals sign, type = equals sign and return nothing (exit function)
    if(s == "="){
        type = EqualSign; return;
    }

    //Case OPEN BRACE - If it is the open brace, type = open brace and return nothing (exit function)
    if(s == "("){
        type = OpenBrace; return;
    }

    //Case CLOSE BRACE - If it is the close brace, type = close brace and return nothing (exit function)
    if(s == ")"){
        type = CloseBrace; return;
    }

    type = INVALID;
}

void Token::set(string s)
{
    setType(s);
    token = s;
    if(s == "(")
        priority = 0;
    else if(s == "+" || s == "-")
        priority = 1;
    else if(s == "*" || s == "/")
        priority = 2;
    else
        priority = -1;
}
int Token::value() const {
    if(type == Identifier)
        return -1;
    else if(type == Integer)
    {
        int i;
        sscanf(token.c_str(), "%d", &i);
        return i;
    }
    else
        return -2;
}

void Token::display() const {
    cout << "type = " << type_to_string(type) << endl;
    cout << "token = " << token << endl;
    cout << "priority = " << priority << endl;
    cout << endl;

}
