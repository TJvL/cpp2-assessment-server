#ifndef CPP2SERVER_COMMANDFACTORY_H
#define CPP2SERVER_COMMANDFACTORY_H

#include <memory>
#include "CommandName.h"
#include "AbstractCommand.h"

namespace cpp2 {
    class CommandFactory {
    public:
        CommandFactory() = default;

        ~CommandFactory() = default;

        std::unique_ptr<AbstractCommand> createCommand(const CommandName commandName, ClientConnection& clientConnection, FileSystemManager &fileSystemManager) const;

    private:
        template<ACommand AC>
        std::unique_ptr<AC> create(ClientConnection& clientConnection, FileSystemManager &syncManager) const {
            return std::make_unique<AC>(clientConnection, syncManager);
        }
    };
}

#endif //CPP2SERVER_COMMANDFACTORY_H
