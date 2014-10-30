#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QNetworkReply>
#include <QFile>

class NetworkReply : public QNetworkReply
{
    Q_OBJECT

public:


    explicit NetworkReply(const QNetworkRequest& request, QIODevice* outgoingData, QObject* parent = 0);

    void abort();
    qint64 bytesAvailable() const;
    bool isSequential() const;

public slots:
    void dataAvailable();

protected:
    qint64 readData(char* data, qint64 maxSize);

private:
    QString m_path;
    QFile m_file;

signals:
    void signalDataAvailable();

};

#endif // NETWORKREPLY_H
