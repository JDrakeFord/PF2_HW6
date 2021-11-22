#include <iostream>
#include "Sequence.h"
using namespace std;
int main() {
    /*
    cout << "=== expression evaluation program starts ===" << endl;
    cout << "input:";
    string input;
    string toAppend;
    getline(cin, input);
    string choice;
    bool exit = false;
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
                cout << "Chosen postfix" << endl; break;
            case 'f':
                cout << "Chosen fully parenthesized." << endl; break;
            case 'q':
                exit = true; cout << "Chosen exit" << endl; break;
            case 'c':
                cout << "Chosen continue appending sequence" << endl;
                cout << "input:";
                getline(cin, toAppend);
                break;
            case 's':
                cout << "Chosen to start over inputting sequence" << endl;
                cout << "input:";
                getline(cin, input); break;
            default:
                cout << "Sorry! That was not valid input" << endl; break;
        }
    }
     */
    Expression a("a+b/c");
    a.display();

    return 0;
}
