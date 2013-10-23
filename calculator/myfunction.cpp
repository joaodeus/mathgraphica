#include "myfunction.h"


#include <QStringList>

myFunction::myFunction(Parser *parser_)
{

    parser = parser_;
}

bool myFunction::SetFunction(QString &functionDefinition)
{

    //example functionDefinition = "f1(x,y)=4x+2+y"
    functionDefinition.remove(" ",Qt::CaseInsensitive);
    m_functionDefinition=functionDefinition;

    QStringList list;
    list = functionDefinition.split("=");

    //list[0]="f1(x,y)"
    //list[1]="4x+2+y"
    if (list.size() != 2)
        return false;
    if (list[0].size() == 0)
        return false;

    m_function = list[1];


    //check for valid function name -f1-, must start with a letter or underscore
    //and only have letters and numbers
    QString fName_aux = list[0]; // == "f1(x,y)"

    if (!fName_aux.at(0).isLetter() && fName_aux.at(0) != '_')
        return false;

    int i=0;
    m_functionName.clear();
    // save "f1" to m_functionName
    //while(i < fName_aux.size() && (fName_aux.at(i).isLetterOrNumber() || fName_aux.at(i) == '_'))
    while (i < fName_aux.size())
    {
        if ( !fName_aux.at(i).isLetterOrNumber() && fName_aux.at(i) != '_')
        {
            break;
        }


        m_functionName.append(fName_aux.at(i));
        i++;
    }

    //if first member is only a variable, return false, it's not a function
    if (m_functionName == list[0])
        return false;

    QString variables_aux;
    variables_aux= list[0]; //assign f1(x,y) to variables_aux
    //now lets remove "f1"
    variables_aux.remove(0,m_functionName.size()); //variables_aux == "(x,y)"

    //lets check if first and last caracter are really "(" and ")"
    if ( (variables_aux.at(0) != '(' ) || variables_aux.at(variables_aux.size()-1) != ')' )
        return false;

    variables_aux.chop(1);
    variables_aux.remove(0,1);
    // we now have variables_aux = "x,y"

    //lets grab the variables
    QStringList list_variables_aux;
    list_variables_aux = variables_aux.split(",");
    //list_variables_aux[0] == "x"
    //list_variables_aux[1] == "y"


    //lets check if this variables are the same from m_function "4x+2+y"
    QStringList list_var_aux2;

    parser->GrabVariables(list[1],list_var_aux2);

    //if they are different there is a error
    if (list_variables_aux != list_var_aux2)
        return false;

    //assign the variables
    m_variables = list_variables_aux;
    m_number_variables = m_variables.size();

    //now lets check if m_function is without errors
    // we assing some test values, i.e. 1.27, to the variables and perform a
    //validation with SolveExpression_fn(...)

    QList<double> list_values_aux;
    for(int j=0;j<m_number_variables;j++)
    {
        list_values_aux.append(1.27); //append some random teste value
    }

    //lets calculate and perform a validation
    //calc.f_n_variaveis(m_function,list_values_aux,m_variables);
    parser->SolveExpression_fn(m_function, list_values_aux, m_variables);
    if (parser->error())
    {
        return false;
    }

    return true;

    /*
    QString m_functionName; //e.g. m_functionName="f1";
    QString m_function; // e.g. m_function="4x+2"
    QString m_functionDefinition; // e.g. m_functionDefinition="f1(x)=4x+2";
    int m_number_variables; // e.g n_number_variable=1;
    QStringList m_variables; // e.g. m_variables.at(0)="x";
    */

}


QDataStream & operator<< (QDataStream& stream, const myFunction& function)
{
    /*
    stream<<function.m_function;
    stream<<function.m_functionDefinition;
    stream<<function.m_functionName;
    stream<<function.m_number_variables;
    stream<<function.m_variables;
*/

    stream<<function.GetFunction();
    stream<<function.GetFunctionDefinition();
    stream<<function.GetfunctionName();
    stream<<function.GetNumberVariables();
    stream<<function.GetVariables();

    return stream;
}

QDataStream & operator>> (QDataStream& stream, myFunction& function)
{
    QString m_functionName; //e.g. m_functionName="f1";
    QString m_function; // e.g. m_function="4x+2+y"
    QString m_functionDefinition; // e.g. m_functionDefinition="f1(x)=4x+2+y";
    int m_number_variables; // e.g n_number_variable=2;
    QStringList m_variables; // e.g. m_variables.at(0)="x";m_variables.at(1)="y"

    stream>>m_function;
    stream>>m_functionDefinition;
    stream>>m_functionName;
    stream>>m_number_variables;
    stream>>m_variables;

    function.SetFunction(m_functionDefinition);
    /*
    stream>>function.GetFunction();
    stream>>function.GetFunctionDefinition();
    stream>>function.GetfunctionName();
    stream>>function.GetNumberVariables();
    stream>>function.GetVariables();
*/
    return stream;
}
