#ifndef CPP2SERVER_COMMANDNAME_H
#define CPP2SERVER_COMMANDNAME_H

namespace cpp2 {
    enum CommandName {
        SERVER_INFORMATION,
        LIST_DIRECTORY,
        MAKE_DIRECTORY,
        DOWNLOAD_FILE,
        UPLOAD_FILE,
        RENAME_FILE,
        DELETE_FILE,
        CLOSE_CONNECTION
    };
}

#endif //CPP2SERVER_COMMANDNAME_H
