#pragma once
#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H
#include "includes.h"
#include "globals.h"
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::placeholders;

class Client_session : public boost::enable_shared_from_this<Client_session>
                     , boost::noncopyable, public coroutine
{
    typedef Client_session self_type;
    Client_session();
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<Client_session> ptr;
    ip::tcp::socket& get_socket();
    void start();
    void stop();
    bool is_started();
    static Client_session::ptr new_client()
    {
        Client_session::ptr new_client(new Client_session);
        return new_client;
    }
    

private:
    
    void client_session_loop(const error_code & err, size_t bytes);
    void answer_from_client();
    void read_message();
    void send_message();

    ip::tcp::socket socket;
    bool started_session;
    streambuf read_buffer_package;
    streambuf write_buffer_package;
    std::string message;
    io_service* my_service;
    ip::tcp::acceptor* my_acceptor;
    
};

#endif //CLIENT_SESSION_H