#include "TaskRepository.hpp"
#include "Task.hpp"
#include <algorithm>
#include <exception>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iomanip>

TaskRepository::TaskRepository(): data() {
    try {
        data = readJsonFile();
        isValidTaskArray(data);
    } catch(const std::exception& e) {
        data = {
            {"nextId", 1},
            {"tasks", json::array()}
        };

        try {
            writeJsonFile();
        } catch(const std::exception& e){
            throw std::runtime_error("Neither file opening was possible, nor creating base json file: " + std::string(e.what()));
        }
    }
}


Task TaskRepository::newTask(const std::string description) {
    int nextIdValue = data["nextId"].get<int>();

    std::string nextId = std::to_string(nextIdValue);

    Task newTask = Task(
        nextId,
        description
    );

    data["nextId"] = nextIdValue + 1;
    data["tasks"].push_back(newTask.toJson());

    writeJsonFile();

    return newTask;
}

void TaskRepository::update(const Task& task) {
    std::string taskId = task.getId();
    bool isUpdated = false;

    for(auto& taskJson : data["tasks"]){
        if(taskJson["id"] == taskId){
            taskJson = task.toJson();
            isUpdated = true;
            break;
        }
    }

    if(!isUpdated){ throw std::runtime_error("Could not find task with id " + taskId + " on update"); }

    writeJsonFile();
}

void TaskRepository::deleteById(const std::string &id) {
    auto& taskArray = data["tasks"];

    auto newEnd = std::remove_if(
        taskArray.begin(),
        taskArray.end(),
        [&id](const json& task){
            return task["id"] == id;
        }
    );

    bool idNotFound = newEnd == taskArray.end();
    if(idNotFound){ throw std::runtime_error("Task with id: " + id + " not found"); }

    taskArray.erase(newEnd, taskArray.end());
    writeJsonFile();
}

Task TaskRepository::getById(const std::string &id) const {
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

    throw std::runtime_error("Task with id: " + id + " not found");
}

std::vector<Task> TaskRepository::getAll() const {
    std::vector<Task> allTasks;

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

    return allTasks;
}

std::vector<Task> TaskRepository::getAllByStatus(Task::Status status) const{
    std::vector<Task> allTasksByStatus;

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

    return allTasksByStatus;
}

json TaskRepository::readJsonFile() const{
    std::ifstream f(JSONPATH);

    if (!f.is_open()) {
        throw std::runtime_error("Error when opening json/tasks.json for reading");
    }

    return json::parse(f);
}

void TaskRepository::writeJsonFile(){
    std::ofstream o(JSONPATH);

    if (!o.is_open()) {
        throw std::runtime_error("Error when opening json/tasks.json para writing");
    }

    try{
        o << std::setw(4) << data << std::endl;
        o.close();
    } catch(std::exception& e) {
        throw std::runtime_error("Could not save the json file: " + std::string(e.what()));
    }

}

void TaskRepository::isValidTaskArray(const json &data){
    bool isValid = data.contains("tasks") && data["tasks"].is_array();
    if(!isValid){ throw std::runtime_error("The opened json file does not contain a valid task component"); }
}
