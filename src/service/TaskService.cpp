#include "TaskService.hpp"
#include "DateUtils.hpp"
#include "TaskDTO.hpp"
#include "TaskRepository.hpp"
#include <stdexcept>
#include <vector>

TaskService::TaskService(TaskRepository& taskRepository): taskRepo(taskRepository) {}

TaskDTO TaskService::createTask(const std::string& description){
    validateDescription(description);

    Task newTask = taskRepo.newTask(description);
    return TaskDTO::fromTask(newTask);
}

void TaskService::updateTaskDescription(const std::string& id, const std::string& newDescription){
    validateDescription(newDescription);
    auto task = taskRepo.getById(id);

    task.setDescription(newDescription);
    task.setUpdatedAt(DateUtils::nowToString());

    taskRepo.update(task);

}

void TaskService::updateStatus(const std::string& id, Task::Status newStatus){
    auto task = taskRepo.getById(id);

    task.setStatus(newStatus);
    task.setUpdatedAt(DateUtils::nowToString());

    taskRepo.update(task);
}

void TaskService::deleteTask(const std::string& id){
    taskRepo.deleteById(id);
}

TaskDTO TaskService::getTaskById(const std::string& id) const {
    auto task = taskRepo.getById(id);

    return TaskDTO::fromTask(task);
}

std::vector<TaskDTO> TaskService::listAllTasks() const{
    auto allTasks = taskRepo.getAll();
    std::vector<TaskDTO> allTasksDTO;

    for(auto task : allTasks){
        allTasksDTO.push_back(TaskDTO::fromTask(task));
    }

    return allTasksDTO;
}

std::vector<TaskDTO> TaskService::listAllByStatus(Task::Status status) const{
    auto allTasks = taskRepo.getAllByStatus(status);
    std::vector<TaskDTO> allTasksDTO;

    for(auto task : allTasks){
        allTasksDTO.push_back(TaskDTO::fromTask(task));
    }

    return allTasksDTO;
}

void TaskService::validateDescription(const std::string& description) const{
    if(description.empty()){
        throw std::invalid_argument("Description cannot be empty");
    }
}
