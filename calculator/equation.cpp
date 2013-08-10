#include "equation.h"

Equation::Equation(Parser *parser_)
{
    parser = parser_;
    flagCalculationEquation=false;
    flagAbortFunction=false;

    min = -1E6;
    minExpression = "-1E6";
    max = 1E6;
    maxExpression = "1E6";
    delta = 0.1;
    deltaExpression = "0.1";
    precision = 1E-6;
    precisionExpression = "1E-6";
    m_f1 = "4x+3";
    m_f2 = "2x^2-3";
    m_equation = "4x+3=2x^2-3";

}


void Equation::setLimits(const double &min_, const double &max_)
{
    min = min_;
    minExpression = QString("%1").arg(min);
    max = max_;
    maxExpression = QString("%1").arg(max);
}

void Equation::setLimits(const QString &minExpression_, const QString &maxExpression_)
{
    minExpression = minExpression_;
    min = parser->SolveExpression(minExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid min value."));
    }

    maxExpression = maxExpression_;
    max = parser->SolveExpression(maxExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid max value."));
    }

}

void Equation::setPrecision(const double &precision_)
{
    precision = precision_;
    precisionExpression = QString("%1").arg(precision_);
}

void Equation::setPrecision(const QString &precisionExpression_)
{
    precisionExpression = precisionExpression_;
    precision = parser->SolveExpression(precisionExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid precision"));
    }

}

void Equation::setDelta(const double &delta_)
{
    delta = delta_;
    deltaExpression = QString("%1").arg(delta);
}

void Equation::setDelta(const QString &deltaExpression_)
{
    deltaExpression = deltaExpression_;
    delta = parser->SolveExpression(deltaExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid search delta"));
    }
}

void Equation::setEquation(const QString &equation_)
{
    QStringList aux = equation_.split("=");
    if (aux.size() == 2)
    {
        m_equation = equation_;
        m_f1 = aux[0];
        m_f2 = aux[1];
    }

}

QList<Complexo> Equation::solveEquation(const QString &equation)
{
    QStringList aux = equation.split("=");
    if (aux.size() != 2)
    {
        equation_solutions.clear();
        return equation_solutions;
    }
    else
    {
        m_equation = equation;
        return solveEquation(aux[0],aux[1]);
    }
}


