#ifndef MONGODB_ASYNC_INSERTMANY_H
#define MONGODB_ASYNC_INSERTMANY_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef core::optional<mongocxx:: result::insert_many> mongocxxInsertManyResult;
typedef shared_ptr<mongocxxInsertManyResult> InsertManyResult;
typedef function<void(bool err, InsertManyResult)> InsertManyCompletionHandler;

class InsertManyTask: public TaskContext {
public:
    string collection;
    document_vector_ptr documents;
    InsertManyCompletionHandler completionHandler;
    InsertManyTask(io_service& targetService, string collection, document_vector_ptr documents, InsertManyCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), documents(documents), completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_INSERTMANY_H
