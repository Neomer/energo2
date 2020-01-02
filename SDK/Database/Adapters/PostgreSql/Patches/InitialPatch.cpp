//
// Created by kir on 18.12.2019.
//

#include "../../../../Metadata/TypeUids.h"
#include "InitialPatch.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::patch;
using namespace energo::types;


InitialPatch::InitialPatch() :
    Patch{types::Uuid{12423920561079274481ull, 13753580057830260991ull}, types::Uuid::Empty(), POSTGRESQLPROVIDER_TYPE_UID}
{

}

void InitialPatch::apply(const DatabaseConnection &connection) const {
    // Create database Users
    connection.exec(R"(CREATE TABLE IF NOT EXISTS public."Users"
(
    "Uid" uuid NOT NULL,
    "Username" character varying(128) COLLATE pg_catalog."default" NOT NULL,
    "FirstName" character varying(128) COLLATE pg_catalog."default",
    "SecondName" character varying(128) COLLATE pg_catalog."default",
    CONSTRAINT "Users_pkey" PRIMARY KEY ("Uid")
)
WITH (
    OIDS = FALSE
)
TABLESPACE pg_default;

ALTER TABLE public."Users"
    OWNER to postgres;)").reset(nullptr);
    
}


InitialPatchMetadata::InitialPatchMetadata() :
        meta::ClassMetadata{ types::Uuid{11981550171035681722ull, 11002200308128057647ull}, PATCH_TYPE_UID }
{
}

void *InitialPatchMetadata::createInstance() const {
    return (void *)this;
}

string_view InitialPatchMetadata::getTypeName() const {
    return "InitialPatch";
}
