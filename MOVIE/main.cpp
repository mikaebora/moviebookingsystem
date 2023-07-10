
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <unordered_set>
#include <iomanip>
#include <regex>
#include <string>

struct Movie {
    std::string title;
    double price;
    std::string duration;
    std::vector<std::string> availableTimes;
    std::string cinema;
    bool exists;
};


struct Client {
    std::string name;
    std::string phoneNumber;
    std::string emailAddress;
    std::string movieTitle;
    std::string availableTime;
    std::string cinema;
};

std::unordered_map<std::string, Movie> movies;
std::vector<Client> clients;


void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
    std::cout << std::flush;
}

void showAdminConsole();
void showUserConsole();
void bookMovie();
void uploadMovie();
void viewClients();
void modifyClient();
void deleteClient();
void saveDataToFile();
void loadDataFromFile();
void modifyMovieInfo();
void viewMovieInfo();
void deleteMovie();

bool isValidTimeFormat(const std::string& time) {
    const std::regex pattern(R"(^(0?[1-9]|1[0-2]):[0-5][0-9](AM|PM)$)");
    return std::regex_match(time, pattern);
}

bool isValidDurationFormat(const std::string& duration) {
    if (duration.length() != 8) {
        return false;
    }

    if (!isdigit(duration[0]) || !isdigit(duration[1]) ||
        duration[2] != ':' ||
        !isdigit(duration[3]) || !isdigit(duration[4]) ||
        duration[5] != ':' ||
        !isdigit(duration[6]) || !isdigit(duration[7])) {
        return false;
    }

    int hour = std::stoi(duration.substr(0, 2));
    int minute = std::stoi(duration.substr(3, 2));
    int second = std::stoi(duration.substr(6, 2));

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return false;
    }

    return true;
}



bool isValidFullName(const std::string& name) {
    return !name.empty() && !std::any_of(name.begin(), name.end(), ::isdigit);
}

bool isDuplicateFullName(const std::string& name) {
    for (const auto& client : clients) {
        if (client.name == name) {
            return true;
        }
    }
    return false;
}
bool isValidPhoneNumber(const std::string& phoneNumber) {
    return phoneNumber.length() == 11 && std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
}
bool isDuplicatePhoneNumber(const std::string& phoneNumber) {
    for (const auto& client : clients) {
        if (client.phoneNumber == phoneNumber) {
            return true;
        }
    }
    return false;
}
bool isValidEmailAddress(const std::string& emailAddress) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(emailAddress, pattern) && emailAddress.find("@") != 0 && emailAddress.find(".") != emailAddress.length() - 1;
}

bool isDuplicateEmailAddress(const std::string& emailAddress) {
    for (const auto& client : clients) {
        if (client.emailAddress == emailAddress) {
            return true;
        }
    }
    return false;
}
bool isMovieTitleExists(const std::string& movieTitle, const std::unordered_map<std::string, Movie>& movies) {
    auto it = movies.find(movieTitle);
    if (it != movies.end()) {
        return it->second.exists;
    }
    return false;
}


bool isValidPrice(const std::string& price) {
    const std::regex pattern(R"([0-9]+(\.[0-9]{1,2})?)");
    return std::regex_match(price, pattern);
}
bool isValidAvailableTime(const std::string& time) {
    std::regex timeRegex(R"(\d{1,2}:\d{2}(AM|PM))");
    return std::regex_match(time, timeRegex);
}

bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time) {
    for (const auto& availableTime : availableTimes) {
        if (availableTime == time) {
            return true;
        }
    }
    return false;
}
void showAdminConsole() {
    std::string password = "admin";
    std::string inputPassword;

    clearScreen();

    std::cout << "Admin Console\n";
    std::cout << "-------------\n\n";

    int attempts = 3;
    bool authenticated = false;

    while (attempts > 0) {
        clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Enter password (Attempts left: " << attempts << "): ";

        char c;
        while ((c = _getch()) != '\r') {
            if (c == '\b') {
                if (!inputPassword.empty()) {
                    inputPassword.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                inputPassword += c;
                std::cout << '*';
            }
        }

        if (inputPassword == password) {
            authenticated = true;
            break;
        } else {
            std::cout << "\nIncorrect password!\n";
            inputPassword = "";
            --attempts;

        }
    }

    if (authenticated) {

        clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Authentication successful!\n";

        clearScreen();

    } else {

    clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Maximum attempts exceeded. returning to main menu\n";

        return;
    }

    while (true) {
        std::cout << "Admin Console\n";
        std::cout << "1. Upload a movie\n";
        std::cout << "2. View clients booked movie\n";
        std::cout << "3. Modify a user's booked movie\n";
        std::cout << "4. Delete a user's booked movie\n";
        std::cout << "5. Modify movie information\n";
        std::cout << "6. View movies info\n";
        std::cout << "7. delete a movie\n";
        std::cout << "8. Exit\n";

        std::cout << "Enter your choice (1-8): ";
        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

       switch (choice) {
    case 1:
        std::cout << "Upload a movie\n";
        uploadMovie();
        break;
    case 2:
        std::cout << "View clients booked movie\n";
        viewClients();
        break;
    case 3:
        std::cout << "Modify a client's booked movie\n";
        modifyClient();
        break;
    case 4:
        std::cout << "Delete a client's booked movie\n";
        deleteClient();
        break;
    case 5:
        std::cout << "Modify movie information\n";
        modifyMovieInfo();
        break;
    case 6:
        std::cout << "View movie information\n";
        viewMovieInfo();
        break;
    case 7:
        std::cout << "Delete a movie\n";
        deleteMovie();
        break;
    case 8:
        return;
    default:
        std::cout << "Invalid choice!\n";
}

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }
}

void uploadMovie() {
    Movie movie;
    std::string input;

    clearScreen();
    std::cout << "Upload a movie\n";
    std::cout << "('abort' to cancel)\n";

    while (true) {
        std::cout << "Movie title: ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        if (input.empty()) {
            std::cout << "Invalid movie title!\n";
        } else {
            movie.title = input;
            break;
        }
    }

    while (true) {
        std::cout << "Price: ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> movie.price && movie.price > 0.0) {
            break;
        } else {
            std::cout << "Invalid price!\n";
        }
    }

    while (true) {
        std::cout << "Duration (hh:mm:ss): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        if (isValidDurationFormat(input)) {
            movie.duration = input;
            break;
        } else {
            std::cout << "Invalid duration! Use the format 'hh:mm:ss'.\n";
        }
    }

    while (true) {
        std::cout << "Choose a cinema:\n";
        std::cout << "1. Cinema 1\n";
        std::cout << "2. Cinema 2\n";
        std::cout << "3. Cinema 3\n";
        std::cout << " choose (1-3): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Cinema selection canceled.\n";
            return;
        }

        if (input == "1") {
            movie.cinema = "Cinema 1";
            break;
        } else if (input == "2") {
            movie.cinema = "Cinema 2";
            break;
        } else if (input == "3") {
            movie.cinema = "Cinema 3";
            break;
        } else {
            std::cout << "Invalid cinema choice! Please enter a number from the list.\n";
        }
    }

    while (true) {
        std::cout << "Available time (hh:mmAM/PM, between 8:00AM and 11:00PM): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::string hourStr, minuteStr, meridiem;
        std::regex timeRegex(R"((\d{1,2}):(\d{2})(AM|PM))", std::regex_constants::icase);
        std::smatch timeMatch;

        if (std::regex_match(input, timeMatch, timeRegex)) {
            hourStr = timeMatch[1].str();
            minuteStr = timeMatch[2].str();
            meridiem = timeMatch[3].str();

            int hour = std::stoi(hourStr);
            int minute = std::stoi(minuteStr);

            if ((hour >= 1 && hour <= 12) && (minute >= 0 && minute <= 59)) {
                std::ostringstream formattedTime;
                formattedTime << std::setw(2) << std::setfill('0') << hourStr << ":" << std::setw(2) << std::setfill('0') << minuteStr << meridiem;
                movie.availableTimes.push_back(formattedTime.str());

                while (true) {
        std::cout << "Do you want to add more available times? (yes/no): ";
        std::getline(std::cin, input);
        if (input == "yes") {
            std::cout << "Enter the available time (hh:mmAM/PM): ";
            std::getline(std::cin, input);
            if (std::regex_match(input, timeMatch, timeRegex)) {
                hourStr = timeMatch[1].str();
                minuteStr = timeMatch[2].str();
                meridiem = timeMatch[3].str();
                hour = std::stoi(hourStr);
                minute = std::stoi(minuteStr);
                if ((hour >= 1 && hour <= 12) && (minute >= 0 && minute <= 59)) {
                    formattedTime.str("");
                    formattedTime << std::setw(2) << std::setfill('0') << hourStr << ":" << std::setw(2) << std::setfill('0') << minuteStr << meridiem;
                    movie.availableTimes.push_back(formattedTime.str());
                } else {
                    std::cout << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format.\n";
                }
            } else {
                std::cout << "Invalid time format! Please use the 'hh:mmAM/PM' format.\n";
            }
        }         else if (input == "no") {
                        movies[movie.title] = movie;
                        saveDataToFile();
                        std::cout << "Movie uploaded successfully!\n";
                        viewMovieInfo();
                        return;
                    } else if (input == "abort") {
                        std::cout << "Movie upload canceled.\n";
                        return;
                    } else {
                        std::cout << "Invalid input! Enter 'yes', 'no', or 'abort'.\n";
                    }
                }
            } else {
                std::cout << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format.\n";
            }
        } else {
            std::cout << "Invalid time format! Please use the 'hh:mmAM/PM' format.\n";
        }
    }

    movies[movie.title] = movie;

    std::cout << "Movie uploaded successfully!\n";
    viewMovieInfo();
}

