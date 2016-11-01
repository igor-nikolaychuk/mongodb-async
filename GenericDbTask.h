#ifndef MONGODB_ASYNC_DBTASK_H
#define MONGODB_ASYNC_DBTASK_H

#include "TaskType.h"
#include <boost/variant.hpp>
#include "FindTask.h"
#include "BaseHeader.h"

using boost::variant;

class GenericDbTask {
public:
    variant<FindTask*> task;
    GenericDbTask(FindTask* findTask): task(findTask) {
    }
};

typedef shared_ptr<GenericDbTask> GenericDbTaskPtr;
#endif //MONGODB_ASYNC_DBTASK_H
