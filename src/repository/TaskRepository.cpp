#include "TaskRepository.hpp"
#include "Task.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>


Task TaskRepository::newTask(const std::string description){
    json data = readJsonFile();
    int nextIdValue = data["nextId"].get<int>();

    std::string nextId = std::to_string(nextIdValue);

    Task newTask = Task(
        nextId,
        description
    );

    data["nextId"] = nextIdValue + 1;

    if(isValidTaskArray(data)){
        data["tasks"].push_back(newTask.toJson());
    }

    writeJsonFile(data);

    return newTask;
}

void TaskRepository::update(const Task& task){
    json data = readJsonFile();
    std::string taskId = task.getId();

    if(isValidTaskArray(data)){
        for(auto& taskJson : data["tasks"]){
            if(taskJson["id"] == taskId){
                taskJson = task.toJson();
                break;
            }
        }
    }

    writeJsonFile(data);
}

void TaskRepository::deleteById(const std::string &id){
    json data = readJsonFile();

    if(isValidTaskArray(data)){
        auto& taskArray = data["tasks"];

        auto newEnd = std::remove_if(
            taskArray.begin(),
            taskArray.end(),
            [&id](const json& task){
                return task["id"] == id;
            }
        );

        if(newEnd != taskArray.end()){
            taskArray.erase(newEnd, taskArray.end());
            writeJsonFile(data);
        } else {
            throw std::runtime_error("Task with id: " + id + " not found");
        }
    }
}

Task TaskRepository::getById(const std::string &id) const{
    json data = readJsonFile();

    if(isValidTaskArray(data)){
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
    json data = readJsonFile();
    std::vector<Task> allTasks;

    if(isValidTaskArray(data)){
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

std::vector<Task> TaskRepository::getAllByStatus(Task::Status status) const{
    json data = readJsonFile();
    std::vector<Task> allTasksByStatus;

    if(isValidTaskArray(data)){
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
