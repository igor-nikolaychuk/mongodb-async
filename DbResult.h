#ifndef MONGODB_ASYNC_DBRESULT_H
#define MONGODB_ASYNC_DBRESULT_H

class DbResult {
public:
    bool err;
    DbResult(bool err) : err(err) {}
};

#endif //MONGODB_ASYNC_DBRESULT_H
