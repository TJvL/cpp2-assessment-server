#include <iostream>
#include "../include/Application.h"
#include "../include/Constants.h"

namespace cpp2 {
    Application::Application(const int port, const std::string &syncDirectoryName, const bool canRemoteTerminate)
            : server(port, syncDirectoryName, canRemoteTerminate) {}

    int Application::run() const {
        auto result = EXIT_SUCCESS;
        auto running = true;
        while (running) {
            try {
                server.handleClientConnection();
            } catch (const TerminationException &terminationException) {
                std::cout << terminationException.what() << NEW_LINE;
                result = REMOTE_TERMINATION_EXIT;
                running = false;
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
