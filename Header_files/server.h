#pragma once
#ifndef SERVER_H
#define SERVER_H
#include "includes.h"
#include "client_session.h"
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::placeholders;
class Server
{
public:
    Server();
    void start();
private:
    int port;
    static void client_accept(Client_session::ptr client, const boost::system::error_code & err)
    {
        client->start();
        Client_session::ptr new_client = Client_session::new_client();
        global::acceptor.async_accept(new_client->get_socket(), boost::bind(client_accept, new_client,_1));
    }
};

#endif //SERVER_H