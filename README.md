<div align="center">
</div>

# Movie Booking System
A Command-Line Application for Booking Movie Tickets

## Introduction
The Movie Booking System is a command-line application implemented in C++. It allows users to book movie tickets, view movie information, and manage user data. The program provides separate consoles for administrators and users, each with different functionalities.

## Workflow
The program follows the following workflow:

1. **Main Menu**: The program starts by displaying the main menu, giving the user the option to log in as an admin or a user.

2. **Admin Login**: If the user selects the admin option, the program prompts for an admin password. If the password is correct, the admin console is displayed.

3. **Admin Console**: In the admin console, the admin can perform various actions like adding a movie, deleting a movie, viewing user information, etc.

4. **User Login**: If the user selects the user option from the main menu, the user console is displayed.

5. **User Console**: In the user console, the user can book a movie or exit the user console.

6. **Movie Booking**: When booking a movie, the user is presented with a list of available movies and prompted to select one.

7. **Select Time Slot and Provide Information**: After selecting a movie, the user is prompted to choose an available time slot and provide their information.

8. **Confirmation and Next Steps**: The booking is then confirmed, and the user can choose to book another movie or exit the user console.

9. **Return to Main Menu**: If the admin or user chooses to exit their respective consoles, the program returns to the main menu.

10. **Program Termination**: The program continues to display the main menu until the user chooses to exit the program.

## File Structure
The program is structured into the following files:

- `main.cpp`: This is the entry point of the program. It contains the main function that starts the execution of the application.

- `admin.h` and `admin.cpp`: These files contain the class definition and implementation for the Admin class. The Admin class provides functionalities for the admin console, such as adding movies, deleting movies, viewing user information, etc.

- `fileio.h` and `fileio.cpp`: These files contain the class definition and implementation for the FileIO class. The FileIO class handles reading from and writing to files, allowing the program to store and retrieve movie and user data.

- `utils.h` and `utils.cpp`: These files contain utility functions used throughout the program, such as input validation, error handling, and formatting output.

- `user.h` and `user.cpp`: These files contain the class definition and implementation for the User class. The User class provides functionalities for the user console, such as viewing available movies and booking movie tickets.

## Data Structures
The code utilizes the following data structures:

- `std::unordered_map<std::string, Movie>`: This unordered map stores movies as key-value pairs, where the movie title is the key and the associated movie information is the value. It allows fast access to movie information based on the title.

- `std::vector<User>`: This vector stores user information. Each element in the vector represents a user and contains attributes such as name, phone number, and email address. The vector allows storing and accessing multiple user records.

Both data structures are used to store and manage movie and user data, respectively, throughout the program. The unordered map provides efficient lookup based on movie titles, while the vector allows storing and iterating over multiple user records.

## Algorithms
The program incorporates various algorithms to implement its functionality:

- **Input Validation**: The program uses regular expressions (`std::regex_match`) to validate user input, such as full names, phone numbers, and email addresses. Regular expressions allow for pattern matching and ensure that the entered data meets the required format.

- **Error Handling**: Error handling techniques are used to handle invalid user input gracefully. The program provides meaningful error messages to guide the user in correcting their input and prevents the program from crashing due to unexpected input.

- **Sorting**: The `std::sort` algorithm is used to sort movie titles in alphabetical order. This allows for a more organized display of movie information.

## Libraries Used
The following libraries are used in the code:

- `iostream`: Provides input/output stream operations for reading input from the user (`std::cin`) and displaying output to the console (`std::cout`).
- `fstream`: Enables file stream operations, allowing reading from and writing to files (`std::ifstream`, `std::ofstream`).
- `sstream`: Provides string stream operations for reading from and writing to strings (`std::stringstream`).
- `cstdlib`: Provides general-purpose functions for C programming language.
- `unordered_map`: Used for storing key-value pairs in an unordered map data structure. In this code, it is used to store movie information, with the movie title as the key and the corresponding movie details as the value (`std::unordered_map<std::string, Movie>`).
- `vector`: Supports dynamic arrays and is used to store lists of movie titles and user information (`std::vector<std::string>`, `std::vector<User>`).
- `algorithm`: Provides various algorithms such as sorting (`std::sort`) and finding the maximum value (`std::max`). It is used in this code to sort movie titles and format output.
- `windows.h` and `conio.h`: These Windows-specific libraries are used for console-related functions. In this code, they may be used for clearing the console screen (`clearScreen()`) and reading user input without waiting for the Enter key (`_getch()`).
- `unordered_set`: Used for storing unique elements in no particular order. In this code, it may be used to store unique phone numbers or email addresses (`std::unordered_set<std::string>`).
- `iomanip`: Provides input/output manipulation for formatting output, such as aligning text (`std::setw`, `std::left`).
- `regex`: Supports regular expressions for pattern matching and validation. In this code, it may be used for validating email addresses or performing pattern matching operations on strings (`std::regex_match`).
- `string`: Used for string operations and manipulations (`std::string`).

These libraries provide essential functionalities for various aspects of the code, including input/output handling, file operations, data storage, manipulation of strings, and more.

## Usage
To use the Movie Booking System:

1. Clone the repository and navigate to the project directory.
2. Compile the code using a C++ compiler (e.g., g++).
3. Run the compiled executable.
4. Follow the on-screen prompts to access the admin or user console and interact with the program.

## Dependencies
The Movie Booking System has the following dependencies:

- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

## Contributing
Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

## Acknowledgments
This project was inspired by the need for a simple movie booking system. It aims to provide a foundational structure for similar applications, making it easier for developers to build upon and customize the system according to their specific requirements.
