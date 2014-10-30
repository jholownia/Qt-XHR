#include "networkreply.h"

#include <QDebug>
#include <QFileInfo>
#include <QTimer>


NetworkReply::NetworkReply(const QNetworkRequest &request, QIODevice *outgoingData, QObject *parent)
{
    qDebug() << "Request header: " << request.rawHeader("My-Header");

    QObject::connect(this, SIGNAL(signalDataAvailable()), this, SLOT(dataAvailable()));

    m_path = "." + request.url().path();
    m_path += (m_path[m_path.size() - 1] == '/') ? "index.html" : "";

    m_file.setFileName(m_path);
    if (!m_file.open(QFile::ReadOnly))
    {
        qDebug() << m_file.errorString();
    }

    //QTimer::singleShot(0, this, SLOT(dataAvailable()));

    dataAvailable();
}

void NetworkReply::dataAvailable()
{
    if (m_file.isOpen())
    {
        open(ReadOnly | Unbuffered);

        // Guess the ContentType
        QFileInfo fileInfo(m_file);
        QString extension = fileInfo.suffix();
        QVariant mimeType("text/plain");

        if( extension == "html")
            mimeType = "text/html";
        else if( extension == "json")
            mimeType = "application/json";
        else if( extension == "js")
            mimeType = "application/javascript";
        else if( extension == "css")
            mimeType = "text/css";
        else if( extension == "php")
            mimeType = "application/json";

        setHeader( QNetworkRequest::ContentTypeHeader, mimeType );

        qint64 file_size = m_file.size();
        qDebug() << "Path: " << m_path << " Length: " << file_size;
        setHeader( QNetworkRequest::ContentLengthHeader, QVariant(file_size));

        emit readyRead();
        emit finished();
    }
}

void NetworkReply::abort()
{

}

qint64 NetworkReply::bytesAvailable() const
{
    return m_file.bytesAvailable() + QNetworkReply::bytesAvailable();
}

bool NetworkReply::isSequential() const
{
    return true;
}

qint64 NetworkReply::readData(char *data, qint64 maxSize)
{
    qint64 length = m_file.read( data, maxSize );
    return length;
}
