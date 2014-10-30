#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QByteArray>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject* parent = 0) {}
    ~Worker() {}

public slots:
    void doWork(int limit)
    {
        std::vector<bool> primes(limit + 1, true);
        sieve(primes);

        QByteArray result = "{ \"primes\": [2";

        for (int i = 3; i <= limit; ++i)
        {
            if (primes[i])
            {
                result.append("," + QString::number(i));
            }
        }

        result.append("]}");

        emit signalResultReady(result);
    }

signals:
    void signalResultReady(QByteArray data);

private:
    void sieve(std::vector<bool>& primes)
    {
        primes[0] = primes[1] = false;

        for (unsigned int i = 2; i * i < primes.size(); ++i)
        {
            if (primes[i])
            {
                for (unsigned int k = i * i; k < primes.size(); k+= i)
                {
                    primes[k] = false;
                }
            }
        }
    }
};


#endif // WORKER_H