void viewClients() {
    loadDataFromFile();
    clearScreen();
    std::cout << "View clients who have booked a movie:\n\n";

    // Sort clients by name
    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    // Calculate the maximum lengths for other fields
    size_t maxNameLength = 0;
    size_t maxPhoneNumberLength = 0;
    size_t maxEmailAddressLength = 0;
    size_t maxMovieTitleLength = 0;
    size_t maxCinemaLength = 0;
    size_t maxAvailableTimeLength = 0;

    for (const auto& client : clients) {
        if (!client.movieTitle.empty()) { // Display only if movie title is not empty
            maxNameLength = std::max(maxNameLength, client.name.length());
            maxPhoneNumberLength = std::max(maxPhoneNumberLength, client.phoneNumber.length());
            maxEmailAddressLength = std::max(maxEmailAddressLength, client.emailAddress.length());
            maxMovieTitleLength = std::max(maxMovieTitleLength, client.movieTitle.length());
            maxCinemaLength = std::max(maxCinemaLength, movies[client.movieTitle].cinema.length());
            maxAvailableTimeLength = std::max(maxAvailableTimeLength, client.availableTime.length());
        }
    }

    // Display client information
    for (const auto& client : clients) {
        if (!client.movieTitle.empty()) { // Display only if movie title is not empty
            std::cout << "Name: " << std::left << std::setw(maxNameLength) << client.name << "\n";
            std::cout << "Phone Number: " << std::left << std::setw(maxPhoneNumberLength) << client.phoneNumber << "\n";
            std::cout << "Email Address: " << std::left << std::setw(maxEmailAddressLength) << client.emailAddress << "\n";
            std::cout << "Movie Title: " << std::left << std::setw(maxMovieTitleLength) << client.movieTitle << "\n";
            std::cout << "Cinema: " << std::left << std::setw(maxCinemaLength) << movies[client.movieTitle].cinema << "\n";

            // Display available time if it's not empty
            if (!client.availableTime.empty()) {
                std::cout << "Available Time: " << std::left << std::setw(maxAvailableTimeLength) << client.availableTime << "\n";
            }

            std::cout << std::string(maxNameLength + maxPhoneNumberLength + maxEmailAddressLength +
                                      maxMovieTitleLength + maxCinemaLength + maxAvailableTimeLength + 34, '-') << "\n";
        }
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}




void modifyClient() {
    loadDataFromFile();
    clearScreen();
    std::cout << "Modify a client's booked movie\n";
    std::cout << "(enter 'abort' to cancel)\n";

    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << i + 1 << ". " << clients[i].name << "\n";
    }

    std::string indexStr;
    size_t index;
    std::cout << "Enter the index number of the client to modify: ";
    std::getline(std::cin, indexStr);

    if (indexStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }
    clearScreen();
    std::stringstream(indexStr) >> index;

    if (index <= 0 || index > clients.size()) {
        std::cout << "Invalid index number!\n";
        return;
    }

    Client& client = clients[index - 1];

    std::cout << "Select the action to modify:\n";
    std::cout << "(enter 'abort' to cancel)\n";
    std::cout << "1. Name\n";
    std::cout << "2. Phone number\n";
    std::cout << "3. Email address\n";
    std::cout << "4. Movie title\n";
    std::cout << "5. Available time\n";
    std::cout << "Enter the action number: ";

    std::string actionStr;
    std::getline(std::cin, actionStr);

    if (actionStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }
    clearScreen();
    int action;
    std::stringstream(actionStr) >> action;

    switch (action) {
        case 1: {
            std::cout << "Enter 'abort' to cancel or enter 'skip' to the information.\n";
            std::string newName;
            std::cout << "Name (" << client.name << "): ";
            std::getline(std::cin, newName);
            if (newName == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newName != "skip") {
                if (!isValidFullName(newName)) {
                    std::cout << "Invalid full name! Please enter a valid full name.\n";
                    return;
                } else if (isDuplicateFullName(newName)) {
                    std::cout << "Name already exists! Please enter a different name.\n";
                    return;
                }
                client.name = newName;
            }
            break;
        }
        case 2: {
            std::cout << "enter 'abort' to cancel, enter 'skip' to remain the information.\n";
            std::string newPhoneNumber;
            std::cout << "Phone number (" << client.phoneNumber << "): ";
            std::getline(std::cin, newPhoneNumber);
            if (newPhoneNumber == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newPhoneNumber != "skip") {
                if (!isValidPhoneNumber(newPhoneNumber)) {
                    std::cout << "Invalid phone number! Please enter a valid 11-digit phone number.\n";
                    return;
                } else if (isDuplicatePhoneNumber(newPhoneNumber)) {
                    std::cout << "Phone number already exists! Please enter a different phone number.\n";
                    return;
                }
                client.phoneNumber = newPhoneNumber;
            }
            break;
        }
        case 3: {
            std::cout << "enter 'abort' to cancel, enter 'skip' to remain the information.\n";
            std::string newEmailAddress;
            std::cout << "Email address (" << client.emailAddress << "): ";
            std::getline(std::cin, newEmailAddress);
            if (newEmailAddress == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newEmailAddress != "skip") {
                // Validate and update email address
                if (!isValidEmailAddress(newEmailAddress)) {
                    std::cout << "Invalid email address! Please enter a valid email address.\n";
                    return;
                } else if (isDuplicateEmailAddress(newEmailAddress)) {
                    std::cout << "Email address already exists! Please enter a different email address.\n";
                    return;
                }
                client.emailAddress = newEmailAddress;
            }
            break;
        }
        case 4: {
    std::cout << "enter 'abort' to cancel, enter 'skip' to remain the information.\n";
    std::string newMovieTitle;
    std::cout << "Movie title (" << client.movieTitle << "): ";
    std::getline(std::cin, newMovieTitle);
    if (newMovieTitle == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    } else if (newMovieTitle != "skip") {
        // Validate and update movie title
        if (!isMovieTitleExists(newMovieTitle, movies)) {
            std::cout << "Movie title not found! Please enter a valid movie title.\n";
            return;
        }
        client.movieTitle = newMovieTitle;
    }
    break;
}

        case 5: {
            std::cout << "enter 'abort' to cancel, enter 'skip' to remain the information.\n";
            std::string newTime;
            std::cout << "Available time (" << client.availableTime <<"): ";
            std::getline(std::cin, newTime);
            if (newTime == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newTime != "skip") {
                if (!isValidTimeFormat(newTime)) {
                    std::cout << "Invalid time format! Please use the format 'hh:mmAM' or 'hh:mmPM'.\n";
                    return;
                }
                client.availableTime = newTime;
            }
            break;
        }
        default:
            std::cout << "Invalid action number!\n";
            return;
    }

    saveDataToFile();

    std::cout << "Client information modified successfully!\n";
    viewClients();
}

