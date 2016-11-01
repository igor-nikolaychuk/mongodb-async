#include <iostream>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "MongoDbHeader.h"
#include "DbConnectionPoolClient.h"
//#include "DbConnectionPool.h"
#include "BaseHeader.h"
io_service io(1);
DbConnectionPool db("mongodb://localhost:27017", "main", 2);
DbConnectionPoolClient client(io, db);


int main(int, char**) {
    function<void(void)> foo;
    foo = [&]() {
        document_ptr d = make_shared<document_value>(document{} << "a" << 10 << finalize);
        client.insertOne("test", move(d), [&](bool err, InsertOneResult res) {
            if (res) {
                bsoncxx::oid oid = res.get().inserted_id().get_oid().value;
                std::string JobID = oid.to_string();
                cout << JobID << endl;
            }
            foo();
        });
    };
    foo();
    foo();
    boost::asio::io_service::work work(io);
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