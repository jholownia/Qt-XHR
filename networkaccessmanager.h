#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit NetworkAccessManager(QNetworkAccessManager* manager, QObject *parent = 0);

public slots:
    virtual QNetworkReply* createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
};

#endif // NETWORKACCESSMANAGER_H
