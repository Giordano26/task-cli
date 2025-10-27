#ifndef TASKDTO_HPP
#define TASKDTO_HPP
#include <string>
#include "Task.hpp"

struct TaskDTO {
    std::string id;
    std::string description;
    std::string status;

    TaskDTO() = default;

    TaskDTO(const std::string& id,
            const std::string& description,
            const std::string& status
    );

    static TaskDTO fromTask(const Task& task);

};

#endif