void modifyMovieInfo() {
    loadDataFromFile();
    clearScreen();
    std::cout << "Modify movie information\n\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    if (movieTitles.empty()) {
        std::cout << "No movies available to modify.\n";
        std::cout << "Press Enter to exit...";
        std::cin.ignore();
        return;
    }

    std::cout << "Available movie titles:\n";
    std::cout << "----------------------\n";
    for (size_t i = 0; i < movieTitles.size(); ++i) {
        std::cout << i + 1 << ". " << movieTitles[i] << "\n";
    }
    std::cout << "----------------------\n";

    std::string input;
    int selectedIndex = -1;
    bool isValidIndex = false;
    while (!isValidIndex) {
        std::cout << "Select the index of the movie to modify (1-" << movieTitles.size() << "): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> selectedIndex && selectedIndex >= 1 && selectedIndex <= static_cast<int>(movieTitles.size())) {
            isValidIndex = true;
        } else {
            std::cout << "Invalid index!\n";
        }
    }

    clearScreen();

    std::string movieTitle = movieTitles[selectedIndex - 1];
    Movie& movie = movies[movieTitle];

    while (true) {
        std::cout << "'abort' to cancel.\n";
        std::cout << "Movie title (" << movie.title <<"): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (input.empty()) {
            std::cout << "Invalid movie title!\n";
        } else {
            movie.title = input;
            break;
        }
    }

    while (true) {
        std::cout << "Price (" << movie.price << "): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> movie.price && movie.price > 0.0) {
            break;
        } else {
            std::cout << "Invalid price!\n";
        }
    }

    while (true) {
        std::cout << "Duration (hh:mm:ss) (" << movie.duration << "): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (isValidDurationFormat(input)) {
            movie.duration = input;
            break;
        } else {
            std::cout << "Invalid duration! Use the format 'hh:mm:ss'.\n";
        }
    }

    clearScreen();

    while (true) {
    std::cout << "Available times:\n";
    std::cout << "'abort' to cancel.\n";

    for (unsigned int i = 0; i < movie.availableTimes.size(); ++i) {
    std::cout << i + 1 << ". " << movie.availableTimes[i] << std::endl;
}


    std::cout << "Select the index of the time to modify: ";
    std::getline(std::cin, input);

    if (input == "abort") {
        std::cout << "Movie modification canceled.\n";
        return;
    }

    if (std::isdigit(input[0])) {
        int index = std::stoi(input) - 1;
        if (index >= 0 && static_cast<size_t>(index) < movie.availableTimes.size()) {
    std::string selectedTime = movie.availableTimes[index];
    std::cout << "Selected time: " << selectedTime << std::endl;

            while (true) {
                std::cout << "Enter the modified time: ";
                std::getline(std::cin, input);

                if (isValidTimeFormat(input)) {

                    std::cout << "Time modified successfully!\n";
                    break;
                } else {
                    std::cout << "Invalid time format! Use 'hh:mmAM' or 'hh:mmPM'.\n";
                }
            }

            while (true) {
                std::cout << "Modify another available time? (yes/no): ";
                std::getline(std::cin, input);

                if (input == "yes") {
                    break;
                } else if (input == "no") {
                    std::cout << "Movie modification completed.\n";
                    saveDataToFile();
                    return;
                } else {
                    std::cout << "Invalid input! Enter 'yes' or 'no'.\n";
                }
            }
        } else {
            std::cout << "Invalid index! Please enter a valid index.\n";
        }
    } else {
        std::cout << "Invalid input! Please enter a valid index.\n";
    }
}
}
void viewMovieInfo() {
    loadDataFromFile();
    clearScreen();
    std::cout << "View movie information:\n\n";

    if (movies.empty()) {
        std::cout << "No movies available.\n";
    } else {
        std::vector<std::string> movieTitles;

        // Extract movie titles from the map
        for (const auto& movie : movies) {
            movieTitles.push_back(movie.first);
        }

        // Sort movie titles alphabetically
        std::sort(movieTitles.begin(), movieTitles.end());

        // Calculate the maximum lengths for other fields
        size_t maxTitleLength = 0;
        size_t maxPriceLength = 0;
        size_t maxCinemaLength = 0;

        for (const auto& title : movieTitles) {
            const Movie& movie = movies[title];
            maxTitleLength = std::max(maxTitleLength, movie.title.length());
            maxPriceLength = std::max(maxPriceLength, std::to_string(movie.price).length());
            maxCinemaLength = std::max(maxCinemaLength, movie.cinema.length());
        }

        // Display movie information
        for (const auto& title : movieTitles) {
            const Movie& movie = movies[title];

            std::cout << "Movie Title: " << std::left << std::setw(maxTitleLength) << movie.title << "\n";
            std::cout << "Price: " << std::left << std::setw(maxPriceLength) << movie.price << "\n";
            std::cout << "Duration: " << movie.duration << "\n";
            std::cout << "Cinema: " << std::left << std::setw(maxCinemaLength) << movie.cinema << "\n";
            std::cout << "Available Times: ";
            for (const auto& time : movie.availableTimes) {
                std::cout << time << " ";
            }
            std::cout << "\n";

            // Display partition line
            std::cout << std::string(79, '-') << "\n";
        }
    }

    // Prompt user for input
    std::cout << "Enter 'Y' to proceed to the menu or any other key to remain in movie information: ";
    std::string choice;
    std::getline(std::cin, choice);

    if (choice.size() == 1 && (std::toupper(choice[0]) == 'Y')) {
        // Proceed to the menu
    } else {
        viewMovieInfo(); // Call the function recursively to remain in movie information
    }
}

