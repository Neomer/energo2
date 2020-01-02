//
// Created by kir on 29.12.2019.
//

#ifndef ENERGO_CONNECTIONPOINT_H
#define ENERGO_CONNECTIONPOINT_H

#include "../global.h"
#include <string>
#include <string_view>

namespace energo::net {

class EXPORTS ConnectionPoint {
    std::string _ip4Address;
    uint16_t _port;
    
public:
    ConnectionPoint();
    
    ConnectionPoint(std::string_view ipAddress, uint16_t port);
    
    [[nodiscard]] std::string_view getIp4Address() const;
    
    void setIp4Address(std::string_view hostName);
    
    [[nodiscard]] uint16_t getPort() const;
    
    void setPort(uint16_t port);
};

}


#endif //ENERGO_CONNECTIONPOINT_H
