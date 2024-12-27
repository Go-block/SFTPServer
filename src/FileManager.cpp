#include "FileManager.h"
#include <iostream>

FileManager::FileManager(sftp_session sftp) : sftp_(sftp) {}

void FileManager::handleRequests() {
    // Placeholder for handling SFTP requests
    std::cout << "Handling SFTP requests...\n";
    listDirectory("/");
}

void FileManager::listDirectory(const std::string& path) {
    sftp_dir dir = sftp_opendir(sftp_, path.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << path << "\n";
        return;
    }

    sftp_attributes attr;
    while ((attr = sftp_readdir(sftp_, dir)) != nullptr) {
        std::cout << "File: " << attr->name << "\n";
        sftp_attributes_free(attr);
    }

    sftp_closedir(dir);
}
