/*
 * SocketWrapper.cpp
 *
 *  Created on: 	06 May 2016
 *  Modified on: 	07 May 2016
 *
 *      Author: Asaf Sarid
 */

//General Includes
#include <iostream>
#include <cstring>			//Needed for memset and string functions
//Socket Includes
#include <sys/socket.h>		//Core socket functions and data structures
#include <sys/types.h>		//Core socket functions and data structures
#include <sys/time.h>		//Needed for timeval struct
#include <netdb.h>			//Functions for translating protocol names and host names into numeric addresses
#include <fcntl.h>			//fcntl() function and defines
#include <arpa/inet.h>
#include <unistd.h>			//Needed for I/O system calls
//Class Headers
#include "SocketHub.h"
#include "IServerHandler.h"
#include <assert.h>

using namespace std;
namespace Servers {

    SocketHub::SocketHub() {
        //Clearing master and read sets
        FD_ZERO(&masterFDSet_);
        FD_ZERO(&readFDSet_);
    }
    SocketHub::~SocketHub() {
    }

    bool SocketHub::bindOnPort(int port, int& listener_fd) {
        struct addrinfo hints;					//Holds wanted settings for the listener socket
        struct addrinfo *server_info_list;		//A list of possible information to create socket

        //All the other fields in the addrinfo struct (hints) must contain 0
        memset(&hints, 0, sizeof hints);

        //Initialize connection information
        hints.ai_family = AF_UNSPEC;			//Supports IPv4 and IPv6
        hints.ai_socktype = SOCK_STREAM;		//Reliable Stream (TCP)
        hints.ai_flags = AI_PASSIVE;			//Assign local host address to socket

        //Get address information
        int err;
        err = getaddrinfo(NULL, to_string(port).c_str(), &hints, &server_info_list);
        if (err != 0) {
            cerr << "getaddrinfo: " << gai_strerror(err) << endl;
            //exit(EXIT_STATUS);
            return false;
        }

        //Go over list and try to create socket and bind
        addrinfo* p;
        for(p = server_info_list; p != NULL; p = p->ai_next) {

            //Create the socket - system call that returns the file descriptor of the socket
            listener_fd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
            if (listener_fd == -1) {
                continue; //try next
            }

            //Make sure the port is not in use. Allows reuse of local address (and port)
            int yes = 1;
            if (setsockopt(listener_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
                perror("setsockopt");
                //exit(EXIT_STATUS);
                return false;
            }

            //Bind socket to specific port (p->ai_addr holds the address and port information)
            if (::bind(listener_fd, p->ai_addr, p->ai_addrlen) == -1) {
                closeAll(listener_fd);
                continue; //try next
            }

            break; //success
        }

        //No one from the list succeeded - failed to bind
        if (p == NULL)  {
            cerr << "failed to bind" << endl;
            //exit(EXIT_STATUS);
            return false;
        }

        //If we got here we successfully created a socket to listen on
        //Free list as we no longer need it
        freeaddrinfo(server_info_list);

        //return the listener socket descriptor
        return listener_fd;
    }

    void SocketHub::listenSocket(int listener_fd, int backlog) {
        //Listen on the given port for incoming connections (Maximum BACKLOG waiting connections in queue)
        if (::listen(listener_fd, backlog) == -1) {
            perror("listen");
            exit(EXIT_STATUS);
        }
    }

    void SocketHub::setNonBlock(int socket) {
        int flags;
        // save current flags
        flags = fcntl(socket, F_GETFL, 0);
        if (flags == -1)
            perror("fcntl");
        // set socket to be non-blocking
        if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1)
            perror("fcntl");
    }

    void SocketHub::createSets(int listener_fd) {
        //clear master and read sets
        FD_ZERO(&masterFDSet_);
        FD_ZERO(&readFDSet_);
        // add the listener socket descriptor to the master set
        FD_SET(listener_fd, &masterFDSet_);
    }

