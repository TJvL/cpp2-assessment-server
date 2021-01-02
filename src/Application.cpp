#include <iostream>
#include "../include/Application.h"
#include "../include/Constants.h"

namespace cpp2 {
    Application::Application(const int port, const std::string &syncDirectoryName)
            : server(port, syncDirectoryName) {}

    int Application::run() const {
        auto result = EXIT_SUCCESS;
        auto running = true;
        while (running) {
            try {
                server.handleClientConnection();
            } catch (const std::runtime_error &error) {
                std::cout << "error: " << error.what() << NEW_LINE;
                continue;
            } catch (const std::exception &exception) {
                std::cout << "fatal error: " << exception.what() << NEW_LINE;
                result = EXIT_FAILURE;
                running = false;
            }
        }
        return result;
    }
}
