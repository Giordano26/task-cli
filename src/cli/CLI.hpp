#ifndef CLI_HPP
#define CLI_HPP


#include "TaskDTO.hpp"
#include "TaskService.hpp"
#include <functional>
#include <unordered_map>
class CLI {
private:
    TaskService& taskService;

public:
    CLI(TaskService& taskService);
    void run(int argc, char* argv []);

private:
    using CommandHandler = std::function<void(int, char**)>;
    std::unordered_map<std::string, CommandHandler> commandMap;

    void handleAdd(int argc, char* argv[]);
    void handleList(int argc, char* argv[]);
    void handleUpdate(int argc, char* argv[]);
    void handleDelete(int argc, char* argv[]);
    void handleMark(int argc, char* argv[]);

    void showHelp() const;
    void showTask(const TaskDTO& task) const;

    void registerCommands();
};

#endif
