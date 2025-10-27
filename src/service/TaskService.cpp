#include "TaskService.hpp"
#include "TaskDTO.hpp"
#include "TaskRepository.hpp"
#include <stdexcept>

TaskService::TaskService(TaskRepository& taskRepository): taskRepo(taskRepository) {}

TaskDTO TaskService::createTask(const std::string& description){
    validateDescription(description);

    Task newTask = taskRepo.newTask(description);
    return TaskDTO::fromTask(newTask);
}

void TaskService::updateTaskDescription(const std::string& id, const std::string& newDescription){

}

void TaskService::validateDescription(const std::string& description) const{
    if(description.empty()){
        throw std::invalid_argument("Description cannot be empty");
    }
}
