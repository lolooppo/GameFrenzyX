#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>


/**
 * Represents a user with a username and password.
 * This class provides basic functionality for storing and managing
 * a user's credentials, including setting and retrieving the username
 * and password.
 */
class User{

private:

    std::string name;
    std::string password;

public:

    User (const std::string& name, const std::string& password) :
        name(name), password(password) {
    }

    void setName (const std::string& name) {
        this->name = name;
    }

    std::string getName () const {
        return name;
    }

    void setPassword (const std::string& password) {
        this->password = password;
    }

    std::string getPassword () const {
        return password;
    }

};


/**
 * Interface defining authentication-related operations.
 * Implementations of this interface will provide functionality
 * for user sign-up and sign-in processes.
 */
class IAuthentication {

public:
    IAuthentication () = default;
    virtual bool checkUsername (const std::string& username, const std::set<std::string>& usernames) = 0;
    virtual ~IAuthentication () = default;

};


/**
 * Handles user registration (sign-up) process.
 * This class implements the authentication logic required to
 * create new user accounts and validate input.
 */
class SignUpService : public IAuthentication {

public:

    SignUpService () = default;

    /**
     * Checks whether a given username meets the required format and is not already in use.
     *
     * @param username The username to validate.
     * @param usernames A set of existing usernames to check for duplicates.
     * @return True if the username is valid and available, otherwise false.
     */
    virtual bool checkUsername (const std::string& username, const std::set<std::string>& usernames) override {

        // first check if this user name is already in use by another user.
        if(usernames.count(username))
            return false;

        // second check if the user name format correct which is (name should start by character and contains characters, digits and "-" only).
        if(!isalpha(username[0]))
            return false;

        for(int i=0; i<(int)username.length(); i++){
            if( !(isdigit(username[i]) || (username[i] == '_') || (tolower(username[i]) >= 'a' && tolower(username[i]) <= 'z')) )
                return false;
        }

        // accepted
        return true;
    }


    /**
    * Validates whether the given password meets the required security format.
    * This function ensures that the password follows predefined security rules,
    * such as minimum length, presence of special characters, or other criteria.
    *
    * @param password The password to validate.
    * @return True if the password meets the required format, otherwise false.
    */
    virtual bool validatePasswordFormat (const std::string& password) {
        //the password should contains characters, special characters and digits for maximum length of 10 and minimum of 5.
        bool hasCharacter{false}, hasSpecialcharacter{false}, hasDigit{false};

        if((int)password.length() < 5 || (int)password.length() > 10)
            return false;

        for(int i=0; i<(int)password.length(); i++){
            if(isdigit(password[i]))
                hasDigit = true;

            else if(isalpha(password[i]))
                hasCharacter = true;

            else
                hasSpecialcharacter = true;
        }

        return (hasCharacter && hasSpecialcharacter && hasDigit);
    }


    virtual ~SignUpService () = default;
};


/**
 * Handles user authentication (sign-in) process.
 * This class verifies user credentials, checks authentication rules,
 * and manages login sessions.
 */
class SignInService : public IAuthentication {

public:

    SignInService () = default;

    /**
     * Checks whether a given username is already exist.
     *
     * @param username The username to check.
     * @param usernames A set of existing usernames to check for existence.
     * @return True if the username is valid, otherwise false.
     */
     virtual bool checkUsername(const std::string& username, const std::set<std::string>& usernames) override {
        return usernames.count(username);
     }


     virtual bool verifyUserPassword (const std::string& username, const std::string& userpassword, const std::unordered_map<std::string, User*>& userDirectory) {
        return userpassword == userDirectory.at(username)->getPassword();       // coding tip! You can not use [] operator cause it is not constant operator which violates the constant unordered map passed to the function.
     }

    virtual ~SignInService () = default;

};


/**
 * Manages reading from and writing to the database file.
 * This class provides functionality to store and retrieve user data
 * in a persistent file-based database. It ensures efficient file
 * operations and data integrity.
 *
 * Responsibilities:
 * - Load user data from the database file.
 * - Save user data to the database file.
 * - Ensure data consistency between memory and storage.
 * - Handle file read/write errors gracefully.
 *
 */
class DatabaseManager{

private:

    std::string users_file_path;
    std::string reservations_file_path;
    std::string playgrounds_file_path;

    DatabaseManager(const std::string& users_file_path, const std::string& reservations_file_path, const std::string& playgrounds_file_path) :
        users_file_path(users_file_path), reservations_file_path(reservations_file_path), playgrounds_file_path(playgrounds_file_path){
    }


    static DatabaseManager* databaseManagerInstance;

public:

    static DatabaseManager* getInstance (const std::string& users_file_path, const std::string& reservations_file_path, const std::string& playgrounds_file_path) {
        if(databaseManagerInstance == nullptr)
            databaseManagerInstance = new DatabaseManager (users_file_path, reservations_file_path, playgrounds_file_path);

        return databaseManagerInstance;
    }


    void load_users (std::set<std::string>& usernames, std::unordered_map<std::string, User*>& userDirectory) {
        std::ifstream file_handler(users_file_path);

        if(file_handler.fail()){
            std::cout   <<  "sorry,something went wrong in the users file\n";
            exit(0);
        }

        std::vector<std::string> file_splitted_lines;
        std::string line{""};

        while(std::getline(file_handler,line)) {
            if(line == ""){
                continue;
            }

            file_splitted_lines.push_back(line);
        }

        for(const std::string& line : file_splitted_lines) {
            std::stringstream ss(line);
            std::string name, password;

            std::getline(ss, name, ',');
            std::getline(ss, password, ',');

            userDirectory[name] = new User(name, password);
            usernames.insert(name);
        }
    }

