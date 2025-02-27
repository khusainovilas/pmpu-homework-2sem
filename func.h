#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string> 
#include <iomanip> 
#include <ctime>
#include <vector>

using namespace std;

struct Month {
    unsigned short int name;  
    unsigned short int days;   
};
extern const Month monthsData[12];

void formattedOutput(string day, string month, string year, string name, string tel); 
bool isNumber(string checkstr); 
bool isString(string checkstr); 
int getDaysMonth(short int month, short int year); 
bool checkInputDay(string day, string year, string month); 
bool checkInputMonth(string month); 
bool checkInputYear(string year); 
bool checkInputName(string name); 
bool checkInputTel(string &tel); 
time_t getCurrentTime(short int day, short int month, short int year); 
int calculateDaysToBirthday(string day, string month, string year); 
vector<string> birthdateFormatting(string birthdate); 
void formattedInput(); 
vector<string> readyFileData(string dataAllPerson); 
string fileReading(const string& fileName); 

#endif 