#include <iostream>
#include <string> 
#include <cstdio>
#include <iomanip> 
#include <cctype> 
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

struct Month {
    unsigned short int name;  
    unsigned short int days;     
};

Month monthsData[12] = {
    {1, 31}, {2, 28}, {3, 31},
    {4, 30}, {5, 31}, {6, 30},
    {7, 31}, {8, 31}, {9, 30},
    {10, 31}, {11, 30}, {12, 31}
};

time_t getCurrentTime(short int day, short int month, short int year){
    tm timeStruct = {};
    timeStruct.tm_year = year - 1900;  
    timeStruct.tm_mon = month - 1;     
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;  
    timeStruct.tm_sec = 0;

    time_t secondsSinceEpoch = mktime(&timeStruct);

    if (secondsSinceEpoch == -1) {
        cerr << "Time conversion error!" << endl;
        return -1;
    }
    return secondsSinceEpoch; 
}

void formattedInput(){
    cout << "DATA ENTRY" << endl; 
    cout << setfill('-') << setw(15) << "" << endl;
}

void formattedOutput(string day, string month, string year, string name, string tel){
    string date = day + "." + month + "." + year;
    unsigned short int widthDataField = max(name.size(), tel.size()); 
    unsigned short int widthTitleField = 15;  
    cout << right << setfill('-') << setw(widthDataField + widthTitleField + 5) << "\n" << setfill(' ');
    cout << "| " << left << setw(widthTitleField) << "Name:" << setw(widthDataField) << name << " |\n";
    cout << "| " << left << setw(widthTitleField) << "Telephone:" << setw(widthDataField) << tel << " |\n";
    cout << "| " << left << setw(widthTitleField) << "Birth date:" << setw(widthDataField) << date << " |\n";
    cout << setfill('-') << setw(widthDataField + widthTitleField + 4) << "" << endl;
}

bool isNumber(string checkstr){
    for (char s: checkstr){
        if (!isdigit(s)){
            cout << "You did not enter a number!!!" << endl; 
            return false;
        }
    }
    if (checkstr.empty()){
        cout << "You didn't enter anything!!!" << endl; 
        return false;
    };
    return true; 
}

bool isString(string checkstr){
    for (char s: checkstr){
        if (isdigit(s)){
            cout << "You did not enter a letter!!!" << endl; 
            return false;
        }
    }
    if (checkstr.empty()){
        cout << "You didn't enter anything!!!" << endl; 
        return false;
    };
    return true; 
}

int getDaysMonth(int month, int year){
    if (month != 2){
        return monthsData[month - 1].days; 
    }
    if (year % 4 == 0 & year % 100 != 0){
        return monthsData[month - 1].days + 1; 
    }
    return monthsData[month - 1].days; 
}

bool checkInputDay(string day, string month, string year){
    if (!isNumber(day) || !isNumber(year) || !isNumber(month)) return false;
    short int intday = stoi(day), intyear = stoi(year), intmonth = stoi(month); 
    if (intday < 0 || intday > 31){
        cout << "You entered a day that doesn't exist" << endl; 
        return false; 
    }
    return true; 
}

bool checkInputMonth(string month){
    if (!isNumber(month)) return false;
    const short int intmonth = stoi(month); 
    if (intmonth < 0 || intmonth > 12){
        cout << "You entered a month that doesn't exist" << endl; 
        return false; 
    }
    return true; 
}

bool checkInputYear(string year){
    return isNumber(year);
}

bool checkInputName(string name){
    return (isString(name)); 
}

bool checkInputTel(string &tel){
    if (tel[0] == '+'){
        tel.erase(0, 1); 
    }
    if (!isNumber(tel)) return false;
    tel = '+' + tel; 
    return true; 
}

vector<string> birthdateFormatting(string birthdate){
    string itemsCurrent;
    vector<string> resultBirthdate; 
    for (char c: birthdate){
        if (c == '/' || c == '.' || c == ' '){
            resultBirthdate.push_back(itemsCurrent); 
            itemsCurrent = ""; 
        }
        else{
            itemsCurrent = itemsCurrent + c; 
        }
    }
    resultBirthdate.push_back(itemsCurrent); 
    return resultBirthdate;
}

int calculateDaysToBirthday(string day, string month, string year){
    time_t currentTime = time(0); 
    tm *localTime = localtime(&currentTime);
    short int currentYear = localTime->tm_year + 1900, intday = stoi(day), intmonth = stoi(month);
    time_t expectedDateOfBirth = getCurrentTime(intday, intmonth, currentYear);

    if (currentTime > expectedDateOfBirth){
        expectedDateOfBirth = getCurrentTime(intday, intmonth, currentYear + 1);
    }

    time_t resultingDateDifferenceTime = expectedDateOfBirth - currentTime; 
    int daysRemaining = resultingDateDifferenceTime / (60 * 60 * 24);

    return daysRemaining; 
}

string fileReading(const string& fileName){
    ifstream file(fileName);
    if (!file.is_open()){
        cerr << "Error opening file for reading!" << endl;
        return "";
    }
    string dataAllPerson;
    string line;
    while (getline(file, line)){
        dataAllPerson += line + " ";
    }
    file.close();
    return dataAllPerson;
}

vector<string> readyFileData(string dataAllPerson){
    vector<string> readyDataBase; 
    string temp; 
    for (int i = 0; i < dataAllPerson.size(); i++){
        if (dataAllPerson[i] == ' '){
            if (!temp.empty()){
                readyDataBase.push_back(temp);
                temp = "";
            }
        }
        else{
            temp += dataAllPerson[i];
        }
    }
    if (!temp.empty()){  
        readyDataBase.push_back(temp);
    }
    return readyDataBase;
}
