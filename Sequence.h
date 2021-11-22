//
// Created by Drake Ford on 11/15/2021.
//

#ifndef HW6_SEQUENCE_H
#define HW6_SEQUENCE_H
#include <list>
#include "Expression.h"
#include "Token.h"

class Sequence {
public:
    Sequence(string input);
    int getSize();
    vector<Expression> getSequence();
    void append(string input);
    string getOrig();
    void clear();
private:
    string orig;
    int size;
    vector<Expression> sequence;

};


#endif //HW6_SEQUENCE_H
