#ifndef CPP2SERVER_APPLICATION_H
#define CPP2SERVER_APPLICATION_H

namespace cpp2 {
    class Application {
    public:
        Application(const int serverPort);

        virtual ~Application() = default;

        int run() const;

        void handleClientConnection() const;

    private:
        const int serverPort;
    };
}

#endif //CPP2SERVER_APPLICATION_H