QList<Complexo> Equation::solveEquation(const QString &f1, const QString &f2)
{

    m_f1 = f1;
    m_f2 = f2;
    double initial_delta = delta;

    //double incremento_maximo=incremento; //debug porpuse
    //double incremento_minimo=incremento; //debug porpuse

    equation_solutions.clear(); //clear all previous solutions because we will start a solution search

    //----------------------------------------------------------------------------
    //this if will optimize the search
    //if the expression is of the type 'x=0' or 'x=3+7' it will skip the search and do the assignment

    if (parser->isValidEquation_Explicit_From_Constant(f1+"="+f2))
    {
        bool ok;
        Complexo y;
        y.r = f2.toDouble(&ok);
        if (ok) //if f2 is a number e.g. '7' save the solution
        {
            equation_solutions.append(y);  //save the solution
            return equation_solutions;
        }
        else  // f2 is a expresion e.g '3+7'
        {
            y = parser->SolveExpression(f2).numberComplexo(); //y=f(f2); // then calculate it
            equation_solutions.append(y);  // save the solution
            return equation_solutions;
        }
    }
    //---------------------------------------------------------------------


    QStringList variablesList;
    if (parser->GetVariables(f1+"="+f2, variablesList) != 1)
        return equation_solutions;

    QString variable = variablesList.at(0);

    double fa = parser->SolveExpression_fx(f1,min,variable).numberReal();
    double fb = parser->SolveExpression_fx(f2,min,variable).numberReal();

    //QList<double> faxx;
    //QList<double> fayy;
    //QList<double> fbxx;
    //QList<double> fbyy;


    flagCalculationEquation=true;
    flagAbortFunction=false;

    double l;
    double fa1;
    double fb1;
    double da;
    double db;
    double dab;
    double dab1;

    for(double i=min ; i<=max ; i+=delta)
    {
        l   = i + delta;
        fa1 = parser->SolveExpression_fx(f1,l,variable).numberReal();
        fb1 = parser->SolveExpression_fx(f2,l,variable).numberReal();

        // aux variables to draw debug graphs--------------------
       // faxx.append(i);
       // fayy.append(fa1);

      //  fbxx.append(i);
      //  fbyy.append(fb1);
     //------------------------------------------------------------

        QCoreApplication::processEvents();

        if (flagAbortFunction)
        {
            flagCalculationEquation=false;
            return equation_solutions;
        }

        /////evita funçoes trigonometrica com muitas soluçoes
      //  if (solucoes_equacao.size()>10)
      //  {
         //   str.sprintf("maximo=%lf\nminimo=%lf\ncontador=%d",incremento_maximo,incremento_minimo,contador);
         //   QMessageBox::about(0,"",str);
          //  return 10;
        //}



        /////incremento dinamico/////////////////////////
        //contador++;
        da=fabs(fa1-fa);
        db=fabs(fb1-fb);
        dab=fabs(fa-fb);
        dab1=fabs(fa1-fb1);


        if (da < db)
            da=db;

        if (dab < dab1)
            dab=dab1;

        if (da < 0.2*dab)
            delta += delta*0.05;//5%
        else
        {
            delta = initial_delta;
            //if (incremento > 0.1*incremento_inicial) //10%
            //    incremento=incremento-incremento*0.1;//10%
        }
        ////////////////////////////////////////////////




        //---------------------------------------------------
        //uncomment the next four lines for debug porpuse
        //if (incremento > incremento_maximo)
        //    incremento_maximo=incremento;

        //if (incremento < incremento_minimo)
        //      incremento_minimo=incremento;
        //---------------------------------------------------



        //check if there is a complex(imaginary) solution when the real part is zero
       /* if ( (l < 0) && ( (l+incremento)>0 ) )
        {
            if ( cabs( fx(f1,0,x) - fx(f2,0,x) )  < precisao )
            {
                solucoes_equacao.append(0);
            }
        }
*/




        if (fb >= fa)
        {
            if (fb1 <= fa1)
                root_finder(parser, f1, f2, variable, i, l, precision);
                //equacao_resolve(f1,f2,x,i,l,precisao);
        }
        else
        {
            if (fa1 < fb1)
                root_finder(parser, f1, f2, variable, i, l, precision);
                //equacao_resolve(f1,f2,x,i,l,precisao);
        }
        fa=fa1;
        fb=fb1;
    }

    flagCalculationEquation=false;


    //---graph for debug porpuse-------------------------------
/*
    GLGraph *graph_fa = new GLGraph();
    GLGraph *graph_fb = new GLGraph();


    graph_fa->SetGraph2D(faxx,fayy);
    graph_fa->showNormal();
    graph_fa->updateGL();

    graph_fb->SetGraph2D(fbxx,fbyy);
    graph_fb->showNormal();
    graph_fb->updateGL();
*/
    //-------------------------------------------------------------------



  //  str.sprintf("maximo=%lf\nminimo=%lf\ncontador=%d",incremento_maximo,incremento_minimo,contador);
  //  QMessageBox::about(0,"",str);

    return equation_solutions;
}


double Equation::root_finder(Parser *p, QString f1, QString f2, QString variable,
                             double a, double b, double precision)
{
    //Complexo fa=fx(f1,a,x);
    //Complexo fb=fx(f2,a,x);
    Complexo fa = p->SolveExpression_fx(f1,a,variable).numberComplexo();
    Complexo fb = p->SolveExpression_fx(f2,a,variable).numberComplexo();


    double d = (a+b)/2;
    Complexo fda = p->SolveExpression_fx(f1,d,variable).numberComplexo();
    Complexo fdb = p->SolveExpression_fx(f2,d,variable).numberComplexo();
//    Complexo fda=fx(f1,d,x);
  //  Complexo fdb=fx(f2,d,x);


    if (fda == fdb)
    {
        equation_solutions.append(d);
        return 1;
    }


    //double zzz = cabs(fda-fdb);
    if ( fabs(fda.r-fdb.r) <= precision)
    {
        if (cabs(fda-fdb)<=precision) // this is for the imaginary part
            equation_solutions.append(d);
        return 1;
    }


    if (fa.r > fb.r)
    {
        if (fda.r > fdb.r)
            return root_finder(p,f1,f2,variable,d,b,precision);
        else
            return root_finder(p,f1,f2,variable,a,d,precision);
    }
    else
    {
        if (fdb.r > fda.r)
            return root_finder(p,f1,f2,variable,d,b,precision);
        else
            return root_finder(p,f1,f2,variable,a,d,precision);
    }

}
