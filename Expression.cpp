//
// Created by Drake Ford on 10/1/2021.
//

#include "Expression.h"
#include <iostream>
#include <stack>
#include <sstream>

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

void Expression::setPrefix() {
    stack<string> ops;
    for(int i = 0; i < postfix.size(); i++)
    {
        if(postfix[i].get_type() == Token::Integer || postfix[i].get_type() == Token::Identifier)
        {
            ops.push(postfix[i].get_token());
        }
        else if(postfix[i].get_type() == Token::Operators)
        {
            string a = ops.top();
            ops.pop();
            string b = ops.top();
            ops.pop();
            ops.push(postfix[i].get_token() + b + a);
        }
    }
    string temp;
    while(!ops.empty())
    {
        temp += ops.top();
        ops.pop();
    }
    for(int i = 0; i < temp.length(); i++)
    {
        string temp2 = "";
        temp2 += temp[i];
        prefix.push_back(temp2);
    }
}

void Expression::fullParen() {
    vector<string> postfixString;
    int size = postfix.size();
    int numOperators = 0;
    for(int i = 0; i < postfix.size(); i++)
    {
        postfixString.push_back(postfix[i].get_token());
        if(postfix[i].get_type() == Token::Operators)
            numOperators++;
    }

    for(int i = 0; i < size; i++)
    {
        string tokenTemp;
        tokenTemp += postfixString[i];
        Token temp(tokenTemp);
        if(temp.get_type() == Token::Operators)
        {
            numOperators--;
            string a = postfixString[i - 2];
            string b = postfixString[i - 1];
            string tempString;
            tempString += '(';
            tempString += a;
            tempString += postfixString[i];
            tempString += b;
            tempString += ")";
            postfixString.erase(postfixString.begin() + (i-2), postfixString.begin() + i + 1);
            i -=2;
            postfixString.insert(postfixString.begin() + i, tempString);
            size += 2;
            if(numOperators == 0)
                break;
        }
    }
    for(int i = 0; i < postfixString.size(); i++)
    {
        cout << postfixString[i];
    }
    cout << endl;
}

void Expression::setValid() {
    enum States {expect_operand, expect_operator, done};
    bool eqtrue = false;
    States state = expect_operand;
    int pcount = 0;
    valid = true;
    int tokenCount = 0;

    while(state != done && tokenCount < tokenized.size())
    {
        Token t = tokenized[tokenCount];
        tokenCount++;
        switch(state) {
            case expect_operand:
                if (t.get_type() == Token::OpenBrace)
                    pcount++;
                else if (t.get_type() == Token::Integer || t.get_type() == Token::Identifier)
                    state = expect_operator;
                else {
                    valid = false;
                    state = done;
                }
                break;
            case expect_operator:
                if(t.get_type() == Token::CloseBrace)
                {
                    pcount--;
                    if(pcount < 0)
                    {
                        valid = false;
                        state = done;
                    }
                }
                else if(t.get_type() == Token::EqualSign)
                {
                    eqtrue = true;
                    state = expect_operand;
                }
                else if(t.get_type() == Token::Operators)
                    state = expect_operand;
                else
                {
                    valid = false;
                    state = done;
                }
                break;
            default:
                break;
        }
    }
    if(pcount != 0)
        valid = false;
    if(state == expect_operand)
        valid = false;
    if(valid)
    {
        if(eqtrue)
        {
            if(tokenized.size() == 3 && tokenized[0].get_type() == Token::Identifier && tokenized[2].get_type() == Token::Integer)
                type = Expression::Assignment;
            else
                valid = false;
        }
        else
            type = Expression::Arithmetic;
    }
    if(!valid)
    {
        type = Expression::Bad;
        cout << "TYPE SET TO BAD" << endl;
    }
}





int Expression::evaluate() const {
    stack<Token> eval;
    for(int i = 0; i < postfix.size(); i++)
    {
        if(postfix[i].get_type() == Token::Integer)
        {
            eval.push(postfix[i]);
        }
        else if(postfix[i].get_type() == Token::Operators)
        {
            int b = eval.top().value();
            eval.pop();
            int a = eval.top().value();
            eval.pop();
            switch(postfix[i].get_token()[0])
            {
                case '+': {
                    Token temp(a+b);
                    eval.push(temp);
                    break;
                }
                case '-': {
                    Token temp(a-b);
                    eval.push(temp);
                    break;
                }
                case '*': {
                    Token temp(a*b);
                    eval.push(temp);
                    break;
                }
                case '/': {
                    Token temp(a/b);
                    eval.push(temp);
                    break;
                }
            }
        }
    }
    return eval.top().value();
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
    setValid();
    setPostfix();
    setPrefix();
}

vector<Token> Expression::get_prefix() const {
    return prefix;
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
