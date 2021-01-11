#include <iostream>
#include "../include/Application.h"
#include "../include/Constants.h"

int main(int argc, char *argv[]) {
    int port = 5000;
    std::string syncDirectoryName{"sync"};

    if (argc >= 2) {
        try {
            port = std::stoi(argv[1]);
        } catch (std::invalid_argument &error) {
            std::cerr << "could not parse port argument: "
                      << argv[1]
                      << " fallback to port: 5000"
                      << NEW_LINE;
        }
    }

    if (argc >= 3) {
        syncDirectoryName = argv[2];
    }

    cpp2::Application application{port, syncDirectoryName};
    return application.run();
}
