#include "TaskDTO.hpp"
#include "Task.hpp"

TaskDTO::TaskDTO(
    const std::string& id,
    const std::string& description,
    const std::string& status
): id(id), description(description), status(status) {}

TaskDTO TaskDTO::fromTask(const Task &task){
    return TaskDTO(
        task.getId(),
        task.getDescription(),
        task.getStatusToDisplay()
    );
};
