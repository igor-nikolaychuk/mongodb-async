#ifndef MONGODB_ASYNC_DELETEONETASK_H
#define MONGODB_ASYNC_DELETEONETASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef function<void(bool err, bool deleted)> DeleteOneCompletionHandler;

class DeleteOneTask: public TaskContext {
public:
    string collection;
    document_ptr query;
    DeleteOneCompletionHandler completionHandler;
    DeleteOneTask(io_service& targetService, string collection, document_ptr query, DeleteOneCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), query(query), completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_DELETEONETASK_H
