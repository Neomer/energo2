//
// Created by kir on 29.12.2019.
//

#ifndef ENERGO_DEVICE_H
#define ENERGO_DEVICE_H

namespace energo::io {

class Device {
public:
    enum class OpenMode {
        None = 0,
        ReadOnly = 1,
        WriteOnly = 2,
        ReadWrite = 3
    };
    
    Device() = default;
    virtual ~Device() = default;
    
    [[nodiscard]] virtual bool open(OpenMode openMode) = 0;
    
    virtual void close() = 0;
};

}


#endif //ENERGO_DEVICE_H
