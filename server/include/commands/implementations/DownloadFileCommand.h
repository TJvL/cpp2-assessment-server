#ifndef CPP2SERVER_DOWNLOADFILECOMMAND_H
#define CPP2SERVER_DOWNLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DownloadFileCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const override;
    };
}

#endif //CPP2SERVER_DOWNLOADFILECOMMAND_H
