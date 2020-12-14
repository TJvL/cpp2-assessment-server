#include <iostream>
#include "../include/Application.h"

namespace cpp2 {
    Application::Application(const int serverPort)
            : server(serverPort) {}

    int Application::run() const {
        auto result = EXIT_SUCCESS;
        auto running = true;
        while (running) {
            try {
                server.handleClientConnection();
            } catch(const std::runtime_error &error) {
                std::cerr << "server: " << error.what() << '\n';
                continue;
            } catch (const std::exception &exception) {
                std::cerr << "server: " << exception.what() << '\n';
                result = EXIT_FAILURE;
                running = false;
            }
        }
        return result;
    }
}
