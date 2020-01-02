//
// Created by kir on 29.12.2019.
//

#ifndef ENERGO_TCPSERVER_H
#define ENERGO_TCPSERVER_H

#include <atomic>
#include <functional>
#include <memory>
#include <optional>
#include "TcpSocket.h"

namespace energo::net {

/**
 * Сервер для TCP входящих подключений.
 */
class TcpServer : public TcpSocket {
    net::ConnectionPoint _connectionPoint;
    std::atomic_bool _run;
    std::optional<std::function<void(std::shared_ptr<TcpSocket>)>> _connectionReadyListener;
    
public:
    TcpServer();
    ~TcpServer();
    
    /**
     * Связывает сервер с указанной точкой подключения на локальной машине.
     * @param connectionPoint Точка подключения на локальной машине. Порт, который будет слушать сервер и подсеть от которой будут ожидаться подключения.
     * @return
     */
    [[nodiscard]] bool bind(const net::ConnectionPoint &connectionPoint);
    
    /**
     * Запускает поток для ожидания входящих подключений. Поток завершится, если не установлен метод, обрабатывающий входящие подключения.
     * @throws NetException - не установлен с помощью onConnectionReadyListener метод, обрабатывающий входящие подключения.
     */
    void listen();
    
    void close();
    
    void onConnectionReadyListener(const std::optional<std::function<void(std::shared_ptr<TcpSocket>)>> &listener);

private:
    void listenProc();
};

}

#endif //ENERGO_TCPSERVER_H
