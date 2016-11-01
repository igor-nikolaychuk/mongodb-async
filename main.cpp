#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "MongoDbHeader.h"
#include "ConnectionPoolClient.h"
//#include "DbConnectionPool.h"

io_service io(1);
DbConnectionPool db(4);
ConnectionPoolClient client(io, db);


int main(int, char**) {
    document_ptr d = make_shared<document_value>(document{} << "a" << 10 << finalize);
    client.findAsync(string("main"), move(d), [](bool err, document_vector_ptr documents) {
        cout << bsoncxx::to_json((*documents)[0]) << endl;
    });
    boost::asio::io_service::work work(io);
    sleep(4);
    io.run();

    cout << "exit" << endl;
    /*
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    document document{};

    auto collection = conn["testdb"]["testcollection"];
    int a = sizeof(collection);
    document << "hello" << "world";
*/
    //mongocxx::cursor cursor = collection.find(document{} << finalize);
    //for(auto doc : cursor) {
    //    std::cout << bsoncxx::to_json(doc) << "\n";
    //}
}