void deleteClient() {
    loadDataFromFile();
    clearScreen();
    std::cout << "Delete a client's booked movie\n\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    std::vector<Client> bookedClients;
    for (const auto& client : clients) {
        if (!client.movieTitle.empty()) {
            bookedClients.push_back(client);
        }
    }

    if (bookedClients.empty()) {
        std::cout << "No clients found.\n";
        return;
    }

    for (size_t i = 0; i < bookedClients.size(); ++i) {
        std::cout << i + 1 << ". " << bookedClients[i].name << "\n";
    }

    std::string indexStr;
    int index;
    std::cout << "\nEnter the index number of the client to delete: ";
    std::getline(std::cin, indexStr);

    if (indexStr == "abort") {
        std::cout << "Client deletion aborted.\n";
        return;
    }

    try {
        index = std::stoi(indexStr);

        if (index <= 0 || index > static_cast<int>(bookedClients.size())) {
            throw std::out_of_range("Invalid index number!");
        }

        std::cout << "Are you sure you want to delete the client's information? (yes/no): ";
        std::string confirm;
        std::getline(std::cin, confirm);

        if (confirm == "yes") {
            size_t clientIndex = 0;
            for (size_t i = 0; i < clients.size(); ++i) {
                if (clients[i].name == bookedClients[index - 1].name) {
                    clientIndex = i;
                    break;
                }
            }

            clients.erase(clients.begin() + clientIndex);
            saveDataToFile();
            std::cout << "Client information deleted successfully!\n";
        } else {
            std::cout << "Deletion canceled.\n";
        }
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid index number! Please enter a valid index.\n";
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << "\n";
    }
}


