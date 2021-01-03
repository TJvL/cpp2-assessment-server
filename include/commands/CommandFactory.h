#ifndef CPP2SERVER_COMMANDFACTORY_H
#define CPP2SERVER_COMMANDFACTORY_H

#include <memory>
#include "CommandName.h"
#include "AbstractCommand.h"

namespace cpp2 {
    class CommandFactory {
    public:
        std::unique_ptr<AbstractCommand> createCommand(const CommandName commandName) const;

    private:
        template<ACommand AC>
        std::unique_ptr<AC> create() const {
            return std::make_unique<AC>();
        }
    };
}

#endif //CPP2SERVER_COMMANDFACTORY_H
