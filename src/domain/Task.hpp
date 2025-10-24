#ifndef TASK_H
#define TASK_H
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Task {
public:
    enum class Status {
        TODO,
        IN_PROGRESS,
        DONE
    };

    // Constructor
    Task(const std::string& id, const std::string& description);

    Task(const std::string& id,
        const std::string& description,
        Status status,
        const std::string& createdAt,
        const std::string& updatedAt
    );


    // Setters
    void setDescription(const std::string& description);
    void setStatus(Status status);
    void setUpdatedAt(const std::string& updatedAt);

    // Getters
    std::string getId() const;
    std::string getDescription() const;
    std::string getStatusToDisplay() const;
    Status getStatus() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;

    //Helper methods
    static std::string statusToJsonString(Status status);
    static Status jsonStringToStatus(const std::string& status);
    json toJson() const;


private:
    const std::string id;
    std::string description;
    Status status;
    const std::string createdAt;
    std::string updatedAt;

    // Helper methods
    std::string nowToString();
    std::string statusToDisplay(Status status) const;

};

#endif
