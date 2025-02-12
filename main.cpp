#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <iomanip>


/**
 * Represents a user with a user-name and password.
 * This class provides basic functionality for storing and managing
 * a user's credentials, including setting and retrieving the user-name
 * and password.
 */
class User {

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









class Reservable {

private:

    std::string name;
    std::string category;
    bool available;
    int availablePeriods[13];

public:

    Reservable (std::string name, std::string category, bool available) :
        name(name), category(category), available(available) {
            memset(availablePeriods, 0, sizeof(availablePeriods));
    }


    std::string getName () const {
        return name;
    }

    std::string getCategory () const {
        return category;
    }

    bool isReservableAvailable () const {
        return available;
    }

    void changeReservableAvailability (const bool& new_status) {
        available = new_status;
    }

    void reservePeriod (const int& from, const int& to) {
        for(int i=from; i<=to; i++)
            availablePeriods[i]++;
    }

    void freePeriod (const int& from, const int& to) {
        for(int i=from; i<=to; i++){
            availablePeriods[i]--;
            availablePeriods[i] = std::max(availablePeriods[i], 0);
        }
    }

    bool isPeriodAvailable (const int& from, const int& to) const {
        for(int i = from; i<=to; i++)
            if(availablePeriods[i] != 0)
                return false;

        return true;

    }

    void showAvailablePeriods () const {
        for(int i=1; i<=12; i++){
            if(availablePeriods[i] == 0){
                std::cerr   <<  i <<  ", ";
            }
        }

        std::cerr   <<  "\n";

    }

    virtual void showReservableInfo () const {
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
        std::cerr   <<  "| Name             : "    <<  name       <<  "\n";
        std::cerr   <<  "| Category         : "    <<  category   <<  "\n";
        std::cerr   <<  "| Status           : ";
        available ? std::cerr   <<  "Available\n" : std::cerr <<  "Under Maintenance\n";
        std::cerr   <<  "| Available Periods: " ;
        for(int i=1; i<=12; i++){
            if(availablePeriods[i] == 0)
                std::cerr   <<  i <<  ", ";
        }
        std::cerr   <<  "\n";
    }

    ~Reservable () {}

} ;







class FootballPlayGround : public Reservable {

private:

    double AmPrice;
    double PmPrice;

public:

    FootballPlayGround(std::string name, bool available, double AmPrice, double PmPrice) :
        Reservable(name, "Football", available), AmPrice(AmPrice), PmPrice(PmPrice) {
    }

    double getAmPrice () const {
        return AmPrice;
    }

    double getPmPrice () const {
        return PmPrice;
    }

    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Morning Price    : " <<  AmPrice <<  "\n";
        std::cerr   <<  "| Night   Price    : " <<  PmPrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }
};






class VolleyballPlayGround : public Reservable {

private:

    double SandGroundPrice;
    double RubberGroundPrice;

public:

    VolleyballPlayGround(const std::string& name, const bool& available, const double& SandGroundPrice, const double& RubberGroundPrice) :Volleyball
        Reservable(name, "Volleyball", available), SandGroundPrice(SandGroundPrice), RubberGroundPrice(RubberGroundPrice) {
    }

    double getSandGroundPrice () const {
        return SandGroundPrice;
    }

    double getRubberGroundPrice () const {
        return RubberGroundPrice;
    }

    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Sand Ground Price    : "   <<  SandGroundPrice   <<  "\n";
        std::cerr   <<  "| Rubber Ground Price    : " <<  RubberGroundPrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }

};






class TennisPlayGround : public Reservable {

private:
    double SinglePlayerMatchPrice;
    double MultiPlayerMatchPrice;

public:

    TennisPlayGround(const std::string& name, const bool& available, const double& SinglePlayerMatchPrice, const double& MultiPlayerMatchPrice) :
        Reservable(name, "Tennis", available), SinglePlayerMatchPrice(SinglePlayerMatchPrice), MultiPlayerMatchPrice(MultiPlayerMatchPrice) {
    }

    double getSinglePlayerMatchPrice () const {
        return SinglePlayerMatchPrice;
    }

    double getMultiPlayerMatchPrice () const {
        return MultiPlayerMatchPrice;
    }


    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Singles Match Price    : "   <<  SinglePlayerMatchPrice   <<  "\n";
        std::cerr   <<  "| Doubles Match Price    : " <<  MultiPlayerMatchPrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }

};



class SwimmingPool : public Reservable {

private:

    double ColdWaterPrice;
    double WarmWaterPrice;

public:

