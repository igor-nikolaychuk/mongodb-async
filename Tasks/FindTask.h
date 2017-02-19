#ifndef MONGODB_ASYNC_FINDTASK_H
#define MONGODB_ASYNC_FINDTASK_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef shared_ptr<vector<document_view>> FindResult;
typedef function<void(bool err, FindResult)> FindCompletionHandler;

class FindTask: public TaskContext {
public:
    string collection;
    document_ptr query;
    find_options_ptr findOptionsPtr;
    FindCompletionHandler completionHandler;
    FindTask(const FindTask& oth) = delete;
    FindTask(FindTask&& oth) = delete;
    FindTask(io_service& targetService,
             string collection,
             document_ptr query,
             FindCompletionHandler completionHandler,
             find_options_ptr findOptionsPtr = nullptr)
            : TaskContext(targetService),
              collection(collection),
              query(query),
              completionHandler(completionHandler),
              findOptionsPtr(findOptionsPtr){
    }
};

#endif //MONGODB_ASYNC_FINDTASK_H