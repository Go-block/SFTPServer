#ifndef SESSIONHANDLER_H
#define SESSIONHANDLER_H

#include <libssh/libssh.h>
#include <libssh/server.h>
#include <libssh/sftp.h>
#include "FileManager.h"

class SessionHandler {
public:
    SessionHandler(ssh_session session);
    ~SessionHandler();
    void handleSession();

private:
    ssh_session session_;
    sftp_session sftp_;
    void authenticate();
    void initializeSFTP();
};

#endif
