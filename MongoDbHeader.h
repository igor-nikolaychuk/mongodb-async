#ifndef MONGODB_ASYNC_MONGODBHEADER_H
#define MONGODB_ASYNC_MONGODBHEADER_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include "BaseHeader.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

typedef bsoncxx::document::value document_value;
typedef shared_ptr<document_value> document_ptr;
typedef vector<document_value> document_vector;
typedef shared_ptr<document_vector> document_vector_ptr;

#endif //MONGODB_ASYNC_MONGODBHEADER_H
