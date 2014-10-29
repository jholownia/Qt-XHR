#include "networkreply.h"

#include <QDebug>


NetworkReply::NetworkReply(const QNetworkRequest &request, QIODevice *outgoingData, QObject *parent)
{
    qDebug() << "Request header: " << request.rawHeader("My-Header");
}

void NetworkReply::abort()
{

}

qint64 NetworkReply::readData(char *data, qint64 maxSize)
{
    return 10;
}
