#include "SocketManager.h"
#include <QtNetwork/QNetworkInterface>

SocketManager* SocketManager::m_pObject = NULL;

SocketManager::SocketManager(){
    m_pObject = this;
    m_pMainNodeIP = "192.168.100.22";
    m_pListenHostPort = 8081;
    m_pMaxPeers = 0;
    
    QList<QHostAddress> listHostIP = QNetworkInterface::allAddresses();

    for(int i=0; i<listHostIP.count(); i++){
        if(!listHostIP[i].isLoopback())
          if (listHostIP[i].protocol() == QAbstractSocket::IPv4Protocol ){
                m_pHostNodeIP = listHostIP[i].toString();
                break;
          }
     }
    m_pPeerManager = new PeerManager();
    m_pListenSocket = new QTcpServer();
    connect(m_pListenSocket, SIGNAL(newConnection()), this, SLOT(ReceiveNewConnectionRequest()));
}

SocketManager::~SocketManager(){

}

int SocketManager::GetMaxPeers() const {
    return m_pMaxPeers;
}

SocketManager * SocketManager::GetSocketManager() {
    return m_pObject;
}


void SocketManager :: ListenOnHost(){

    if(m_pHostNodeIP != m_pMainNodeIP)
    {
        SendConnectionRequest((QHostAddress)m_pMainNodeIP, m_pListenHostPort);
    }
    
    qDebug () <<"*************************************************************";
    qDebug() <<"*  Listening on  Host IP:"<<m_pHostNodeIP << "         *";
    qDebug () <<"*************************************************************";
    m_pListenSocket->listen((QHostAddress)m_pHostNodeIP ,m_pListenHostPort);
}

void SocketManager::SendConnectionRequest(QHostAddress ip,int port)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost(ip,port);
    if(socket->waitForConnected(3000)){
        m_pPeerManager->AddNewPeer(socket);
    }
    else{
        qDebug() << "Connection Failed ====================";
    }
}

void SocketManager :: ReceiveNewConnectionRequest(){
    QTcpSocket *clientSocket=m_pListenSocket->nextPendingConnection();
    m_pPeerManager->AddNewPeer(clientSocket);
}
