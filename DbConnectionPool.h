#ifndef MONGODB_ASYNC_DBCONNECTIONPOOL_H
#define MONGODB_ASYNC_DBCONNECTIONPOOL_H

#include "MongoDbHeader.h"
#include "FindTask.h"
#include "DbWorker.h"
#include <thread>
#include "BaseHeader.h"
using namespace std;

class DbConnectionPool {
    vector<DbWorker*> mWorkers;
    ConcurrentQueue<GenericDbTask> mTasks;
public:
    DbConnectionPool(int concurrencyLevel) {
        mWorkers.push_back(new DbWorker(mTasks));
    }
    void findAsync(io_service& io, string& collection, document_ptr& query, FindCompletionHandler& callback) {
        mTasks.push(GenericDbTask(new FindTask(io, move(collection),move(query), callback)));
    }
    DbConnectionPool operator= (DbConnectionPool& oth) = delete;
    ~DbConnectionPool() {
        for(auto worker: mWorkers) {
            delete worker;
        }
    }
};

#endif //MONGODB_ASYNC_DBCONNECTIONPOOL_H