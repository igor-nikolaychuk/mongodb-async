#ifndef MONGODB_ASYNC_DBTASK_H
#define MONGODB_ASYNC_DBTASK_H

#include <boost/variant.hpp>
#include "BaseHeader.h"

#include "Tasks/FindTask.h"
#include "Tasks/DeleteOneTask.h"
#include "Tasks/DeleteManyTask.h"
#include "Tasks/UpdateOne.h"
#include "Tasks/FindOneTask.h"
#include "Tasks/UpdateMany.h"
#include "Tasks/InsertOne.h"
#include "Tasks/InsertMany.h"

using boost::variant;

class GenericDbTask {
public:
    variant<InsertOneTask*, InsertManyTask*, FindTask*, FindOneTask*, UpdateOneTask*, UpdateManyTask*, DeleteOneTask*, DeleteManyTask*> task;

    GenericDbTask(InsertOneTask* t): task(t) { }
    GenericDbTask(InsertManyTask* t): task(t) { }

    GenericDbTask(FindTask* t): task(t) { }
    GenericDbTask(FindOneTask* t): task(t) { }

    GenericDbTask(UpdateOneTask* t): task(t) { }
    GenericDbTask(UpdateManyTask* t): task(t) { }

    GenericDbTask(DeleteOneTask* t): task(t) { }
    GenericDbTask(DeleteManyTask* t): task(t) { }
};

typedef shared_ptr<GenericDbTask> GenericDbTaskPtr;
#endif //MONGODB_ASYNC_DBTASK_H
