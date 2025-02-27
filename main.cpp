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


//Administrator Credintals
const std::string name     = "lolooppo";
const std::string password = "lolooppo@2004";






/**
 * Represents a user with a username and password.
 * This class provides basic functionality for storing and managing
 * a user's credentials, including setting and retrieving the username
 * and password.
 */
class User {
private:
    std::string name;
    std::string password;

public:
    User(const std::string& name, const std::string& password) :
        name(name), password(password) {
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    std::string getName() const {
        return name;
    }

    void setPassword(const std::string& password) {
        this->password = password;
    }

    std::string getPassword() const {
        return password;
    }
};







/**
 * Represents a reservable item with a name, category, availability status,
 * and available periods. This class provides functionality for managing
 * reservations and checking availability.
 */
class Reservable {
private:
    std::string name;
    std::string category;
    bool available;
    int availablePeriods[13];

public:
    Reservable(std::string name, std::string category, bool available) :
        name(name), category(category), available(available) {
            memset(availablePeriods, 0, sizeof(availablePeriods));
    }

    virtual ~Reservable(){}

    std::string getName() const {
        return name;
    }

    std::string getCategory() const {
        return category;
    }

    bool isReservableAvailable() const {
        return available;
    }

    void changeReservableAvailability(const bool& new_status) {
        available = new_status;
    }

    void reservePeriod(const int& from, const int& to) {
        for(int i=from; i<=to; i++)
            availablePeriods[i]++;
    }

    void freePeriod(const int& from, const int& to) {
        for(int i=from; i<=to; i++){
            availablePeriods[i]--;
            availablePeriods[i] = std::max(availablePeriods[i], 0);
        }
    }

    void freeWholePeriods() {
        memset(availablePeriods, 0, sizeof(availablePeriods));
    }

    bool isPeriodAvailable(const int& from, const int& to) const {
        for(int i = from; i<=to; i++)
            if(availablePeriods[i] != 0)
                return false;

        return true;
    }

    void showAvailablePeriods() const {
        for(int i=1; i<=12; i++){
            if(availablePeriods[i] == 0){
                std::cerr << i << ", ";
            }
        }
        std::cerr << "\n";
    }

    virtual void showReservableInfo() const {
        std::cerr << "----------------------------------------------------------------------------------\n";
        std::cerr << "| Name             : " << name << "\n";
        std::cerr << "| Category         : " << category << "\n";
        std::cerr << "| Status           : ";
        available ? std::cerr << "Available\n" : std::cerr << "Under Maintenance\n";
        std::cerr << "| Available Periods: ";
        for(int i=1; i<=12; i++){
            if(availablePeriods[i] == 0)
                std::cerr << i << ", ";
        }
        std::cerr << "\n";
    }

};






/**
 * Represents a football playground, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for football playgrounds, such as morning and night prices.
 */
class FootballPlayGround : public Reservable {
private:
    double AmPrice;
    double PmPrice;

public:
    FootballPlayGround(std::string name, bool available, double AmPrice, double PmPrice) :
        Reservable(name, "Football", available), AmPrice(AmPrice), PmPrice(PmPrice) {
    }


    double getAmPrice() const {
        return AmPrice;
    }

    double getPmPrice() const {
        return PmPrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Morning Price    : " << AmPrice << "\n";
        std::cerr << "| Night   Price    : " << PmPrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};






/**
 * Represents a volleyball playground, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for volleyball playgrounds, such as sand and rubber ground prices.
 */
class VolleyballPlayGround : public Reservable {
private:
    double SandGroundPrice;
    double RubberGroundPrice;

public:
    VolleyballPlayGround(const std::string& name, const bool& available, const double& SandGroundPrice, const double& RubberGroundPrice) :
        Reservable(name, "Volleyball", available), SandGroundPrice(SandGroundPrice), RubberGroundPrice(RubberGroundPrice) {
    }

    double getSandGroundPrice() const {
        return SandGroundPrice;
    }

    double getRubberGroundPrice() const {
        return RubberGroundPrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Sand Ground Price    : " << SandGroundPrice << "\n";
        std::cerr << "| Rubber Ground Price    : " << RubberGroundPrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};








/**
 * Represents a tennis playground, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for tennis playgrounds, such as single and multiplayer match prices.
 */
class TennisPlayGround : public Reservable {
private:
    double SinglePlayerMatchPrice;
    double MultiPlayerMatchPrice;

public:
    TennisPlayGround(const std::string& name, const bool& available, const double& SinglePlayerMatchPrice, const double& MultiPlayerMatchPrice) :
        Reservable(name, "Tennis", available), SinglePlayerMatchPrice(SinglePlayerMatchPrice), MultiPlayerMatchPrice(MultiPlayerMatchPrice) {
    }


    double getSinglePlayerMatchPrice() const {
        return SinglePlayerMatchPrice;
    }

    double getMultiPlayerMatchPrice() const {
        return MultiPlayerMatchPrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Singles Match Price    : " << SinglePlayerMatchPrice << "\n";
        std::cerr << "| Doubles Match Price    : " << MultiPlayerMatchPrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};






/**
 * Represents a swimming pool, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for swimming pools, such as cold and warm water prices.
 */
class SwimmingPool : public Reservable {
private:
    double ColdWaterPrice;
    double WarmWaterPrice;

public:
    SwimmingPool(const std::string& name, const bool& available, const double& ColdWaterPrice, const double& WarmWaterPrice) :
        Reservable(name, "Swimming", available), ColdWaterPrice(ColdWaterPrice), WarmWaterPrice(WarmWaterPrice) {
    }


    double getColdWaterPrice() const {
        return ColdWaterPrice;
    }

