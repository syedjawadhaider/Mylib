/* 
 * File:   Peer.h
 * Author: Jawad Haider
 *
 * Created on March 19, 2020, 10:32 AM
 */

#ifndef PEER_H
#define	PEER_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

class Peer : public QObject
{
    public:
        Peer();
        ~Peer();
        QHostAddress GetIP();
        void SetIP(QString);
        int  GetPort();
        void SetPort(int);
        void SetTcpSocket(QTcpSocket*);
        QTcpSocket* GetTcpSocket();
        
    public slots:
        void OnReadDataFromSocket();
        void OnSocketStateChanged(QAbstractSocket::SocketState);
        
    private:
        QHostAddress m_pPeerIP;
        int m_pPeerPort;
        QTcpSocket *m_pPeerTcpSocket;
};


#endif	/* PEER_H */

