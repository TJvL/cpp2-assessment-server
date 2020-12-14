//
// Created by thomas on 14-12-20.
//

#ifndef CPP2SERVER_LISTDIRECTORYCOMMAND_H
#define CPP2SERVER_LISTDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class ListDirectoryCommand : public AbstractCommand {
    public:
        explicit ListDirectoryCommand(cpp2::ClientConnection& clientConnection);

        ~ListDirectoryCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_LISTDIRECTORYCOMMAND_H