    double getWarmWaterPrice() const {
        return WarmWaterPrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Cold Water Pool: " << ColdWaterPrice << "\n";
        std::cerr << "| Warm Water Pool: " << WarmWaterPrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};







/**
 * Represents a ping-pong table, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for ping-pong tables, such as single and multiplayer match prices.
 */
class PingbongTable : public Reservable {
private:
    double SinglePlayerMatchPrice;
    double MultiPlayerMatchPrice;

public:
    PingbongTable(const std::string& name, const bool& available, const double& SinglePlayerMatchPrice, const double& MultiPlayerMatchPrice) :
        Reservable(name, "Ping", available), SinglePlayerMatchPrice(SinglePlayerMatchPrice), MultiPlayerMatchPrice(MultiPlayerMatchPrice) {
    }


    double getSinglePlayerMatchPrice() const {
        return SinglePlayerMatchPrice;
    }

    double getMultiPlayerMatchPrice() const {
        return MultiPlayerMatchPrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Singles Match Price: " << SinglePlayerMatchPrice << "\n";
        std::cerr << "| Doubles Match Price: " << MultiPlayerMatchPrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};







/**
 * Represents a billiards table, which is a type of reservable item.
 * This class extends the Reservable class and adds specific attributes
 * for billiards tables, such as normal and American game prices.
 */
class BilliardsTable : public Reservable {
private:
    double NormalGamePrice;
    double AmericanGamePrice;

public:
    BilliardsTable(const std::string& name, const bool& available, const double& NormalGamePrice, const double& AmericanGamePrice) :
       Reservable(name, "Billiards", available), NormalGamePrice(NormalGamePrice), AmericanGamePrice(AmericanGamePrice) {
    }


    double getNormalGamePrice() const {
        return NormalGamePrice;
    }

    double getAmericanGamePrice() const {
        return AmericanGamePrice;
    }

    void showReservableInfo() const {
        Reservable::showReservableInfo();
        std::cerr << "| Normal Match Price: " << NormalGamePrice << "\n";
        std::cerr << "| American Match Price: " << AmericanGamePrice << "\n";
        std::cerr << "----------------------------------------------------------------------------------\n";
    }
};







/**
 * Represents a reservation made by a user for a specific reservable item.
 * This class provides functionality for managing reservations, including
 * calculating the total price and displaying reservation information.
 */
class Reservation {
protected:
    int from;
    int to;
    std::string userName;
    Reservable* reservable;

public:
    Reservation(const int& from, const int& to, const std::string& userName) :
        from(from), to(to), userName(userName) {
    }

    virtual ~Reservation(){}

    virtual double getTotalPrice() = 0;

    void setReservable(Reservable* reservable) {
        this->reservable = reservable;
    }

    const Reservable* getReservable() const {
        return reservable;
    }

    std::string getUserName() const {
        return userName;
    }

    std::pair<int, int> getReservedPeriod() const {
        return {from, to};
    }

    virtual bool getStatus() = 0;

    int totalTimeReserved() {
        return to - from;
    }

    virtual void ShowReservationInfo() {
        std::cerr << "-----------------------------------------------------------------------\n";
        std::cerr << "|  Reserved From: " << from << ", To: " << to << "\n";
        std::cerr << "|  Reserved By: " << userName << "\n";
        std::cerr << "|  Reserved Item Name: " << reservable->getName() << "\n";
        std::cerr << "|  Total Price:    " << getTotalPrice() << "\n";
    }

    std::string ShowReserverInfo() const {
        return userName;
    }
};






/**
 * Represents a reservation for a football playground.
 * This class extends the Reservation class and adds specific attributes
 * for football reservations, such as morning or night reservation.
 */
class FootballReservation : public Reservation {
private:
    bool isMorningReservation;

public:
    FootballReservation(const int& from, const int& to, const std::string& userName, const bool& isMorningReservation) :
        Reservation(from, to, userName), isMorningReservation(isMorningReservation) {
    }

    double getTotalPrice() override {
        double total_price = isMorningReservation ? (totalTimeReserved() * static_cast<FootballPlayGround*>(reservable)->getAmPrice()) : (totalTimeReserved() * static_cast<FootballPlayGround*>(reservable)->getPmPrice());
        return total_price;
    }

    bool getStatus() override {
        return isMorningReservation;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Reservation Slot: ";
        isMorningReservation ? std::cerr << "Morning" : std::cerr << "Night";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};





/**
 * Represents a reservation for a volleyball playground.
 * This class extends the Reservation class and adds specific attributes
 * for volleyball reservations, such as sand or rubber ground reservation.
 */
class VolleyballReservation : public Reservation {
private:
    bool isSandGround;

public:
    VolleyballReservation(const int& from, const int& to, const std::string& userName, const bool& isSandGround) :
        Reservation(from, to, userName), isSandGround(isSandGround) {
    }

    virtual double getTotalPrice() override {
        double total_price = isSandGround ? (totalTimeReserved() * static_cast<VolleyballPlayGround*>(reservable)->getSandGroundPrice()) : (totalTimeReserved() * static_cast<VolleyballPlayGround*>(reservable)->getRubberGroundPrice());
        return total_price;
    }

    bool getStatus() override {
        return isSandGround;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Playground Type: ";
        isSandGround ? std::cerr << "Sand" : std::cerr << "Rubber";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};





/**
 * Represents a reservation for a tennis playground.
 * This class extends the Reservation class and adds specific attributes
 * for tennis reservations, such as single or multiplayer match reservation.
 */
class TennisReservation : public Reservation {
private:
    bool isSingleMatch;

public:
    TennisReservation(const int& from, const int& to, const std::string& userName, const bool& isSingleMatch) :
        Reservation(from, to, userName), isSingleMatch(isSingleMatch) {
    }

    virtual double getTotalPrice() override {
        double total_price = isSingleMatch ? (totalTimeReserved() * static_cast<TennisPlayGround*>(reservable)->getSinglePlayerMatchPrice()) : (totalTimeReserved() * static_cast<TennisPlayGround*>(reservable)->getMultiPlayerMatchPrice());
        return total_price;
    }

