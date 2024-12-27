#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <libssh/sftp.h>

class FileManager {
public:
    explicit FileManager(sftp_session sftp);
    void handleRequests();

private:
    sftp_session sftp_;
    void listDirectory(const std::string& path);
};

#endif