void saveDataToFile() {
    std::ofstream outFile("data.dat");
    if (!outFile.is_open()) {
        std::cout << "Failed to open data file for writing!\n";
        return;
    }

    // Write movie data
    outFile << movies.size() << "\n";
    for (const auto& movie : movies) {
        outFile << movie.second.title << "\n";
        outFile << movie.second.price << "\n";
        outFile << movie.second.duration << "\n";
        outFile << movie.second.availableTimes.size() << "\n";
        for (const auto& time : movie.second.availableTimes) {
            outFile << time << "\n";
        }
        outFile << movie.second.cinema << "\n"; // Add cinema to the file
    }

    // Write client data
    outFile << clients.size() << "\n";
    for (const auto& client : clients) {
        outFile << client.name << "\n";
        outFile << client.phoneNumber << "\n";
        outFile << client.emailAddress << "\n";
        outFile << client.movieTitle << "\n";
        outFile << client.availableTime << "\n";
        outFile << client.cinema << "\n"; // Add cinema to the file
    }

    outFile.close();
}

void loadDataFromFile() {
    std::ifstream inFile("data.dat");
    if (!inFile.is_open()) {
        std::cout << "Failed to open data file for reading!\n";
        return;
    }

    movies.clear();
    clients.clear();

    // Read movie data
    int movieCount;
    inFile >> movieCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < movieCount; ++i) {
        Movie movie;
        std::getline(inFile, movie.title);
        inFile >> movie.price;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(inFile, movie.duration);
        int timeCount;
        inFile >> timeCount;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int j = 0; j < timeCount; ++j) {
            std::string time;
            std::getline(inFile, time);
            movie.availableTimes.push_back(time);
        }
        std::getline(inFile, movie.cinema); // Read cinema from the file
        movies[movie.title] = movie;
    }

    // Read client data
    int clientCount;
    inFile >> clientCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < clientCount; ++i) {
        Client client;
        std::getline(inFile, client.name);
        std::getline(inFile, client.phoneNumber);
        std::getline(inFile, client.emailAddress);
        std::getline(inFile, client.movieTitle);
        std::getline(inFile, client.availableTime);
        std::getline(inFile, client.cinema); // Read cinema from the file
        clients.push_back(client);
    }

    inFile.close();
}


