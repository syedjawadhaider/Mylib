/* 
 * File:   PeerManager.h
 * Author: Jawad Haider
 *
 * Created on March 19, 2020, 10:31 AM
 */

#ifndef PEERMANAGER_H
#define	PEERMANAGER_H

#include "Peer.h"

class PeerManager
{
    public:
        PeerManager();
        ~PeerManager();
        void AddNewPeer(QTcpSocket*);
        void RemovePeer(QHostAddress);
        void SendPeers(QTcpSocket *);
        bool ConnectedPeers(QHostAddress);
        
    private:
        QList<Peer*> m_pPeersList;
        
};

#endif	/* PEERMANAGER_H */

