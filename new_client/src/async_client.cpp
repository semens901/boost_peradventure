#include <boost/thread.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include<boost/noncopyable.hpp>
#include<functional>
#include<iostream>
#include "coroutine.hpp"
#include "yield.hpp"

using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::placeholders;
io_service service;
class client_server;
class server_session;
const int PORT = 8001;

#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

class server_session : public boost::enable_shared_from_this<server_session>
                  , boost::noncopyable, public coroutine
{
    friend client_server;
    typedef server_session self_type;
    server_session(std::string message) : socket(service), started_session(false), message(message){}
    void start(ip::tcp::endpoint ep)
    {
        socket.async_connect(ep, MEM_FN2(step,_1,0));
        step();
    }
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<server_session> ptr;

    void step(const error_code & err = error_code(), size_t bytes = 0)
    {
        reenter(this)
        {
            for(;;)
            {
                if(!started_session)
                {
                    started_session = true;
                    /*std::ostream out(&write_buffer);
                    out << "Hello server!\n";
                    service.post( MEM_FN2(step,error_code(),0));*/
                }
                if(message.size() > 0)
                {
                    std::ostream out(&write_buffer);
                    out << message + '\n';
                    service.post( MEM_FN2(step,error_code(),0));
                }
                yield async_write(socket, write_buffer, MEM_FN2(step,_1,_2) );
                yield async_read_until( socket, read_buffer, "\n", MEM_FN2(step,_1,_2));
                yield service.post( MEM_FN(on_answer_from_server));
            }
        }
    }

    void on_answer_from_server() 
    {
        std::istream in(&read_buffer);
        std::getline(in, message);
        if(!message.empty())
        {
            write_buffer.consume(write_buffer.size());
            std::cout << "Server:\t" << message << "\nMessage: ";
            getline(std::cin, message);
            std::ostream out(&write_buffer);
            out << message + '\n';
        }
        read_buffer.consume( read_buffer.size());
        service.post( MEM_FN2(step,error_code(),0));
    }

    void stop() {
        if ( !started_session) return;
        std::cout << "stopping " << std::endl;
        started_session = false;
        socket.close();
    }

    bool is_started(){return started_session;}

private:
    streambuf read_buffer;
    streambuf write_buffer;
    ip::tcp::socket socket;
    bool started_session;
    std::string message;
};

class client_server
{
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<server_session> ptr;
    client_server() : port(PORT){}
    ptr start(ip::tcp::endpoint ep, std::string& msg)
    {
        std::cout << "Start client server\n";
        ptr new_(new server_session(msg));
        new_->start(ep);
        return new_;
    }
private:
    int port;
};

typedef boost::shared_ptr<server_session> ptr;

int main()
{
    ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
    client_server c_server;
    std::string msg = "Hello!\n";
    ptr started_server = c_server.start(ep, msg);
    service.run();
    
    //std::thread main_thread([&](){service.run();});
    /*
    std::thread send_messages([&]()
    {
        std::string message;
        std::cin >> message;
        started_server.get()->send_message(message);
    });
    */
    //main_thread.join();
    //send_messages.join();

    return 0;
}