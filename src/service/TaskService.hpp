#ifndef TASKSERVICE_HPP
#define TASKSERVICE_HPP
#include "TaskRepository.hpp"
#include "Task.hpp"
#include "TaskDTO.hpp"
#include <string>
#include <vector>

class TaskService {
    private:
        TaskRepository& taskRepo;

    public:
        TaskService(TaskRepository& taskRepository);

        TaskDTO createTask(const std::string& description);
        void updateTaskDescription(const std::string& id, const std::string& newDescription);
        void updateStatus(const std::string& id, Task::Status newStatus);
        void deleteTask(const std::string& id);

        TaskDTO getTaskById(const std::string& id) const;
        std::vector<TaskDTO> listAllTasks() const;
        std::vector<TaskDTO> listAllByStatus(Task::Status status) const;

    private:
        void validateDescription(const std::string& description) const;
};

#endif