    SwimmingPool(const std::string& name, const bool& available, const double& ColdWaterPrice, const double& WarmWaterPrice) :
        Reservable(name, "Swimming pool", available), ColdWaterPrice(ColdWaterPrice), WarmWaterPrice(WarmWaterPrice) {
    }

    double getColdWaterPrice () const {
        return ColdWaterPrice;
    }

    double getWarmWaterPrice () const {
        return WarmWaterPrice;
    }

    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Cold Water Pool: "   <<  ColdWaterPrice   <<  "\n";
        std::cerr   <<  "| Warm Water Pool: " <<  WarmWaterPrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }

};






class PingbongTable : public Reservable {

private:

    double SinglePlayerMatchPrice;
    double MultiPlayerMatchPrice;

public:

    PingbongTable(const std::string& name, const bool& available, const double& SinglePlayerMatchPrice, const double& MultiPlayerMatchPrice) :
        Reservable(name, "Ping bong", available), SinglePlayerMatchPrice(SinglePlayerMatchPrice), MultiPlayerMatchPrice(MultiPlayerMatchPrice) {
    }

    double getSinglePlayerMatchPrice () const {
        return SinglePlayerMatchPrice;
    }

    double getMultiPlayerMatchPrice () const {
        return MultiPlayerMatchPrice;
    }

    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Singles Match Price: "   <<  SinglePlayerMatchPrice   <<  "\n";
        std::cerr   <<  "| Doubles Match Price: " <<  MultiPlayerMatchPrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }

};






class BilliardsTable : public Reservable {

private:

    double NormalGamePrice;
    double AmericanGamePrice;

public:

    BilliardsTable(const std::string& name, const bool& available, const double& NormalGamePrice, const double& AmericanGamePrice) :
       Reservable(name, "Billiards", available), NormalGamePrice(NormalGamePrice), AmericanGamePrice(AmericanGamePrice) {
    }

    double getNormalGamePrice () const {
        return NormalGamePrice;
    }

    double getAmericanGamePrice () const {
        return AmericanGamePrice;
    }


    void showReservableInfo () const {
        Reservable::showReservableInfo();
        std::cerr   <<  "| Normal Match Price: "   <<  NormalGamePrice   <<  "\n";
        std::cerr   <<  "| American Match Price: " <<  AmericanGamePrice <<  "\n";
        std::cerr   <<  "----------------------------------------------------------------------------------\n";
    }

};














class Reservation {

protected:

    int from;
    int to;
    User* user;
    Reservable* reservable;

public:

    Reservation(const int& from, const int& to, User* user, Reservable* reservable) :
        from(from), to(to), user(user), reservable(reservable) {
    }

    virtual double getTotalPrice () = 0;

    std::pair<int, int> getReservedPeriod () const {
        return {from, to};
    }

    int totalTimeReserved () {
        return to - from;
    }

    virtual void ShowReservationInfo () const {
        std::cerr   <<  "-----------------------------------------------------------------------\n";
        std::cerr   <<  "|  Reserved From: "  <<   from << ", To: "  <<  to  <<  "\n";
        std::cerr   <<  "|  Reserved By: " <<  user->getName() <<  "\n";
        std::cerr   <<  "|  Reserved Item Category: "  <<  reservable->getCategory() <<  "\n";
        std::cerr   <<  "|  Reserved Item Name: "  <<  reservable->getName() <<  "\n";
    }

    std::string ShowReserverInfo () const{
        return user->getName();
    }

};






class FootballReservation : public Reservation {

private:

    bool isMorningReservation;

public:

    FootballReservation(const int& from, const int& to, User* user, FootballPlayGround* playGround, const bool& isMorningReservation) :
        Reservation(from, to, user, playGround), isMorningReservation(isMorningReservation) {
    }

    double getTotalPrice () override {
        double total_price = isMorningReservation ? (totalTimeReserved() * static_cast<FootballPlayGround*>(reservable)->getAmPrice()) : (totalTimeReserved() * static_cast<FootballPlayGround*>(reservable)->getPmPrice());

        return total_price;
    }


    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Reservation Slot: " ;
        isMorningReservation ? std::cerr    <<  "Morning" : std::cerr    <<  "Night";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};






class VolleyballReservation : public Reservation {

private:

    bool isSandGround;

public:

    VolleyballReservation(const int& from, const int& to, User* user, Reservable* reservable, const bool& isSandGround) :
        Reservation(from, to, user, reservable), isSandGround(isSandGround) {
    }

