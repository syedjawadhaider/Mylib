/* 
 * File:   SocketManager.h
 * Author: Jawad Haider
 *
 * Created on March 19, 2020, 10:28 AM
 */

#ifndef SOCKETMANAGER_H
#define	SOCKETMANAGER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include "PeerManager.h"

class SocketManager : public QObject
{
    Q_OBJECT 
    
    public:
        SocketManager();
        ~SocketManager();
        static SocketManager *GetSocketManager();
        int GetMaxPeers() const;
        void ListenOnHost();
        void SendConnectionRequest(QHostAddress, int);
        
        PeerManager *m_pPeerManager;
        
    public slots:
        void ReceiveNewConnectionRequest();
        
    private:
        static SocketManager *m_pObject;
        int m_pMaxPeers;
        QString m_pMainNodeIP;
        QString m_pHostNodeIP;
        int m_pListenHostPort;
        QTcpServer *m_pListenSocket;
            
};

#endif	/* SOCKETMANAGER_H */

