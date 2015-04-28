#include "error.h"

Error::Error()
{
}

void Error::setError(const bool &error_, const QString &errorMessage_)
{
    if (m_errorMessage != errorMessage_)
        m_errorMessage = errorMessage_;

    if (m_error != error_)
    {
        m_error = error_;
        if (error_) //emit error if its true
        {
            emit errorFired(error_);
            emit errorMessageFired(errorMessage_);
        }
    }
}

bool Error::getError()
{
    return m_error;
}

QString Error::errorMessage()
{
    return m_errorMessage;
}
