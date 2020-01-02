//
// Created by vinokurov on 23.12.2019.
//

#include "../NetworkHelper.h"
#include "../../os.h"

#ifdef OS_WIN

#include <cinttypes>
using namespace std;
using namespace energo::net;

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>

#include <stdexcept>

#pragma comment(lib, "Ws2_32.lib")

void NetworkHelper::Initialize() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw runtime_error("Не удалось инициализировать систему сокетов.");
    }
}

void NetworkHelper::Release() {
    WSACleanup();
}

#endif