    bool getStatus() override {
        return isSingleMatch;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Game Type: ";
        isSingleMatch ? std::cerr << "Singles" : std::cerr << "Doubles";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};






/**
 * Represents a reservation for a swimming pool.
 * This class extends the Reservation class and adds specific attributes
 * for swimming pool reservations, such as cold or warm water reservation.
 */
class SwimmingpoolReservation : public Reservation {
private:
    bool isColdWaterReservation;

public:
    SwimmingpoolReservation(const int& from, const int& to, const std::string& userName, const bool& isColdWaterReservation) :
        Reservation(from, to, userName), isColdWaterReservation(isColdWaterReservation) {
    }

    virtual double getTotalPrice() override {
        double total_price = isColdWaterReservation ? (totalTimeReserved() * static_cast<SwimmingPool*>(reservable)->getColdWaterPrice()) : (totalTimeReserved() * static_cast<SwimmingPool*>(reservable)->getWarmWaterPrice());
        return total_price;
    }

    bool getStatus() override {
        return isColdWaterReservation;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Pool water Condition: ";
        isColdWaterReservation ? std::cerr << "Cold" : std::cerr << "Warm";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};






/**
 * Represents a reservation for a ping-pong table.
 * This class extends the Reservation class and adds specific attributes
 * for ping-pong reservations, such as single or multiplayer match reservation.
 */
class PingbongReservation : public Reservation {
private:
    bool isSingleMatch;

public:
    PingbongReservation(const int& from, const int& to, const std::string& userName, const bool& isSingleMatch) :
        Reservation(from, to, userName), isSingleMatch(isSingleMatch) {
    }

    virtual double getTotalPrice() override {
        double total_price = isSingleMatch ? (totalTimeReserved() * static_cast<PingbongTable*>(reservable)->getSinglePlayerMatchPrice()) : (totalTimeReserved() * static_cast<PingbongTable*>(reservable)->getMultiPlayerMatchPrice());
        return total_price;
    }

    bool getStatus() override {
        return isSingleMatch;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Game Type: ";
        isSingleMatch ? std::cerr << "Singles" : std::cerr << "Doubles";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};






/**
 * Represents a reservation for a billiards table.
 * This class extends the Reservation class and adds specific attributes
 * for billiards reservations, such as normal or American game reservation.
 */
class BilliardsReservation : public Reservation {
private:
    bool isNormalGame;

public:
    BilliardsReservation(const int& from, const int& to, const std::string& userName, const bool& isNormalGame) :
        Reservation(from, to, userName), isNormalGame(isNormalGame) {
    }

    virtual double getTotalPrice() override {
        double total_price = isNormalGame ? (totalTimeReserved() * static_cast<BilliardsTable*>(reservable)->getNormalGamePrice()) : (totalTimeReserved() * static_cast<BilliardsTable*>(reservable)->getAmericanGamePrice());
        return total_price;
    }

    bool getStatus() override {
        return isNormalGame;
    }

    virtual void ShowReservationInfo() {
        Reservation::ShowReservationInfo();
        std::cerr << "|  Game Type: ";
        isNormalGame ? std::cerr << "Normal" : std::cerr << "American";
        std::cerr << "\n";
        std::cerr << "-----------------------------------------------------------------------\n";
    }
};






/**
 * Represents an itinerary, which is a collection of reservations made by a user.
 * This class provides functionality for managing and displaying the itinerary,
 * including calculating the total price of all reservations.
 */
class Itinerary {
private:
    std::vector<Reservation*> reservations;

public:
    void add_reservation(Reservation* reservation) {
        reservations.push_back(reservation);
    }

    double get_total_price() const {
        double total_price = 0.0;
        for(int i=0; i<(int)reservations.size(); i++){
            total_price += reservations[i]->getTotalPrice();
        }
        return total_price;
    }

    void showItineraryInfo() const {
        for(int i=0; i<(int)reservations.size(); i++){
            reservations[i]->ShowReservationInfo();
            std::cerr << "\n";
        }
        std::cerr << "-------------------------------------------------------------\n";
        std::cerr << "| Total Itinerary Price: " << get_total_price() << "|\n";
        std::cerr << "-------------------------------------------------------------\n";
    }
};







/**
 * Interface defining authentication-related operations.
 * Implementations of this interface will provide functionality
 * for user sign-up and sign-in processes.
 */
class IAuthentication {
public:
    IAuthentication() = default;
    virtual bool checkUsername(const std::string& username, const std::set<std::string>& usernames) = 0;
    virtual ~IAuthentication() = default;
};







/**
 * Handles user registration (sign-up) process.
 * This class implements the authentication logic required to
 * create new user accounts and validate input.
 */
class SignUpService : public IAuthentication {
public:
    SignUpService() = default;

    /**
     * Checks whether a given username meets the required format and is not already in use.
     *
     * @param username The username to validate.
     * @param usernames A set of existing usernames to check for duplicates.
     * @return True if the username is valid and available, otherwise false.
     */
    virtual bool checkUsername(const std::string& username, const std::set<std::string>& usernames) override {
        if(usernames.count(username))
            return false;

        if(!isalpha(username[0]))
            return false;

        for(int i=0; i<(int)username.length(); i++){
            if(!(isdigit(username[i]) || (username[i] == '_') || (tolower(username[i]) >= 'a' && tolower(username[i]) <= 'z')))
                return false;
        }

        return true;
    }

    /**
     * Validates whether the given password meets the required security format.
     *
     * @param password The password to validate.
     * @return True if the password meets the required format, otherwise false.
     */
    virtual bool validatePasswordFormat(const std::string& password) {
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

    virtual ~SignUpService() = default;
};





/**
 * Handles user authentication (sign-in) process.
 * This class verifies user credentials, checks authentication rules,
 * and manages login sessions.
 */
class SignInService : public IAuthentication {
public:
    SignInService() = default;

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

