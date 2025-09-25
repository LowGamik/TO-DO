#include <cstddef>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdlib.h>
/*

ERROR MESSAGES:
-1 => FILE PATH/NAME WASNT ENTERED
-2 => COULDNT ACCESS SAID FILE

*/
typedef struct{
    std::string name;
    int weight;
    bool isDone;
}task_str; //task structure

int main(int argc, char* argv[]){
    task_str task;
    size_t nameLength;
    int choice;
    bool isOpen = true;
    FILE *data;

    if(argc < 2){ //ERROR HANDLING IF THE PATH/NAME WASNT WRITTEN
        std::cout << "Aplication requires the path of the file (example: .\\output.exe binary.bin)" << std::endl;
        return -1;
    }
    system("cls");
    while (isOpen==true) {
        std::cout << "======TO-DO: ur mom=======" << std::endl; //MENU
        std::cout << "1) add task :3" << std::endl;
        std::cout << "2) list task :3 " << std::endl;
        std::cout << "x) exit app :3" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "What do you want to do: ";
        if (!(std::cin >> choice)) { // HANDLE NON-INT INPUT
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number (1, 2, or 3)" << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                system("cls");
                std::cout << "Task description: ";
                std::cin.ignore();
                std::getline(std::cin, task.name);
                std::cout << "Weight of the task: ";
                std::cin >> task.weight;
                task.isDone = false;

                data = fopen(argv[1],"ab");
                if(data == NULL){
                    std::cout << "The file wasnt found or couldnt be accessed with current permisions" << std::endl;
                    return -2;
                }

                nameLength = task.name.size();
                fwrite(&nameLength, sizeof(size_t), 1, data);
                fwrite(task.name.c_str(), sizeof(char), nameLength, data);
                fwrite(&task.weight, sizeof(int), 1, data);
                fwrite(&task.isDone, sizeof(bool), 1, data);    

                fclose(data);
                system("cls");

                break;
            case 2:
                system("cls");
                std::cout << "LISTED TASKS" << std::endl;
                data = fopen(argv[1], "rb");
                if(data == NULL){
                    std::cout << "The file wasnt found or couldnt be accessed with current permisions" << std::endl;
                    return -2;
                }
                while (fread(&nameLength, sizeof(size_t), 1, data) == 1) {
                    task.name.resize(nameLength);
                    fread(&task.name[0], sizeof(char), nameLength, data);
                    fread(&task.weight, sizeof(int), 1, data);
                    fread(&task.isDone, sizeof(bool), 1, data);

                    std::cout << "Task: " << task.name << std::endl
                              << "Weight: " << task.weight <<std::endl
                              << "Done: " << (task.isDone ? "Yes" : "No") << std::endl;
                }
                fclose(data);
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                system("cls");
                break;
            default:
                isOpen = false;
                break;
        }
    }
    system("cls");
    return 0;
}