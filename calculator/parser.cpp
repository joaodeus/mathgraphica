#include "parser.h"
#include <QDebug>
#include "equation.h"
#include "integral.h"

#define DEGREE  0
#define RAD     1
#define GRAD    2

Parser::Parser()
{
    bError=false;

    setDegreeRadGrad(RAD);
    //Degree_Rad_Grad = RAD;
    //Degree=0; Rad=1(default); Grad=2

}

MyNumber Parser::SolveExpression(const QString &expression)
{
    return ParseExpressionToList(expression);
}

QList<double> Parser::SolveExpression_List(const QString &expression, const int &size)
{
    double result = ParseExpressionToList(expression).numberReal();
    QList<double> list;

    for(int i=0;i<size;i++)
    {
        list.append(result);
    }

    return list;
}

MyNumber Parser::SolveExpression_fx(const QString &expression_fx, const double &value_x)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    GrabVariables(expression_fx, variables_List);
    values_List.append(MyNumber(value_x));

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}


MyNumber Parser::SolveExpression_fx(const QString &expression_fx, const QString &value_x, const QString &variable_x)
{
    QStringList variables;
    QStringList values;

    variables.append(variable_x);
    values.append(value_x);



    return SolveExpression( expression_replace_variables_with_values(expression_fx, variables, values) );
}


MyNumber Parser::SolveExpression_fx(const QString &expression_fx, const double &value_x, const QString &variable_x)
{

    QList<MyNumber> values_List;
    QStringList variables_List;

    values_List.append(MyNumber(value_x));
    variables_List.append(variable_x);

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}

MyNumber Parser::SolveExpression_fx(const QString &expression_fx, const MyNumber &value_x, const QString &variable_x)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    values_List.append(value_x);
    variables_List.append(variable_x);

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}

/*
QList<Complexo> Parser::SolveExpression_fx(const QString &expression_fx, QList<Complexo> &value_x,
                                           const QString &variable_x)
{
    QList<Number> values_List;
    QStringList variables_List;

    Number aux;
    aux.SetNumber(value_x);

    values_List.append(aux);
    variables_List.append(variable_x);

    return ParseExpressionToList(expression_fx, variables_List, values_List).numberList();
}*/

MyNumber Parser::SolveExpression_fx(const QString &expression_fx, QList<Complexo> &value_x,
                                           const QString &variable_x)

{
    QList<MyNumber> values_List;
    QStringList variables_List;

    MyNumber aux;
    aux.SetMyNumber(value_x);

    values_List.append(aux);
    variables_List.append(variable_x);

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}



QList<Complexo> Parser::SolveExpression_fx_ComplexList(const QString &expression_fx, QList<double> &value_x,
                                           const QString &variable_x)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    MyNumber aux;
    aux.SetMyNumber(value_x);

    values_List.append(aux);
    variables_List.append(variable_x);

    MyNumber result = ParseExpressionToList(expression_fx, variables_List, values_List);

    return result.numberListComplexo();
}


QList<double> Parser::SolveExpression_fx_List(const QString &expression_fx, QList<double> &value_x,
                                         const QString &variable_x)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    MyNumber aux;
    aux.SetMyNumber(value_x);

    values_List.append(aux);
    variables_List.append(variable_x);

    MyNumber result = ParseExpressionToList(expression_fx, variables_List, values_List);

    QList<double> result_list;
    int size = result.numberListComplexo().size();
    for (int i=0;i<size;i++)
    {
        result_list.append(result.numberListComplexo().at(i).r);
    }

    return result_list;
}

QList<double> Parser::SolveExpression_fx_List(const QString &expression_fx, QList<double> &value_x)
{
    QStringList variables_list;

    GrabVariables(expression_fx, variables_list);

    //if it's a math expression like f(x) let's solve it
    if (variables_list.size() == 1)
    {
        return SolveExpression_fx_List(expression_fx, value_x, variables_list[0]);
    }

    //if it's a constant math expression let's still solve it
    if (variables_list.size() == 0)
    {
        return SolveExpression_List(expression_fx, value_x.size());
    }

    //error, return a empty list
    bError = true;
    QList<double> result;
    return result;
}


QList<double> Parser::SolveExpression_fxt(const QString &expression_fx, QList<double> &value_x, const double &t)
{
    QString variable_x;
    if (isValidExpression_fxt(expression_fx, variable_x))
    {
        return SolveExpression_fxy(expression_fx, MyNumber(value_x), variable_x, MyNumber(t),"t").numberListReal();
    }
    else if (isValidExpression_ft(expression_fx))
    {
        double aux_number = SolveExpression_fx(expression_fx, t).numberReal();
        QList<double> aux_list;
        for (int i=0;i<value_x.size();i++)
        {
            aux_list.append(aux_number);
        }
        return aux_list;
    }
    else
    {
        //error, return a empty list
        bError = true;
        QList<double> result;
        return result;
    }
}

MyNumber Parser::SolveExpression_fxt(const QString &expression_fx, const double &value_x, const double &t)
{
    QString variable_x;

    if (isValidExpression_fxt(expression_fx, variable_x))
    {
        return SolveExpression_fxy(expression_fx, MyNumber(value_x), variable_x, MyNumber(t),"t");
    }
    else if (isValidExpression_ft(expression_fx))
    {
        return SolveExpression_fx(expression_fx, t).numberReal();
    }
    else
    {
        //error, return empty number;
        bError = true;
        return MyNumber();
    }

}


MyNumber Parser::SolveExpression_fxy(const QString &expression_fx,
                                  const QString &value_x, const QString &variable_x,
                                  const QString &value_y, const QString &variable_y)
{
    QStringList variables;
    QStringList values;

    variables.append(variable_x);
    variables.append(variable_y);

    values.append(value_x);
    values.append(value_y);

    return SolveExpression( expression_replace_variables_with_values(expression_fx, variables, values) );
}


