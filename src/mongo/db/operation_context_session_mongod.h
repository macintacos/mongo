
/**
 *    Copyright (C) 2018-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include <boost/optional.hpp>

#include "mongo/db/session_catalog.h"

namespace mongo {

class OperationContext;

/**
 * Scoped object, which checks out the session specified in the passed operation context and stores
 * it for later access by the command. The session is installed at construction time and is removed
 * at destruction.
 */
class OperationContextSessionMongod {
public:
    OperationContextSessionMongod(OperationContext* opCtx,
                                  bool shouldCheckOutSession,
                                  const OperationSessionInfoFromClient& sessionInfo);

private:
    OperationContextSession _operationContextSession;
};

/**
 * Similar to OperationContextSessionMongod, but marks the TransactionParticipant as valid without
 * refreshing from disk and starts a new transaction unconditionally.
 *
 * NOTE: Only used by the replication oplog application logic on secondaries in order to replay
 * prepared transactions.
 */
class OperationContextSessionMongodWithoutRefresh {
public:
    OperationContextSessionMongodWithoutRefresh(OperationContext* opCtx);

private:
    OperationContextSession _operationContextSession;
};

}  // namespace mongo
