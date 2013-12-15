#ifndef FORMULAS_H
#define FORMULAS_H

#include <QStringList>
#include "parser.h"


class Formulas
{
public:
    //Formulas();
    Formulas(Parser *parser_);
    ~Formulas();


    void setFormula(const QString &formula_){m_formula = formula_;}
    void setDescription(const QString &descripton_){m_description = descripton_;}
    void calculateConstants();

    // Note:setConstantsFromSerialization() should only be used for serialization in QDataStream,
    // constants should be set from calculateConstants();
    void setConstantsFromSerialization(const QStringList &constants_){m_constants = constants_;}

    void setValues(const QStringList &values_){m_values = values_;}
    void setMin(const QString &min_){m_min = min_;}
    void setMax(const QString &max_){m_max = max_;}
    void setDelta(const QString &delta_){m_delta = delta_;}
    void setPrecision(const QString &precision_){m_precision = precision_;}
    void setSolution(const QList<Complexo> &solution_){m_solution = solution_;}//only for stream from file

    QString getFormula()const{return m_formula;}
    QString getDescription()const{return m_description;}
    QStringList getConstants()const{return m_constants;}
    QStringList getValues()const{return m_values;}
    QString getMin()const{return m_min;}
    QString getMax()const{return m_max;}
    QString getPrecision()const{return m_precision;}
    QString getDelta()const{return m_delta;}

    QList<Complexo> solve();
    QList<Complexo> getSolution()const{return m_solution;}

private:
    QString m_formula;
    QString m_description;
    QStringList m_constants;
    QStringList m_values;
    QString m_min;
    QString m_max;
    QString m_precision;
    QString m_delta;
    QList<Complexo> m_solution;

    Parser *parser;
    //bool parserAllocated;

};


QDataStream & operator<< (QDataStream& stream, const Formulas& formula_);
QDataStream & operator>> (QDataStream& stream, Formulas& formula_);


#endif // FORMULAS_H
