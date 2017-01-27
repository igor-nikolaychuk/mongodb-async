cmake_minimum_required(VERSION 3.1)
project(mongodb_async)

find_package(libmongocxx)
find_package(libbsoncxx)
find_package( Boost COMPONENTS system filesystem  REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3")

set(SOURCE_FILES main.cpp BaseHeader.h DbConnectionPool.h MongoDbHeader.h Tasks/FindOneTask.h DbWorker.h ConcurrentQueue.h Tasks/FindTask.h GenericDbTask.h DbConnectionPoolClient.h TaskContext.h TaskExecutor.h Tasks/DeleteOneTask.h Tasks/DeleteManyTask.h Tasks/UpdateOne.h Tasks/UpdateMany.h Tasks/InsertOne.h Tasks/InsertMany.h)
include_directories(mongodb_async ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(mongodb_async ${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
add_executable(mongodb_async ${SOURCE_FILES})
target_link_libraries(mongodb_async libmongocxx.so bsoncxx.so ${Boost_LIBRARIES})