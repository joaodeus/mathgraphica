#ifndef FORMATRESULT_H
#define FORMATRESULT_H

#include <QString>
#include <QStringList>
#include "complexo.h"
#include "mynumber.h"


class FormatResult
{
public:
    FormatResult();

    //set all options at once
    void setFormatResult(const bool &bAutomaticPrecision_, const int &precision_, const char &format_, const bool &bGroup_);
    void setAutomaticPrecision(const bool &bAutomaticPrecision_);
    void setPrecision(const int &precision_);
    void setFormat(const char &format_);
    void setGroupDigits(const bool &bGroup_);
    void setPolarForm(const bool &bPolarForm_);

    bool getAutomaticPrecision();
    int  getPrecision();
    char getFormat();
    bool getGroup();
    bool getPolarForm();

    QString formatPolarForm(const Complexo &z);
    QString formatResult(const Complexo &z);
    QString formatResult(const double &x);
    QString formatResult(Matrix &matrix);
    QString formatResult(MyNumber &num);

    void setDegreeRadGrad(int &Degree_Rad_Grad_){Degree_Rad_Grad = Degree_Rad_Grad_;}
    int getDegreeRadGrad(){return Degree_Rad_Grad;}
private:
    int Degree_Rad_Grad;

    QString groupDigits(const QString &str, const bool &bGroup);
    bool bAutomaticPrecision;
    int precision;
    char format;
    bool bGroup;
    bool bPolarForm;

};


#endif // FORMATRESULT_H
