#include "SessionHandler.h"
#include <iostream>

SessionHandler::SessionHandler(ssh_session session) : session_(session), sftp_(nullptr) {}

SessionHandler::~SessionHandler() {
    if (sftp_) {
        sftp_free(sftp_);
    }
    if (session_) {
        ssh_disconnect(session_);
        ssh_free(session_);
    }
}

void SessionHandler::authenticate() {
    if (ssh_handle_key_exchange(session_) != SSH_OK) {
        throw std::runtime_error("SSH key exchange failed");
    }
    // Authentication placeholder (e.g., password-based)
    ssh_message message = ssh_message_get(session_);
    if (!message) {
        throw std::runtime_error("Authentication failed");
    }
    ssh_message_reply_default(message);
    ssh_message_free(message);
}

void SessionHandler::initializeSFTP() {
    sftp_ = sftp_new(session_);
    if (!sftp_) {
        throw std::runtime_error("Failed to create SFTP session");
    }
    if (sftp_init(sftp_) != SSH_OK) {
        throw std::runtime_error("Failed to initialize SFTP session");
    }
}

void SessionHandler::handleSession() {
    try {
        authenticate();
        initializeSFTP();
        FileManager manager(sftp_);
        manager.handleRequests();
    } catch (const std::exception& e) {
        std::cerr << "Session error: " << e.what() << "\n";
    }
}
