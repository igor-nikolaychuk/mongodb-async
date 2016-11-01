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

class DbWorker {
    class TaskExecutor : public boost::static_visitor<int>
    {
    public:
        TaskExecutor(){}
    public:
        int operator()(const FindTask* task) const
        {
            cout << "FindTask!" << endl;
            document_vector_ptr documents = make_shared<document_vector>();
            auto handler = task->completionHandler;
            documents->push_back(document{} << "a" << 8 << finalize);
            task->targetService.post([=]() {
                cout << "lol" << endl;
                //handler(true, move(documents));
            });
            delete task;
        }
    };
    ConcurrentQueue<GenericDbTask>& mTasks;
    int mTaskCount = 0;
    shared_ptr<bool> mStopFlagPtr;
    TaskExecutor mTaskExecutor;

    void mTaskLoop() {
        auto stopFlagPtrCopy = mStopFlagPtr;
        while(!*stopFlagPtrCopy) {
            GenericDbTask t = mTasks.pop();
            boost::apply_visitor(mTaskExecutor, t.task);
        }
    }
public:
    DbWorker&operator=(const DbWorker& oth) = delete;
    inline int getTaskCount() {
        return mTaskCount;
    }
    DbWorker(ConcurrentQueue<GenericDbTask>& _tasks): mTasks(_tasks) {
        mStopFlagPtr = make_shared<bool>(false);
        thread(&DbWorker::mTaskLoop, this).detach();
    }
    void pushTask (GenericDbTask task) {
        mTasks.push(task);
    }
    ~DbWorker() {
        *mStopFlagPtr = true;
    }
};

#endif //MONGODB_ASYNC_DBWORKER_H
