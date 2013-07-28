#ifndef FORMATRESULT_H
#define FORMATRESULT_H

#include <QString>
#include <QStringList>
#include "complexo.h"


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


    //QString formatResult(const Complexo &z, bool bAutomaticPrecision, int precision, char format, bool bGroup);
    QString formatResult( const Complexo &z);
    //QString formatResult( const Complexo &z, const int &precision);

private:
    QString groupDigits(const QString &str, const bool &bGroup);
    bool bAutomaticPrecision;
    int precision;
    char format;
    bool bGroup;

};


#endif // FORMATRESULT_H
