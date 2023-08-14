#include "../Header_files/client_session.h"


Client_session::Client_session() : socket(global::service), started_session(false){}


void Client_session::client_session_loop(const error_code & err = error_code(), size_t bytes = 0)
{
    reenter(this)
        {
            for(;;)
            {
                if(!started_session)
                {
                    started_session = true;
                    std::ostream out(&write_buffer_package);
                    out << "Your connected to server!\n";
                    global::service.post(MEM_FN2(client_session_loop, error_code(), 0));
                }
                yield async_write(socket, write_buffer_package, MEM_FN2(client_session_loop, _1, _2));
                yield async_read_until( socket, read_buffer_package, "\n", MEM_FN2(client_session_loop, _1, _2));
                yield global::service.post(MEM_FN(answer_from_client));
            }
        }
}

void Client_session::answer_from_client()
{
    write_buffer_package.consume(write_buffer_package.size());
    read_message();
    std::cout << "Client: " << message << std::endl;
    read_buffer_package.consume(read_buffer_package.size());
    send_message();
    if(write_buffer_package.size() > 0)
        global::service.post(MEM_FN2(client_session_loop, error_code(), 0));
    
}

void Client_session::read_message()
{
    std::istream in(&read_buffer_package);
    std::getline(in, message);
}

void Client_session::send_message()
{
    std::ostream out(&write_buffer_package);
    out << message + '\n';

}

ip::tcp::socket& Client_session::get_socket()
{
    return socket;
}
void Client_session::start()
{
    std::cout << "Start client session\n";
    std::cout << "client accepted" << std::endl;
    global::clients.push_back(shared_from_this());
    global::service.post(MEM_FN2(client_session_loop, error_code(), 0));
    //client_session_loop();
    //server_loop();
}

void Client_session::stop()
{
    if ( !started_session) return;
        started_session = false;
        socket.close();

        ptr self = shared_from_this();
        std::vector<client_ptr>::iterator it = std::find(global::clients.begin(), global::clients.end(), self);
        global::clients.erase(it);
}

bool Client_session::is_started()
{
    return started_session;
}