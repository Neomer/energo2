//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <Database/Adapters/PostgreSql/PostgreSqlConnectionAdapter.h>
#include <Database/Adapters/PostgreSql/PostgreSqlQueryBuilder.h>
#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/DatabaseConnection.h>
#include <Database/DatabaseUnavailableException.h>
#include <Database/Model/User.h>

using namespace std;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::exceptions;

int main(int argv, char **argc) {
    random_device rd;

    DatabaseConnectionSettings settings;
    settings.setHost("localhost");
    settings.setPort(5432);
    settings.setUser("postgres");
    settings.setPassword("123456");
    settings.setDatabase("energo2");
    
    adapters::PostgreSqlTransformationProvider transformationProvider;
    adapters::PostgreSqlQueryBuilder queryBuilder(transformationProvider);
    adapters::PostgreSqlConnectionAdapter connection(rd, settings);
    try {
        connection.open();
        cout << "Connection ready!\n";
        
        auto query = connection.exec(
                queryBuilder
                .createSelectQueryBuilder("Users")
                ->build());
        User user;
        if (!query->any()) {
            cout << "No users were registered.";
        } else {
            do {
                user.fromSql(query->getReader());
                cout << "Found user: " << user.getFirstName() << " " << user.getSecondName()  << " [" << user.getUid() << "] " << endl;
            } while (query->next());
        }
    } catch (DatabaseUnavailableException &) {
        cout << "Database is unavailable!\n";
    }
    connection.close();

    return 0;
}

