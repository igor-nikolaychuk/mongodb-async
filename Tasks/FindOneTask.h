#ifndef MONGODB_ASYNC_FINDONETASK_H
#define MONGODB_ASYNC_FINDONETASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

#include "boost/optional.hpp"
using boost::optional;

typedef function<void(bool err, optional<document_ptr>)> FindOneCompletionHandler;

class FindOneTask: public TaskContext {
public:
    string collection;
    document_ptr query;
    FindOneCompletionHandler completionHandler;
    FindOneTask(io_service& targetService, string collection, document_ptr query, FindOneCompletionHandler completionHandler)
            : TaskContext(targetService), collection(collection), query(query), completionHandler(completionHandler) {
    }
};

#endif //MONGODB_ASYNC_FINDONETASK_H