    /**
     * Verifies whether the given password matches the user's password.
     *
     * @param username The username to verify.
     * @param userpassword The password to verify.
     * @param userDirectory A map of users to check against.
     * @return True if the password matches, otherwise false.
     */
    virtual bool verifyUserPassword(const std::string& username, const std::string& userpassword, const std::unordered_map<std::string, User*>& userDirectory) {
        return userpassword == userDirectory.at(username)->getPassword();
    }

    virtual ~SignInService() = default;
};





/**
 * Manages reading from and writing to the database file.
 * This class provides functionality to store and retrieve user data
 * in a persistent file-based database. It ensures efficient file
 * operations and data integrity.
 */
class DatabaseManager {
private:
    std::string users_file_path;
    std::string reservables_file_path;
    std::string reservations_file_path;

    DatabaseManager(const std::string& users_file_path, const std::string& reservables_file_path, const std::string& reservations_file_path) :
        users_file_path(users_file_path), reservables_file_path(reservables_file_path), reservations_file_path(reservations_file_path) {
    }

    static DatabaseManager* databaseManagerInstance;

public:
    static DatabaseManager* getInstance(const std::string& users_file_path, const std::string& reservables_file_path, const std::string& reservations_file_path) {
        if(databaseManagerInstance == nullptr)
            databaseManagerInstance = new DatabaseManager(users_file_path, reservables_file_path, reservations_file_path);

        return databaseManagerInstance;
    }

    void load_users(std::set<std::string>& usernames, std::unordered_map<std::string, User*>& userDirectory) {
        std::ifstream file_handler(users_file_path);

        if(file_handler.fail()){
            std::cout << "sorry,something went wrong in the users file\n";
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

    void update_users(std::unordered_map<std::string, User*>& userDirectory) {
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

    void load_reservables(std::set<std::string>& reservableNames, std::unordered_map<std::string, Reservable*>& reservablesDirectory, std::vector<Reservable*>& reservables) {
        std::ifstream file_handler(reservables_file_path);

        if(file_handler.fail()){
            std::cout << "sorry,something went wrong in the reservables file\n";
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
                std::string SandGroundPriceString;
                std::string RubberGroundPriceString;
                double SandGroundPrice;
                double RubberGroundPrice;

                std::getline(ss, SandGroundPriceString, ',');
                std::getline(ss, RubberGroundPriceString, ',');

                SandGroundPrice   = std::stod(SandGroundPriceString);
                RubberGroundPrice = std::stod(RubberGroundPriceString);

                reservablesDirectory[name] = new VolleyballPlayGround(name, available, SandGroundPrice, RubberGroundPrice);

            }else if (category == "Tennis") {
                std::string SinglePlayerMatchPriceString;
                std::string MultiPlayerMatchPriceString ;
                double SinglePlayerMatchPrice;
                double MultiPlayerMatchPrice ;

                std::getline(ss, SinglePlayerMatchPriceString, ',');
                std::getline(ss, MultiPlayerMatchPriceString, ',' );

                SinglePlayerMatchPrice = std::stod(SinglePlayerMatchPriceString);
                MultiPlayerMatchPrice  = std::stod(MultiPlayerMatchPriceString );

                reservablesDirectory[name] = new TennisPlayGround(name, available, SinglePlayerMatchPrice, MultiPlayerMatchPrice);

            }else if (category == "Swimming") {
                std::string ColdWaterPriceString;
                std::string WarmWaterPriceString;
                double ColdWaterPrice;
                double WarmWaterPrice;

                std::getline(ss, ColdWaterPriceString, ',');
                std::getline(ss, WarmWaterPriceString, ',');

                ColdWaterPrice = std::stod(ColdWaterPriceString);
                WarmWaterPrice = std::stod(WarmWaterPriceString);

                reservablesDirectory[name] = new SwimmingPool(name, available, ColdWaterPrice, WarmWaterPrice);

            }else if (category == "Ping bong") {
                std::string SinglePlayerMatchPriceString;
                std::string MultiPlayerMatchPriceString ;
                double SinglePlayerMatchPrice;
                double MultiPlayerMatchPrice ;

                std::getline(ss, SinglePlayerMatchPriceString, ',');
                std::getline(ss, MultiPlayerMatchPriceString, ',' );

                SinglePlayerMatchPrice = std::stod(SinglePlayerMatchPriceString);
                MultiPlayerMatchPrice  = std::stod(MultiPlayerMatchPriceString );

                reservablesDirectory[name] = new PingbongTable(name, available, SinglePlayerMatchPrice, MultiPlayerMatchPrice);

            }else if (category == "Billiards") {
                std::string NormalGamePriceString;
                std::string AmericanGamePriceStirng;
                double NormalGamePrice;
                double AmericanGamePrice;

                std::getline(ss, NormalGamePriceString, ','  );
                std::getline(ss, AmericanGamePriceStirng, ',');

                NormalGamePrice   = std::stod(NormalGamePriceString  );
                AmericanGamePrice = std::stod(AmericanGamePriceStirng);

                reservablesDirectory[name] = new BilliardsTable(name, available, NormalGamePrice, AmericanGamePrice);

            }

            reservableNames.insert(name);
            reservables.push_back(reservablesDirectory[name]);
        }

    }

    void update_reservables(const std::unordered_map<std::string, Reservable*>& reservablesDirectory) {
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

            }else if (category == "Volleyball") {
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<VolleyballPlayGround*>(pair.second) -> getSandGroundPrice  ();
                oss2 << std::fixed << std::setprecision(2) << static_cast<VolleyballPlayGround*>(pair.second) -> getRubberGroundPrice();

                std::string SandGroundPriceString   = oss1.str();
                std::string RubberGroundPriceString = oss2.str();

                oss<<SandGroundPriceString<<","<<RubberGroundPriceString;

            }else if (category == "Tennis") {
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<TennisPlayGround*>(pair.second) -> getSinglePlayerMatchPrice();
                oss2 << std::fixed << std::setprecision(2) << static_cast<TennisPlayGround*>(pair.second) -> getMultiPlayerMatchPrice ();

                std::string SinglePlayerMatchPriceString   = oss1.str();
                std::string MultiPlayerMatchPriceString    = oss2.str();

                oss<<SinglePlayerMatchPriceString<<","<<MultiPlayerMatchPriceString;

            }else if (category == "Swimming") {
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<SwimmingPool*>(pair.second) -> getColdWaterPrice();
                oss2 << std::fixed << std::setprecision(2) << static_cast<SwimmingPool*>(pair.second) -> getWarmWaterPrice();

                std::string ColdWaterPriceString    = oss1.str();
                std::string WarmWaterPriceString    = oss2.str();

                oss<<ColdWaterPriceString<<","<<WarmWaterPriceString;

            }else if (category == "Ping bong") {
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<PingbongTable*>(pair.second) -> getSinglePlayerMatchPrice();
                oss2 << std::fixed << std::setprecision(2) << static_cast<PingbongTable*>(pair.second) -> getMultiPlayerMatchPrice ();

                std::string SinglePlayerMatchPriceString   = oss1.str();
                std::string MultiPlayerMatchPriceString    = oss2.str();

                oss<<SinglePlayerMatchPriceString<<","<<MultiPlayerMatchPriceString;

            }else if (category == "Billiards") {
                std::ostringstream oss1, oss2;
                oss1 << std::fixed << std::setprecision(2) << static_cast<BilliardsTable*>(pair.second) -> getNormalGamePrice  ();
                oss2 << std::fixed << std::setprecision(2) << static_cast<BilliardsTable*>(pair.second) -> getAmericanGamePrice();

                std::string NormalGamePriceString      = oss1.str();
                std::string AmericanGamePriceString    = oss2.str();

                oss<<NormalGamePriceString<<","<<AmericanGamePriceString;

            }

            file_handler<<oss.str()<<"\n";
        }

        file_handler.close();
    }

