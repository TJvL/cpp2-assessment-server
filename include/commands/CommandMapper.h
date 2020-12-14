#ifndef CPP2SERVER_COMMANDMAPPER_H
#define CPP2SERVER_COMMANDMAPPER_H

#include <string>
#include <unordered_map>
#include "CommandName.h"

namespace cpp2 {
    class CommandMapper {
    public:
        CommandMapper()
                : commandMap({
                                     {"INFO",  CommandName::SERVER_INFORMATION},
                                     {"DIR",   CommandName::LIST_DIRECTORY},
                                     {"GET",   CommandName::DOWNLOAD_FILE},
                                     {"PUT",   CommandName::UPLOAD_FILE},
                                     {"REN",   CommandName::RENAME_FILE},
                                     {"DEL",   CommandName::DELETE_FILE},
                                     {"MKDIR", CommandName::MAKE_DIRECTORY},
                                     {"QUIT",  CommandName::CLOSE_CONNECTION},
                             }) {};

        ~CommandMapper() = default;

        const CommandName& getCommandName (const std::string& name) const {
            try {
                return commandMap.at(name);
            } catch (const std::out_of_range &error) {
                throw std::runtime_error("the name: " + name + " has no mapped command name");
            }
        }
    private:
        const std::unordered_map<std::string, CommandName> commandMap;
    };
}

#endif //CPP2SERVER_COMMANDMAPPER_H
