//
// Created by Drake Ford on 11/15/2021.
//

#include "Sequence.h"
#include "Expression.h"
#include <map>
#include <sstream>
#include <iostream>

Sequence::Sequence(string &input) {
    set(input);
}

void Sequence::set(string &input) {
    bool flag = false;
    orig = input;
    size = 0;
    int start = 0;
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == ';')
        {
            sequence.push_back(input.substr(start, i - start));
            start = i + 1;
            size++;
        }
        else if(i == input.length() - 1 && input[i] != ';')
        {
            std::cout << "Sorry! That input wasn't valid. Be sure to include a semicolon after each expression." << endl << "input:";
            clear();
            getline(cin, input);
            set(input);
            flag = true;
            break;
        }
    }
    if(!flag)
    {
        assignVariables();
    }
}

void Sequence::assignVariables() {
    for(int i = 0; i < sequence.size(); i++)
    {
        if(sequence[i].getType() == Expression::Assignment)
        {
            int p;
            std::istringstream(sequence[i].get_original().substr(sequence[i].get_tokenized()[0].get_token().length() + 1))  >> p;
            variables.insert(variables.begin(), std::pair<string, int>(sequence[i].get_tokenized()[0].get_token().substr(0, sequence[i].get_tokenized()[0].get_token().length()), p));
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
    assignVariables();
}

string Sequence::getOrig() {
    return orig;
}
