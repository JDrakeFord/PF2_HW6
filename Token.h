//
// Created by Drake Ford on 10/1/2021.
//

#ifndef HW3_TOKEN_H
#define HW3_TOKEN_H
#include <string>

using namespace std;
class Token {
public:
    enum Token_type {Identifier, Integer, Operators, EqualSign,
        OpenBrace, CloseBrace, INVALID};
    Token();
    Token(string s);
    void set(string s);
    void setType(string s);
    int value() const;
    void display() const;
    Token_type get_type() const;
    string get_token() const;
    int get_priority() const;
private:
    Token_type type;
    string token;
    int priority;
    string type_to_string(Token_type t) const;

};


#endif //HW3_TOKEN_H
