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
    //While the user does not exit
    while(!exit)
    {
        cout << "action:";
        getline(cin, choice);
        switch(choice[0])
        {
            //Evaluation case
            case '=':
                cout << "Chosen evaluation" << endl;
                for(unsigned int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].setValid() && seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        bool complete = true;
                        try{
                            int result = seq.getSequence()[i].evaluate(complete, seq.getMap());
                            if(complete)
                            {
                                cout << seq.getSequence()[i].get_original() << " = " << result << endl;
                            }
                            else
                            {
                                cout << seq.getSequence()[i].get_original() << " no result, some variable has undefined value." << result << endl;
                            }
                        }
                        catch(runtime_error &e){
                            cout << "Cannot evaluate " << seq.getSequence()[i].get_original() << ", divide by 0 error!" << endl;
                        }
                    }
                    else if(!seq.getSequence()[i].setValid())
                    {
                        cout << "Cannot evaluate " << seq.getSequence()[i].get_original() << ", which is an invalid expression." << endl;
                    }
                    else if(seq.getSequence()[i].getType() == Expression::Assignment)
                    {
                        cout << "Cannot evaluate " << seq.getSequence()[i].get_original() << " which is not an arithmetic expression, but assignment." << endl;
                    }
                }
                break;
                //Prefix case
            case '>':
                for(unsigned int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].getType() == Expression::Assignment)
                        cout << "No prefix of " << seq.getSequence()[i].get_original() << ", which is assignment, not arithmetic." << endl;
                    else if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        cout << "Prefix of " << seq.getSequence()[i].get_original() << " = ";
                        for(unsigned int k = 0; k < seq.getSequence()[i].get_prefix().size(); k++)
                        {
                            if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                                cout <<  seq.getSequence()[i].get_prefix()[k].get_token() << " ";
                        }
                        cout << endl;
                    }
                    else
                    {
                        cout << "No prefix of " << seq.getSequence()[i].get_original() << ", which is an invalid expression." << endl;
                    }
                }
                break;
                //Postfix case
            case '<':
                for(unsigned int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].getType() == Expression::Assignment)
                        cout << "No postfix of " << seq.getSequence()[i].get_original() << ", which is assignment, not arithmetic." << endl;
                    else if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        cout << "Postfix of " << seq.getSequence()[i].get_original() << " = ";
                        for(unsigned int k = 0; k < seq.getSequence()[i].get_postfix().size(); k++)
                        {
                            if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                                cout <<  seq.getSequence()[i].get_postfix()[k].get_token() << " ";
                        }
                        cout << endl;
                    }
                    else
                    {
                        cout << "No postfix of " << seq.getSequence()[i].get_original() << ", which is an invalid expression." << endl;
                    }
                }
                break;
                //Full parentheses case
                case 'f': case 'F':
                for(unsigned int i = 0; i < seq.getSequence().size(); i++)
                {
                    if(seq.getSequence()[i].getType() == Expression::Arithmetic)
                    {
                        cout << seq.getSequence()[i].get_original() << " fully parenthesized is ";
                        seq.getSequence()[i].fullParen();
                    }
                    else if(seq.getSequence()[i].getType() == Expression::Assignment)
                    {
                        cout << "Cannot parenthesize " << seq.getSequence()[i].get_original() << ", which is assignment, not arithmetic." << endl;
                    }
                    else if(seq.getSequence()[i].getType() == Expression::Bad)
                    {
                        cout << "Cannot parenthesize " << seq.getSequence()[i].get_original() << ", which is an invalid expression." << endl;
                    }
                }
                break;
                //Quit case
                case 'q': case 'Q':
                exit = true; cout << "Chosen exit" << endl; break;
                //Continue case
                case 'c': case 'C':
                cout << "Chosen continue appending sequence" << endl;
                cout << "input:";
                getline(cin, toAppend);
                seq.append(toAppend);
                toAppend = "";
                break;
                //Start over case
                case 's': case 'S':
                cout << "Chosen to start over inputting sequence" << endl;
                cout << "input:";
                getline(cin, input);
                seq.clear();
                seq.append(input);
                seq.getMap().clear();
                break;
            default:
                cout << "Wrong input for the action! Please type one of =, <, >, f(F), q(Q), c(C), s(S)" << endl; break;
        }
    }


    return 0;
}
