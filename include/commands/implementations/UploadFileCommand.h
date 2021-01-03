#ifndef CPP2SERVER_UPLOADFILECOMMAND_H
#define CPP2SERVER_UPLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class UploadFileCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) override;
    };
}

#endif //CPP2SERVER_UPLOADFILECOMMAND_H
