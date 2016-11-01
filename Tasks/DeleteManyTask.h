#ifndef MONGODB_ASYNC_DELETEMANYTASK_H
#define MONGODB_ASYNC_DELETEMANYTASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef function<void(bool err, size_t count)> DeleteManyCompletionHandler;

class DeleteManyTask: public TaskContext {
public:
    string collection;
    document_ptr query;
    DeleteManyCompletionHandler completionHandler;
    DeleteManyTask(io_service& targetService, string collection, document_ptr query, DeleteManyCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), query(query), completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_DELETEMANYTASK_H
