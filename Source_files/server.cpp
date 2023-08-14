#include "../Header_files/server.h"

//public
Server::Server() : port(global::PORT){}

void Server::start()
{
    std::cout << "Start server\n";
    Client_session::ptr client = Client_session::new_client();
    global::acceptor.async_accept(client->get_socket(), boost::bind(client_accept, client, _1));
    global::service.run();
}

//private