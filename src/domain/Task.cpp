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
           Status status,
           const std::string& createdAt,
           const std::string& updatedAt)
 : id(id),
   description(description),
   status(status),
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

std::string Task::getStatusToDisplay() const {
    return statusToDisplay(status);
}

Task::Status Task::getStatus() const{
    return status;
}

std::string Task::getCreatedAt() const {
    return createdAt;
}

std::string Task::getUpdatedAt() const {
    return updatedAt;
}

std::string Task::statusToDisplay(Status status) const {
    switch (status) {
        case Status::TODO:       return "To-do";
        case Status::IN_PROGRESS: return "In progress";
        case Status::DONE:        return "Done";
        default:                  return "To-do";
    }
}

std::string Task::statusToJsonString(Status status) {
    switch (status) {
        case Status::TODO:       return "TODO";
        case Status::IN_PROGRESS: return "IN_PROGRESS";
        case Status::DONE:        return "DONE";
        default:                  return "TODO";
    }
}

Task::Status Task::jsonStringToStatus(const std::string &status) {
    if (status == "TODO") return Task::Status::TODO;
    if (status == "IN_PROGRESS") return Task::Status::IN_PROGRESS;
    if (status == "DONE") return Task::Status::DONE;
    return Task::Status::TODO;
}

std::string Task::nowToString() {
    const auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

 json Task::toJson() const {
    json j;
    j["id"] = id;
    j["description"] = description;
    j["status"] = statusToJsonString(status);
    j["createdAt"] = createdAt;
    j["updatedAt"] = updatedAt;

    return j;
 }
