#ifndef MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H
#define MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H

#include "BaseHeader.h"
#include "DbConnectionPool.h"

using namespace std::placeholders;

class DbConnectionPoolClient {
    io_service& mIoService;
    DbConnectionPool& mDbConnectionPool;
public:
    void insertOne(string &&collection, document_ptr &&document, InsertOneCompletionHandler callback) {
        mDbConnectionPool.insertOne(mIoService, collection, document, callback);
    }
    void insertMany(string &&collection, document_vector_ptr &&documents, InsertManyCompletionHandler callback) {
        mDbConnectionPool.insertMany(mIoService, collection, documents, callback);
    }
    void find(string &&collection, document_ptr &&query, FindCompletionHandler callback, find_options_ptr opt_ptr = nullptr) {
        mDbConnectionPool.find(mIoService, collection, query, callback, opt_ptr);
    }
    void find_json(string &&collection, document_ptr &&query, FindJsonCompletionHandler callback, find_options_ptr opt_ptr = nullptr) {
        mDbConnectionPool.find_json(mIoService, collection, query, callback, opt_ptr);
    }
    void findOne(string &&collection, document_ptr &&query, FindOneCompletionHandler callback, find_options_ptr opt_ptr = nullptr) {
        mDbConnectionPool.findOne(mIoService, collection, query, callback, opt_ptr);
    }
    void updateOne(string&& collection, document_ptr&& query, document_ptr&& document, UpdateOneCompletionHandler callback) {
        mDbConnectionPool.updateOne(mIoService, collection, query, document, callback);
    }
    void updateMany(string&& collection, document_ptr&& query, document_ptr&& document, UpdateManyCompletionHandler callback) {
        mDbConnectionPool.updateMany(mIoService, collection, query, document, callback);
    }
    void deleteOne(string&& collection, document_ptr&& query, DeleteOneCompletionHandler callback) {
        mDbConnectionPool.deleteOne(mIoService, collection, query, callback);
    }
    void deleteMany(string&& collection, document_ptr&& query, DeleteManyCompletionHandler callback) {
        mDbConnectionPool.deleteMany(mIoService, collection, query, callback);
    }
    void dbSession(DbSessionDelegate delegate) {
        mDbConnectionPool.dbSession(delegate);
    }

    DbConnectionPoolClient(io_service &mIoService, DbConnectionPool& cp)
            : mIoService(mIoService), mDbConnectionPool(cp) {
    }
};

#endif //MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H
