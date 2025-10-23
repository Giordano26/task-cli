#include <iostream>
#include "TaskRepository.hpp"

int main(){
    TaskRepository taskRepository;

    std::cout << "TaskRepository Tests" << std::endl;
    std::cout << "getAll test" << std::endl;

    auto allTasks = taskRepository.getAll();

    for(const auto& task : allTasks){
        std::cout << task.getDescription() << std::endl;
    }

    std::cout << "getById" << std::endl;

    std::cout << taskRepository.getById("2").getDescription() << std::endl;

    std::cout << "getByStatus" << std::endl;

    auto allTasksByStatus = taskRepository.getAllByStatus(Task::Status::TODO);
    
    for(const auto& task : allTasksByStatus){
        std::cout << task.getDescription() << std::endl;
    }

    return 0;
}
