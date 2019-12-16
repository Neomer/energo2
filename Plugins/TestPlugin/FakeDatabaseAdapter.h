//
// Created by kir on 16.12.2019.
//

#ifndef ENERGO_FAKEDATABASEADAPTER_H
#define ENERGO_FAKEDATABASEADAPTER_H

#include "../../SDK/Database/DatabaseConnection.h"
#include "FakeTransformationProvider.h"

namespace energo::db::adapters {

class EXPORTS FakeDatabaseAdapter : public DatabaseConnection {
    FakeTransformationProvider _transformationProvider;
    
public:
    FakeDatabaseAdapter(std::random_device &randomDevice, const DatabaseConnectionSettings &settings);
    
    void open() override;
    
    void close() override;
    
    const SqlQueryBuilder *queryBuilder() const override;
    
    std::unique_ptr<SqlQuery> exec(std::string_view sql) const override;
    
    const TransformationProvider &transformationProvider() const override;
};

}


#endif //ENERGO_FAKEDATABASEADAPTER_H
