#include<iostream>

typedef struct{
    std::string name;
    int weight;
    bool isDone;
}task_str;

int main(int argc, char* argv[]){
    task_str task;
    int choice;
    bool isOpen = true;
    FILE *file;

    while (isOpen==true) {
        std::cout << "======TO-DO: ur mom=======" << std::endl;
        std::cout << "1) add task :3" << std::endl;
        std::cout << "2) list task :3 " << std::endl;
        std::cout << "x) exit app :3" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "What do you want to do: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "ADDED TASK" << std::endl;
                break;
            case 2:
                std::cout << "LISTED TASKS" << std::endl;
                break;
            default:
                isOpen = false;
                break;
        }
    }

    return 0;
}