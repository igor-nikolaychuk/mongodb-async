#ifndef MONGODB_ASYNC_TASKEXECUTOR_H
#define MONGODB_ASYNC_TASKEXECUTOR_H

#include <boost/variant/static_visitor.hpp>
#include "BaseHeader.h"
#include "MongoDbHeader.h"
#include "Tasks/FindTask.h"
#include "Tasks/DeleteOneTask.h"
#include "Tasks/DeleteManyTask.h"
#include "Tasks/FindOneTask.h"
#include "Tasks/UpdateOne.h"
#include "Tasks/UpdateMany.h"
#include "Tasks/InsertOne.h"
#include "Tasks/InsertMany.h"

class TaskExecutor : public boost::static_visitor<int>
{
    mongocxx::database& defaultDb;
    mongocxx::client& client;
public:
    TaskExecutor(mongocxx::client& client, mongocxx::database& defaultDb): client(client), defaultDb(defaultDb) { }
    int operator()(const InsertOneTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            InsertOneResult resultPtr = make_shared<mongocxxInsertOneResult>(collection.insert_one(task->document->view()));
            task->targetService.post([=]() {
                handler(false, resultPtr);
            });
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, nullptr);
            });
        }
        delete task;
    }
    int operator()(const InsertManyTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            InsertManyResult resultPtr =
                    make_shared<mongocxxInsertManyResult>(
                            collection.insert_many(task->documents->begin(), task->documents->end()));
            task->targetService.post([=]() {
                handler(false, resultPtr);
            });
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, nullptr);
            });
        }
        delete task;
    }

    int operator()(const FindTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            FindResult result = make_shared<vector<document_view>>();
            auto cursor = collection.find(task->query->view());
            for(auto doc: cursor) {
                result->push_back(move(doc));
            }
            task->targetService.post([=]() {
                handler(false, result);
            });
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, nullptr);
            });
        }
        delete task;
    }

    int operator()(const FindOneTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            FindOneResult resultPtr;
            if(!task->findOptionsPtr)
                resultPtr = make_shared<mongocxxFindOneResult>(
                        collection.find_one(task->selection->view()));
            else {
                auto findOptions = task->findOptionsPtr.get();
                resultPtr = make_shared<mongocxxFindOneResult>(
                        collection.find_one(task->selection->view(), *findOptions));
            }
            task->targetService.post([=]() {
                handler(false, resultPtr);
            });
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, nullptr);
            });
        }
        delete task;
    }

    int operator()(const UpdateOneTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            collection.update_one(task->query->view(), task->document->view());
            task->targetService.post([=]() {
                handler(false);
            });
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true);
            });
        }
        delete task;
    }
    int operator()(const UpdateManyTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            auto res = collection.update_many(task->query->view(), task->document->view());
            if(res) {
                task->targetService.post([=]() {
                    handler(false, res.value().modified_count());
                });
            }
            else {
                task->targetService.post([=]() {
                    handler(false, 0);
                });
            }

        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, 0);
            });
        }
        delete task;
    }

    int operator()(const DeleteOneTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            auto res = collection.delete_one(task->query->view());
            if(res && res->deleted_count()) {
                task->targetService.post([=]() {
                    handler(false, true);
                });
            }
            else {
                task->targetService.post([=]() {
                    handler(false, false);
                });
            }
        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, false);
            });
        }
        delete task;
    }

    int operator()(const DeleteManyTask* task) const
    {
        auto collection = defaultDb[task->collection];
        auto handler = task->completionHandler;
        try {
            auto res = collection.delete_many(task->query->view());
            if(res) {
                task->targetService.post([=]() {
                    handler(false, res.value().deleted_count());
                });
            }
            else {
                task->targetService.post([=]() {
                    handler(false, 0);
                });
            }

        }
        catch(...) {
            task->targetService.post([=]() {
                handler(true, 0);
            });
        }
        delete task;
    }
};

#endif //MONGODB_ASYNC_TASKEXECUTOR_H
