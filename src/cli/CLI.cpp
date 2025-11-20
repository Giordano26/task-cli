#include "CLI.hpp"
#include "TaskDTO.hpp"
#include "TaskService.hpp"
#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <stdexcept>

CLI::CLI(TaskService& s): taskService(s){
    registerCommands();
}

void CLI::registerCommands(){

    commandMap["add"] = [this](int argc, char** argv){
        handleAdd(argc, argv);
    };

    commandMap["list"] = [this](int argc, char** argv){
        handleList(argc, argv);
    };

    commandMap["update"] = [this](int argc, char** argv){
        handleUpdate(argc, argv);
    };

    commandMap["delete"] = [this](int argc, char** argv){
        handleDelete(argc, argv);
    };

    commandMap["mark"] = [this](int argc, char** argv){
        handleMark(argc, argv);
    };
}

void CLI::run(int argc, char* argv[]){
    if(argc < 2){ showHelp(); return;}

    std::string command = argv[1];

    try {
        auto it = commandMap.find(command);
        bool commandNotFound = it == commandMap.end();

        if(commandNotFound){
            std::cerr << "Command not found: " << command << std::endl;
            showHelp();
            return;
        }

        it->second(argc, argv);

    } catch(const std::exception& e){
        std::cerr << "Error during the execution of " << e.what() << std::endl;
    }
}

void CLI::handleAdd(int argc, char* argv[]){
    if(argc < 3){ throw std::runtime_error("Task description is missing \n task-cli add \"description\""); }

    std::string description = argv[2];

    TaskDTO newTask = taskService.createTask(description);

    std::cout << "Task added successfully (ID: " << newTask.id << ")\n";
}

void CLI::handleList(int argc, char* argv[]){
    std::vector<TaskDTO> tasks;

    switch(argc){
        case 2: {
            tasks = taskService.listAllTasks();
            break;
        }
        case 3:{
            Task::Status status = Task::jsonStringToStatus(argv[3]);
            tasks = taskService.listAllByStatus(status);
            break;
        }
        default:
            throw std::runtime_error("Too many args for list command");
    }

    if(tasks.empty()){
        std::cout << "No tasks registered!" << std::endl;
        return;
    }

    for(const auto& task : tasks){
        showTask(task);
    }
}

void CLI::handleUpdate(int argc, char* argv[]){
    if(argc < 4){ throw std::runtime_error("Missing args for update \n task-cli update <id> <new_description>"); }

    std::string id = argv[2];
    std::string newDescription = argv[3];

    taskService.updateTaskDescription(id, newDescription);

    std::cout << "Task " << id << "description updated successfully" << std::endl;
}

void CLI::handleMark(int argc, char* argv[]){
    if(argc < 3){ throw std::runtime_error("Missing args for mark \n task-cli mark <new_status>"); }

    std::string id = argv[2];
    std::string newStatus = argv[3];

    std::transform(newStatus.begin(), newStatus.end(), newStatus.begin(),[](unsigned char c){
        return std::toupper(c);
    });

    taskService.updateStatus(id, Task::jsonStringToStatus(newStatus));

    std::cout << "Task " << id <<"status updated sucessfuyllt" << std::endl;
}

void CLI::handleDelete(int argc, char* argv[]){
    if(argc < 3){ throw std::runtime_error("Missing args for mark \n task-cli delete <id>"); }

    std::string id = argv[2];

    taskService.deleteTask(id);

    std::cout << "Task " << id << " has been deleted sucessfully" << std::endl;
}

void CLI::showHelp() const{
    std::cout << "Task Tracker CLI" << std::endl;
    std::cout << "Available commands: " << std::endl;
    std::cout << "  add <desc> \n  list [status] \n  update <id> <status> \n  delete <id>" << std::endl;
}

void CLI::showTask(const TaskDTO& task) const{
    std::cout << "[" << task.id << "] " << task.description << std::endl;
    std::cout << "Status: " << task.status << std::endl;
}
