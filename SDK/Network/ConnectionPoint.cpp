//
// Created by kir on 29.12.2019.
//

#include "ConnectionPoint.h"

using namespace std;
using namespace energo::net;


ConnectionPoint::ConnectionPoint() {

}

ConnectionPoint::ConnectionPoint(string_view ipAddress, uint16_t port) :
        _ip4Address{ipAddress},
        _port{port}
{

}

string_view ConnectionPoint::getIp4Address() const {
    return _ip4Address;
}

void ConnectionPoint::setIp4Address(string_view hostName) {
    _ip4Address = hostName;
}

uint16_t ConnectionPoint::getPort() const {
    return _port;
}

void ConnectionPoint::setPort(uint16_t port) {
    _port = port;
}
