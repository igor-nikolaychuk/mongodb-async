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
        auto result = collection.insert_one(task->document->view());
        auto handler = task->completionHandler;
        if(result)
            task->targetService.post([=]() {
                handler(false, optional<mongocxx:: result::insert_one>(result.value()));
            });
        delete task;
    }
    int operator()(const InsertManyTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            //handler(false, );
        });
        delete task;
    }
    int operator()(const FindTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false, move(documents));
        });
        delete task;
    }
    int operator()(const FindOneTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false, optional<document_ptr>());
        });
        delete task;
    }
    int operator()(const UpdateOneTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false);
        });
        delete task;
    }
    int operator()(const UpdateManyTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false, 0);
        });
        delete task;
    }
    int operator()(const DeleteOneTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false);
        });
        delete task;
    }
    int operator()(const DeleteManyTask* task) const
    {
        document_vector_ptr documents = make_shared<document_vector>();
        auto handler = task->completionHandler;
        documents->push_back(document{} << "a" << 8 << finalize);
        task->targetService.post([=]() {
            handler(false, 2);
        });
        delete task;
    }
};

#endif //MONGODB_ASYNC_TASKEXECUTOR_H
