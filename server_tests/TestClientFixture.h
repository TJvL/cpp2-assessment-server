#ifndef CPP2SERVER_TESTCLIENTFIXTURE_H
#define CPP2SERVER_TESTCLIENTFIXTURE_H

#include "TestServerConnection.h"

class TestClientFixture {
public:
    TestClientFixture();

    ~TestClientFixture();

    void sendRemoteTermination();

    TestServerConnection &getTestServerConnection();

    static const std::string TEST_FILE_CONTENT;
    static const std::string TEST_HOST;
    static const std::string TEST_SYNC_DIRECTORY;
    static const int TEST_PORT;
private:
    TestServerConnection testServerConnection;
};

#endif //CPP2SERVER_TESTCLIENTFIXTURE_H
