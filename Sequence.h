//
// Created by Drake Ford on 11/15/2021.
//

#ifndef HW6_SEQUENCE_H
#define HW6_SEQUENCE_H
#include <list>
#include "Expression.h"
#include "Token.h"
#include <map>

class Sequence {
public:
    Sequence(string &input);
    int getSize();
    vector<Expression> getSequence();
    void append(string input);
    string getOrig();
    void clear();
    map<string, int> getMap();
private:
    string orig;
    int size;
    vector<Expression> sequence;
    map<string, int> variables;
    void assignVariables();
    void set(string &input);


};


#endif //HW6_SEQUENCE_H
