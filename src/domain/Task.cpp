#include "Task.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


Task::Task(const std::string& id, const std::string& description)
    : id(id),
      description(description),
      status(Status::TODO),
      createdAt(nowToString()),
      updatedAt(nowToString())
{ }

Task::Task(const std::string& id, 
           const std::string& description, 
           const std::string& status,
           const std::string& createdAt, 
           const std::string& updatedAt)
 : id(id),
   description(description),
   status(stringToStatus(status)),
   createdAt(createdAt),
   updatedAt(updatedAt)
{ }

void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::setStatus(Status status) {
    this->status = status;
}

void Task::setUpdatedAt(const std::string& updatedAt) {
    this->updatedAt = updatedAt;
}

std::string Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

std::string Task::getStatus() const {
    return statusToString(status);
}

std::string Task::getCreatedAt() const {
    return createdAt;
}

std::string Task::getUpdatedAt() const {
    return updatedAt;
}

std::string Task::statusToString(Status status) const {
    switch (status) {
        case Status::TODO:
            return "To-do";
        case Status::IN_PROGRESS:
            return "In progress";
        case Status::DONE:
            return "Done";
        default:
            return "Unknown";
    }
}

Task::Status Task::stringToStatus(const std::string& status){
    if (status == "To-do") return Status::TODO;
    if (status == "In progress") return Status::IN_PROGRESS;
    if (status == "Done") return Status::DONE;
    return Status::TODO;
}

std::string Task::nowToString() {
    const auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}