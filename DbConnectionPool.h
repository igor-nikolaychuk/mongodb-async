#ifndef MONGODB_ASYNC_DBCONNECTIONPOOL_H
#define MONGODB_ASYNC_DBCONNECTIONPOOL_H

#include "MongoDbHeader.h"
#include "Tasks/FindTask.h"
#include "DbWorker.h"
#include <thread>
#include "BaseHeader.h"
#include "Tasks/DeleteManyTask.h"

using namespace std;

class DbConnectionPool {
    vector<shared_ptr<DbWorker>> mWorkers;
    ConcurrentQueue<GenericDbTask> mTasks;
public:
    DbConnectionPool(string uri, string db, int concurrencyLevel) {
        for(int i = 0; i < concurrencyLevel; ++i) {
            auto worker = make_shared<DbWorker>(mTasks, mongocxx::uri(uri), db);
            worker->start();
            mWorkers.push_back(move(worker));
        }
    }
    void insertMany(io_service &io, string &collection, document_vector_ptr &documents, InsertManyCompletionHandler &callback) {
        mTasks.push(GenericDbTask(new InsertManyTask(io, move(collection),move(documents), callback)));
    }
    void insertOne(io_service &io, string &collection, document_ptr &document, InsertOneCompletionHandler &callback) {
        mTasks.push(GenericDbTask(new InsertOneTask(io, move(collection),move(document), callback)));
    }
    void find(io_service &io, string &collection, document_ptr &query, FindCompletionHandler &callback) {
        mTasks.push(GenericDbTask(new FindTask(io, move(collection),move(query), callback)));
    }
    void findOne(io_service &io, string &collection, document_ptr &query, FindOneCompletionHandler &callback) {
        mTasks.push(GenericDbTask(new FindOneTask(io, move(collection),move(query), callback)));
    }
    void updateOne(io_service& io, string& collection, document_ptr& query, UpdateOneCompletionHandler& callback) {
        mTasks.push(GenericDbTask(new UpdateOneTask(io, move(collection),move(query), callback)));
    }
    void updateMany(io_service& io, string& collection, document_ptr& query, UpdateManyCompletionHandler& callback) {
        mTasks.push(GenericDbTask(new UpdateManyTask(io, move(collection),move(query), callback)));
    }
    void deleteOne(io_service& io, string& collection, document_ptr& query, DeleteOneCompletionHandler& callback) {
        mTasks.push(GenericDbTask(new DeleteOneTask(io, move(collection),move(query), callback)));
    }
    void deleteMany(io_service& io, string& collection, document_ptr& query, DeleteManyCompletionHandler& callback) {
        mTasks.push(GenericDbTask(new DeleteManyTask(io, move(collection),move(query), callback)));
    }


    DbConnectionPool operator= (DbConnectionPool& oth) = delete;
    ~DbConnectionPool() {
        for(auto workerPtr: mWorkers) {
            workerPtr->shutdown();
        }
    }
};

#endif //MONGODB_ASYNC_DBCONNECTIONPOOL_H