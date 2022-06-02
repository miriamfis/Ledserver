#include "ledserver.h"
#include <QDebug>

LedServer::LedServer(quint16 port, QObject *parent) : QObject(parent), m_port(port)
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this,
            &LedServer::myNewConnection);
}

void LedServer::start()
{
    m_server->listen(QHostAddress::Any, m_port);
}

// Client hat Verbindung zum Server aufgebaut
void LedServer::myNewConnection()
{
    qDebug() << "Bitte Zahl von 0...15 eingeben: ";
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, &QTcpSocket::readyRead, this, &LedServer::myServerRead);
}

// Client hat Verbindung zum Server getrennt
void LedServer::myClientDisconnect()
{
    //m_socket->disconnectFromHost();
}

// Client hat eine Zahl (0...15) zum Server gesendet
void LedServer::myServerRead()
{
    QString zahl = m_socket->readAll();
    //qDebug() << "OK";
}
