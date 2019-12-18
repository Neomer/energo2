//
// Created by kir on 18.12.2019.
//

#include "Patch.h"

using namespace energo::types;
using namespace energo::db;

Patch::Patch(const Uuid &patchUid, const Uuid &prevPatchUid, const types::Uuid &databaseTypeUid) :
    _patchUid{patchUid},
    _prevPatchUid{prevPatchUid},
    _databaseTypeUid{databaseTypeUid}
{

}

const Uuid &Patch::getPatchUid() const {
    return _patchUid;
}

const Uuid &Patch::getPreviousPatchUid() const {
    return _prevPatchUid;
}

bool Patch::isSupported(const DatabaseConnectionProvider &provider) const {
    return provider.getTypeUid().equals(_databaseTypeUid);
}
