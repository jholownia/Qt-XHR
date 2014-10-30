#include "networkreply.h"

#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <QBuffer>


NetworkReply::NetworkReply(const QNetworkRequest &request, QIODevice *outgoingData, QObject *parent) :
    m_path(request.url().path()),
    m_device(nullptr)
{
    // Set default path to index.html if no file name is provided
    m_path += (m_path[m_path.size() - 1] == '/') ? "index.html" : "";

    // Check for Test-Header
    if (request.hasRawHeader("Test-Header"))
    {
        qDebug() << "[Qt] Received request with Test-Header value: " << request.rawHeader("Test-Header");

        // Set Test-Header for this reply to the same value as the request
        this->setRawHeader("Test-Header", request.rawHeader("Test-Header"));
    }

    // If it's an existing file, just open it and make data available
    if (QFile::exists("." + m_path))
    {
        QFile file("." + m_path);

        if (!file.open(QFile::ReadOnly))
        {
            qCritical() << file.errorString();
            return;
        }

        m_data = file.readAll();

        m_device.reset(new QBuffer(&m_data));
        m_device->open(QIODevice::ReadOnly);

        QTimer::singleShot(0, this, SLOT(dataAvailable()));
    }
    else
    {
        // Spawn a worker thread to make calculations, setData() slot will be called when it's done
        if (m_path == "/test.php" && request.hasRawHeader("Test-Header"))
        {
            Worker* worker = new Worker;
            worker->moveToThread(&m_workerThread);

            connect(&m_workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
            connect(this, SIGNAL(signalWorkerRun(int)), worker, SLOT(doWork(int)));
            connect(worker, SIGNAL(signalResultReady(QByteArray)), this, SLOT(setData(QByteArray)));

            m_workerThread.start();

            emit signalWorkerRun(request.rawHeader("Test-Header").toInt());
        }
    }
}

NetworkReply::~NetworkReply()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void NetworkReply::dataAvailable()
{
    if (!m_device.isNull())
    {
        open(ReadOnly | Unbuffered);

        // Guess the ContentType
        QFileInfo fileInfo(m_path);
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

        qint64 size = m_device->size();
        qDebug() << "Loading: " << m_path << " Size: " << size;
        setHeader( QNetworkRequest::ContentLengthHeader, QVariant(size));

        emit readyRead();
        emit finished();
    }
}

void NetworkReply::setData(QByteArray data)
{
    m_data = data;
    m_device.reset(new QBuffer(&m_data));
    m_device->open(QIODevice::ReadOnly);

    dataAvailable();
}

void NetworkReply::abort()
{

}

qint64 NetworkReply::bytesAvailable() const
{
    return m_device->bytesAvailable() + QNetworkReply::bytesAvailable();
}

bool NetworkReply::isSequential() const
{
    return true;
}

qint64 NetworkReply::readData(char *data, qint64 maxSize)
{
    qint64 length = m_device->read( data, maxSize );
    return length;
}
