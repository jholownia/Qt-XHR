#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QNetworkReply>

class NetworkReply : public QNetworkReply
{
public:
    explicit NetworkReply(const QNetworkRequest& request, QIODevice* outgoingData, QObject* parent = 0);

protected:
    void abort();
    qint64 readData(char* data, qint64 maxSize);
};

#endif // NETWORKREPLY_H
