#ifndef MONGODB_ASYNC_TASKTYPE_H
#define MONGODB_ASYNC_TASKTYPE_H

enum class TaskType {
    find,
    update,
    insert_one,
    insert_many
};

#endif //MONGODB_ASYNC_TASKTYPE_H
