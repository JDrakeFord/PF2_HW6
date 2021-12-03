//
// Created by Drake Ford on 11/15/2021.
//

#include "Sequence.h"
#include "Expression.h"
#include <map>
#include <sstream>

Sequence::Sequence(string input) {
    orig = input;
    size = 0;
    int start = 0;
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == ';' && i != input.length() - 1)
        {
            sequence.push_back(input.substr(start, i - start));
            start = i + 1;
            size++;
        }
        else if(i == input.length() - 1)
        {
            sequence.push_back(input.substr(start, i - start));
            size++;
        }
    }
    assignVariables();
}

void Sequence::assignVariables() {
    for(int i = 0; i < sequence.size(); i++)
    {
        if(sequence[i].getType() == Expression::Assignment)
        {
            int p;
            std::istringstream(sequence[i].get_original().substr(2, 1))  >> p;
            variables.insert(variables.begin(), std::pair<string, int>(sequence[i].get_original().substr(0, 1), p));
        }
    }
}

map<string, int> Sequence::getMap() {
    return variables;
}

vector<Expression> Sequence::getSequence() {
    return sequence;
}

int Sequence::getSize() {
    return size;
}

void Sequence::clear() {
    sequence.clear();
    size = 0;
    orig = "";
}

void Sequence::append(string input) {
    orig += input;
    int start = 0;
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == ';' && i != input.length() - 1)
        {
            sequence.push_back(input.substr(start, i - start));
            start = i + 1;
            size++;
        }
        else if(i == input.length() - 1)
        {
            sequence.push_back(input.substr(start, i - start));
            size++;
        }
    }
}

string Sequence::getOrig() {
    return orig;
}
