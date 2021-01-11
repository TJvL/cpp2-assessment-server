cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(server_tests)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(INCLUDES
        ../server/include/Constants.h
        ../server/include/Application.h
        ../server/include/communication/Server.h
        ../server/include/communication/ClientConnection.h
        ../server/include/commands/AbstractCommand.h
        ../server/include/commands/CommandName.h
        ../server/include/commands/CommandFactory.h
        ../server/include/commands/CommandMapper.h
        ../server/include/commands/implementations/ServerInformationCommand.h
        ../server/include/commands/implementations/ListDirectoryCommand.h
        ../server/include/commands/implementations/DownloadFileCommand.h
        ../server/include/commands/implementations/UploadFileCommand.h
        ../server/include/commands/implementations/RenameCommand.h
        ../server/include/commands/implementations/DeleteCommand.h
        ../server/include/commands/implementations/MakeDirectoryCommand.h
        ../server/include/commands/implementations/CloseConnectionCommand.h
        ../server/include/filesystem/FileSystemManager.h
        ../server/include/filesystem/FileInfo.h
        ../server/include/filesystem/FileType.h
        ../server/include/filesystem/FileTypeMapper.h)

set(SOURCE_FILES
        ../server/src/Application.cpp
        ../server/src/communication/Server.cpp
        ../server/src/communication/ClientConnection.cpp
        ../server/src/commands/CommandFactory.cpp
        ../server/src/commands/implementations/ServerInformationCommand.cpp
        ../server/src/commands/implementations/ListDirectoryCommand.cpp
        ../server/src/commands/implementations/DownloadFileCommand.cpp
        ../server/src/commands/implementations/UploadFileCommand.cpp
        ../server/src/commands/implementations/RenameCommand.cpp
        ../server/src/commands/implementations/DeleteCommand.cpp
        ../server/src/commands/implementations/MakeDirectoryCommand.cpp
        ../server/src/commands/implementations/CloseConnectionCommand.cpp
        ../server/src/filesystem/FileSystemManager.cpp
        ../server/src/filesystem/FileInfo.cpp)

set(TEST_FILES Tests.cpp)

add_executable(server_tests
        ${TEST_FILES}
        ${INCLUDES}
        ${SOURCE_FILES})

target_include_directories(server_tests PRIVATE ../lib/catch2)
target_include_directories(server_tests PRIVATE ../lib/asio-standalone)

target_link_libraries(server_tests PRIVATE Threads::Threads)