    void load_reservations(std::unordered_map<std::string, std::vector<Reservation*>>& reservationsDirectory, std::unordered_map<std::string, Reservable*>& reservablesDirectory, std::vector<Reservation*>& reservations) {
        std::ifstream file_handler(reservations_file_path);

        if(file_handler.fail()){
            std::cout << "sorry,something went wrong in the reservations file\n";
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

            std::string fromString;
            std::string toString;
            std::string category;
            std::string userName;
            std::string reservableName;
            std::string statusString;

            int from;
            int to;
            bool status;

            std::getline(ss, fromString,       ',');
            std::getline(ss, toString,         ',');
            std::getline(ss, category,         ',');
            std::getline(ss, userName,         ',');
            std::getline(ss, reservableName,   ',');
            std::getline(ss, statusString,     ',');

            from = std::stoi(fromString);
            to   = std::stoi(toString);
            status = (statusString == "1");

            Reservation* reservation;

            if(category == "Football"){
                reservation = new FootballReservation(from, to, userName, status);
            }else if(category == "Volleyball"){
                reservation = new VolleyballReservation(from, to, userName, status);
            }else if(category == "Tennis"){
                reservation = new TennisReservation(from, to, userName, status);
            }else if(category == "Swimming"){
                reservation = new SwimmingpoolReservation(from, to, userName, status);
            }else if(category == "Ping"){
                reservation = new PingbongReservation(from, to, userName, status);
            }else if(category == "Billiards"){
                reservation = new BilliardsReservation(from, to, userName, status);
            }

            reservablesDirectory[reservableName]->reservePeriod(from, to);
            reservation->setReservable(reservablesDirectory.at(reservableName));
            reservationsDirectory[userName].push_back(reservation);
            reservations.push_back(reservation);

        }
    }

    void update_reservations(const std::vector<Reservation*>& reservations) {
        auto file_status = std::ios::in | std::ios::out | std::ios::trunc;
        std::ofstream file_handler(reservations_file_path, file_status);

        for(auto& reservation : reservations) {
            std::ostringstream oss;

            std::string fromString     = std::to_string(reservation->getReservedPeriod().first);
            std::string toString       = std::to_string(reservation->getReservedPeriod().second);
            std::string category       = reservation->getReservable()->getCategory();
            std::string userName       = reservation->getUserName();
            std::string reservableName = reservation->getReservable()->getName();
            std::string statusString   = reservation->getStatus() ? "1" : "0";

            oss<<fromString<<","<<toString<<","<<category<<","<<userName<<","<<reservableName<<","<<statusString<<"\n";
            file_handler<<oss.str();
        }

        file_handler.close();
    }

    static void freeInstance() {
        if(databaseManagerInstance == nullptr)
            return;

        delete databaseManagerInstance;
        databaseManagerInstance = nullptr;
    }

};
DatabaseManager* DatabaseManager :: databaseManagerInstance = nullptr;






// UI interface
class UI {
public:
    virtual void ShowMessage () = 0;
};





/**
 * Represents the user interface for the home screen.
 * This class provides functionality for displaying the home screen and
 * handling user input.
 */
class HomeUI : public UI {
public:
    void ShowMessage() override {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "                                   |Choose|                               \n";
        std::cerr << "                                    ------                                \n";
        std::cerr << "| 1. Sign In                                                              \n";
        std::cerr << "| 2. Sign Up                                                              \n";
        std::cerr << "| 3. Admin                                                                \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }
};





/**
 * Represents the user interface for the user screen.
 * This class provides functionality for displaying the user screen and
 * handling user input.
 */
class UserUI : public UI {
public:
    void EnterUserNameMessage() {
        std::cout << "---------------------\n";
        std::cout << "|Enter The User Name|\n";
        std::cout << "---------------------\n";
    }

    void EnterUserPasswordMessage() {
        std::cout << "--------------------------\n";
        std::cout << "|Enter The User Password: \n";
        std::cout << "--------------------------\n";
    }

    void ShowErrorMessage() {
        std::cout << "---------------------\n";
        std::cout << "| Sorry, try again! |\n";
        std::cout << "---------------------\n";
    }