    virtual double getTotalPrice () override {
        double total_price = isSandGround ? (totalTimeReserved() * static_cast<VolleyballPlayGround*>(reservable)->getSandGroundPrice()) : (totalTimeReserved() * static_cast<VolleyballPlayGround*>(reservable)->getRubberGroundPrice());

        //item->updatePeriods(from, to);

        return total_price;

    }

    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Playground Type: " ;
        isSandGround ? std::cerr    <<  "Sand" : std::cerr    <<  "Rubber";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};


class TennisReservation : public Reservation {

private:

    bool isSingleMatch;

public:

    TennisReservation (const int& from, const int& to, User* user, Reservable* reservable, const bool& isSingleMatch) :
        Reservation(from, to, user, reservable), isSingleMatch(isSingleMatch) {
    }

    virtual double getTotalPrice () override {
        double total_price = isSingleMatch ? (totalTimeReserved() * static_cast<TennisPlayGround*>(reservable)->getSinglePlayerMatchPrice()) : (totalTimeReserved() * static_cast<TennisPlayGround*>(reservable)->getMultiPlayerMatchPrice());

        return total_price;
    }


    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Game Type: " ;
        isSingleMatch ? std::cerr    <<  "Singles" : std::cerr    <<  "Doubles";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};




class SwimmingpoolReservation : public Reservation {

private:

    bool isColdWaterReservation;

public:

    SwimmingpoolReservation(const int& from, const int& to, User* user, Reservable* reservable, const bool& isColdWaterReservation) :
        Reservation(from, to, user, reservable), isColdWaterReservation(isColdWaterReservation) {
    }

    virtual double getTotalPrice () override {
        double total_price = isColdWaterReservation ? (totalTimeReserved() * static_cast<SwimmingPool*>(reservable)->getColdWaterPrice()) : (totalTimeReserved() * static_cast<SwimmingPool*>(reservable)->getWarmWaterPrice());

        return total_price;
    }

    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Pool water Condition: " ;
        isColdWaterReservation ? std::cerr    <<  "Cold" : std::cerr    <<  "Warm";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};


class PingbongReservation : public Reservation {

private:

    bool isSingleMatch;

public:

    PingbongReservation(const int& from, const int& to, User* user, Reservable* reservable, const bool& isSingleMatch) :
        Reservation(from, to, user, reservable), isSingleMatch(isSingleMatch) {
    }

    virtual double getTotalPrice () override {
        double total_price = isSingleMatch ? (totalTimeReserved() * static_cast<PingbongTable*>(reservable)->getSinglePlayerMatchPrice()) : (totalTimeReserved() * static_cast<PingbongTable*>(reservable)->getMultiPlayerMatchPrice());

        return total_price;
    }

    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Game Type: " ;
        isSingleMatch ? std::cerr    <<  "Singles" : std::cerr    <<  "Doubles";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};


class BilliardsReservation : public Reservation {

private:
    bool isNormalGame;

public:

    BilliardsReservation(const int& from, const int& to, User* user, Reservable* reservable, const bool& isNormalGame) :
        Reservation(from, to, user, reservable), isNormalGame(isNormalGame) {
    }

    virtual double getTotalPrice () override {
        double total_price = isNormalGame ? (totalTimeReserved() * static_cast<BilliardsTable*>(reservable)->getNormalGamePrice()) : (totalTimeReserved() * static_cast<BilliardsTable*>(reservable)->getAmericanGamePrice());

        return total_price;
    }

    virtual void ShowReservationInfo () const {
        Reservation::ShowReservationInfo();
        std::cerr   <<  "|  Game Type: " ;
        isNormalGame ? std::cerr    <<  "Normal" : std::cerr    <<  "American";
        std::cerr   <<  "\n";
        std::cerr   <<  "-----------------------------------------------------------------------\n";
    }

};










class Itinerary {

private:

    std::vector<Reservation*> reservations;

public:

    void add_reservation (Reservation* reservation) {
        reservations.push_back(reservation);
    }

    double get_total_price () const {
        double total_price = 0.0;

        for(int i=0; i<(int)reservations.size(); i++){
            total_price += reservations[i]->getTotalPrice();
        }

        return total_price;
    }

