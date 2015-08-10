#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <QString>
#include <QStringList>
#include <QDataStream>
#include "parser.h"

class myFunction
{
public:
    //myFunction();
    myFunction(Parser *parser_);
    ~myFunction();

    //void setParser(Parser *parser_);

private:
    Parser *parser;
//    bool parserAllocated;

    QString m_functionName; //e.g. m_functionName="f1";
    QString m_function; // e.g. m_function="4x+2+y"
    QString m_functionDefinition; // e.g. m_functionDefinition="f1(x)=4x+2+y";
    int m_number_variables; // e.g n_number_variable=2;
    QStringList m_variables; // e.g. m_variables.at(0)="x";m_variables.at(1)="y"

public:
    //check if QString is a function, if true sets the private atributes
    //return false if is not a function
    //example functionDefinition = "f1(x,y)=4x+2+y"
    bool SetFunction(QString &functionDefinition);

    QString GetFunction()const{return m_function;} //return m_function
    QString GetfunctionName()const{return m_functionName;}// return m_functionName
    QStringList GetVariables()const{return m_variables;}//return m_variables
    int GetNumberVariables()const{return m_number_variables;}//return m_number_variables
    QString GetFunctionDefinition()const{return m_functionDefinition;}//return m_functionDefinition



    //returns a function with their arguments replace with the correespondig values
    //i.e. m_function="4x+2+y"
    //arguments_values[0]=3.2 ; arguments_values[1]=7
    // the function will return 4(3.2)+2+(7)
   // QString setFunctionWithValues(QStringList arguments_values);

};

QDataStream & operator<< (QDataStream& stream, const myFunction& function);
QDataStream & operator>> (QDataStream& stream, myFunction& function);

#endif // MYFUNCTION_H