    void update_users (std::unordered_map<std::string, User*>& userDirectory) {
        auto file_status = std::ios::in | std::ios::out | std::ios::trunc;
        std::ofstream file_handler(users_file_path, file_status);

        for(auto& pair : userDirectory){
            std::ostringstream oss;

            std::string name = pair.second->getName(), password = pair.second->getPassword();

            oss<<name<<","<<password;
            file_handler<<oss.str()<<"\n";
        }

        file_handler.close();
    }


    //void load_reservations () {}


    //void load_playgrounds () {}


    static void freeInstance () {
        if(databaseManagerInstance == nullptr)
            return;

        delete databaseManagerInstance;
        databaseManagerInstance = nullptr;
    }

};
DatabaseManager* DatabaseManager :: databaseManagerInstance = nullptr;


/**
 * Manages the core system operations, including user sign-up, sign-in,
 * and database interactions. This class serves as the central controller
 * for user authentication and data management.
 *
 * Responsibilities:
 * - Handles user registration and login.
 * - Interfaces with the database manager to load and update user data.
 * - Maintains in-memory user records for quick lookups.
 */
class SystemManager {

private:

    SignUpService SignUpServiceInstance;
    SignInService SignInServiceInstance;
    DatabaseManager* databaseManagerInstance;

    std::unordered_map<std::string, User*> userDirectory;  // Stores registered users in memory.
    std::set<std::string> usernames;  // Tracks unique usernames for quick lookup.

public:

    /**
     * Initializes the SystemManager by loading user data from the database.
     *
     * @param users_file_path Path to the user database file.
     */
    SystemManager(const std::string& users_file_path) {
        databaseManagerInstance = DatabaseManager::getInstance(users_file_path, "blabla", "blabla");
        databaseManagerInstance->load_users(usernames, userDirectory);
    }


    /**
     * Handles the sign-up process, ensuring username uniqueness and password validity.
     * The user is prompted to enter a valid username and password before being registered.
     */
    void doSignUp() {
        std::string name;
        std::string password;

        // Prompt user for a valid user name
        while (true) {
            std::cout << "---------------------\n";
            std::cout << "|Enter the user name|\n";
            std::cout << "---------------------\n";
            std::getline(std::cin, name);

            if (!SignUpServiceInstance.checkUsername(name, usernames)) {
                std::cout << "---------------------\n";
                std::cout << "| Sorry, try again! |\n";
                std::cout << "---------------------\n";
            } else {
                break;
            }
        }

        // Prompt user for a valid password
        while (true) {
            std::cout << "---------------------\n";
            std::cout << "|Enter your password|\n";
            std::cout << "---------------------\n";
            std::cin >> password;

            if (!SignUpServiceInstance.validatePasswordFormat(password)) {
                std::cout << "---------------------\n";
                std::cout << "| Sorry, try again! |\n";
                std::cout << "---------------------\n";
            } else {
                break;
            }
        }

        std::cout << "---------------------\n";
        std::cout << "|  Congratulations  |\n";
        std::cout << "---------------------\n";

        // Register new user
        User* new_user = new User(name, password);
        userDirectory[name] = new_user;
    }


    /**
     * Handles the sign-in process, verifying the username and password.
     * The user is prompted to enter valid credentials before logging in.
     */
    void doSignIn() {
        std::string name;
        std::string password;

        // Prompt user for a valid username
        while (true) {
            std::cout << "---------------------\n";
            std::cout << "|Enter the user name|\n";
            std::cout << "---------------------\n";
            std::getline(std::cin, name);

            if (!SignInServiceInstance.checkUsername(name, usernames)) {
                std::cout << "---------------------\n";
                std::cout << "| Sorry, try again! |\n";
                std::cout << "---------------------\n";
            } else {
                break;
            }
        }

        // Prompt user for a valid password
        while (true) {
            std::cout << "---------------------\n";
            std::cout << "|Enter your password|\n";
            std::cout << "---------------------\n";
            std::cin >> password;

            if (!SignInServiceInstance.verifyUserPassword(name, password, userDirectory)) {
                std::cout << "---------------------\n";
                std::cout << "| Sorry, try again! |\n";
                std::cout << "---------------------\n";
            } else {
                break;
            }
        }

        std::cout << "----------------------------\n";
        std::cout << "|  Successfully logged in  |\n";
        std::cout << "----------------------------\n";
    }


    /**
     * Prints all user data stored in memory.
     * This is mainly for testing and debugging purposes.
     */
    void print_users_data() {
        for (auto& pair : userDirectory) {
            std::cout << "Name: " << pair.second->getName()
                      << ", Password: " << pair.second->getPassword() << "\n";
        }
    }

    /**
     * Simulates the sign-up process for testing.
     * After signing up, it updates the database and prints the updated user data.
     */
    void test_sign_up() {
        print_users_data();
        doSignUp();
        databaseManagerInstance->update_users(userDirectory);
        print_users_data();
    }

    /**
     * Simulates the sign-in process for testing.
     * This function prints user data before and after signing in.
     */
    void test_sign_in() {
        print_users_data();
        doSignIn();
        print_users_data();
    }

};


int main() {

    SystemManager sys("users.txt");
    sys.test_sign_in();
}
