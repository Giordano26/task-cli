#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Task.hpp"

using json = nlohmann::json;

class TaskRepository {
public:
    void deleteById(const std::string& id);
    Task newTask(const std::string description);
    void update(const Task& task);
    Task getById(const std::string& id) const;
    std::vector<Task> getAll() const;
    std::vector<Task> getAllByStatus(Task::Status status) const;

private:
    // Helpers for JSON
    json readJsonFile() const;
    void writeJsonFile(const json& jsonContent);
    static bool isValidTaskArray(const json &data);
};

#endif
