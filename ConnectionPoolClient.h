#ifndef MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H
#define MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H

#include "BaseHeader.h"
#include "DbConnectionPool.h"
//#include "DbConnectionPool.h"
using namespace std::placeholders;
class A {
public:
    A() {}
    A(const A& oth) {
        cout << "Coupy constructor" << endl;
    }
};


class ConnectionPoolClient {
    io_service& mIoService;
    DbConnectionPool& mDbConnectionPool;
public:
    void findAsync(string&& collection, document_ptr&& query, FindCompletionHandler callback) {
        mDbConnectionPool.findAsync(mIoService, collection, query, callback);
    }
    ConnectionPoolClient(io_service &mIoService, DbConnectionPool& cp)
            : mIoService(mIoService), mDbConnectionPool(cp) {
    }
};
#endif //MONGODB_ASYNC_CONNECTIONPOOLCLIENT_H
