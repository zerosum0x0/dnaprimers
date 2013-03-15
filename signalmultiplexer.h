#ifndef SIGNALMULTIPLEXER_H
#define SIGNALMULTIPLEXER_H

#include <QObject>
#include <QPointer>

class SignalMultiplexer : public QObject
{
    Q_OBJECT

public:
    SignalMultiplexer(QObject *parent = 0, const char *name = 0);

    void connect(QObject *sender, const char *signal, const char *slot);
    bool disconnect(QObject *sender, const char *signal, const char *slot);
    void connect(const char *signal, QObject *receiver, const char *slot);
    bool disconnect(const char *signal, QObject *receiver, const char *slot);

    QObject *currentObject() const { return object; }

public slots:
    void setCurrentObject(QObject *newObject);

private:
    struct Connection
    {
        QPointer<QObject> sender;
        QPointer<QObject> receiver;
        const char *signal;
        const char *slot;
    };

    void connect(const Connection &conn);
    void disconnect(const Connection &conn);

    QPointer<QObject> object;
    QList<Connection> connections;

};

class DocumentObject
{
public:
    /*virtual*/  DocumentObject() {}
    virtual void emitAllSignals() = 0;
};

#endif // SIGNALMULTIPLEXER_H
