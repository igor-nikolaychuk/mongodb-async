//
// Created by origin on 30.10.16.
//

#ifndef MONGODB_ASYNC_DBWORKER_H
#define MONGODB_ASYNC_DBWORKER_H

#include "BaseHeader.h"

#include "boost/asio.hpp"
using boost::asio::io_service;
#include "BaseHeader.h"
#include "ConcurrentQueue.h"
#include "GenericDbTask.h"
#include "TaskExecutor.h"

class DbWorker: public std::enable_shared_from_this<DbWorker> {
    ConcurrentQueue<GenericDbTask>& mTasks;
    bool mStopFlag = false;
    TaskExecutor* mTaskExecutor;
    void mTaskLoop() {
        auto destroyProtector = shared_from_this();
        while(!mStopFlag) {
            GenericDbTask t = mTasks.pop();
            boost::apply_visitor(*mTaskExecutor, t.task);
        }
    }
    mongocxx::database mDb;
    mongocxx::client mClient;
public:
    DbWorker&operator=(const DbWorker& oth) = delete;
    DbWorker(ConcurrentQueue<GenericDbTask>& _tasks, const mongocxx::uri _uri, string db): mDb(), mClient(_uri), mTasks(_tasks) {
        mDb = mClient[db];
        mTaskExecutor = new TaskExecutor(mClient, mDb);
    }
    void start() {
        thread(&DbWorker::mTaskLoop, this).detach();
    }
    void pushTask (GenericDbTask task) {
        mTasks.push(task);
    }
    void shutdown() {
        mStopFlag = true;
    }
    ~DbWorker() {
        delete mTaskExecutor;
    }
};

#endif //MONGODB_ASYNC_DBWORKER_H
