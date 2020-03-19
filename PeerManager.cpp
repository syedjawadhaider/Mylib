#include "PeerManager.h"

PeerManager::PeerManager(){

}

PeerManager::~PeerManager(){

}

void PeerManager::AddNewPeer(QTcpSocket* tcpSocket)
{
    QString tempString;
    tempString=tcpSocket->peerAddress().toString();
    Peer *peerNew = new Peer();    
    peerNew->SetIP(tempString);
    peerNew->SetPort(tcpSocket->peerPort());
    peerNew->SetTcpSocket(tcpSocket);
    m_pPeersList.append(peerNew);
    qDebug () <<"*************************************************************";
    qDebug () <<"Connected" << tcpSocket->peerAddress().toString() <<" :: "<<tcpSocket->peerPort();
    qDebug () <<"*************************************************************";
    tcpSocket->write("peers");
    tcpSocket->flush();
}

void PeerManager::SendPeers(QTcpSocket *readSocket){
    QString tempString;
    qDebug () <<"Peer connected size :=>"<<m_pPeersList.size();
    
    for(int i = 0; i < m_pPeersList.count(); i++)
    {
        if(readSocket->peerAddress()!= m_pPeersList.at(i)->GetIP()){
            tempString = m_pPeersList.at(i)->GetIP().toString();
            tempString+=",";
            readSocket->write(tempString.toLocal8Bit());
            readSocket->flush();
            tempString.clear();
        }
    }
}

bool PeerManager::ConnectedPeers(QHostAddress ip){

    for(int i = 0; i < m_pPeersList.count(); i++){
        if(m_pPeersList.at(i)->GetIP() == ip){
            return false;
        }
    }
    return true;
}

void PeerManager::RemovePeer(QHostAddress peerIP)
{
    qDebug() <<"__________________________";
    qDebug() <<"Peer Disconnected";
    qDebug() <<"IP:"<<peerIP.toString();

    for(int i = 0; i < m_pPeersList.count(); i++){
        if(m_pPeersList.at(i)->GetIP() == peerIP){
            m_pPeersList.removeAt(i);
            qDebug() <<"Removed";
            qDebug() << "Total connected Peers" <<m_pPeersList.count();
            qDebug() <<"__________________________";
            return;
        }
    }
}
