//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <BenchmarkTimer.h>
#include <Database/Adapters/PostgreSql/PostgreSqlConnectionAdapter.h>
#include <Database/Adapters/PostgreSql/PostgreSqlQueryBuilder.h>
#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/DatabaseConnection.h>
#include <Database/DatabaseUnavailableException.h>
#include <Database/Model/User.h>

using namespace std;
using namespace energo::benchmark;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::exceptions;

int main(int argv, char **argc) {
    BenchmarkTimer timer("Configurator app", cout);
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
        BenchmarkTimer timer2("Read users table", cout);
        connection.open();
        timer2.lap("database connection");
        cout << "Connection ready!\n";

        auto sql = queryBuilder
            .createSelectQueryBuilder("Users")
            ->build();
        timer2.lap("Query building");

        auto query = connection.exec(sql);
        timer2.lap("Query execution");

        User user;
        if (!query->any()) {
            cout << "No users were registered.";
        } else {
            do {
                user.fromSql(query->getReader());
                cout << "Found user: " << user.getFirstName() << " " << user.getSecondName()  << " [" << user.getUid() << "] " << endl;
            } while (query->next());
        }
        timer2.lap("Entities generation");
    } catch (DatabaseUnavailableException &) {
        cout << "Database is unavailable!\n";
    }
    connection.close();

    return 0;
}