    void ShowSuccessMessage() {
        std::cout << "---------------------\n";
        std::cout << "|  Congratulations  |\n";
        std::cout << "---------------------\n";
    }

    virtual void ShowMessage() override {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "| 1. Reserve                                                              \n";
        std::cerr << "| 2. Show My Reservations                                                 \n";
        std::cerr << "| 3. Cancel Reservation                                                   \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowCategoryList() {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "|                             |Choose Category|                           \n";
        std::cerr << "                               ---------------                            \n";
        std::cerr << "| 1.Football                                                              \n";
        std::cerr << "| 2.Volleyball                                                            \n";
        std::cerr << "| 3.Tennis                                                                \n";
        std::cerr << "| 4.Swimming                                                              \n";
        std::cerr << "| 5.Ping Bong                                                             \n";
        std::cerr << "| 6.Billiards                                                             \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowEnterCategoryMessage() {
        std::cerr << " ---------------- \n";
        std::cerr << "|Enter Category: |\n";
        std::cerr << " ---------------- \n";
    }

    void ShowEnterPeriodMessage() {
        std::cerr << " -------------- \n";
        std::cerr << "|Enter Period: |\n";
        std::cerr << " -------------- \n";
    }

    void ShowAvailableReservables(const std::unordered_map<std::string, Reservable*>& reservablesDirectory, const std::string& category, const std::pair<int, int>& period) {
        for(auto& pair : reservablesDirectory) {
            if(reservablesDirectory.at(pair.first)->isReservableAvailable() && reservablesDirectory.at(pair.first)->getCategory() == category && reservablesDirectory.at(pair.first)->isPeriodAvailable(period.first, period.second))
                reservablesDirectory.at(pair.first)->showReservableInfo();
            else
                continue;
        }
    }

    void ShowMyReservations(std::unordered_map<std::string, std::vector<Reservation*>>& reservationsDirectory, const std::string& userName) const {
        if(reservationsDirectory.count(userName) == 0 || (int)reservationsDirectory.at(userName).size() == 0){
            std::cerr << "Sorry, you have no reservations yet\n";
            return;
        }



        for(auto& reservation : reservationsDirectory[userName])
            reservation->ShowReservationInfo();
    }
};





/**
 * Represents the user interface for the admin screen.
 * This class provides functionality for displaying the admin screen and
 * handling admin input.
 */
class AdminUI : public UI {
public:
    void EnterAdminNameMessage() {
        std::cout << "----------------------\n";
        std::cout << "|Enter The Admin Name|\n";
        std::cout << "----------------------\n";
    }

    void EnterAdminPasswordMessage() {
        std::cout << "---------------------------\n";
        std::cout << "|Enter The Admin Password: \n";
        std::cout << "---------------------------\n";
    }

    void ShowErrorMessage() {
        std::cout << "---------------------\n";
        std::cout << "| Sorry, try again! |\n";
        std::cout << "---------------------\n";
    }

    void ShowSuccessMessage() {
        std::cout << "---------------------\n";
        std::cout << "|  Congratulations  |\n";
        std::cout << "---------------------\n";
    }

    virtual void ShowMessage() override {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "| 1. Add Reservable                                                       \n";
        std::cerr << "| 2. Update Reservable Status                                             \n";
        std::cerr << "| 3. Reservables List                                                     \n";
        std::cerr << "| 4. Reservations List                                                    \n";
        std::cerr << "| 5. Clear Reservations                                                   \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowCategoryList() {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "|                             |Choose Category|                           \n";
        std::cerr << "                               ---------------                            \n";
        std::cerr << "| 1.Football                                                              \n";
        std::cerr << "| 2.Volleyball                                                            \n";
        std::cerr << "| 3.Tennis                                                                \n";
        std::cerr << "| 4.Swimming                                                              \n";
        std::cerr << "| 5.Ping Bong                                                             \n";
        std::cerr << "| 6.Billiards                                                             \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowEnterReservableName() {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "| Enter Reservable Name:                                                  \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowAddReservableMessage() {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "| Enter Name, Is Available?(true or false)                                \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowUpdateReservableStatusMessage() {
        std::cerr << "--------------------------------------------------------------------------\n";
        std::cerr << "| Enter New Reservable Status Is Available?(true or false)                \n";
        std::cerr << "--------------------------------------------------------------------------\n";
    }

    void ShowReservablesList(const std::unordered_map<std::string, Reservable*>& reservablesDirectory) {
        for(auto& pair : reservablesDirectory){
            pair.second->showReservableInfo();
        }
    }

    void ShowReservationsList(const std::vector<Reservation*>& reservations) {
        for(auto& reservation : reservations){
            reservation->ShowReservationInfo();
        }
        std::cerr<<"\n";
    }
};








// useful for mapping each game category
std::unordered_map<int, std::string> categories_map = {{1,"Football"}, {2,"Volleyball"}, {3,"Tennis"}, {4,"Swimming"}, {5,"Ping"}, {6,"Billiards"}};

/**
 * Manages the core system operations, including user sign-up, sign-in,
 * and database interactions. This class serves as the central controller
 * for user authentication and data management.
 */
class SystemManager {
private:
    HomeUI  homeUI;
    UserUI  userUI;
    AdminUI adminUI;

    SignUpService SignUpServiceInstance;
    SignInService SignInServiceInstance;
    DatabaseManager* databaseManagerInstance;

    std::unordered_map<std::string, User*> userDirectory;  // Stores registered users in memory.
    std::set<std::string> usernames;  // Tracks unique usernames for quick lookup.

    std::unordered_map<std::string, std::vector<Reservation*>> reservationsDirectory;
    std::vector<Reservation*> reservations;

    std::unordered_map<std::string, Reservable*> reservablesDirectory;
    std::vector<Reservable*> reservables;
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
        databaseManagerInstance->load_reservables(reservablenames, reservablesDirectory, reservables);
        databaseManagerInstance->load_reservations(reservationsDirectory, reservablesDirectory, reservations);
    }

