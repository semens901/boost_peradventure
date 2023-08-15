#include "Header_files/client_session.h"
#include "Header_files/includes.h"
#include "Header_files/server.h"

int main()
{
    Server server;
    server.start();
    global::service.run();
    return 0;
}
