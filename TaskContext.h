#ifndef MONGODB_ASYNC_TASKCONTEXT_H
#define MONGODB_ASYNC_TASKCONTEXT_H

#include "BaseHeader.h"
class TaskContext {
public:
    io_service& targetService;
    TaskContext(io_service &targetService) : targetService(targetService) { }
};

#endif //MONGODB_ASYNC_TASKCONTEXT_H
