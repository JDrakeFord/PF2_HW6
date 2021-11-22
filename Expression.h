//
// Created by Drake Ford on 10/1/2021.
//

#ifndef HW3_EXPRESSION_H
#define HW3_EXPRESSION_H
#include <string>
#include <vector>
#include "Token.h"

using namespace std;
class Expression {
public:
    enum Exp_type {Assignment, Arithmetic, Bad};
    Expression();
    Expression(const string& s);
    void set(const string& s);
    void display() const;
    string get_original() const;
    vector<Token> get_tokenized() const;
    vector<Token> get_postfix() const;

private:
    string original;
    vector<Token> tokenized;
    vector<Token> postfix;
    bool valid;
    Exp_type type;
    string type_to_string(Exp_type type) const;
    void setType();
    void setPostfix();

};


#endif //HW3_EXPRESSION_H
