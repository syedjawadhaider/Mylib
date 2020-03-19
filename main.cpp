/*
 * File:   main.cpp
 * Author: root
 *
 * Created on March 19, 2020, 10:24 AM
 */

#include <QCoreApplication>
#include "SocketManager.h"

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QCoreApplication app(argc, argv);

    SocketManager *m_pSocketManager = new SocketManager();
    m_pSocketManager->ListenOnHost();

    // create and show your widgets here

    return app.exec();
}
