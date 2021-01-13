#include <thread>
#include <filesystem>
#include "TestClientFixture.h"

const std::string TestClientFixture::TEST_FILE_CONTENT = "This is test content."; // NOLINT(cert-err58-cpp)
const std::string TestClientFixture::TEST_HOST = "localhost"; // NOLINT(cert-err58-cpp)
const std::string TestClientFixture::TEST_SYNC_DIRECTORY = "test_sync"; // NOLINT(cert-err58-cpp)
const int TestClientFixture::TEST_PORT = 5000;

TestClientFixture::TestClientFixture()
        : testServerConnection(TEST_HOST, std::to_string(TEST_PORT)) {
    const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
    std::filesystem::create_directory(testSyncDirectoryPath);
}

TestClientFixture::~TestClientFixture() {
    testServerConnection.sentOutgoingMessage("QUIT");

    const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
    std::filesystem::remove_all(testSyncDirectoryPath);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void TestClientFixture::sendRemoteTermination() {
    testServerConnection.sentOutgoingMessage("REMOTE_TERMINATION");
}

TestServerConnection &TestClientFixture::getTestServerConnection() {
    return testServerConnection;
}