void deleteMovie() {
    loadDataFromFile();

    clearScreen();
    std::cout << "Delete a movie\n\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    while (true) {
        std::vector<std::string> movieTitles;
        for (const auto& movie : movies) {
            movieTitles.push_back(movie.first);
        }

        std::sort(movieTitles.begin(), movieTitles.end());
        std::cout << "Movie List:\n";
        for (size_t i = 0; i < movieTitles.size(); ++i) {
            std::cout << "[" << (i + 1) << "] " << movieTitles[i] << "\n";
        }

        std::string movieIndexStr;
        std::cout << "\nEnter the index of the movie to delete: ";
        std::getline(std::cin, movieIndexStr);

        if (movieIndexStr == "abort") {
            std::cout << "Movie deletion aborted.\n";
            return;
        }

        int movieIndex = 0;
        try {
            movieIndex = std::stoi(movieIndexStr);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid movie index! Please enter a valid integer.\n";
            continue;
        } catch (const std::out_of_range& e) {
            std::cout << "Invalid movie index! The entered value is out of range.\n";
            continue;
        }

        if (movieIndex < 1 || movieIndex > static_cast<int>(movieTitles.size())) {
            std::cout << "Invalid movie index!\n";
            continue;
        }

        const std::string& movieTitle = movieTitles[movieIndex - 1];

        auto iter = movies.find(movieTitle);
        if (iter == movies.end()) {
            std::cout << "Movie title not found!\n";
            continue;
        }

        std::string confirm;
        while (true) {
            std::cout << "Are you sure you want to delete the movie '" << movieTitle << "'? (yes/no): ";
            std::getline(std::cin, confirm);

            if (confirm == "yes") {
                for (auto& client : clients) {
                    if (client.movieTitle == movieTitle) {
                        client.movieTitle.clear();
                        client.availableTime.clear();
                    }
                }

                movies.erase(iter);
                saveDataToFile();

                std::cout << "Movie deleted successfully!\n";
                break;
            } else if (confirm == "no") {
                std::cout << "Movie deletion canceled.\n";
                break;
            } else {
                std::cout << "Invalid choice! Please enter 'yes' or 'no'.\n";
                continue;
            }
        }

        std::string deleteMore;
        while (true) {
            std::cout << "\nDo you want to delete more movies? (yes/no): ";
            std::getline(std::cin, deleteMore);

            if (deleteMore == "yes") {
                break;
            } else if (deleteMore == "no") {
                return;
            } else {
                std::cout << "Invalid choice! Please enter 'yes' or 'no'.\n";
                continue;
            }
        }
    }
}




