#include "TaskRepository.hpp"
#include "Task.hpp"
#include <nlohmann/json.hpp>
#include <fstream>


void TaskRepository::save(const Task &task){
}

void TaskRepository::deleteById(const std::string &id)
{
}

Task TaskRepository::getById(const std::string &id) const{
    json data = TaskRepository::readJsonFile();

    if(TaskRepository::isValidTaskArray(data)){
       for(const auto& taskJson : data["tasks"]){
            if(taskJson["id"] == id){
                return Task(
                    taskJson["id"],
                    taskJson["description"],
                    Task::jsonStringToStatus(taskJson["status"]),
                    taskJson["createdAt"],
                    taskJson["updatedAt"]
                );
            }
       }
    }

    throw std::runtime_error("Task with id: " + id + " not found");
}

std::vector<Task> TaskRepository::getAll() const{   
    json data = TaskRepository::readJsonFile();
    std::vector<Task> allTasks;

    if(TaskRepository::isValidTaskArray(data)){
        for(const auto& taskJson : data["tasks"]){
            Task task(
                taskJson["id"],
                taskJson["description"],
                Task::jsonStringToStatus(taskJson["status"]),
                taskJson["createdAt"],
                taskJson["updatedAt"]
            );

            allTasks.push_back(task);
        }
    }

    return allTasks;
}

std::vector<Task> TaskRepository::getAllByStatus(Task::Status status) const
{   
    json data = TaskRepository::readJsonFile();
    std::vector<Task> allTasksByStatus;

    if(TaskRepository::isValidTaskArray(data)){
        for(const auto& taskJson : data["tasks"]){
            if(Task::jsonStringToStatus(taskJson["status"]) == status){
                Task task(
                    taskJson["id"],
                    taskJson["description"],
                    Task::jsonStringToStatus(taskJson["status"]),
                    taskJson["createdAt"],
                    taskJson["updatedAt"]
                );

                allTasksByStatus.push_back(task);
            }
        }
    }

    return allTasksByStatus;
}

std::string TaskRepository::getNextId(){
    json data = TaskRepository::readJsonFile();

    return data["nextId"];
}

json TaskRepository::readJsonFile() const{
    std::ifstream f("json/tasks.json");

    if (!f.is_open()) {
        throw std::runtime_error("Error when opening json/tasks.json for reading");
    }

    return json::parse(f);
}

void TaskRepository::writeJsonFile(const json& jsonContent){
    std::ofstream o("json/tasks.json");

    if (!o.is_open()) {
        throw std::runtime_error("Error when opening json/tasks.json para writing");
    }

    o << std::setw(4) << jsonContent << std::endl;
}

bool TaskRepository::isValidTaskArray(const json &data){
    return data.contains("tasks") && data["tasks"].is_array() ;
}
