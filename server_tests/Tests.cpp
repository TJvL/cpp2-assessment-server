#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "../server/include/Application.h"
#include "../server/include/Constants.h"
#include "TestClientFixture.h"

int runApplication() {
    cpp2::Application application{TestClientFixture::TEST_PORT, TestClientFixture::TEST_SYNC_DIRECTORY, true};
    return application.run();
}

// custom main to setup a server application in a different thread and shut it down after all tests.
int main(int argc, char *argv[]) {
    auto task = std::async(std::launch::async, runApplication);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int result = Catch::Session().run(argc, argv);

    TestClientFixture testClientFixture{};
    testClientFixture.sendRemoteTermination();

    auto serverExitCode = task.get();

    // if server application did not shutdown with a 500 then remote termination failed
    if (serverExitCode != 500) {
        return EXIT_FAILURE;
    }

    return result;
}

TEST_CASE_METHOD(TestClientFixture, "Commands") {
    SECTION("INFO Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("INFO");

            const auto infoResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(infoResponse == INFO_RESPONSE);
        }
    }

    SECTION("DIR Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // needed paths
            const auto listDirectoryName = "list_dir";
            const auto listFileName = "list_file";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto listDirectoryPath = testSyncDirectoryPath / listDirectoryName;
            const auto listFilePath = testSyncDirectoryPath / listFileName;

            // create a directory and a file
            std::filesystem::create_directory(listDirectoryPath);
            std::ofstream listFileStream{listFilePath};
            listFileStream << TestClientFixture::TEST_FILE_CONTENT;
            listFileStream.close();

            // send and receive
            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();

            testServerConnection.sentOutgoingMessage("DIR");
            testServerConnection.sentOutgoingMessage(""); // list the root dir

            const auto listEntriesResponse = testServerConnection.waitForIncomingMessage();

            const auto listEntries = std::stoi(listEntriesResponse);

            std::vector<std::string> list{};
            list.reserve(listEntries);
            for (auto i = 0; i < listEntries; ++i) {
                list.push_back(testServerConnection.waitForIncomingMessage());
            }

            // assert responses
            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(listEntries == 2); // expect two entries

            // entry format should be:
            // {'D' or 'F'}|{file name}|YYYY-MM-DD HH:MM:SS|{file size}
            REQUIRE(std::regex_match(list[0],
                                     std::regex{
                                             "D\\|list_dir\\|(19[0-9]{2}|2[0-9]{3})-(0[1-9]|1[012])-([123]0|[012][1-9]|31) ([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\\|0"
                                     }));
            REQUIRE(std::regex_match(list[1],
                                     std::regex{
                                             "F\\|list_file\\|(19[0-9]{2}|2[0-9]{3})-(0[1-9]|1[012])-([123]0|[012][1-9]|31) ([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\\|21"
                                     }));
        }

        SECTION("Error: no such directory") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();

            testServerConnection.sentOutgoingMessage("DIR");
            testServerConnection.sentOutgoingMessage("non_existing_dir");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_DIRECTORY);
        }
    }

    SECTION("GET Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto getFileName = "get_file";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto getFilePath = testSyncDirectoryPath / getFileName;

            // create a test file
            std::ofstream listFileStream{getFilePath};
            listFileStream << TestClientFixture::TEST_FILE_CONTENT;
            listFileStream.close();

            // send and receive
            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("GET");
            testServerConnection.sentOutgoingMessage(getFileName);

            const auto fileSizeResponse = testServerConnection.waitForIncomingMessage();
            const auto fileSize = std::stoul(fileSizeResponse);

            std::ostringstream stringStream;
            auto &inputStream = testServerConnection.getIncomingStream();

            std::copy_n(std::istreambuf_iterator<char>(inputStream),
                        fileSize,
                        std::ostreambuf_iterator<char>(stringStream));
            inputStream.ignore(1);

            const auto fileContentResponse = stringStream.str();

            // assert responses
            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(fileSizeResponse == "21"); // file size should be 21
            REQUIRE(fileContentResponse == TestClientFixture::TEST_FILE_CONTENT);
        }

        SECTION("Error: no such file") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("GET");
            testServerConnection.sentOutgoingMessage("failure.txt");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_FILE);
        }

        SECTION("Error: no permission") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto getFileName = "get_file";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto getFilePath = testSyncDirectoryPath / getFileName;

            // create a test file
            std::ofstream getFileStream{getFilePath};
            getFileStream << TestClientFixture::TEST_FILE_CONTENT;
            getFileStream.close();
            std::filesystem::permissions(getFilePath, std::filesystem::perms::none);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("GET");
            testServerConnection.sentOutgoingMessage(getFileName);

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_PERMISSION);
        }
    }

    SECTION("PUT Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto putFileName = "put_file";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto putFilePath = testSyncDirectoryPath / putFileName;

            // create a test file
            std::stringstream putFileStream;
            putFileStream << TestClientFixture::TEST_FILE_CONTENT;
            const auto fileSize = TestClientFixture::TEST_FILE_CONTENT.length();

            // send and receive
            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("PUT");
            testServerConnection.sentOutgoingMessage(putFileName);
            testServerConnection.sentOutgoingMessage(std::to_string(fileSize));

            const auto okResponse = testServerConnection.waitForIncomingMessage();

            testServerConnection.pipeStreamTillEnd(putFileStream);

            // give filesystem a chance to finish writing the file
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            // assert responses
            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(okResponse == OK_RESPONSE);
            REQUIRE(std::filesystem::exists(putFilePath));
            REQUIRE(std::filesystem::is_regular_file(putFilePath));
            REQUIRE(std::filesystem::file_size(putFilePath) == fileSize);
        }

        SECTION("Error: no such directory") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("PUT");
            testServerConnection.sentOutgoingMessage("does_not_exist/failure.txt");
            testServerConnection.sentOutgoingMessage("21");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_DIRECTORY);
        }

        SECTION("Error: no permission") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto putDirectoryName = "put_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto putDirectoryPath = testSyncDirectoryPath / putDirectoryName;

            // create a test directory
            std::filesystem::create_directory(putDirectoryPath);
            std::filesystem::permissions(putDirectoryPath, std::filesystem::perms::none);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("PUT");
            testServerConnection.sentOutgoingMessage(std::filesystem::path{putDirectoryName} / "does_not_matter.txt");
            testServerConnection.sentOutgoingMessage("21");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_PERMISSION);
        }
    }

    SECTION("REN Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto renameDirectoryName = "rename_directory";
            const auto newDirectoryName = "new_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto renameDirectoryPath = testSyncDirectoryPath / renameDirectoryName;
            const auto newDirectoryPath = testSyncDirectoryPath / newDirectoryName;

            // create a test directory
            std::filesystem::create_directory(renameDirectoryPath);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("REN");
            testServerConnection.sentOutgoingMessage(renameDirectoryName);
            testServerConnection.sentOutgoingMessage(newDirectoryName);

            const auto okResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(okResponse == OK_RESPONSE);
            REQUIRE_FALSE(std::filesystem::exists(renameDirectoryPath));
            REQUIRE(std::filesystem::exists(newDirectoryPath));
            REQUIRE(std::filesystem::is_directory(newDirectoryPath));
        }

        SECTION("Error: No such file or directory") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("REN");
            testServerConnection.sentOutgoingMessage("does_not_exist");
            testServerConnection.sentOutgoingMessage("does_not_matter");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_PATH);
        }

        SECTION("Error: no permission") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto renameDirectoryName = "rename_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto renameDirectoryPath = testSyncDirectoryPath / renameDirectoryName;

            // create a test directory
            std::filesystem::create_directory(renameDirectoryPath);
            std::filesystem::permissions(renameDirectoryPath, std::filesystem::perms::none);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("REN");
            testServerConnection.sentOutgoingMessage(renameDirectoryName);
            testServerConnection.sentOutgoingMessage("does_not_matter");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_PERMISSION);
        }
    }

    SECTION("DEL Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto delDirectoryName = "delete_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto delDirectoryPath = testSyncDirectoryPath / delDirectoryName;

            // create a test directory
            std::filesystem::create_directory(delDirectoryPath);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("DEL");
            testServerConnection.sentOutgoingMessage(delDirectoryName);

            const auto okResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(okResponse == OK_RESPONSE);
            REQUIRE_FALSE(std::filesystem::exists(delDirectoryPath));
        }

        SECTION("Error: No such file or directory") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("DEL");
            testServerConnection.sentOutgoingMessage("does_not_exist");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_PATH);
        }

        SECTION("Error: no permission") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto delDirectoryName = "delete_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto delDirectoryPath = testSyncDirectoryPath / delDirectoryName;

            // create a test directory
            std::filesystem::create_directory(delDirectoryPath);
            std::filesystem::permissions(delDirectoryPath, std::filesystem::perms::none);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("REN");
            testServerConnection.sentOutgoingMessage(delDirectoryName);
            testServerConnection.sentOutgoingMessage("does_not_matter");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_PERMISSION);
        }
    }

    SECTION("MKDIR Command") {
        SECTION("Success") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto mkdirDirectoryName = "mkdir_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto mkdirDirectoryPath = testSyncDirectoryPath / mkdirDirectoryName;

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("MKDIR");
            testServerConnection.sentOutgoingMessage("");
            testServerConnection.sentOutgoingMessage(mkdirDirectoryName);

            const auto okResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(okResponse == OK_RESPONSE);
            REQUIRE(std::filesystem::exists(mkdirDirectoryPath));
        }

        SECTION("Error: No such directory") {
            auto &testServerConnection = getTestServerConnection();

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("MKDIR");
            testServerConnection.sentOutgoingMessage("does_not_exist");
            testServerConnection.sentOutgoingMessage("does_not_matter");

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_SUCH_DIRECTORY);
        }

        SECTION("Error: no permission") {
            auto &testServerConnection = getTestServerConnection();

            // setup needed paths
            const auto mkdirDirectoryName = "mkdir_directory";
            const auto testSyncDirectoryPath = std::filesystem::current_path() / TestClientFixture::TEST_SYNC_DIRECTORY;
            const auto mkdirDirectoryPath = testSyncDirectoryPath / mkdirDirectoryName;
            const auto parentDirectoryName = "parent_directory";
            const auto parentDirectoryPath = testSyncDirectoryPath / parentDirectoryName;

            std::filesystem::create_directory(parentDirectoryPath);
            std::filesystem::permissions(parentDirectoryPath, std::filesystem::perms::none);

            const auto welcomeResponse = testServerConnection.waitForIncomingMessage();
            testServerConnection.sentOutgoingMessage("MKDIR");
            testServerConnection.sentOutgoingMessage(parentDirectoryName);
            testServerConnection.sentOutgoingMessage(mkdirDirectoryName);

            const auto errorResponse = testServerConnection.waitForIncomingMessage();

            REQUIRE(welcomeResponse == WELCOME_RESPONSE);
            REQUIRE(errorResponse == ERROR_NO_PERMISSION);
        }
    }

    SECTION("Non existing command") {
        auto &testServerConnection = getTestServerConnection();

        const auto welcomeResponse = testServerConnection.waitForIncomingMessage();

        testServerConnection.sentOutgoingMessage("DOES NOT EXIST");

        const auto errorResponse = testServerConnection.waitForIncomingMessage();

        REQUIRE(welcomeResponse == WELCOME_RESPONSE);
        REQUIRE(errorResponse == "the name: DOES NOT EXIST has no mapped command name");
    }
}
