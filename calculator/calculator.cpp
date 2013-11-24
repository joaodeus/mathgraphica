#include "calculator.h"

#define DEGREE  0
#define RAD     1
#define GRAD    2


Calculator::Calculator(): m_equation(&parser), m_integral(&parser), m_integralDouble(&parser), m_function(&parser)

{

    setDegreeRadGrad(RAD);

    setPreDefinedFormulas();


 //   variables_List.append("t");
 //   values_List.append(MyNumber(0));

}

Calculator::~Calculator()
{

}


void Calculator::setPreDefinedFormulas()
{
    Formulas formula(&parser); // create one default formula

    //Einstein Formula
    formula.setFormula("E=m*C^2");
    formula.setDescription("Einstein mass–energy equivalence");
    formula.calculateConstants();
    QStringList values;
    values<<"5000"<<"?"<<"3E8";
    formula.setValues(values);
    m_formulasList.append(formula);


    //Quadratic equation
    formula.setFormula("a*x^2 + b*x + c = 0");
    formula.setDescription("Quadratic equation");
    formula.calculateConstants();
    formula.setMin("-1000");
    formula.setMax("1000");
    values.clear();
    values<<"2"<<"?"<<"-2"<<"-4";
    formula.setValues(values);
    m_formulasList.append(formula);


    //Quadratic equation explict to x
    formula.setFormula("x=(-b+sqrt(b^2-4*a*c))/(2*a)");
    formula.setDescription("Quadratic equation explicit to x1");
    formula.calculateConstants();
    values.clear();
    values<<"?"<<"3"<<"1"<<"5";
    formula.setValues(values);
    m_formulasList.append(formula);



 /*   //Ideal Gas Formula
    formula.setFormula("P*V=n*R*T");
    formula.setDescription("Ideal Gas Formula");
    formula.calculateConstants();
    formula.setMin("-1E6");
    formula.setMax("1E6");
    values.clear();
    values<<"50"<<"30"<<"?"<<"8.314"<<"350";
    formula.setValues(values);
    m_formulasList.append(formula);
*/

    /*
    //Circle Perimeter Formula
    formula.setFormula("P=2*pi*r");
    formula.setDescription("Circle Perimeter");
    formula.calculateConstants();
    formula.setMin("-1000");
    formula.setMax("1000");
    values.clear();
    values<<"?"<<"30";
    formula.setValues(values);
    m_formulasList.append(formula);
*/


}


MyNumber Calculator::SolveExpression(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.SolveExpression(expression);
}

MyNumber Calculator::SolveExpression_fx(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.SolveExpression_fn(expression, values_List, variables_List);
}

QList<double> Calculator::SolveExpression_list(const QString &expression, const int &size)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    MyNumber aux = parser.SolveExpression_fn(expression, values_List, variables_List);
    if (aux.numberListComplexo().size() == 0)
    {
        QList<double> listReal;
        for (int i = 0; i < size; i++)
        {
            listReal.append(aux.numberReal());
        }
        return listReal;
    }

    return aux.numberListReal();
}


MyNumber Calculator::SolveExpression_fn(const QString &expression_fn, QList<MyNumber> &values_List_, QStringList &variables_List_)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.SolveExpression_fn(expression_fn, values_List_, variables_List_);
}



/*
void Calculator::clear_Variables_Values()
{
    variables_List.clear();
    values_List.clear();
}*/


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


bool Calculator::checkIfVariableExists(const QString &variable, int &index)
{
    index = variables_List.indexOf(variable);
    if (index == -1)
        return false;
    else
        return true;
}


int Calculator::GrabVariables(const QString &expression, QStringList &list_variables)
{
    parser.GrabVariables(expression,list_variables);
    return list_variables.size();
}


QString Calculator::formatResult( const Complexo &z)
{
    format.setDegreeRadGrad(parser.getDegreeRadGrad());
    return format.formatResult(z);
}

QString Calculator::formatResult( const double &x)
{
    format.setDegreeRadGrad(parser.getDegreeRadGrad());
    return format.formatResult(x);
}

QString Calculator::formatResult(MyNumber num)
{
    format.setDegreeRadGrad(parser.getDegreeRadGrad());
    return format.formatResult(num);
}


bool Calculator::error()
{
    return parser.error();
}


bool Calculator::isValidExpression_ft(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidExpression_ft(expression);
}

bool Calculator::isValidExpression_fxt(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidExpression_fxt(expression);
}

bool Calculator::isValidExpression_fxt(const QString &expression, QString &variable)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidExpression_fxt(expression,variable);
}



