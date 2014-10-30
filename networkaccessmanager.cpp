#include "networkaccessmanager.h"
#include "networkreply.h"

#include <QNetworkProxy>
#include <QDebug>


NetworkAccessManager::NetworkAccessManager(QNetworkAccessManager* manager, QObject* parent) :
    QNetworkAccessManager(parent)
{    
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());
}

QNetworkReply *NetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    if( request.url().host() == "test" )
    {
        NetworkReply* nr = new NetworkReply(request, outgoingData);
        qDebug() <<  nr->rawHeader("Test-Header");
        return nr;
    }

    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
