#include "SFTPServer.h"
#include <iostream>


SFTPServer::SFTPServer(const std::string& address, int port)
    : address_(address), port_(port), sshBind_(nullptr) {
    initialize();
}

SFTPServer::~SFTPServer() {
    if (sshBind_) {
        ssh_bind_free(sshBind_);
    }
}

void SFTPServer::initialize() {
    sshBind_ = ssh_bind_new();
    if (!sshBind_) {
        throw std::runtime_error("Failed to create SSH bind");
    }
    ssh_bind_options_set(sshBind_, SSH_BIND_OPTIONS_BINDADDR, address_.c_str());
    ssh_bind_options_set(sshBind_, SSH_BIND_OPTIONS_BINDPORT, &port_);
}

void SFTPServer::start() {
    if (ssh_bind_listen(sshBind_) != SSH_OK) {
        throw std::runtime_error("Failed to start SSH server");
    }
    std::cout << "SFTP server listening on " << address_ << ":" << port_ << "\n";

    while (true) {
        ssh_session session = ssh_new();
        if (!session) {
            std::cerr << "Failed to create session\n";
            continue;
        }

        if (ssh_bind_accept(sshBind_, session) == SSH_OK) {
            SessionHandler handler(session);
            handler.handleSession();
        } else {
            ssh_free(session);
        }
    }
}
