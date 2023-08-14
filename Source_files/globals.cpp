#include "../Header_files/globals.h"
namespace global
{
    const int PORT = 8001;
    io_service service;
    ip::tcp::acceptor acceptor = ip::tcp::acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), PORT));
    std::vector<client_ptr> clients;
}
