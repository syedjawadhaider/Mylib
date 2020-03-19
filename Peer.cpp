#include "Peer.h"
#include "SocketManager.h"

Peer::Peer(){
    m_pPeerTcpSocket = new QTcpSocket();
    connect(m_pPeerTcpSocket,SIGNAL(readyRead()),this,SLOT(OnReadDataFromSocket()));
    connect(m_pPeerTcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(OnSocketStateChanged(QAbstractSocket::SocketState)));
}

Peer::~Peer(){
   
}

void Peer::SetIP(QString ip){
    m_pPeerIP.setAddress(ip);
}

void Peer::SetPort(int port){
    m_pPeerPort=port;
}

QHostAddress Peer::GetIP(){
    return m_pPeerIP;
}

int Peer::GetPort(){
    return m_pPeerPort;
}

void Peer::SetTcpSocket(QTcpSocket *tcpSocket)
{
    m_pPeerTcpSocket = tcpSocket;
}

QTcpSocket* Peer::GetTcpSocket()
{
    return m_pPeerTcpSocket;
}

void Peer::OnReadDataFromSocket()
{
    QByteArray buffer;
    QTcpSocket* readSocket = qobject_cast<QTcpSocket*>(sender());
    buffer.clear();
    buffer = readSocket->readAll();

    QString mytext = (QString::fromStdString(buffer.toStdString()).toLocal8Bit());
    QStringList connections;
    QHostAddress tempIp(mytext);
    if(mytext=="peers"){
        SocketManager::GetSocketManager()->m_pPeerManager->SendPeers(readSocket);
        mytext="";
    }
    else{
        QStringList list=mytext.split(",");
        for(int i=0;i<list.size();++i){
          if(QHostAddress(list[i])!= m_pPeerIP && SocketManager::GetSocketManager()->m_pPeerManager->ConnectedPeers(QHostAddress(list[i]))){
              SocketManager::GetSocketManager()->SendConnectionRequest(QHostAddress(list[i]),m_pPeerPort);
           }
        }
    }
}

void Peer::OnSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState){
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        SocketManager::GetSocketManager()->m_pPeerManager->RemovePeer(sender->peerAddress());
    }
}

