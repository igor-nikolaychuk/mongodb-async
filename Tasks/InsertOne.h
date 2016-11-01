#ifndef MONGODB_ASYNC_INSERTONE_H
#define MONGODB_ASYNC_INSERTONE_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef optional<mongocxx:: result::insert_one> InsertOneResult;
typedef function<void(bool err, InsertOneResult )> InsertOneCompletionHandler;

class InsertOneTask: public TaskContext {
public:
    string collection;
    document_ptr document;
    InsertOneCompletionHandler completionHandler;
    InsertOneTask(io_service& targetService, string collection, document_ptr document, InsertOneCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), document(document), completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_INSERTONE_H
