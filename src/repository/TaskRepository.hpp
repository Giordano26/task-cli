#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H
#define JSONPATH "json/tasks.json"

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Task.hpp"

using json = nlohmann::json;

class TaskRepository {
public:
    TaskRepository();

    void deleteById(const std::string& taskId);
    Task newTask(const std::string description);
    void update(const Task& task);
    Task getById(const std::string& taskId) const;
    std::vector<Task> getAll() const;
    std::vector<Task> getAllByStatus(Task::Status status) const;

private:
    json data;
    // Helpers for JSON
    json readJsonFile() const;
    void writeJsonFile();
    void isValidTaskObject(const json &data);
};

#endif