MyNumber Parser::SolveExpression_fxy(const QString &expression_fx,
                                   const double &value_x, const QString &variable_x,
                                   const double &value_y, const QString &variable_y)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    values_List.append(MyNumber(value_x));
    variables_List.append(variable_x);

    values_List.append(MyNumber(value_y));
    variables_List.append(variable_y);

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}

MyNumber Parser::SolveExpression_fxy(const QString &expression_fx,
                           const MyNumber &value_x, const QString &variable_x,
                           const MyNumber &value_y, const QString &variable_y)
{
    QList<MyNumber> values_List;
    QStringList variables_List;

    values_List.append(value_x);
    variables_List.append(variable_x);

    values_List.append(value_y);
    variables_List.append(variable_y);

    return ParseExpressionToList(expression_fx, variables_List, values_List);
}




MyNumber Parser::SolveExpression_fn(const QString &expression_fn, QStringList &values_List_,
                                  QStringList &variables_List_)
{
    return SolveExpression( expression_replace_variables_with_values(expression_fn, variables_List_, values_List_) );
}


MyNumber Parser::SolveExpression_fn(const QString &expression_fn, QList<double> &values_List_,
                                  QStringList &variables_List_)
{
    QList<MyNumber> values_List;

    for (int i=0;i<values_List_.size();i++)
    {
        values_List.append(MyNumber(values_List_[i]));
    }

    return ParseExpressionToList(expression_fn, variables_List_, values_List);
}


MyNumber Parser::SolveExpression_fn(const QString &expression_fn, QList<MyNumber> &values_List_,
                                  QStringList &variables_List_)
{
    return ParseExpressionToList(expression_fn, variables_List_, values_List_);
}


QString Parser::Expression_ReplaceVariables_WithValues(QString expression, QStringList &variables, QStringList &values)
{

    if (variables.size() != values.size())
    {
        bError = true;
        return expression;
    }

    QString aux;
    int ii;
    for(int i=0;i<expression.length();i++)
    {
        ii = i;
        aux = "";
        grabFunction_or_Variable_userdefined(expression,i,aux);

        if (aux != "")
        {
            for (int l=0;l<variables.size();l++)
            {
                if (aux == variables[l])
                {
                    expression.remove(ii,aux.length());
                    expression.insert(ii,"("+values[l]+")");
                    i = i + ( values[l].length() - aux.length() ) + 2;
                    break;
                }
            }
        }
    }

    return expression;
}



///////////////////////////////////////////////////////////////////////////////////////////////////


