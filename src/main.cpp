#include "TaskRepository.hpp"
#include "TaskService.hpp"
#include "CLI.hpp"

int main(int argc, char* argv[]){

    TaskRepository repo;
    TaskService service(repo);
    CLI cli(service);

    cli.run(argc, argv);

    return 0;
}
