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
                cout << "Chosen evaluation" << endl; break;
            case '>':
                cout << "Chosen prefix" << endl; break;
            case '<':
                cout << "Chosen postfix" << endl;
                for(int i = 0; i < seq.getSequence().size(); i++)
                {
                    for(int k = 0; k < seq.getSequence()[i].get_postfix().size(); k++)
                    {
                        cout << seq.getSequence()[i].get_postfix()[k].get_token() << " ";
                    }
                    cout << endl;
                }
                break;
            case 'f':
                cout << "Chosen fully parenthesized." << endl; break;
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
                break;
            default:
                cout << "Sorry! That was not valid input" << endl; break;
        }
    }


    return 0;
}
