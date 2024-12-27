
#ifndef SFTPSERVER_H
#define SFTPSERVER_H

#include <string>
#include <libssh/libssh.h>
#include <libssh/server.h>
#include "SessionHandler.h"


class SFTPServer {
public:
    SFTPServer(const std::string& address, int port);
    ~SFTPServer();
    void start();

private:
    std::string address_;
    int port_;
    ssh_bind sshBind_;
    void initialize();
};

#endif
