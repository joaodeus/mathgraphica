#include "formulas.h"

#include "equation.h"
//#include <QDebug>


//Formulas::Formulas()
//{
    //if an object of myfunctions is instaciated with this constructor
    //let's garantee that parser is allocated, to avoid a memory crash
    //when using SetFunction(....)
//    parserAllocated = true;
  //  parser = new Parser;
//}


Formulas::Formulas(Parser *parser_)
{
    //parserAllocated = false;
    parser          = parser_;

    //m_formula   = "En=m*C^2";
    m_min       = "-1E6";
    m_max       = "1E6";
    m_delta     = "0.1";
    m_precision = "0.000001";
    //m_constants <<"En"<<"m"<<"C";
    //m_values    <<"5000"<<"?"<<"3E8";

}

Formulas::~Formulas()
{
    m_constants.clear();
    m_values.clear();

  //  if (parserAllocated)
    //    delete parser;
}

QList<Complexo> Formulas::solve()
{
    //qDebug()<<"Solve: \n"<<m_formula;
    QString expression;
    expression = parser->Expression_ReplaceVariables_WithValues(m_formula, m_constants, m_values);
    //qDebug()<<expression;
    expression.replace("?","x");
    //qDebug()<<expression;

    Equation equation(parser);

    equation.setEquation(expression);
    equation.setLimits(m_min, m_max);
    equation.setDelta(m_delta);
    equation.setPrecision(m_precision);
    m_solution = equation.solveEquation(expression);

    return m_solution;

}

void Formulas::calculateConstants()
{
    parser->GrabVariables(m_formula, m_constants);

    //set size of values equal to constants
    //if (m_values.size() < m_constants.size())
    //{
    for (int i = m_values.size(); i < m_constants.size() ;i++ )
    {
        m_values.append("");
    }

        //}

}

QDataStream & operator<< (QDataStream& stream, const Formulas& formula_)
{
    stream<<formula_.getFormula();
    stream<<formula_.getDescription();
    stream<<formula_.getConstants();
    stream<<formula_.getValues();
    stream<<formula_.getMin();
    stream<<formula_.getMax();
    stream<<formula_.getDelta();
    stream<<formula_.getPrecision();
    stream<<formula_.getSolution();

    return stream;
}

QDataStream & operator>> (QDataStream& stream, Formulas& formula_)
{
    QString formula;
    QString description;
    QStringList constants;
    QStringList values;
    QString min;
    QString max;
    QString precision;
    QString delta;
    QList<Complexo> solution;

    stream>>formula;    formula_.setFormula(formula);
    stream>>description;formula_.setDescription(description);
    stream>>constants;  formula_.setConstantsFromSerialization(constants);
    stream>>values;     formula_.setValues(values);
    stream>>min;        formula_.setMin(min);
    stream>>max;        formula_.setMax(max);
    stream>>precision;  formula_.setPrecision(precision);
    stream>>delta;      formula_.setDelta(delta);
    stream>>solution;   formula_.setSolution(solution);

    return stream;
}
