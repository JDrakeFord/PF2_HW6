#include <iostream>
#include "Sequence.h"
using namespace std;
int main() {
    cout << "=== expression evaluation program starts ===" << endl;
    cout << "input:";
    string input;
    string toAppend;
    getline(cin, input);
    string choice;
    bool exit = false;
    Sequence seq(input);
    while(!exit)
    {
        cout << "action:";
        getline(cin, choice);
        switch(choice[0])
        {
            case '=':
                cout << "Chosen evaluation" << endl;
                for(int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].setValid() && seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        bool complete = true;
                        int result = seq.getSequence()[i].evaluate(complete, seq.getMap());
                        if(complete)
                        {
                            cout << seq.getSequence()[i].get_original() << " = " << result << endl;
                        }
                        else
                        {
                            cout << "Sorry, not all variables are assigned for " << seq.getSequence()[i].get_original() << endl;
                        }
                    }
                    else if(!seq.getSequence()[i].setValid())
                    {
                        cout << "Sorry! " << seq.getSequence()[i].get_original() << " is not a valid expression!" << endl;
                    }
                    else if(seq.getSequence()[i].getType() == Expression::Assignment)
                    {
                        cout << "Cannot evaluate " << seq.getSequence()[i].get_original() << " which is assignment" << endl;
                    }
                }
                break;
            case '>':
                for(int i = 0; i < seq.getSequence().size(); i++)
                {
                    for(int k = 0; k < seq.getSequence()[i].get_prefix().size(); k++)
                    {
                        if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                             cout <<  seq.getSequence()[i].get_prefix()[k].get_token() << " ";
                    }
                    if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                        cout << endl;
                }
                break;
            case '<':
                for(int i = 0; i < seq.getSequence().size(); i++)
                {
                    cout << "Postfix of " << seq.getSequence()[i].get_original() << " = ";
                    for(int k = 0; k < seq.getSequence()[i].get_postfix().size(); k++)
                    {
                        if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                            cout << seq.getSequence()[i].get_postfix()[k].get_token() << " ";
                    }
                    if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                        cout << endl;
                }
                break;
            case 'f':
                for(int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        cout << seq.getSequence()[i].get_original() << " fully parenthesized is ";
                        seq.getSequence()[i].fullParen();
                    }
                    else if(seq.getSequence()[i].getType() == Expression::Assignment)
                    {
                        cout << "Cannot parenthesize " << seq.getSequence()[i].get_original() << ", which is assignment" << endl;
                    }
                }
                break;
            case 'q':
                exit = true; cout << "Chosen exit" << endl; break;
            case 'c':
                cout << "Chosen continue appending sequence" << endl;
                cout << "input:";
                getline(cin, toAppend);
                seq.append(toAppend);
                toAppend = "";
                break;
            case 's':
                cout << "Chosen to start over inputting sequence" << endl;
                cout << "input:";
                getline(cin, input);
                seq.clear();
                seq.append(input);
                seq.getMap().clear();
                break;
            default:
                cout << "Sorry! That was not valid input" << endl; break;
        }
    }


    return 0;
}
