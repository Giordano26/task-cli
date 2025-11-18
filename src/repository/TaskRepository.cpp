#include "TaskRepository.hpp"
#include "Task.hpp"
#include <exception>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iomanip>

TaskRepository::TaskRepository(): data() {
    try {
        data = readJsonFile();
        isValidTaskObject(data);
    } catch(const std::exception& e) {
        data = {
            {"nextId", 1},
            {"tasks", json::object()}
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
    data["tasks"][nextId] = newTask.toJson();

    writeJsonFile();
    return newTask;
}

void TaskRepository::update(const Task& task) {
    std::string taskId = task.getId();
    bool idExists = data["tasks"].contains(taskId);

    if(!idExists){ throw std::runtime_error("Could not find task with id: "+ taskId + " on update"); }

    data["task"][taskId] = task.toJson();
    writeJsonFile();
}

void TaskRepository::deleteById(const std::string &taskId) {
    bool wasErased = data["tasks"].erase(taskId);

    if(!wasErased){ throw std::runtime_error("Could not find task with id: "+ taskId + " on delete"); }

    writeJsonFile();
}

Task TaskRepository::getById(const std::string &taskId) const {
    bool idExists = data["tasks"].contains(taskId);

    if(!idExists){ throw std::runtime_error("Could not find task with id: "+ taskId + " on get by id"); }

    const auto& taskJson = data["tasks"][taskId];

    return Task(
            taskJson["id"],
            taskJson["description"],
            Task::jsonStringToStatus(taskJson["status"]),
            taskJson["createdAt"],
            taskJson["updatedAt"]
        );
}

std::vector<Task> TaskRepository::getAll() const {
    std::vector<Task> allTasks;

    for(const auto& item : data["tasks"].items()){

        const auto& taskJson = item.value();

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

    for(const auto& item : data["tasks"].items()){

        const auto& taskJson = item.value();

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

void TaskRepository::isValidTaskObject(const json &data){
    bool isValid = data.contains("tasks") && data["tasks"].is_object();
    if(!isValid){ throw std::runtime_error("The opened json file does not contain a valid task component"); }
}