int Parser::GrabVariables(const QString &expression, QStringList &list_variables)
{
    MyNumber variable;
    QString variable_aux;
    list_variables.clear();

    for (int i=0; i<expression.size(); i++)
    {
        if ( grabFunction_or_Variable_userdefined(expression, i, variable_aux) )
        {
            list_variables.append(variable_aux);
        }
    }

    list_variables.removeDuplicates();

    return list_variables.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// validate expressions


bool Parser::isValidExpression(const QString &expression)
{
    SolveExpression(expression);
    return !error();
}

bool Parser::isValidExpression(const QString &expression, MyNumber &value_)
{
    value_ = SolveExpression(expression);
    return !error();
}


bool Parser::isValidExpression_fx(const QString &expression)
{
    QString variable;
    return isValidExpression_fx(expression, variable);
}

bool Parser::isValidExpression_fx(const QString &expression, QString &variable)
{
    QStringList variables_list;

    //it's a expression with one variable ...
    if (GrabVariables(expression,variables_list) == 1)
    {
        variable = variables_list[0];
        //now let's check if it's a valid expression_fx, we will use a random number "1.34" for that
        SolveExpression_fx(expression, 1.34, variables_list[0]);
        return !error();
    }

    return false;
}


bool Parser::isValidExpression_ft(const QString &expression)
{

    QStringList variables_list;

    //it's a expression with one variable ...
    if (GrabVariables(expression,variables_list) == 1)
    {
        //if variable is not 't' return false
        if (variables_list[0] != "t")
        {
            return false;
        }

        //now let's check if it's a valid expression_fx, we will use a random number "1.34" for that
        SolveExpression_fx(expression, 1.34, variables_list[0]);
        return !error();
    }

    return false;
}


bool Parser::isValidExpression_fxt(const QString &expression)
{
    QString variable;
    return isValidExpression_fxt(expression, variable);
}


bool Parser::isValidExpression_fxt(const QString &expression, QString &variable)
{
    QStringList variables_list;

    //it's a expression with 2 variables ...
    if (GrabVariables(expression,variables_list) == 2)
    {
        if ( (variables_list[0] == "t") || (variables_list[1] == "t") )
        {
            QStringList values_list;
            //lets create 2 random values (i.e. 1.34) to validate the expression with the 2 variables
            values_list.append("1.34");
            values_list.append("1.34");

            //lets save our variable other that 't'
            if (variables_list[0] == "t")
            {
                variable = variables_list[1];
            }
            else
            {
                variable = variables_list[0];
            }

            //now lets check if expression is valid
            SolveExpression_fn(expression, values_list, variables_list);
            return !error();
        }
    }

    return false;
}


bool Parser::isValidExpression_fn(const QString &expression)
{
    QStringList variables_list;

    if (GrabVariables(expression, variables_list) > 0)
    {
        QStringList values_list;
        for (int i=0;i<variables_list.size();i++)
        {
            //we create a list of a random values (i.e 1.34) to match the size of the list of variables of the expression
            values_list.append("1.34");
        }

        //now lets check if expression is valid
        SolveExpression_fn(expression, values_list, variables_list);
        return !error();
    }
    else
    {
        return false;
    }
}

/*
bool Parser::isValidExpression_fn(const QString &expression, const uint n)
{
    QStringList variables_list;

    if (GetVariables(expression, variables_list) > 1)
    {
        QStringList values_list;
        for (int i=0;i<variables_list.size();i++)
        {
            //we create a list of a random value (i.e 1.34) to math the list of variables of the expression
            values_list.append("1.34");
        }

        //now lets check if expression is valid
        SolveExpression_fn(expression, values_list, variables_list);
        return !error();
    }
    else
    {
        return false;
    }
}
*/
/*
bool isValidExpression_fn(const QString &expression)
{

}*/

bool Parser::isValidEquation(const QString &expression)
{
    QString f1;
    QString f2;
    QString var;

    return isValidEquation(expression,f1,f2,var);
}


bool Parser::isValidEquation(const QString &expression, QString &equation_First_Member, QString &equation_Second_Member, QString &variable)
{
    QStringList equation_members = expression.split("=");
    QStringList variables_aux;

    if (equation_members.size() != 2)
    {
        return false;
    }

    equation_First_Member   = equation_members[0];
    equation_Second_Member  = equation_members[1];


    if (        ( isValidExpression(equation_members[0]) || isValidExpression_fx(equation_members[0]) )
            &&  ( isValidExpression(equation_members[1]) || isValidExpression_fx(equation_members[1]) )
            &&  ( GrabVariables(expression, variables_aux) == 1 )  )
    {
        variable = variables_aux[0];
        return true;
    }
    else
    {
        return false;
    }
}


bool Parser::isValidEquation_Explicit_From_Constant(const QString &equation)
{
    QString variable_aux;
    MyNumber value_aux;
    return isValidEquation_Explicit_From_Constant(equation, variable_aux, value_aux);
}

bool Parser::isValidEquation_Explicit_From_Constant(const QString &equation, QString &variable_, MyNumber &value_)
{
    QStringList equation_members = equation.split("=");
    QStringList variables_aux;

    if ( equation_members.size() != 2 )
    {
        return false;
    }

    if ( GrabVariables(equation, variables_aux) != 1 )
    {
        return false;
    }

   if ( ( (equation_members[0] == variables_aux[0])
           || (equation_members[0] ==  ("("+ variables_aux[0] +")" )  ) )
         && isValidExpression(equation_members[1], value_) )
    {
        variable_ = variables_aux[0];

        return true;
    }
    else
    {
        return false;
    }
}


bool Parser::isValidEquation_Explicit_From_Variables(const QString &equation)
{
    QString member1;
    QString member2;
    return isValidEquation_Explicit_From_Variables(equation, member1, member2);
}


bool Parser::isValidEquation_Explicit_From_Variables(const QString &equation,
                                             QString &first_member, QString &second_member)
{
    QStringList equation_members = equation.split("=");

    if ( equation_members.size() != 2 )
    {
        return false;
    }


    //check if first member of equation has only one variable
    QStringList variable_member1;
    if ( GrabVariables(equation_members[0], variable_member1) != 1 )
    {
        return false;
    }


    //check if equation is explicit, i.e. if the variable of the equation first member is equal to the first member
    if (equation_members[0] != variable_member1[0])
    {
        return false;
    }

    //check if second member has at least one variable
    QStringList variables_member2;
    if ( GrabVariables(equation_members[1], variables_member2) < 1  )
    {
        return false;
    }

    //Let's check if the variable of the fist member isn't repeated in the second member
    //(if there is, than it isn't an explicit equation)
    if (variables_member2.contains(equation_members[0]))
    {
        return false;
    }

    //check is the second member is a valid expression
    if (isValidExpression_fn(equation_members[1]))
    {
        first_member = equation_members[0];
        second_member = equation_members[1];
        return true;
    }
    else
    {
        return false;
    }

}


bool Parser::error()
{
    return bError;
}

void Parser::setDegreeRadGrad(const int isDegreeRadGrad_)
{
    Degree_Rad_Grad = isDegreeRadGrad_;
}

int Parser::getDegreeRadGrad()
{
    return Degree_Rad_Grad;
}

///////////////////////////////////////////////////////////////
// equations
/*
QVector<Complexo> Parser::equation(const QString &equation_expression)
{
    double min      = -1000000;
    double max      = 1000000;
    double step     = 0.1;
    double precision= 0.000001;

    return equation(equation_expression, min, max, step, precision);
}

QVector<Complexo> Parser::equation(const QString &equation_expression, double &min, double &max, double &step, double &precision)
{
    Equation equation(this);

    QString f1;
    QString f2;
    QString var;

    if (isValidEquation(equation_expression,f1,f2, var))
    {
        bError = false;
        equation.equation_solver(this,f1,f2,var,min, max,step, precision);
    }
    else
    {
        bError = true;
    }

    return equation.equation_solutions;
}
*/


MyNumber Parser::ParseExpressionToList(const QString &expression_)
{

    QStringList variables;
    QList<MyNumber> values;

    return ParseExpressionToList(expression_, variables, values);
}


MyNumber Parser::ParseExpressionToList(const QString &expression_, QStringList &variables_List, QList<MyNumber> &values_List)
{
    bError = false;
    QString functions_aux; //store the functions from expression_
    double numberDouble_aux; //store the numbers from expression_
    MyNumber token_aux; //when sucessfully grabbed a number, operator or function from expression_
    //store it on tokenNumber_aux and add it to the list m_tokenNumberList
    Matrix matrix_aux;

    // count the parentheses for auto completation
    int count_Left_Bracket=0;
    int count_Right_Bracket=0;

    m_tokenNumberList.clear();


    if (expression_.size() == 0)
    {
        bError = true;
        return MyNumber();
    }



    for (int i=0;i<expression_.size();i++)
    {

        bError = true;


        //check if it's a number
        if ( grabNumber(expression_, i, numberDouble_aux) )
        {                        
            int L = m_tokenNumberList.size();

            //let's check if before the number there's a imaginary 'i'
            //if so, we'll add a token '*' to the list, this eases the writing for the user
            //example: for imaginary numbers the user can write i2 for simplicity instead of i*2
            if (L > 0)
            {
                if (m_tokenNumberList[L-1].isImaginary())
                {                    
                    token_aux.setOperatorFunction("*");
                    m_tokenNumberList.append(token_aux); //add our muliplication token to the list
                }
            }

            bError = false;            
            token_aux.SetMyNumber(numberDouble_aux);
            m_tokenNumberList.append(token_aux); //finally add our number to the list
        }




        //check if it's a operator or parentheses
        // like +,-, *, /, E, ^ or (,), |
        else if ( grabOperatorOrParentheses(expression_[i]) )
        {


            int L = m_tokenNumberList.size();
            token_aux.setOperatorFunction(expression_[i]);

            if (L > 0) //if our list is not empty ....
            {
                //if our current token is "(" and previous is ")" our a number
                //we add a "*" token between then
                //this allows user to input expressions like "(2+3)(4-2)" instead of "(2+3)*(4-2)"
                // or expressions like "4(3+2)" instead of "4*(3+2)"
                if ( (token_aux.isLeft_Parentheses()) &&
                     ( m_tokenNumberList[L-1].isRight_Parentheses() ||  m_tokenNumberList[L-1].isNumber()) )
                {
                    MyNumber token_multiplication;
                    token_multiplication.setOperatorFunction("*");
                    m_tokenNumberList.append(token_multiplication);
                }
            }


            //if this is out first elements and it's "-" we'll prepend a number zero
            //this will change expressions like "-2" to "0-2", it will make the parser's life easier and avoid bugs in parsing
            //if (L == 0)
            //{
              //  if (token_aux.isOperatorMinus())
               // {
                 //   Number token_zero;
                  //  token_zero.SetNumber(0.0);
                   // m_tokenNumberList.append(token_zero);
               // }
            //}

            bError = false;
            m_tokenNumberList.append(token_aux); //finally append our token

            //and count the parentheses for auto completation later
            if (token_aux.isRight_Parentheses())
                count_Right_Bracket++;

            if (token_aux.isLeft_Parentheses())
                count_Left_Bracket++;

        }




        //check if it's a function like sin, cos, log, ....
        else if (grabFunction_predefined(expression_, i, functions_aux))
        {            
            //check if previous element is a number, if so appen a token multiplication "*"
            //that way the user con write "2cos(2)" instead of "2*cos(3)"
            int L = m_tokenNumberList.size();
            if (L > 0)
            {
                if (m_tokenNumberList[L-1].isNumber())
                {
                    MyNumber token_multiplication;
                    token_multiplication.setOperatorFunction("*");
                    m_tokenNumberList.append(token_multiplication);
                }
            }

            bError = false;
            token_aux.setOperatorFunction(functions_aux);
            m_tokenNumberList.append(token_aux); //append our token
        }


        //check if it's a imaginary number: i
        else if( isImaginaryNumber(expression_, i, functions_aux) )
        {
            //check if before there is a number:  2
            //if so, set it to 2i
            int L = m_tokenNumberList.size();
            if ( L > 0) //if list is not empty...
            {
                if (m_tokenNumberList[L-1].isNumber()) //...and the previous element is number..
                {
                    bError = false;
                    token_aux.SetMyNumber(Complexo(0,1));
                    m_tokenNumberList[L-1]=m_tokenNumberList[L-1]*token_aux; //multiplie it with imaginary
                    //m_tokenNumberList[L-1]=m_tokenNumberList[L-1]*Complexo(0,1); //multiplie it with imaginary
                }
                else // if previous element is not a number, lets add our imaginary
                {
                    bError = false;
                    token_aux.SetMyNumber(Complexo(0,1));
                    m_tokenNumberList.append(token_aux);
                }

            }else // L = 0, list is empty, just add our imaginary number
            {
                bError = false;
                token_aux.SetMyNumber(Complexo(0,1));
                m_tokenNumberList.append(token_aux);
            }
        }




        //check for constants: "pi"
        else if( isPiNumber(expression_, i, functions_aux) )
        {
            //check if previous element is a number i.e.  2pi
            //if so, add token "*" so it will be 2*pi
            int L = m_tokenNumberList.size();
            if (L > 0)
            {
                if (m_tokenNumberList[L-1].isNumber())
                {
                    MyNumber token_multiplication;
                    token_multiplication.setOperatorFunction("*");
                    m_tokenNumberList.append(token_multiplication);
                }
            }

            bError = false;
            token_aux.SetMyNumber(PI);
            m_tokenNumberList.append(token_aux); //finally add our number to the list
        }




        //check for constants: "e" (neper number)
        else if( isNeper(expression_, i, functions_aux) )
        {
            //check if previous element is a number i.e.  2e
            //if so, add token "*" so it will be 2*e
            int L = m_tokenNumberList.size();
            if (L > 0)
            {
                if (m_tokenNumberList[L-1].isNumber())
                {
                    MyNumber token_multiplication;
                    token_multiplication.setOperatorFunction("*");
                    m_tokenNumberList.append(token_multiplication);
                }
            }

            bError = false;
            token_aux.SetMyNumber(e_Neper);
            m_tokenNumberList.append(token_aux); //finally add our number to the list
        }


        //check if it's a variable
        //variables should start with a letter, and contain letters, numbers and underscores
        //and should be different from predefined functions like sin,cos, ...
        else if (grabFunction_aux(expression_, i, functions_aux) && ( variables_List.size() == values_List.size() ) )
        {
            for(int j=0;j<variables_List.size();j++)
            {
                if (functions_aux == variables_List.at(j))
                {
                    //check if previous element is a number i.e.  2e
                    //if so, add token "*" so it will be 2*e
                    int L = m_tokenNumberList.size();
                    if (L > 0)
                    {
                        if (m_tokenNumberList[L-1].isNumber())
                        {
                            MyNumber token_multiplication;
                            token_multiplication.setOperatorFunction("*");
                            m_tokenNumberList.append(token_multiplication);
                        }
                    }

                    bError = false;
                    m_tokenNumberList.append(values_List.at(j));
                }
            }
        }



        // check for a matrix inside the expression_ at given index and return true if it's a valid matrix
        //example: number_ = "2+[2 3; 6 8]*7" ,  index = 2
        // return true,  stores [2 3; 6 8] in matrix_  and set's index to 11 (ending index of the matrix)
        else if( grabMatrix(expression_, i, matrix_aux) )
        {
            bError = false;
            token_aux.SetMyNumber(matrix_aux);
            m_tokenNumberList.append(token_aux);
        }


        //if it's just a white space, thats ok, do nothing and keep parsing ... :)
        else if( expression_.at(i) == ' ' )
        {
            bError = false;
        }


        // if bError is true, there's something wrong, we fail all previous options to set it to false
        //so there is a expression error, lets abort, user can check later for errors with error()
        if (bError)
        {
            return MyNumber();
        }

    }



    //code completation the number of parentheses
    token_aux.setOperatorFunction(")");
    if(count_Left_Bracket > count_Right_Bracket)
    {
        while(count_Left_Bracket > count_Right_Bracket)
        {
            m_tokenNumberList.append(token_aux);
            count_Right_Bracket++;
        };
    }


    return ListSolver();

}


MyNumber Parser::ListSolver()
{


    if (m_tokenNumberList.size() == 1)
    {
        if (m_tokenNumberList[0].isNumber())
        {
            bError = false;
            //QMessageBox::about(0,"resultados",
            //QString("%1+i%2").arg(m_tokenNumberList[0].numberComplexo().r).arg(m_tokenNumberList[0].numberComplexo().i));
            //m_tokenNumberList[0].showNumber();
            return m_tokenNumberList[0];
        }
    }



    for (int i=0; i < m_tokenNumberList.size() ; i++)
    {


        //lets go to a operator/function
        while( m_tokenNumberList[i].isNumber()  &&  i < m_tokenNumberList.size()-1)
        {
            i++;
        }


        //check in the list for 2 consecutives elements respectively with a function and a number
        // i.e. : cos 2
        // the 2 elements will be replaced by one element with the result of cos2
        // we return the to ListSolver() until the list is one element size, wich is the math expression solution
        if (m_tokenNumberList[i].isFunction() && bExist_Next_Element_List(i))
        {
            if (m_tokenNumberList[i+1].isNumber())
            {
                SolveFunctions(i);
                return ListSolver();
            }
        }




        //check for 3 elements in the list, a number, a operator and a number
        // something like 2+3
        // the 3 elements will be replaced by just one with the solution, 5
        // will have to take care with operator priority
        if (m_tokenNumberList[i].isOperator() && bExist_Previous_Element_List(i) && bExist_Next_Element_List(i))
        {
            //if this element is a operator and previous and next elements are numbers
            if (m_tokenNumberList[i-1].isNumber() && m_tokenNumberList[i+1].isNumber())
            {
                //if there isn't more element after the element(i+1)
                //we can solve without worring with operator priorities
                if (!bExist_Next_2_Elements_List(i))
                {
                    SolveOperator(i);
                    return ListSolver();
                }
                else //if there is more elements we must check operator priorities
                {
                    if (m_tokenNumberList[i+2].isParentheses()
                            || (m_tokenNumberList[i].operatorPriority() == 0 && m_tokenNumberList[i+2].operatorPriority() == 0)
                            || (m_tokenNumberList[i].operatorPriority() == 1 && m_tokenNumberList[i+2].operatorPriority() <= 1)
                            || (m_tokenNumberList[i].operatorPriority() == 2 && m_tokenNumberList[i+2].operatorPriority() <  2)  )
                    {
                        SolveOperator(i);
                        return ListSolver();
                    }

                }

            }
        }





        //se (2) ou |5|, remove parentesis
        //check if we have 3 elements with parentheses, number and parentheses
        //if so, we can remove the 2 elements with parentheses
        // (2) or |5|, remove parentheses => 2 or 5
        if ( bExist_Next_2_Elements_List(i) )
        {
            if (m_tokenNumberList[i].isLeft_Parentheses() && m_tokenNumberList[i+1].isNumber() && m_tokenNumberList[i+2].isRight_Parentheses())
            {
                RemoveParentheses(i);
                return ListSolver();
            }

            if (m_tokenNumberList[i].isParentheses_abs() && m_tokenNumberList[i+1].isNumber() && m_tokenNumberList[i+2].isParentheses_abs())
            {
                RemoveParentheses_abs(i);
                return ListSolver();
            }
        }


        //check for (-2) => solve -2 or
        //          |-3| => solve -3
        if (bExist_Previous_Element_List(i) && bExist_Next_2_Elements_List(i))
        {
            if ( (m_tokenNumberList[i].isOperatorMinus() || m_tokenNumberList[i].isOperatorPlus() )
                 && m_tokenNumberList[i+1].isNumber())
            {
                //if (-2)
                if (m_tokenNumberList[i-1].isLeft_Parentheses() && m_tokenNumberList[i+2].isRight_Parentheses())
                {
                    SolveFunctions(i);
                    return ListSolver();
                }

                //if |-3|
                if (m_tokenNumberList[i-1].isParentheses_abs() && m_tokenNumberList[i+2].isParentheses_abs())
                {
                    SolveFunctions(i);
                    return ListSolver();
                }

            }
        }

        //SolveFunctions()

        //check for expressions like cos-2 => solves -2; or 8/-3
        // solves                   8/-3   => solves -3
        // 8/-2^2

        if ( (m_tokenNumberList[i].isOperatorPlus() || m_tokenNumberList[i].isOperatorMinus())
              && bExist_Previous_Element_List(i) && bExist_Next_Element_List(i)  )
        {            
            if (!bExist_Next_2_Elements_List(i))
            {
                if (m_tokenNumberList[i-1].isFunction_or_Operator() && m_tokenNumberList[i+1].isNumber())
                {
                    SolveFunctions(i);
                    return ListSolver();
                }
            }
            else
            {
                if (m_tokenNumberList[i-1].isFunction() && m_tokenNumberList[i+1].isNumber()
                        && ( m_tokenNumberList[i+2].isFunction() ||  m_tokenNumberList[i+2].isParentheses()) )
                {
                    SolveFunctions(i);
                    return ListSolver();
                }

                if (m_tokenNumberList[i-1].isFunction() && m_tokenNumberList[i+1].isNumber()
                        && m_tokenNumberList[i+2].isOperator() && (m_tokenNumberList[i+2].operatorPriority() < 2) )
                {
                    SolveFunctions(i);
                    return ListSolver();
                }
            }
        }


        //check for expression that start with "-" or "+" followed by a number: i.e. -2
        //lets check operator priorities of the next elements to find if we can operate -2
        //
        if ( (m_tokenNumberList[i].isOperatorPlus() || m_tokenNumberList[i].isOperatorMinus())
              && !bExist_Previous_Element_List(i) )
        {
            //if there is only 2 elements i.e.: -2, lets solve it
            if (!bExist_Next_2_Elements_List(i))
            {
                SolveFunctions(i);
                return ListSolver();
            }
            else //else lets check for priorities: i.i. -2|
            {
                if ( m_tokenNumberList[i+2].isFunction() ||  m_tokenNumberList[i+2].isParentheses() )
                {
                    SolveFunctions(i);
                    return ListSolver();
                }

                if (m_tokenNumberList[i+2].isOperator() && (m_tokenNumberList[i+2].operatorPriority() < 2) )
                {
                    SolveFunctions(i);
                    return ListSolver();
                }
            }
        }


    }


    bError = true;
    return MyNumber();
}



bool Parser::grabOperatorOrParentheses(const QString expression_)
{

    MyNumber token_aux;
    token_aux.setOperatorFunction(expression_);
    return ( token_aux.isOperator() || token_aux.isParentheses() );
}

// check for a number inside the expression_
// return if exist and assign it to number_
// example: number_ = "2+3.45*7" ,  i = 2 => return 3.45 and i = 5
bool Parser::grabNumber(const QString &expression_, int &index, double &number_)
{
    if (!expression_[index].isDigit() && expression_[index] != '.')
    {
        return false;
    }

    int index_aux = index;

    QString number_aux;
    bool ok;

    while (expression_[index].isDigit() || expression_[index]=='.' || expression_[index]==' ' )
    {
        number_aux += expression_[index];

        if (index <  ( expression_.size()-1 ) )
        {
            index++;
        }
        else
        {
            number_aux.remove(" ",Qt::CaseSensitive);
            number_ = number_aux.toDouble(&ok);
            //return ok;
            if (ok)
            {
                return ok;
            }
            else
            {
                index = index_aux;
                return ok;
            }
        }
    }

    index--;

    number_aux.remove(" ",Qt::CaseSensitive);
    number_ = number_aux.toDouble(&ok);
    if (ok)
    {
        return ok;
    }
    else
    {
        index = index_aux;
        return ok;
    }

}


bool Parser::grabMatrix(const QString &expression_, int &index, Matrix &matrix_)
{
    if (expression_[index] != '[')
    {
        return false;
    }


    if (index >= (expression_.size()-1) )
    {
        return false;
    }


    QString matrix_str;
    int i = index+1;

    while ( expression_[i] != ']' )
    {
        matrix_str += expression_[i];
        i++;

        if ( i >= expression_.size() )
        {
            return false;
        }
    };



    QStringList matrix_aux = matrix_str.split(";", QString::SkipEmptyParts);
    QStringList matrix_line_elements;
    int first_line_element_count;
    int following_lines_element_count;

    for (int j=0;j<matrix_aux.size();j++)
    {
        matrix_aux[j].replace(","," ");
        matrix_line_elements = matrix_aux[j].split(" ", QString::SkipEmptyParts);

        if (j == 0) // first line elements count should be equal to the following lines element count
        {
            first_line_element_count = matrix_line_elements.size();
            matrix_.SetLinesCols(matrix_aux.size(), first_line_element_count);//set matrix dimension

            matrix_.SetLineElements(matrix_line_elements,j);
         }
        else
        {
            following_lines_element_count = matrix_line_elements.size();

            if (following_lines_element_count != first_line_element_count)
            {
                return false; // error, matrix dimensions don't match
            }

            matrix_.SetLineElements(matrix_line_elements,j);
        }
    }

    index = i;
  //  matrix_.Show();
    return true;
}



bool Parser::grabFunction_aux(const QString &expression_, int &index, QString &function_)
{

    //if the first character is not a letter, exits with a empty string, this is not a function
    if (!expression_[index].isLetter())
    {
        return false;
    }

    //check for a false function like 2E3
    if ( (index>0) && (expression_[index] == 'E') )
    {
        if ( index < expression_.size()-1 )
        {
            if (expression_[index+1] == '-' || expression_[index+1] == '+' || expression_[index+1].isDigit())
            //if (expression_[index-1].isDigit() && expression_[index+1].isDigit())
                return false;
        }
    }

    function_.clear();
    //lets grab the function
    while (expression_[index].isLetterOrNumber() || expression_[index]=='_' )
    {
        function_+=expression_[index];

        if (index < expression_.size()-1)
        {
            index++;
        }
        else
        {
            return true;
        }
    }

    index--;

    return true;
}


bool Parser::grabFunction_predefined(const QString &expression_, int &index, QString &function_)
{
    int index_aux = index;
    QString function_aux = function_;
    if ( !grabFunction_aux(expression_, index, function_) )
    {
        index = index_aux;
        function_ = function_aux;
        return false;
    }

    MyNumber token_aux;
    token_aux.setOperatorFunction(function_);

    if (token_aux.isFunction())
    {
        return true;
    }
    else
    {
        index = index_aux;
        function_ = function_aux;
        return false;
    }
}

// check this function, has a bug
// hopefully bug solved
bool Parser::grabFunction_or_Variable_userdefined(const QString &expression_, int &index, QString &function_)
{

    if ( !grabFunction_aux(expression_, index, function_) )     
        return false;

    MyNumber token_aux;
    token_aux.setOperatorFunction(function_);

    if (token_aux.isFunction())        
        return false;   
    else
        return true;

}


//check for "pi", "e" (euler number) and "i" (imaginary number)
bool Parser::grabConstants(const QString &expression_, int &index, QString &constants_)
{
    grabFunction_aux(expression_, index, constants_);

    if (!constants_.compare("pi",Qt::CaseInsensitive))
        return true;

    if (!constants_.compare("e",Qt::CaseSensitive))
        return true;

    if (!constants_.compare("i",Qt::CaseInsensitive))
        return true;

    return false;
}

bool Parser::isImaginaryNumber(const QString &expression_, int &index, QString &constants_)
{
    int index_aux = index;
    grabFunction_aux(expression_, index, constants_);

    if (constants_.compare("i",Qt::CaseInsensitive))
    {
        index = index_aux;
        return false;
    }
    else
    {
        return true;
    }
}


bool Parser::isPiNumber(const QString &expression_, int &index, QString &constants_)
{
    int index_aux = index;
    grabFunction_aux(expression_, index, constants_);

    if (constants_.compare("pi",Qt::CaseInsensitive))
    {
        index = index_aux;
        return false;
    }
    else
    {
        return true;
    }
}

bool Parser::isNeper(const QString &expression_, int &index, QString &constants_)
{
    int index_aux = index;
    grabFunction_aux(expression_, index, constants_);

    if (constants_.compare("e",Qt::CaseSensitive))
    {
        index = index_aux;
        return false;
    }
    else
    {
        return true;
    }
}


//convenience method
QString Parser::expression_replace_variables_with_values(const QString &expression_, QPair<QStringList, QStringList> &variables_values)
{

    bError = false;

    if (variables_values.first.size() != variables_values.second.size())
    {
        bError = true;
        return expression_;
    }

    QStringList variables   = variables_values.first;
    QStringList values      = variables_values.second;


    return expression_replace_variables_with_values(expression_, variables, values);
}


//replace in an expression, a list of varibles by a list of values
//example: expression_ = "cos(x)+y*z" ; variables={x,y,z}; values={3,2,4}
// will return "cos(3)+2*4"
QString Parser::expression_replace_variables_with_values(const QString &expression_, QStringList &variables, QStringList &values)
{

    QString expression(expression_);
    bError = false;


    if (variables.size() != values.size()) // error, numbers of variables and values should match
    {
        bError = true;
        return expression;
    }

    QString variable_aux;
    int ii;
    for (int i=0;i<expression.size();i++)
    {
        ii=i;
        variable_aux.clear();
        //variable_aux = grabFunction(expression,i);
        grabFunction_or_Variable_userdefined(expression,i, variable_aux);


        if (variable_aux != "")
        {
            for (int l=0;l<variables.size();l++)
            {
                if (variable_aux == variables[l])
                {
                    expression.remove(ii,variable_aux.length());
                    expression.insert(ii,"("+values[l]+")");
                    //i+= (values[l].length()-variable_aux.length()) + 2;
                    i+= (values[l].length()-variable_aux.length()) + 2;
                }
            }
        }
    }

    return expression;
}





void Parser::SolveOperator(int &i)
{

    if (m_tokenNumberList[i].isOperatorPlus())
    {
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] + m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }

    if (m_tokenNumberList[i].isOperatorMinus())
    {
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] - m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }


    if (m_tokenNumberList[i].isOperatorMultiplication())
    {
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] * m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }

    if (m_tokenNumberList[i].isOperatorDivision())
    {
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] / m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }

    if (m_tokenNumberList[i].isOperatorPower())
    {
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] ^ m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }

    if (m_tokenNumberList[i].isOperatorE())
    {
        MyNumber aux;
        aux.SetMyNumber(10);
        aux = aux^m_tokenNumberList[i+1];
        m_tokenNumberList[i-1] = m_tokenNumberList[i-1] * aux;
        //m_tokenNumberList[i-1] = m_tokenNumberList[i-1] * aux^m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i);
        m_tokenNumberList.remove(i);
        return;
    }


}



