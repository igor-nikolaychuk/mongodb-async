#ifndef MONGODB_ASYNC_FINDONETASK_H
#define MONGODB_ASYNC_FINDONETASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef mongocxx::stdx::optional<bsoncxx::document::value> mongocxxFindOneResult;
typedef shared_ptr<mongocxxFindOneResult> FindOneResult;
typedef function<void(bool err, FindOneResult)> FindOneCompletionHandler;

class FindOneTask: public TaskContext {
public:
    string collection;
    document_ptr selection;
    find_options_ptr findOptionsPtr;
    FindOneCompletionHandler completionHandler;
    FindOneTask(io_service& targetService, string collection, document_ptr selection,
                FindOneCompletionHandler completionHandler,
                find_options_ptr findOptionsPtr = nullptr
    )
            : TaskContext(targetService), collection(collection), selection(selection), completionHandler(completionHandler),
            findOptionsPtr(findOptionsPtr)
    {
    }
};

#endif //MONGODB_ASYNC_FINDONETASK_H