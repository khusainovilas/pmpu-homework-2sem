#include <iostream>
#include <string> 
#include <ctime>
#include <vector>
#include "func.h"
#include "Person.h"

using namespace std;

Person::Person(){
    birthDate.day = "";
    birthDate.month = "";
    birthDate.year = "";
    fullName = "";
    telephone = ""; 
}

void Person::displayingPersonData() const{
    if (fullName.empty()){
        cerr << "Error: Name is not set!" << endl;
        return;
    }
    if (telephone.empty()){
        cerr << "Error: Telephone number is not set!" << endl;
        return;
    }
    if (birthDate.day.empty() || birthDate.month.empty() || birthDate.year.empty()){
        cerr << "Error: Birth date is not set!" << endl;
        return;
    }
    formattedOutput(birthDate.day, birthDate.month, birthDate.year, fullName, telephone); 
}

string Person::getName() const{
    return fullName;
}

string Person::getBirthDay() const{
    return birthDate.day;
}

string Person::getBirthMonth() const{
    return birthDate.month;
}

string Person::getBirthYear() const{
    return birthDate.year;
}

void Person::inputDataFromConsole(){
    void formattedInput(); 
    bool flag = false;
    while (!flag){
        cout << "Enter birthday: ";
        string fullBirthDate; 
        getline(cin, fullBirthDate);
        vector<string> arrayDatebirth = birthdateFormatting(fullBirthDate); 
        if (arrayDatebirth.size() != 3){
            cout << "Date entered incorrectly!!!" << endl; 
        }
        else{
            string day = arrayDatebirth[0], month = arrayDatebirth[1], year = arrayDatebirth[2];
            flag = checkInputYear(year) * checkInputMonth(month) * checkInputDay(day, month, year); 
            birthDate.day = day; 
            birthDate.month = month; 
            birthDate.year = year; 
        }
    }

    flag = false;
    while (!flag){
        cout << "Enter telephone number: ";
        string temptel; 
        getline(cin, temptel);
        flag = checkInputTel(temptel); 
        if (flag){
            telephone = temptel; 
        }
    }
    flag = false;
    while (!flag){
        cout << "Enter full name: ";
        string tempname; 
        getline(cin, tempname);
        flag = checkInputName(tempname); 
        if (flag){
            fullName = tempname; 
        }
    }
}
    
void Person::inputDataFromFile(const string& fileName) {
    string file = fileReading(fileName);
    vector<string> data = readyFileData(file);
    string birthday = "", name = "", tel = ""; 

    for (string& s : data){
        if (s[0] == '+'){
            s.erase(0, 1); 
            if (isNumber(s) && tel == ""){
                tel = '+' + s; 
            }
        }
        else if(!isdigit(s[0])){
            if (name.empty()){
                name = s; 
            } 
            else{
                name += " " + s; 
            }
        }
        else{
            birthday = s; 
        }
    }
    vector<string> arrayDatebirth = birthdateFormatting(birthday); 
    if (arrayDatebirth.size() != 3){
        cout << "Date entered incorrectly!!!" << endl; 
        return; 
    }
    string day = arrayDatebirth[0], month = arrayDatebirth[1], year = arrayDatebirth[2]; 
    birthDate.day = day; 
    birthDate.month = month; 
    birthDate.year = year; 

    if (!checkInputTel(tel)){
        cout << "Invalid telephone number!" << endl;
        return;
    }
    telephone = tel; 

    if (!checkInputName(name)) {
        cout << "Invalid name!" << endl;
        return;
    }
    fullName = name;
}

void Person::nameCompare(const Person& person1, const Person& person2){
    if (person1.fullName.empty() || person2.fullName.empty()) {
        cerr << "One or both names are empty, cannot compare." << endl;
        return;
    }
    string fullNameperson1 = person1.getName(); 
    string fullNameperson2 = person2.getName(); 
    if (fullNameperson1 < fullNameperson2){
        cout << fullNameperson1 << "'s name comes before " << fullNameperson2 << "'s name." << endl; 
    }
    else if (fullNameperson2 > fullNameperson1){
        cout << fullNameperson2 << "'s name comes before " << fullNameperson1 << "'s name." << endl; 
    }
    else{
        cout << "Both persons have the same name." << endl; 
    }
}

void Person::birthDayCompare(const Person& person1, const Person& person2){
    if (person1.birthDate.day.empty() || person1.birthDate.month.empty() || person1.birthDate.year.empty() || 
        person2.birthDate.day.empty() || person2.birthDate.month.empty() || person2.birthDate.year.empty()){
        cerr << "One or both birth dates are incomplete, cannot compare." << endl;
        return;
    }
    time_t person1birthdate = getCurrentTime(stoi(person1.getBirthDay()), stoi(person1.getBirthMonth()), stoi(person1.getBirthYear())); 
    time_t person2birthdate = getCurrentTime(stoi(person2.getBirthDay()), stoi(person2.getBirthMonth()), stoi(person2.getBirthYear())); 
    if (person1birthdate < person2birthdate){
        cout << person1.getName() <<  " is older than " << person2.getName() << "." << endl; 
    }
    else if (person2birthdate < person1birthdate){
        cout << person2.getName() <<  " is older than " << person1.getName() << "." << endl; 
    }
    else{
        cout << "Both persons were born on the same date." << endl; 
    }
}

void Person::daysUntilBirthday() const{
    if (birthDate.day.empty() || birthDate.month.empty() || birthDate.year.empty()){
        cerr << "Error: Birth date is not set!" << endl;
        return;
    }
    int daysRemaining = calculateDaysToBirthday(birthDate.day, birthDate.month, birthDate.year); 
    cout << "There are " << daysRemaining << " days left until your birthday." << endl;
}