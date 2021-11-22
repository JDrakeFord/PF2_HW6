//
// Created by Drake Ford on 10/1/2021.
//

#include "Expression.h"
#include <iostream>
#include <stack>

using namespace std;
//Defualt constructor, sets all fields to either blank, false, or Bad.
Expression::Expression() {
    original = "";
    valid = false;
    type = Bad;
}

//String constructor - Runs the set(string s) method with the input paramater s passed into the set method.
//This is because the set method is identical to the behavior of the constructor.
Expression::Expression(const string &s) {
    set(s);
}

//This is the function that sets the fields for Expression.
void Expression::set(const string &s) {
    bool firstCharFound = false;
    int tokenStart = 0;
    //Set original variable
    original = s;
    //Loop through string
    tokenized.clear();

    for(int i = 0; i < s.length(); i++)
    {
        //We don't need to make a token if we hit a space but have not found a character
        if(s[i] == ' ' && !firstCharFound)
            tokenStart = i + 1;
        //If it is not a space, then we have found our first character.
        else
            firstCharFound = true;
        //If we find a space and have found a character and we have more than one character
        //to tokenize, then we make a token out of the previous characters and skip over the space
        if(s[i] == ' ' && firstCharFound && i != tokenStart)
        {
            tokenized.push_back(s.substr(tokenStart, (i - tokenStart)));
            tokenStart = i + 1;
        }
        //If we find a space, have found a character, but tokenStart is already at the space
        //(this can happen if a token was just created but not triggered by a space)
        //then we need to skip over the space.
        if(s[i] == ' ' && firstCharFound && i == tokenStart)
        {
            tokenStart = i + 1;
        }
        //If it is a special character
        else if(s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' ||
        s[i] == '=' || s[i] == '(' || s[i] == ')')
        {
            //If we need to create two tokens, one for what came before and one for the
            //special character, then we create two tokens
            if(tokenStart != i)
            {
                tokenized.push_back(s.substr(tokenStart, (i - tokenStart)));
                tokenized.push_back(s.substr(i, 1));
                tokenStart = i + 1;
            }
            //If we only need to create a token for a special character
            //then we only create one token
            else
            {
                tokenized.push_back(s.substr(i, 1));
                tokenStart = i + 1;
            }

        }
        //If we are at the end, we create the final token, as long as the token hasn't
        //just been created by a space
        else if(i == s.length() - 1 && s[s.length()-1] != ' ')
            tokenized.push_back(s.substr(tokenStart, (i - tokenStart + 1)));


    }
    setType();
    setPostfix();
    //TODO SET VALID - CURRENTLY HARD CODED
    valid = true;
}

void Expression::setPostfix() {
    postfix.clear();
    stack<Token> ops;

    for(int i = 0; i < tokenized.size(); i++)
    {
        if(tokenized[i].get_type() == Token::Identifier ||
           tokenized[i].get_type() == Token::Integer)
        {
            postfix.push_back(tokenized[i]);
        }
        else if(tokenized[i].get_type() == Token::OpenBrace)
        {
            ops.push(tokenized[i]);
        }
        else if(tokenized[i].get_type() == Token::CloseBrace)
        {
            while(ops.top().get_type() != Token::OpenBrace)
            {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else
        {
            while(!ops.empty() && ops.top().get_priority() >= tokenized[i].get_priority())
            {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(tokenized[i]);
        }
    }
    while(!ops.empty())
    {
        postfix.push_back(ops.top());
        ops.pop();
    }
}

vector<Token> Expression::get_postfix() const {
    return postfix;
}

void Expression::setType() {
    for(int i = 0; i < tokenized.size(); i++)
    {
        if(tokenized[i].get_type() == Token::Operators)
            type = Arithmetic;
        else if(tokenized[i].get_type() == Token::EqualSign)
            type = Assignment;
    }
}

//This is the getter for the tokenized vector.
vector<Token> Expression::get_tokenized() const {
    return tokenized;
}

//This is a private function I added to assist in the conversion
//of the enum Exp_type to an outputable string.
string Expression::type_to_string(Exp_type type) const {
    if(type == Bad)
        return "Bad";
    else if(type == Arithmetic)
        return "Arithmetic";
    else if(type == Assignment)
        return "Assignment";
}

//This function displays each member variable of the expression
void Expression::display() const {
    cout << "original = " << original << endl;
    cout << "tokenized = ";
    //Output each token followed by ';' to signify the end of the token. New line after loop.
    for(int i = 0; i < tokenized.size(); i++)
    {
        cout << tokenized[i].get_token() << ";";
    }
    cout << endl;
    cout << "number of tokens = " << tokenized.size() << endl;
    cout << "postfix = ";
    for(int i = 0; i < postfix.size(); i++)
    {
        cout << postfix[i].get_token() << ";";
    }
    cout << endl;
    cout << "valid = ";
    //We want to output "true" or "false", not '1' or '0'
    if(valid)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    cout << "type = " << type_to_string(type);
    cout << endl << endl;
}

//Getter method for the original variable.
string Expression::get_original() const {
    return original;
}