/////////////////////////////////////////////////////////////////////
// following methods solve functions/operators of the list


void Parser::SolveFunctions(int &i)
{


    if (m_tokenNumberList[i].isOperatorMinus())
    {
        m_tokenNumberList[i] = -m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i+1);
        return;
    }

    if (m_tokenNumberList[i].isOperatorPlus())
    {
        m_tokenNumberList[i] = m_tokenNumberList[i+1];
        m_tokenNumberList.remove(i+1);
        return;
    }


    QString type;
    m_tokenNumberList[i].isFunction(type);


    if ( type == QObject::tr("log") )
    {
        m_tokenNumberList[i] = log(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("ln") )
    {
        m_tokenNumberList[i] = ln(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("abs") )
    {
        m_tokenNumberList[i] = cabs(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("cbrt") )
    {
        m_tokenNumberList[i] = cbrt(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("sqrt") )
    {
        m_tokenNumberList[i] = sqrt(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("conj") )
    {
        m_tokenNumberList[i] = conj(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("real") )
    {
        m_tokenNumberList[i] = real(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("imag") )
    {
        m_tokenNumberList[i] = imag(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("exp") )
    {
        m_tokenNumberList[i] = exp(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }



    MyNumber Degree_Rad_Grad_aux;
    switch(Degree_Rad_Grad)
    {
    case DEGREE: //degree
        Degree_Rad_Grad_aux.SetMyNumber(PI/180);
        Degree_Rad_Grad_aux = Degree_Rad_Grad_aux * m_tokenNumberList[i+1];
        break;

    case RAD://rad
        Degree_Rad_Grad_aux = m_tokenNumberList[i+1];
        break;

    case GRAD: // grad
        Degree_Rad_Grad_aux.SetMyNumber(PI/200);
        Degree_Rad_Grad_aux = Degree_Rad_Grad_aux * m_tokenNumberList[i+1];
        break;
    };



    ///////////////////////////////////////////////////////////////
    //trigonometric functions

    if ( type == QObject::tr("sinc") )
    {
        m_tokenNumberList[i] = sinc(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }


    if ( type == QObject::tr("sin") )
    {
        m_tokenNumberList[i] = sin(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("cos") )
    {
        m_tokenNumberList[i] = cos(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("tan") )
    {
        m_tokenNumberList[i] = tan(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("cot") )
    {
        m_tokenNumberList[i] = cot(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("sec") )
    {
        m_tokenNumberList[i] = sec(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("csc") )
    {
        m_tokenNumberList[i] = csc(Degree_Rad_Grad_aux);
        m_tokenNumberList.remove(i+1);
        return;
    }

    ///////////////////////////////////////////////////////////////
    //trigonometric hyperbolic functions

    if ( type == QObject::tr("sinh") )
    {
        m_tokenNumberList[i] = sinh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("cosh") )
    {
        m_tokenNumberList[i] = cosh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("tanh") )
    {
        m_tokenNumberList[i] = tanh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("coth") )
    {
        m_tokenNumberList[i] = coth(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("sech") )
    {
        m_tokenNumberList[i] = sech(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("csch") )
    {
        m_tokenNumberList[i] = csch(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }


    ///////////////////////////////////////////////////////////////
    //trigonometric inverse functions


    switch (Degree_Rad_Grad)
    {
    case DEGREE: //degree
        Degree_Rad_Grad_aux.SetMyNumber(180/PI);
        break;

    case RAD: //rad
        Degree_Rad_Grad_aux.SetMyNumber(1);
        break;

    case GRAD: //grad
        Degree_Rad_Grad_aux.SetMyNumber(200/PI);
        break;
    }


    if ( type == QObject::tr("asin") )
    {
        m_tokenNumberList[i] = asin(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acos") )
    {
        m_tokenNumberList[i] = acos(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("atan") )
    {
        m_tokenNumberList[i] = atan(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acot") )
    {
        m_tokenNumberList[i] = acot(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("asec") )
    {
        m_tokenNumberList[i] = asec(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acsc") )
    {
        m_tokenNumberList[i] = acsc(m_tokenNumberList[i+1]);
        m_tokenNumberList[i] = m_tokenNumberList[i] * Degree_Rad_Grad_aux;
        m_tokenNumberList.remove(i+1);
        return;
    }


    ///////////////////////////////////////////////////////////////
    //trigonometric inverse hyperbolic functions


    if ( type == QObject::tr("asinh") )
    {
        m_tokenNumberList[i] = asinh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acosh") )
    {
        m_tokenNumberList[i] = acosh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("atanh") )
    {
        m_tokenNumberList[i] = atanh(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acoth") )
    {
        m_tokenNumberList[i] = acoth(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("asech") )
    {
        m_tokenNumberList[i] = asech(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

    if ( type == QObject::tr("acsch") )
    {
        m_tokenNumberList[i] = acsch(m_tokenNumberList[i+1]);
        m_tokenNumberList.remove(i+1);
        return;
    }

}


void Parser::RemoveParentheses(int &i)
{
    m_tokenNumberList.remove(i+2);
    m_tokenNumberList.remove(i);
}


void Parser::RemoveParentheses_abs(int &i)
{
   // m_tokenNumberList[1+i] = abs(m_tokenNumberList[1+i]);

    m_tokenNumberList.remove(i+2);
    m_tokenNumberList.remove(i);
}


//////////////////////////////////////////////////////////////////////////
// following methods check if previous and next elements of the list exist

bool Parser::bExist_Next_Element_List(int &i)
{
    if ( i >= (m_tokenNumberList.size() - 1) )
        return false;
    else
        return true;
}

bool Parser::bExist_Next_2_Elements_List(int &i)
{
    if ( i < (m_tokenNumberList.size() - 2) )
        return true;
    else
        return false;
}

bool Parser::bExist_Previous_Element_List(int &i)
{
    if ( i > 0 )
        return true;
    else
        return false;
}

bool Parser::bExist_Previous_2_Elements_List(int &i)
{
    if ( i > 1 )
        return true;
    else
        return false;
}
