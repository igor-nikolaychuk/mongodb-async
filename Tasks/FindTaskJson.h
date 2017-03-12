#ifndef MONGODB_ASYNC_FINDTASKJSON_H
#define MONGODB_ASYNC_FINDTASKJSON_H

#include "../BaseHeader.h"
#include "../MongoDbHeader.h"
#include "../TaskContext.h"

typedef shared_ptr<vector<string>> FindResultJson;
typedef function<void(bool err, FindResultJson)> FindJsonCompletionHandler;

class FindTaskJson: public TaskContext {
public:
    string collection;
    document_ptr query;
    find_options_ptr findOptionsPtr;
    FindJsonCompletionHandler completionHandler;
    FindTaskJson(const FindTaskJson& oth) = delete;
    FindTaskJson(FindTaskJson&& oth) = delete;
    FindTaskJson(io_service& targetService,
             string collection,
             document_ptr query,
             FindJsonCompletionHandler completionHandler,
             find_options_ptr findOptionsPtr = nullptr)
            : TaskContext(targetService),
              collection(collection),
              query(query),
              completionHandler(completionHandler),
              findOptionsPtr(findOptionsPtr){
    }
};

#endif //MONGODB_ASYNC_FINDTASKJSON_H