    ~SystemManager () {
        databaseManagerInstance->freeInstance();

        for(auto& pair : userDirectory){
            delete pair.second;
        }
        for(auto& i : reservations) {
            delete i;
        }
        for(auto& i: reservables){
            delete i;
        }
    }

    void do_reserve(const std::string& userName, const int& categoryChoise, const std::pair<int, int>& chosenPeriod) {
        Reservable* reservable = nullptr;
        Reservation* reservation = nullptr;

        for(auto& re : reservables) {
            if(re->getCategory() == categories_map[categoryChoise] && re->isReservableAvailable() && re->isPeriodAvailable(chosenPeriod.first, chosenPeriod.second)){
                reservable = re;
                break;
            }
        }

        if(reservable == nullptr){
            std::cerr << "Sorry, no reservables available at this period\n";
            return;
        }

        reservable->showReservableInfo();

        if(categories_map[categoryChoise] == "Football"){
            bool isMorningReservation;
            std::cerr<<"Choose (0)morning,   (1)night: \n";
            std::cin>>isMorningReservation;
            reservation = new FootballReservation(chosenPeriod.first, chosenPeriod.second, userName, !isMorningReservation);
        }else if (categories_map[categoryChoise] == "Volleyball") {
            bool isSandReservation;
            std::cerr<<"Choose (0)sand,      (1)rubber: \n";
            std::cin>>isSandReservation;
            reservation = new VolleyballReservation(chosenPeriod.first, chosenPeriod.second, userName, !isSandReservation);
        }else if (categories_map[categoryChoise] == "Tennis") {
            bool isSingleReservation;
            std::cerr<<"Choose (0)single,      (1)multi: \n";
            std::cin>>isSingleReservation;
            reservation = new TennisReservation(chosenPeriod.first, chosenPeriod.second, userName, !isSingleReservation);
        }else if (categories_map[categoryChoise] == "Swimming") {
            bool isColdReservation;
            std::cerr<<"Choose (0)cold,      (1)warm: \n";
            std::cin>>isColdReservation;
            reservation = new SwimmingpoolReservation(chosenPeriod.first, chosenPeriod.second, userName, !isColdReservation);
        }else if (categories_map[categoryChoise] == "Ping") {
            bool isSingleReservation;
            std::cerr<<"Choose (0)single,      (1)multi: \n";
            std::cin>>isSingleReservation;
            reservation = new PingbongReservation(chosenPeriod.first, chosenPeriod.second, userName, !isSingleReservation);
        }else if (categories_map[categoryChoise] == "Billiards"){
            bool isNormalReservation;
            std::cerr<<"Choose (0)normal,      (1)american: \n";
            std::cin>>isNormalReservation;
            reservation = new BilliardsReservation(chosenPeriod.first, chosenPeriod.second, userName, !isNormalReservation);
        }

        reservable->reservePeriod(chosenPeriod.first, chosenPeriod.second);
        reservation->setReservable(reservable);
        reservations.push_back(reservation);
        reservationsDirectory[userName].push_back(reservation);
        reservation->ShowReservationInfo();
    }

    void cancel_reservation(const std::string& userName, const std::string& reservableName, const std::pair<int, int>& reservedPeriod) {
        for (auto& re : reservables) {
            if(re->getName() == reservableName){
                re->freePeriod(reservedPeriod.first, reservedPeriod.second);
                break;
            }
        }

        for(auto& pair : reservationsDirectory){
            if(pair.first == userName) {
                for(auto& reservation:pair.second){
                    if(reservation->getReservable()->getName() == reservableName && reservation->getReservedPeriod() == reservedPeriod){
                        std::swap(reservation, pair.second.back());
                        pair.second.pop_back();
                        break;
                    }
                }
                break;
            }
            else{
                continue;
            }
        }

        for(auto& reservation : reservations) {
            if(reservation->getUserName() == userName && reservation->getReservedPeriod() == reservedPeriod && reservation->getReservable()->getName() == reservableName){
                delete reservation;
                std::swap(reservation, reservations.back());
                reservations.pop_back();
            }
        }

        std::cerr    <<  "\nReservations canceled\n";
        return;
    }

    void run_user_actions(const std::string& userName) {
        userUI.ShowMessage();

        std::cerr << "Press 0 if want to quit\n";

        int choice;
        std::cin>>choice;

        if(choice == 0) {
            return;

        } else if(choice == 1) {
            userUI.ShowCategoryList();
            userUI.ShowEnterCategoryMessage();

            int categoryChoise;
            std::pair<int, int> chosenPeriod;

            std::cin>>categoryChoise;

            if (categoryChoise < 1 || categoryChoise > 6) {
                std::cerr << "Sorry, invalid choice\n\n";
                return;
            }

            userUI.ShowEnterPeriodMessage();
            std::cin>>chosenPeriod.first>>chosenPeriod.second;

            do_reserve(userName, categoryChoise, chosenPeriod);

        } else if(choice == 2) {
            userUI.ShowMyReservations(reservationsDirectory, userName);

        } else if(choice == 3) {
            std::string reservableName;
            std::pair<int, int> reservedPeriod;

            std::cerr << "Enter reservable name, reservaed period as(from, to): ";
            std::cin >> reservableName >> reservedPeriod.first >> reservedPeriod.second;

            cancel_reservation(userName, reservableName, reservedPeriod);

        } else {
            std::cerr << "Sorry, invalid choice\n\n";
        }

        return;
    }

