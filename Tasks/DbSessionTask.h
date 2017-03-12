#ifndef MONGODB_ASYNC_DBSESSIONTASK_H
#define MONGODB_ASYNC_DBSESSIONTASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef function<void(mongocxx::client& client, mongocxx::database& defaultDb)> DbSessionDelegate;
class DbSessionTask {
public:
    DbSessionDelegate delegate;
    DbSessionTask(DbSessionDelegate delegate): delegate(delegate) {    }
};

#endif //MONGODB_ASYNC_DBSESSIONTASK_H