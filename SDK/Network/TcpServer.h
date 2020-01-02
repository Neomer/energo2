//
// Created by kir on 29.12.2019.
//

#ifndef ENERGO_TCPSERVER_H
#define ENERGO_TCPSERVER_H

#include <thread>
#include "TcpSocket.h"

namespace energo::net {

class TcpServer : public TcpSocket {
    net::ConnectionPoint _connectionPoint;
    
    
    
public:
    /**
     * Связывает сервер с указанной точкой подключения на локальной машине.
     * @param connectionPoint Точка подключения на локальной машине. Порт, который будет слушать сервер и подсеть от которой будут ожидаться подключения.
     * @return
     */
    [[nodiscard]] bool bind(const net::ConnectionPoint &connectionPoint);
    
    void listen();
};

}

#endif //ENERGO_TCPSERVER_H
