#ifndef ERROR_H
#define ERROR_H

#include <QObject>
#include <QString>

class Error : public QObject
{
    Q_OBJECT
public:
    Error();

    static Error& getInstance()
    {
        static Error instance;
        return instance;
    }

    Error (Error const&) = delete;
    Error& operator = (Error const&) = delete;

    void setError(const bool &error_, const QString &errorMessage_ = "");
    bool getError();
    QString errorMessage();
signals:
    void errorFired(bool error_);
    void errorMessageFired(QString errorMessage_);

private:
    bool m_error;
    QString m_errorMessage;

};

#endif // ERROR_H
