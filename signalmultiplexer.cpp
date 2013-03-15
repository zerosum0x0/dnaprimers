#include "signalmultiplexer.h"

SignalMultiplexer::SignalMultiplexer(QObject *parent, const char *name) :
    QObject(parent)
{
}

void SignalMultiplexer::connect(QObject *sender, const char *signal, const char *slot)
{
    Connection conn;
    conn.sender = sender;
    conn.signal = signal;
    conn.slot = slot;

    connections << conn;
    connect(conn);
}

void SignalMultiplexer::connect( const char *signal,
                 QObject *receiver,
                 const char *slot )
{
    Connection conn;
    conn.receiver = receiver;
    conn.signal = signal;
    conn.slot = slot;

    connections << conn;
    connect( conn );
}

bool SignalMultiplexer::disconnect(QObject *sender, const char *signal, const char *slot)
{
    QList<Connection>::Iterator it =
        connections.begin();
    for (; it != connections.end(); ++it)
    {
        Connection conn = *it;
        if ((QObject*)conn.sender == sender &&
             qstrcmp(conn.signal, signal) == 0 &&
                qstrcmp(conn.slot, slot) == 0)
        {
            disconnect(conn);
            connections.erase(it);
            return true;
        }
    }
    return false;
}

void SignalMultiplexer::connect(const Connection &conn)
{
    if (!object)
        return;
    if (!conn.sender && !conn.receiver)
        return;

    if (conn.sender)
        QObject::connect((QObject*)conn.sender, conn.signal, (QObject*)object, conn.slot);
    else
        QObject::connect((QObject*)object, conn.signal, (QObject*)conn.receiver, conn.slot);
}

void SignalMultiplexer::setCurrentObject(QObject *newObject)
{
    if (newObject == object)
        return;

    QList<Connection>::ConstIterator it;
    for (it = connections.begin(); it != connections.end(); ++it)
        disconnect(*it);

    object = newObject;

    for (it = connections.begin(); it != connections.end(); ++it)
        connect(*it);

    DocumentObject *document = dynamic_cast<DocumentObject*>(newObject);
    if (document)
        document->emitAllSignals();
}

void SignalMultiplexer::disconnect(const Connection &conn)
{
    if (!object)
        return;
    if (!conn.sender && !conn.receiver)
        return;

    if (conn.sender)
        QObject::disconnect((QObject*)conn.sender, conn.signal, (QObject*)object, conn.slot);
    else
        QObject::disconnect((QObject*)object, conn.signal, (QObject*)conn.receiver, conn.slot);
}