    void do_add_reservable(const int& chosenCategory){
        Reservable* new_reservable = nullptr;

        std::string name;
        std:: string category = categories_map[chosenCategory];
        bool available;
        double price1, price2;

        adminUI.ShowAddReservableMessage();
        std::cin>>name>>available;

        while(reservablenames.count(name)){
            adminUI.ShowErrorMessage();

            adminUI.ShowAddReservableMessage();
            std::cin>>name>>available;
        }

        if(category == "Football"){
            std::cerr<<"Enter morning and night reservation prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new FootballPlayGround(name, available, price1, price2);

        }else if(category == "Volleyball"){
            std::cerr<<"Enter sand and rubber ground prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new VolleyballPlayGround(name, available, price1, price2);

        }else if(category == "Tennis"){
            std::cerr<<"Enter single and multi reservation prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new TennisPlayGround(name, available, price1, price2);

        }else if(category == "Swimming"){
            std::cerr<<"Enter cold and warm water reservation prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new SwimmingPool(name, available, price1, price2);

        }else if(category == "Ping"){
            std::cerr<<"Enter single and multi reservation prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new PingbongTable(name, available, price1, price2);

        }else {
            std::cerr<<"Enter normal and american reservation prices:  ";
            std::cin>>price1>>price2;
            new_reservable = new BilliardsTable(name, available, price1, price2);
        }

        reservablenames.insert(name);
        reservablesDirectory[name] = new_reservable;
        reservables.push_back(new_reservable);
    }

    void do_clear_reservations(){
        for(auto& reservable : reservables){
            reservable->freeWholePeriods();
        }

        for(auto& reservation : reservations){
            delete reservation;
            reservation = nullptr;
        }

        for(auto& pair : reservationsDirectory) {
            pair.second.clear();
        }

        reservations.clear();
    }

    void run_admin_actions() {
        adminUI.ShowMessage();

        std::cerr << "Press 0 if want to quit\n";

        int choice;
        std::cin>>choice;

        if(choice == 0){
            return;

        }else if (choice == 1){
            adminUI.ShowCategoryList();

            int categoryChoise;
            std::cin>>categoryChoise;

            if (categoryChoise < 1 || categoryChoise > 6) {
                std::cerr << "Sorry, invalid choice\n\n";
                return;
            }
            do_add_reservable(categoryChoise);

        }else if (choice == 2){
            std::string reservableName;
            adminUI.ShowEnterReservableName();
            std::cin>>reservableName;

            while(reservablenames.count(reservableName) == 0){
                adminUI.ShowErrorMessage();

                adminUI.ShowEnterReservableName();
                std::cin>>reservableName;
            }

            for(auto& reservation : reservations){
                if(reservation->getReservable()->getName() == reservableName){
                    std::cerr << "Sorry, but this reservable is already reserved by someone\n";
                    return;
                }
            }

            reservablesDirectory[reservableName]->showReservableInfo();

            bool new_status;
            std::cerr<<"Enter new status (0 or 1): ";
            std::cin>>new_status;
            reservablesDirectory[reservableName]->changeReservableAvailability(new_status);

        }else if (choice == 3){
            adminUI.ShowReservablesList(reservablesDirectory);

        }else if (choice == 4){
            adminUI.ShowReservationsList(reservations);

        }else if (choice == 5){
            do_clear_reservations();

        }else {
            std::cerr << "Sorry, invalid choice\n\n";
        }

        return;
    }

    void user_signin() {
        std::string userName;
        std::string Password;

        userUI.EnterUserNameMessage();
        std::cin>>userName;
        while(!SignInServiceInstance.checkUsername(userName, usernames)){
            userUI.ShowErrorMessage();
            userUI.EnterUserNameMessage();
            std::cin>>userName;
        }

        userUI.EnterUserPasswordMessage();
        std::cin>>Password;
        while(!SignInServiceInstance.verifyUserPassword(userName, Password, userDirectory)){
            userUI.ShowErrorMessage();
            userUI.EnterUserPasswordMessage();
            std::cin>>Password;
        }
        userUI.ShowSuccessMessage();

        run_user_actions(userName);
    }

    void user_signup() {
        std::string userName;
        std::string Password;

        userUI.EnterUserNameMessage();
        std::cin>>userName;
        while(!SignUpServiceInstance.checkUsername(userName, usernames)){
            userUI.ShowErrorMessage();
            userUI.EnterUserNameMessage();
            std::cin>>userName;
        }

        userUI.EnterUserPasswordMessage();
        std::cin>>Password;
        while(!SignUpServiceInstance.validatePasswordFormat(Password)){
            userUI.ShowErrorMessage();
            userUI.EnterUserPasswordMessage();
            std::cin>>Password;
        }
        userUI.ShowSuccessMessage();

        usernames.insert(userName);
        userDirectory[userName] = new User(userName, Password);

        run_user_actions(userName);
    }

    void admin_signin() {
        std::string adminName;
        std::string adminPassword;

        adminUI.EnterAdminNameMessage();
        std::cin>>adminName;

        while(adminName != name){
            adminUI.ShowErrorMessage();

            adminUI.EnterAdminNameMessage();
            std::cin>>adminName;
        }

        adminUI.EnterAdminPasswordMessage();
        std::cin>>adminPassword;

        while(adminPassword != password){
            adminUI.ShowErrorMessage();

            adminUI.EnterAdminPasswordMessage();
            std::cin>>adminPassword;
        }

        adminUI.ShowSuccessMessage();

        run_admin_actions();
    }

    void update_data_base() {
        databaseManagerInstance->update_reservables(reservablesDirectory);
        databaseManagerInstance->update_users(userDirectory);
        databaseManagerInstance->update_reservations(reservations);
    }

    void run_system() {
        while(true){
            std::cerr << "Press 0 if want to quit\n";

            homeUI.ShowMessage();

            int choice = 1;
            std::cin>>choice;

            if(choice == 0)
                break;

            if (choice == 1) {
                user_signin();
            }else if (choice == 2) {
                user_signup();
            }else if (choice == 3) {
                admin_signin();
            }
        }

        update_data_base();
    }
};




int main() {
    SystemManager sys("data_base\\users.txt", "data_base\\reservables.txt", "data_base\\reservations.txt");
    sys.run_system();
}