void showUserConsole() {
    std::cout << "User Console\n";
    std::cout << "------------\n\n";
    clearScreen();
    while (true) {
        std::cout << "HELLO PLEASE CHOOSE\n";
        std::cout << "1. Book a movie\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice (1-2): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                std::cout << "Book a movie\n";
                bookMovie();
                break;
            case 2:
                std::cout << "Exiting User Console...\n";
                return;
            default:
                std::cout << "Invalid choice!\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }
}

void bookMovie() {

    loadDataFromFile();
    clearScreen();

    std::cout << "Available Movies:\n";
    std::cout<< "'abort' to cancel\n";
    std::cout << "-----------------\n\n";
    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    for (const auto& title : movieTitles) {
        const Movie& movie = movies[title];
        std::cout << "Title: " << movie.title << "\n";
        std::cout << "Price: " << movie.price << "\n";
        std::cout << "Duration: " << movie.duration << "\n";
        std::cout << "Cinema: " << movie.cinema << "\n";
        std::cout << "Available Times: ";
        for (const auto& time : movie.availableTimes) {
            std::cout << time << " ";
        }
        std::cout << "\n";
        std::cout << "-------------------------\n";
    }
    std::cout << "\nEnter the movie title you want to book: ";
    std::string movieTitle;
    std::getline(std::cin, movieTitle);

    if (movieTitle == "abort") {
        std::cout << "Booking process canceled.\n";
        return;
    }

    std::transform(movieTitle.begin(), movieTitle.end(), movieTitle.begin(), ::tolower);

    const Movie* movie = nullptr;
    for (const auto& pair : movies) {
        std::string lowercaseTitle = pair.first;
        std::transform(lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), ::tolower);
        if (lowercaseTitle == movieTitle) {
            movie = &pair.second;
            break;
        }
    }

    if (movie == nullptr) {
        std::cout << "Movie title not found!\n";
        return;

    }
      clearScreen();

    std::cout << "\n[Booking Process]\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    Client user;

    while (true) {
        std::cout << "Enter your full name: ";
        std::getline(std::cin, user.name);

        if (user.name == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidFullName(user.name)) {
            std::cout << "Invalid full name! Please enter a valid full name.\n";
        } else if (isDuplicateFullName(user.name)) {
            std::cout << "Name already exists! Please enter a different name.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your phone number (11 digits): ";
        std::getline(std::cin, user.phoneNumber);

        if (user.phoneNumber == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidPhoneNumber(user.phoneNumber)) {
            std::cout << "Invalid phone number! Please enter a valid 11-digit phone number.\n";
        } else if (isDuplicatePhoneNumber(user.phoneNumber)) {
            std::cout << "Phone number already exists! Please enter a different phone number.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your email address: ";
        std::getline(std::cin, user.emailAddress);

        if (user.emailAddress == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidEmailAddress(user.emailAddress)) {
            std::cout << "Invalid email address! Please enter a valid email address.\n";
        } else if (isDuplicateEmailAddress(user.emailAddress)) {
            std::cout << "Email address already exists! Please enter a different email address.\n";
        } else {
            break;
        }
    }

    clearScreen();

    while (true) {
    std::cout << "Available times:\n";
    std::cout << "'abort' to cancel.\n";

    for (size_t i = 0; i < movie->availableTimes.size(); ++i) {
        std::cout << i + 1 << ". " << movie->availableTimes[i] << std::endl;
    }

    std::cout << "Select the index of the available time: ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "abort") {
        std::cout << "Booking process canceled.\n";
        return;
    }

    int selectedIndex = std::stoi(input) - 1;

    if (selectedIndex >= 0 && static_cast<size_t>(selectedIndex) < movie->availableTimes.size()) {
        std::string selectedTime = movie->availableTimes[selectedIndex];
        user.availableTime = selectedTime;
        break;
    } else {
        std::cout << "Invalid index! Please enter a valid index.\n";
    }
}

user.movieTitle = movie->title;
clients.push_back(user);
saveDataToFile();

std::cout << "\nMovie booked successfully!\n";

clearScreen();

}

int main() {

    loadDataFromFile();

    std::cout << "Welcome to the Cinema Booking System!\n";

    while (true) {
        std::cout << "Please select an option:\n";
        std::cout << "1. Admin\n";
        std::cout << "2. User\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                showAdminConsole();
                break;
            case 2:
                showUserConsole();
                break;
            case 3:
                std::cout << "Exiting the Movie Booking System...\n";
                saveDataToFile();
                return 0;
            default:
                std::cout << "Invalid choice!\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }

    return 0;
}
