#include "SFTPServer.h"
#include <iostream>
int main() {
    SFTPServer server("127.0.0.1", 8022);
    try {
    // Kode untuk memulai SSH SFTPServer
    server.start();
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

    
    
    return 0;
}
