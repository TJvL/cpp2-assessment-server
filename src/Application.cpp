#include <iostream>
#include "../include/Application.h"
#include "../include/ClientConnection.h"
#include "../include/Constants.h"

namespace cpp2 {
    Application::Application(const int serverPort)
            : serverPort(serverPort) {}

    int Application::run() const {
        auto result = EXIT_SUCCESS;
        auto running = true;
        while (running) {
            try {
                handleClientConnection();
            } catch (const std::exception &exception) {
                std::cerr << "server: " << exception.what() << '\n';
                result = EXIT_FAILURE;
                running = false;
            }
        }
        return result;
    }

    void Application::handleClientConnection() const {
        // wait for the connection to be established
        std::cout << "waiting for the client to connect" << cpp2::lf;
        cpp2::ClientConnection clientConnection{serverPort};

        std::cout << "the client has connected" << cpp2::lf;
        clientConnection.sentOutgoingMessage("Welcome to AvanSync server 1.0");

        auto handlingConnection = true;
        while (handlingConnection) {
            auto message = clientConnection.waitForIncomingMessage();
            std::cout << "client says: " << message << cpp2::lf;

            // handle command
            if (message == "quit") {
                clientConnection.sentOutgoingMessage("Bye.");
                std::cout << "will disconnect from client" << cpp2::lf;
                handlingConnection = false;
            } else {
                clientConnection.sentOutgoingMessage(message); // simply echo the request
            }
        }
    }
}
