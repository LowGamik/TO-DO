#include <cstddef>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdlib.h>

/*
 * TO-DO LIST APPLICATION
 * A simple command-line to-do list manager that stores tasks in a binary file
 * 
 * ERROR CODES:
 * -1 => FILE PATH/NAME WASN'T ENTERED
 * -2 => COULDN'T ACCESS SPECIFIED FILE
 */

/**
 * Structure to represent a single task
 * Contains all necessary information for task management
 */
typedef struct{
    std::string name;    // Task description/name
    int weight;          // Task priority/weight (higher = more important)
    bool isDone;         // Task completion status (true = completed, false = pending)
} task_str;

/**
 * Main application entry point
 * @param argc - Number of command line arguments
 * @param argv - Array of command line arguments (argv[1] should be the data file path)
 * @return 0 on success, negative values on error
 */
int main(int argc, char* argv[]){
    // Variable declarations
    task_str task;          // Current task being processed
    size_t nameLength;      // Length of task name for binary file I/O
    int choice;             // User's menu choice
    bool isOpen = true;     // Main loop control flag
    FILE *data;             // File pointer for data storage

    // Command line argument validation
    if(argc < 2){ 
        std::cout << "Application requires the path of the file (example: .\\output.exe binary.bin)" << std::endl;
        return -1;
    }

    // Clear screen for clean startup
    system("cls");

    // Main application loop
    while (isOpen == true) {
        // Display main menu
        std::cout << "======TO-DO: ur mom=======" << std::endl;
        std::cout << "1) add task :3" << std::endl;
        std::cout << "2) list task :3 " << std::endl;
        std::cout << "x) exit app :3" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "What do you want to do: ";

        // Input validation for menu choice
        if (!(std::cin >> choice)) { 
            // Clear error flag and ignore invalid input
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number (1, 2, or 3)" << std::endl;
            continue; // Restart loop iteration
        }

        // Process user's menu selection
        switch (choice) {
            case 1: // ADD TASK FUNCTIONALITY
                system("cls"); // Clear screen for clean interface
                
                // Get task information from user
                std::cout << "Task description: ";
                std::cin.ignore(); // Clear input buffer from previous cin operation
                std::getline(std::cin, task.name); // Get full line including spaces
                
                std::cout << "Weight of the task: ";
                std::cin >> task.weight;
                
                task.isDone = false; // New tasks are always incomplete

                // Open file in append binary mode to add new task
                data = fopen(argv[1], "ab");
                if(data == NULL){
                    std::cout << "The file wasn't found or couldn't be accessed with current permissions" << std::endl;
                    return -2;
                }

                // Write task data to binary file
                // Format: [name_length][name_string][weight][isDone]
                nameLength = task.name.size();
                fwrite(&nameLength, sizeof(size_t), 1, data);           // Write string length first
                fwrite(task.name.c_str(), sizeof(char), nameLength, data); // Write string data
                fwrite(&task.weight, sizeof(int), 1, data);             // Write task weight
                fwrite(&task.isDone, sizeof(bool), 1, data);            // Write completion status

                fclose(data); // Close file to ensure data is saved
                system("cls"); // Clear screen after operation
                break;

            case 2: // LIST TASKS FUNCTIONALITY
                system("cls");
                std::cout << "LISTED TASKS" << std::endl;
                
                // Open file in read binary mode to display all tasks
                data = fopen(argv[1], "rb");
                if(data == NULL){
                    std::cout << "The file wasn't found or couldn't be accessed with current permissions" << std::endl;
                    return -2;
                }

                // Read and display all tasks from binary file
                while (fread(&nameLength, sizeof(size_t), 1, data) == 1) {
                    // Read task data in the same order it was written
                    task.name.resize(nameLength);                           // Prepare string for reading
                    fread(&task.name[0], sizeof(char), nameLength, data);   // Read task name
                    fread(&task.weight, sizeof(int), 1, data);              // Read task weight
                    fread(&task.isDone, sizeof(bool), 1, data);             // Read completion status

                    // Display task information in readable format
                    std::cout << "Task: " << task.name << std::endl
                              << "Weight: " << task.weight << std::endl
                              << "Done: " << (task.isDone ? "Yes" : "No") << std::endl;
                }
                
                fclose(data); // Close file after reading
                
                // Wait for user input before returning to menu
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(); // Clear any remaining input
                std::cin.get();    // Wait for Enter key
                system("cls");     // Clear screen before showing menu again
                break;

            default: // EXIT APPLICATION
                isOpen = false; // Set loop control flag to exit
                break;
        }
    }
    
    system("cls"); // Clear screen on exit for clean termination
    return 0;      // Successful program termination
}