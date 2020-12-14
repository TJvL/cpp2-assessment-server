cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(Cpp2Server)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(INCLUDES
        include/Constants.h
        include/Application.h
        include/Server.h
        include/ClientConnection.h
        include/commands/AbstractCommand.h
        include/commands/CommandName.h
        include/commands/CommandFactory.h
        include/commands/CommandMapper.h
        include/commands/implementations/ServerInformationCommand.h
        include/commands/implementations/ListDirectoryCommand.h
        include/commands/implementations/DownloadFileCommand.h
        include/commands/implementations/UploadFileCommand.h
        include/commands/implementations/RenameFileCommand.h
        include/commands/implementations/DeleteFileCommand.h
        include/commands/implementations/MakeDirectoryCommand.h
        include/commands/implementations/CloseConnectionCommand.h
        )

set(SOURCE_FILES
        src/Main.cpp
        src/Application.cpp
        src/Server.cpp
        src/ClientConnection.cpp
        src/commands/CommandFactory.cpp
        src/commands/implementations/ServerInformationCommand.cpp
        src/commands/implementations/ListDirectoryCommand.cpp
        src/commands/implementations/DownloadFileCommand.cpp
        src/commands/implementations/UploadFileCommand.cpp
        src/commands/implementations/RenameFileCommand.cpp
        src/commands/implementations/DeleteFileCommand.cpp
        src/commands/implementations/MakeDirectoryCommand.cpp
        src/commands/implementations/CloseConnectionCommand.cpp
        )

add_executable(Cpp2Server
        ${INCLUDES}
        ${SOURCE_FILES}
        )

target_link_libraries(Cpp2Server PRIVATE Threads::Threads)
