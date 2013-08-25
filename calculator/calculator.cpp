#include "calculator.h"

Calculator::Calculator(): m_equation(&parser), m_integral(&parser)
{
    //m_equation = new Equation(&parser);
}

Calculator::~Calculator()
{
    //delete m_equation;
}

MyNumber Calculator::SolveExpression(const QString &expression)
{
    return parser.SolveExpression(expression);
}

MyNumber Calculator::SolveExpression_fx(const QString &expression)
{
    return parser.SolveExpression_fn(expression, values_List, variables_List);
}



bool Calculator::setVariable_Value(const QStringList &variables, const QList<MyNumber> &values)
{
    if (variables.size() != values.size())
        return false; //error

    for(int i=0;i<variables.size();i++)
    {
        setVariable_Value(variables.at(i), values.at(i));
    }
    return true;
}




void Calculator::setVariable_Value(const QString &variable, const MyNumber &value)
{
    int index = variables_List.indexOf(variable);
    if (index == -1)
    {
        variables_List.append(variable);
        values_List.append(value);
    }
    else
    {
        values_List[index] = value;
    }
}

void Calculator::setVariable_Value(const QString &variable, const double &value)
{
    setVariable_Value(variable, MyNumber(value));
}

void Calculator::setVariable_Value(const QString &variable, const QList<double> &value_list)
{
    setVariable_Value(variable, MyNumber(value_list));
}


void Calculator::setVariable_Value(const QString &variable, const Matrix &value_matrix)
{
    setVariable_Value(variable, MyNumber(value_matrix));
}

QString Calculator::formatResult( const Complexo &z)
{
    return format.formatResult(z);
}

QString Calculator::formatResult( const double &x)
{
    return format.formatResult(x);
}

QString Calculator::formatResult(MyNumber num)
{
    return format.formatResult(num);
}


bool Calculator::error()
{
    return parser.error();
}

void Calculator::setDegreeRadGrad(const int isDegreeRadGrad_)
{
    parser.setDegreeRadGrad(isDegreeRadGrad_);
}

int Calculator::getDegreeRadGrad()
{
    return parser.getDegreeRadGrad();
}


bool Calculator::isValid_Expression_with_time_variable(const QString &expression)
{
    return parser.isValidExpression_ft(expression);
}

bool Calculator::isValidExpression(const QString &expression)
{
    parser.SolveExpression(expression);
    return !parser.error();
}

MyNumber Calculator::isValidExpression(const QString &expression, bool &ok)
{
    MyNumber number = parser.SolveExpression(expression);
    ok = !parser.error();
    return number;
}


bool Calculator::isValidEquation(const QString &equation)
{
    return parser.isValidEquation(equation);
}


/*
QList<Complexo> Calculator::SolveEquation(const QString &equation_)
{
    //Equation m_equation(&parser);
    return m_equation->solveEquation(equation_);
}

QList<Complexo> Calculator::SolveEquation(const QString &f1, const QString &f2)
{
    return SolveEquation(f1+"="+f2);
}
*/




//QString Calculadora::f_replace_UserDefinedFunction(QString &f, QList<myFunction> list_functions)
QString Calculator::Expression_Replace_User_Defined_Function(const QString &expression_, const QList<myFunction> &list_functions_)
{
  /*  QString str_aux;
    int ii;

    //ERRO=true;

    //i.e. f == "2+cos(3)+f1(4,func2(5))*2"
    //f1(4,func2(5)) is the user defined function with 2 arguments that we want to replace
    //the second argument func2(5) is a nested user defined function
    //f1(x,y)=x+y
    //func2(x,y)=4x+2y

    for(int i=0;i<expression_.size();i++)
    {
        ii=i;
        str_aux="";
        //str_aux=SacaFuncao(f,i);
        parser.grabFunction_or_Variable_userdefined(expression_ , i, str_aux);

        for(int l=0;l<list_functions_.size() && str_aux !="" ;l++)
        {
            //if is the user definer function 'f'
            if (str_aux == list_functions_[l].GetfunctionName())
            {

                if (i >= (expression_.size()-1))
                    return expression_; //error

                //the next caracter should be a '(' , if not it's a expression with errors
                if (expression_.at(i+1) != '(' )
                    return expression_;//error

                i=i+2;

                if (i >= expression_.size())
                    return expression_; //error

                //i.e. f == "2+cos(3)+f1(4,func2(5))*2"
                QString expression_aux;
                expression_aux.clear();
                int bracket_count = 0;
                while( (expression_.at(i) != ')') || (bracket_count != 0) )
                {
                    if (expression_.at(i) == '(')
                        bracket_count++;

                    if (expression_.at(i) == ')')
                        bracket_count--;

                    expression_aux.append(expression_.at(i));


                    i++;
                    if (i >= expression_.size())
                        return expression_;  //error
                }

                //lets get the arguments (4,func2(5))
                // i.e:  4, func2(5)
                QStringList arguments;
               // arguments = f_aux.split(",");
                //nota, alterar o split imediatamente em cima para um for de forma forma contar
                //as virgulas das funcoes recursivas
                /////////////////////////////////////////////////////////////
                QString argument_aux;
                argument_aux.clear();
                bracket_count=0;
                for(int j=0;j<expression_aux.size();j++)
                {
                    if (expression_aux.at(j) == '(')
                        bracket_count++;
                    if (expression_aux.at(j) == ')')
                        bracket_count--;


                    if ((expression_aux.at(j) == ',') && (bracket_count == 0))
                    {
                        arguments.append(argument_aux);
                        argument_aux.clear();
                    }
                    else
                    {
                        argument_aux.append(expression_aux.at(j));
                    }
                }
                arguments.append(argument_aux);

                ////////////////////////////////////////////////////////////



                //if the number of arguments macht the function arguments, ok
                if (arguments.size() == list_functions_[l].GetNumberVariables())
                {
                    QString new_function;
                    new_function = f_substitui_var(list_functions_[l].GetFunction(),
                                                   list_functions_[l].GetVariables(),
                                                   arguments);
                    //new_function == "4+func2(5)"
                    //lets replace new_function in f
                    expression_.remove(ii,i-ii+1);
                    expression_.insert(ii,"("+new_function+")");
                    i=ii-1;
                    break;
                }
                else //the function has the same name, but diferent arguments, so keep on searching
                {
                    i=ii;
                }
            }
        }
    }

    //ERRO=false;
    return expression_;
*/
}














