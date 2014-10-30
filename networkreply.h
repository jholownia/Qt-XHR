#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QNetworkReply>
#include <QThread>
#include <QFile>

#include "worker.h"


class NetworkReply : public QNetworkReply
{
    Q_OBJECT

public:
    explicit NetworkReply(const QNetworkRequest& request, QIODevice* outgoingData, QObject* parent = 0);
    ~NetworkReply();

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

public slots:
    void dataAvailable();
    void setData(QByteArray data);

signals:
    void signalDataAvailable();
    void signalRunWorker(int);

protected:
    qint64 readData(char* data, qint64 maxSize);

private:
    QString m_path;
    QByteArray m_data;
    QScopedPointer<QIODevice> m_device;
    QThread m_workerThread;

};

#endif // NETWORKREPLY_H
