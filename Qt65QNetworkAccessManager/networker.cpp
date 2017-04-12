#include "networker.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

class NetWorker::Private
{
public:
    Private(NetWorker *q) : manager(new QNetworkAccessManager(q))
    {

    }

    QNetworkAccessManager *manager;
};

NetWorker * NetWorker::instance()
{
    static NetWorker instance;
    return &instance;
}

NetWorker::NetWorker(QObject *parent) : QObject(parent),d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished, this, &NetWorker::finished);
}

NetWorker::~NetWorker()
{
    delete d;
    d = Q_NULLPTR;
}

void NetWorker::get(const QString &url)
{
    d->manager->get(QNetworkRequest(QUrl(url)));
}
