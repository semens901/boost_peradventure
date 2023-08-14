#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include "includes.h"
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::placeholders;
class Server;
class Client_session;
typedef boost::shared_ptr<Client_session> client_ptr;
namespace global
{
    extern const int PORT;
    extern io_service service;
    extern ip::tcp::acceptor acceptor;
    extern std::vector<client_ptr> clients;
}
#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)
#endif //GLOBALS_H