    void SocketHub::selectSockets(int max_fd, int timeout_sec, int timeout_usec) {
        //Set timeout values (for waiting on select())
        struct timeval timeout = {timeout_sec, timeout_usec};
        //Copy all available (open) sockets to the read set
        readFDSet_ = masterFDSet_;

        //Select - 	modifies read_fds set to show which sockets are ready for reading
        //			if none are ready, it will timeout after the given timeout values
        int sel = ::select(max_fd + 1, &readFDSet_, NULL, NULL, &timeout);
        if (sel == -1) {
            perror("select");
            //exit(EXIT_STATUS);
        }
    }

    bool SocketHub::checkNewConnection(int listenFD, int& retClientFD, std::string& retHost) {
        retClientFD = 0;
        //Check if listener socket is in read set (has changed and has an incoming connection to accept)
        if (FD_ISSET(listenFD, &readFDSet_)) {
            struct sockaddr_storage their_addr;
            socklen_t addr_size = sizeof their_addr;

            //Accept the incoming connection, save the socket descriptor (clientFD)
            retClientFD = ::accept(listenFD, (struct sockaddr *)&their_addr, &addr_size);
            if (retClientFD == -1) {
                perror("accept");
                return false;
            } else { //If connection accepted
                //Set this socket to be non-blocking
                setNonBlock(retClientFD);
                //Add socket to the master set
                FD_SET(retClientFD, &masterFDSet_);
                //Update max_fd

                //Print incoming connection
                if (their_addr.ss_family == AF_INET) {
                    //IPv4
                    char ip_as_string[INET_ADDRSTRLEN];
                    inet_ntop(their_addr.ss_family,&((struct sockaddr_in *)&their_addr)->sin_addr,ip_as_string, INET_ADDRSTRLEN);
                    retHost = ip_as_string;
                    return true;
                } else if(their_addr.ss_family == AF_INET6) {
                    //IPv6
                    char ip_as_string[INET6_ADDRSTRLEN];
                    inet_ntop(their_addr.ss_family,&((struct sockaddr_in6 *)&their_addr)->sin6_addr,ip_as_string, INET6_ADDRSTRLEN);
                    retHost = ip_as_string;
                    return true;
                }
            }
        }
        return false;
    }



    void SocketHub::sendMessage(int clientFD, char* buffer, size_t len) {
        assert(len < sBufferSize);
        if (::send(clientFD, buffer, (int)len, 0) == -1) {
            perror("send");
            this->removeClient(clientFD, SocketCloseReason::SendException);
        }
    }

    void SocketHub::closeAll(int max_fd) {
        //Close all socket descriptors, this will terminate all connections
        for (int i=0; i < max_fd+1; i++) {
            //If socket is in the master set it means it is still open - so close it
            if (FD_ISSET(i, &masterFDSet_))
                ::close(i);
        }
    }

    void SocketHub::forceClose(int socketFD) {
        this->removeClient(socketFD, SocketCloseReason::Server);
    }

    void SocketHub::shutDown() {
    }

    void SocketHub::setServerHandler(IServerHandler* handler) {
        this->serverHandler_ = handler;
    }

    void SocketHub::removeClient(int socketFD, SocketCloseReason reason) {
        ::close(socketFD);
        FD_CLR(socketFD, &masterFDSet_);
        if (serverHandler_ != nullptr) {
            serverHandler_->onDisconnect(socketFD, reason);
        }
        if (reason == SocketCloseReason::Client)
            cout << "Connection has been closed by Client " << socketFD << endl;
        else if (reason == SocketCloseReason::Server)
            cout << "Connection has been closed by Server " << socketFD << endl;
    }

    int SocketHub::receiveMessage(int clientFD) {
        return ::recv(clientFD, buffer_, (int)sBufferSize, 0);
    }

    void SocketHub::zeroBuffer() {
        memset(buffer_, 0, sizeof(buffer_));
    }
}
