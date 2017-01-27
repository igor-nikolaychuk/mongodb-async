#include <iostream>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/third_party/mnmlstc/core/optional.hpp>

#include "MongoDbHeader.h"
#include "DbConnectionPoolClient.h"
//#include "DbConnectionPool.h"
#include "BaseHeader.h"

io_service io(1);
DbConnectionPool db("mongodb://localhost:27017", "alien", 1);
DbConnectionPoolClient client(io, db);

int main(int, char**) {
    function<void(void)> foo;
    /*
     * foo = [&]() {
        document_vector_ptr documents = make_shared<document_vector>();
        for(int i = 0; i < 1000; ++i)
            documents->push_back(document{} << "lalka" << "test" << finalize);
        client.insertMany("test", move(documents), [&](bool err, InsertManyResult res) {
            foo();
        });
    };
     */
    document_ptr testInsert = make_shared<document_value>(document{} << "name" << "test" << finalize);
    int i = 0;
    auto begin = time(0);
    auto d =
    foo = [&]() {
        client.findOne("test", make_shared<document_value>(document{} << "name" << "test" << finalize),
                       [&](bool err, FindOneResult res) {
                           if(i%1000 == 0)
                           {
                               auto diff = time(0) - begin;
                               cout << float(i)/diff << endl;
                           }
                           if(*res) {
                               ++i;
                               auto doc = *res;
                               //cout << bsoncxx::to_json(doc->view()) << endl;
                               foo();
                           }
                           else {
                               cout << "no result!" << endl;
                           }
                       });
    };
    //foo();
    /*
    client.deleteMany("test",
                     make_shared<document_value>(document{} << "name" << "suka" << finalize),
    [](bool err, int32_t count) {
                if(!err) {
                    cout << "deleted!" << endl;
                }
    });
    */
    foo();
    foo();
    foo();
    boost::asio::io_service::work work(io);
    begin = time(0);
    io.run();

    cout << "exit" << endl;
}