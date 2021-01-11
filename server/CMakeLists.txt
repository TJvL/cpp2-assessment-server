cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(server)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(INCLUDES
        include/Constants.h
        include/Application.h
        include/communication/Server.h
        include/communication/ClientConnection.h
        include/commands/AbstractCommand.h
        include/commands/CommandName.h
        include/commands/CommandFactory.h
        include/commands/CommandMapper.h
        include/commands/implementations/ServerInformationCommand.h
        include/commands/implementations/ListDirectoryCommand.h
        include/commands/implementations/DownloadFileCommand.h
        include/commands/implementations/UploadFileCommand.h
        include/commands/implementations/RenameCommand.h
        include/commands/implementations/DeleteCommand.h
        include/commands/implementations/MakeDirectoryCommand.h
        include/commands/implementations/CloseConnectionCommand.h
        include/filesystem/FileSystemManager.h
        include/filesystem/FileInfo.h
        include/filesystem/FileType.h
        include/filesystem/FileTypeMapper.h)

set(SOURCE_FILES
        src/Main.cpp
        src/Application.cpp
        src/communication/Server.cpp
        src/communication/ClientConnection.cpp
        src/commands/CommandFactory.cpp
        src/commands/implementations/ServerInformationCommand.cpp
        src/commands/implementations/ListDirectoryCommand.cpp
        src/commands/implementations/DownloadFileCommand.cpp
        src/commands/implementations/UploadFileCommand.cpp
        src/commands/implementations/RenameCommand.cpp
        src/commands/implementations/DeleteCommand.cpp
        src/commands/implementations/MakeDirectoryCommand.cpp
        src/commands/implementations/CloseConnectionCommand.cpp
        src/filesystem/FileSystemManager.cpp
        src/filesystem/FileInfo.cpp)

add_executable(server
        ${INCLUDES}
        ${SOURCE_FILES})

target_include_directories(server PRIVATE ../lib/asio-standalone)

target_link_libraries(server PRIVATE Threads::Threads)