bool Calculator::isValid_Expression_with_time_variable(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);

    //check if it's a valid expression
    if (parser.isValidExpression_fn(expression) == false)
        return false;

    //now let's check if it has a tima variable
    QStringList variables;
    parser.GrabVariables(expression,variables);

    for (int i = 0; i < variables.size(); i++)
    {
        if (variables[i] == "t")
            return true;
    }

    return false;
}


bool Calculator::isValidExpression_fn(const QString &expression)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidExpression_fn(expression);
}

bool Calculator::isValidExpression(const QString &expression)
{
    parser.SolveExpression(expression);
    return !parser.error();
}

MyNumber Calculator::isValidExpression(const QString &expression, bool &ok)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    MyNumber number = parser.SolveExpression(expression);
    ok = !parser.error();
    return number;
}


bool Calculator::isValidEquation(const QString &equation)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidEquation(equation);
}

bool Calculator::isValidEquation_Explicit_From_Constant(const QString &equation)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidEquation_Explicit_From_Constant(equation);
}

bool Calculator::isValidEquation_Explicit_From_Constant(const QString &equation, QString &variable_, MyNumber &value_)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidEquation_Explicit_From_Constant(equation, variable_, value_);
}

bool Calculator::isValidEquation_Explicit_From_Variables(const QString &equation)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidEquation_Explicit_From_Variables(equation);
}

bool Calculator::isValidEquation_Explicit_From_Variables(const QString &equation,
                                                         QString &first_member, QString &second_member)
{
    //parser.setDegreeRadGrad(Degree_Rad_Grad);
    return parser.isValidEquation_Explicit_From_Variables(equation, first_member, second_member);
}


bool Calculator::isValidMatrixGuiVarible(const QString &matrixVariable_)
{

    QStringList aux = matrixVariable_.split("=");

    if (aux.size() != 2)
        return false;

    QString matrix = aux[1];
    matrix.remove(" ").toLower();

    if (aux[1] != "matrix")
        return false;

    QStringList auxVariables;
    if (GrabVariables(aux[0], auxVariables) != 1)
        return false;

    return true;
}



///////////////////////////////////
// Formulas

void Calculator::addFormula()
{
    Formulas formula(&parser);
    m_formulasList.append(formula);
}

void Calculator::removeFormula(int index)
{
    if ( (index >= 0) && (index < m_formulasList.size()) )
        m_formulasList.removeAt(index);
}



void Calculator::setDegreeRadGrad(const int &isDegreeRadGrad_)
{
    parser.setDegreeRadGrad(isDegreeRadGrad_);
}

int Calculator::getDegreeRadGrad()
{
    return parser.getDegreeRadGrad();
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


void Calculator::addVariableValue(QString variable_, MyNumber value_)
{

    int index = variables_List.indexOf(variable_,0);
    if (index != -1)
    {
        variables_List[index] = variable_;
        values_List[index] = value_;
    }
}

void Calculator::addVariableValue(QString variable_, QString value_)
{
    int index = variables_List.indexOf(variable_,0);
    if (index != -1)
    {
        variables_List[index] = variable_;
        values_List[index] = parser.SolveExpression(value_);
    }
}



void Calculator::addFunction(const myFunction &function_)
{

    for (int i = 0; i < m_FunctionsList.size(); i++)
    {
        if ( (m_FunctionsList[i].GetfunctionName() == function_.GetfunctionName())
             && (m_FunctionsList[i].GetNumberVariables() == function_.GetNumberVariables() ) )
        {
            QString aux = function_.GetFunctionDefinition();
            m_FunctionsList[i].SetFunction( aux ) ;

            return;
        }

    }

    m_FunctionsList.append(function_);

}


//QString Calculadora::f_replace_UserDefinedFunction(QString &f, QList<myFunction> list_functions)
QString Calculator::Expression_Replace_User_Defined_Function(QString &expression_)
{

    QString str_aux;
    int ii;


    for(int i=0;i<expression_.size();i++)
    {
        ii=i;
        str_aux="";
        //str_aux=SacaFuncao(f,i);
        parser.grabFunction_or_Variable_userdefined(expression_ , i, str_aux);

        for(int l=0;l<m_FunctionsList.size() && str_aux !="" ;l++)
        {
            //if is the user definer function 'f'
            if (str_aux == m_FunctionsList[l].GetfunctionName())
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
                if (arguments.size() == m_FunctionsList[l].GetNumberVariables())
                {
                    QString function_aux = m_FunctionsList[l].GetFunction();
                    QStringList variables_aux = m_FunctionsList[l].GetVariables();

                    QString new_function =  parser.expression_replace_variables_with_values(function_aux,
                                                   variables_aux, arguments);



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


  /*
    QString str_aux;
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














