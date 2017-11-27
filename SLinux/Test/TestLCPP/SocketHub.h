#ifndef SocketHub_h__
#define SocketHub_h__

#include <string>
#include <functional>
#include "IServerHandler.h"
namespace Servers {

#define EXIT_STATUS 1

    class IServerHandler;

    class SocketHub {
      public:
        SocketHub();
        virtual ~SocketHub();
        /**
         * creates a listener sockets and binds it to the given port.
         * Returns true if success.
         */
        bool bindOnPort(int port, int& listener_fd);

        /**
         * This method receives listener socket and backlog number.
         * It sets the socket to start listening for incoming connections
         * with maximum backlog number of incoming connections waiting to be accepted.
         */
        void listenSocket(int,int);

        /**
         * This method receives a socket and sets it to be non-blocking.
         */
        void setNonBlock(int);

        /**
         * This method initializes the relevant sets and adds the given socket to the master set.
         */
        void createSets(int);

        /**
         * This method receives the maximum socket descriptor number (max_fd) and timeout values.
         * It checks if sockets descriptors (up to max_fd) are ready for read / write / accept connections,
         * and sets the read_fds set accordingly.
         * If none are ready it will timeout after the given timeout values.
         */
        void selectSockets(int,int,int);

        /**
         * This method a listener socket and the maximum socket descriptor number (max_fd).
         * It checks if the socket is in the read_fds set (meaning that it has a incoming connection waiting to be accepted).
         * If it is, it accepts the incoming connection and adding its socket descriptor to the master set.
         * Updates and returns the new max_fd (if changed).
         */
        bool checkNewConnection(int listenFD, int& retClientFD, std::string& retHost);

        /**
         * This method receives a socket, buffer size, and a reference to data string.
         * It checks if the socket is in the read_fds set (meaning it has incoming data to receive or it has ended the connection).
         * If the socket has ended the connection, it closes the file descriptor and delete it from the master set.
         * If the socket has incoming data, it reads it (up to buffer_size) and assign it to the given string.
         * It returns the number of bytes received or -1 if the socket is not in the read_fds set.
         */
        int receiveMessage(int clientFD);
        void sendMessage(int socketID, char* buffer, size_t len);
        void closeAll(int socketFD);
        void forceClose(int socketFD);
        void shutDown();
        void setServerHandler(IServerHandler* handler);
        const char* getBuffer() const;
        void removeClient(int socketFD, SocketCloseReason reason);
        bool canRead(int clientFD);
      private:
        void zeroBuffer();
      private:
        fd_set readFDSet_;		//Socket descriptor set that holds the sockets that are ready for read
        fd_set masterFDSet_;		//Socket descriptor set that hold all the available (open) sockets
        IServerHandler* serverHandler_;
        static const size_t sBufferSize = 2 << 15;
        char buffer_[sBufferSize];
    };
    inline bool SocketHub::canRead(int clientFD) {
        return FD_ISSET(clientFD, &readFDSet_);
    }
    inline const char* SocketHub::getBuffer() const {
        return this->buffer_;
    }
}

#endif // SocketHub_h__
