#ifndef MONGODB_ASYNC_UPDATEMANY_H
#define MONGODB_ASYNC_UPDATEMANY_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef function<void(bool err, int32_t modifiedCount)> UpdateManyCompletionHandler;

class UpdateManyTask: public TaskContext {
public:
    string collection;
    document_ptr query;
    document_ptr document;
    UpdateManyCompletionHandler completionHandler;
    UpdateManyTask(io_service& targetService, string collection, document_ptr query, document_ptr document, UpdateManyCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), query(query), document(document),
              completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_UPDATEMANY_H