    void showItineraryInfo () const {
        for(int i=0; i<(int)reservations.size(); i++){
            reservations[i]->ShowReservationInfo();
            std::cerr   <<  "\n";
        }

        std::cerr   <<  "-------------------------------------------------------------\n";
        std::cerr   <<  "| Total Itinerary Price: "  <<  get_total_price() <<    "|\n";
        std::cerr   <<  "-------------------------------------------------------------\n";
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
class DatabaseManager {

private:

    std::string users_file_path;
    std::string reservations_file_path;
    std::string reservables_file_path;

    DatabaseManager(const std::string& users_file_path, const std::string& reservations_file_path, const std::string& reservables_file_path) :
        users_file_path(users_file_path), reservations_file_path(reservations_file_path), reservables_file_path(reservables_file_path){
    }


    static DatabaseManager* databaseManagerInstance;

public:

    static DatabaseManager* getInstance (const std::string& users_file_path, const std::string& reservables_file_path,const std::string& reservations_file_path) {
        if(databaseManagerInstance == nullptr)
            databaseManagerInstance = new DatabaseManager (users_file_path, reservations_file_path, reservables_file_path);

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






    void load_reservables (std::set<std::string>& reservableNames, std::unordered_map<std::string, Reservable*>& reservablesDirectory) {
        std::ifstream file_handler(reservables_file_path);

        if(file_handler.fail()){
            std::cout   <<  "sorry,something went wrong in the reservables file\n";
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
            std::string name, category;
            std::string availableString;
            bool available;

            std::getline(ss, name, ',');
            std::getline(ss, category, ',');
            std::getline(ss, availableString, ',');

            available = availableString == "1" ? true : false;

            if(category == "Football") {
                std::string AmPriceString;
                std::string PmPriceString;
                double AmPrice;
                double PmPrice;

                std::getline(ss, AmPriceString, ',');
                std::getline(ss, PmPriceString, ',');

                AmPrice = std::stod(AmPriceString);
                PmPrice = std::stod(PmPriceString);

                reservablesDirectory[name] = new FootballPlayGround(name, available, AmPrice, PmPrice);

            }else if (category == "Volleyball") {
                //std::string 
            }

            reservableNames.insert(name);
        }

    }

    void update_reservables (const std::unordered_map<std::string, Reservable*>& reservablesDirectory) {
        auto file_status = std::ios::in | std::ios::out | std::ios::trunc;
        std::ofstream file_handler(reservables_file_path, file_status);

        for(auto& pair : reservablesDirectory) {
            std::ostringstream oss;

            std::string name = pair.first;
            std::string category = pair.second -> getCategory();
            bool available = pair.second -> isReservableAvailable();
            std::string availableString = available ? "1" : "0";

            oss<<name<<","<<category<<","<<availableString<<",";

            if(category == "Football"){
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<FootballPlayGround*>(pair.second) -> getAmPrice();
                oss2 << std::fixed << std::setprecision(2) << static_cast<FootballPlayGround*>(pair.second) -> getPmPrice();

                std::string AmPriceString = oss1.str();
                std::string PmPriceString = oss2.str();

                oss<<AmPriceString<<","<<PmPriceString;
            }


            file_handler<<oss.str()<<"\n";
        }

        file_handler.close();

    }




    void load_reservations () {}

    void update_reservations () {}




    static void freeInstance () {
        if(databaseManagerInstance == nullptr)
            return;

        delete databaseManagerInstance;
        databaseManagerInstance = nullptr;
    }

};
DatabaseManager* DatabaseManager :: databaseManagerInstance = nullptr;













class UI {

public:

    virtual void ShowMessage () = 0;

};

class HomeUI : public UI {

public:

    void ShowMessage () override {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "                                   |Choose|                               \n";
        std::cerr   <<  "                                    ------                                \n";
        std::cerr   <<  "| 1. User                                                                 \n";
        std::cerr   <<  "| 2. Admin                                                                \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }
};

class UserUI : public UI {

public:

    void ShowUserAuth () {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "                                   |Choose|                               \n";
        std::cerr   <<  "                                    ------                                \n";
        std::cerr   <<  "| 1. Log in (already has an account)                                      \n";
        std::cerr   <<  "| 2. Sign up                                                              \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }


    void EnterUserNameMessage () {
        std::cout << "---------------------\n";
        std::cout << "|Enter The User Name|\n";
        std::cout << "---------------------\n";
    }

    void EnterUserPasswordMessage () {
        std::cout << "--------------------------\n";
        std::cout << "|Enter The User Password: \n";
        std::cout << "--------------------------\n";
    }

    void ShowErrorMessage () {
        std::cout << "---------------------\n";
        std::cout << "| Sorry, try again! |\n";
        std::cout << "---------------------\n";
    }


    void ShowSuccessMessage () {
        std::cout << "---------------------\n";
        std::cout << "|  Congratulations  |\n";
        std::cout << "---------------------\n";
    }

    virtual void ShowMessage() override {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "| 1. Reserve                                                              \n";
        std::cerr   <<  "| 2. Show My Reservations                                                 \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }

    void ShowChooseCategoryMessage () {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "|                             |Choose Category|                           \n";
        std::cerr   <<  "                               ---------------                            \n";
        std::cerr   <<  "| 1.Football                                                              \n";
        std::cerr   <<  "| 2.Volleyball                                                            \n";
        std::cerr   <<  "| 3.Tennis                                                                \n";
        std::cerr   <<  "| 4.Swimming                                                              \n";
        std::cerr   <<  "| 3.Ping Bong                                                             \n";
        std::cerr   <<  "| 3.Billiards                                                             \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }

    void ShowEnterPeriodMessage () {
        std::cerr   <<  " ------------ \n";
        std::cerr   <<  "|Enter Period|\n";
        std::cerr   <<  " ------------ \n";
    }

    void ShowAvailableReservables (const std::unordered_map<std::string, Reservable*>& reservablesDirectory, const std::string& category, const std::pair<int, int>& period) {
        for(auto& pair : reservablesDirectory) {
            if(reservablesDirectory.at(pair.first)->isReservableAvailable() && reservablesDirectory.at(pair.first)->getCategory() == category && reservablesDirectory.at(pair.first)->isPeriodAvailable(period.first, period.second))
                reservablesDirectory.at(pair.first)->showReservableInfo();
            else
                continue;
        }
    }

    void ShowMyReservations (const std::vector<Reservation*>& reservations, const std::string& userName) {
        for(auto& reservation : reservations){
            if(reservation->ShowReserverInfo() == userName)
                reservation->ShowReservationInfo();
        }
    }

};






class AdminUI : public UI {

public:

    void EnterUserNameMessage () {
        std::cout << "---------------------\n";
        std::cout << "|Enter The User Name|\n";
        std::cout << "---------------------\n";
    }

    void EnterUserPasswordMessage () {
        std::cout << "--------------------------\n";
        std::cout << "|Enter The User Password: \n";
        std::cout << "--------------------------\n";
    }

    void ShowErrorMessage () {
        std::cout << "---------------------\n";
        std::cout << "| Sorry, try again! |\n";
        std::cout << "---------------------\n";
    }


    void ShowSuccessMessage () {
        std::cout << "---------------------\n";
        std::cout << "|  Congratulations  |\n";
        std::cout << "---------------------\n";
    }


    virtual void ShowMessage() override {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "| 1. Add Reservable                                                       \n";
        std::cerr   <<  "| 2. Update Reservable Status                                             \n";
        std::cerr   <<  "| 3. Reservables List                                                     \n";
        std::cerr   <<  "| 4. Reservations List                                                    \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }

    void ShowAddReservableMessage () {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "| Enter Name, Category, Is Available?(true or false)                      \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }

    void ShowUpdateReservableStatusMessage () {
        std::cerr   <<  "--------------------------------------------------------------------------\n";
        std::cerr   <<  "| Enter New Reservable Status Is Available?(true or false)                \n";
        std::cerr   <<  "--------------------------------------------------------------------------\n";
    }

    void ShowReservablesList (const std::unordered_map<std::string, Reservable*>& reservablesDirectory) {
        for(auto& pair : reservablesDirectory){
            pair.second->showReservableInfo();
        }
    }

    void ShowReservationsList (const std::unordered_map<std::string, Reservation*>& reservationsDirectory) {
        for(auto& pair : reservationsDirectory){
            pair.second->ShowReservationInfo();
        }
    }

};









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


    std::unordered_map<std::string, Reservable*> reservablesDirectory;
    std::set<std::string> reservablenames;




public:

    /**
     * Initializes the SystemManager by loading user data from the database.
     *
     * @param users_file_path Path to the user database file.
     */
    SystemManager(const std::string& users_file_path, const std::string& reservables_file_path, const std::string& reservations_file_path) {
        databaseManagerInstance = DatabaseManager::getInstance(users_file_path, reservables_file_path, reservations_file_path);
        databaseManagerInstance->load_users(usernames, userDirectory);
        databaseManagerInstance->load_reservables(reservablenames, reservablesDirectory);

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


    void test () {
        for (auto& pair : reservablesDirectory) {
            pair.second -> showReservableInfo();
        }
        databaseManagerInstance->update_reservables(reservablesDirectory);
    }

};




int main() {

    SystemManager sys("data_base\\users.txt", "data_base\\reservables.txt", "blabla");
    sys.test();

}
