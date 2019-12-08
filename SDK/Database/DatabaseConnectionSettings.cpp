//
// Created by kir on 07.12.2019.
//

#include "DatabaseConnectionSettings.h"

using namespace std;
using namespace energo::db;

uint16_t DatabaseConnectionSettings::getPort() const {
    return _port;
}

void DatabaseConnectionSettings::setPort(uint16_t port) {
    _port = port;
}

std::string_view DatabaseConnectionSettings::getHost() const {
    return _host;
}

void DatabaseConnectionSettings::setHost(std::string_view host) {
    _host = host;
}

std::string_view DatabaseConnectionSettings::getUser() const {
    return _user;
}

void DatabaseConnectionSettings::setUser(std::string_view user) {
    _user = user;
}

std::string_view DatabaseConnectionSettings::getPassword() const {
    return _password;
}

void DatabaseConnectionSettings::setPassword(std::string_view password) {
    _password = password;
}

std::string_view DatabaseConnectionSettings::getDatabase() const {
    return _database;
}

void DatabaseConnectionSettings::setDatabase(std::string_view database) {
    _database = database;
}
