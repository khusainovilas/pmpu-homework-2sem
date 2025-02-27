#ifndef PERSON_H 
#define PERSON_H

#include <iostream>
#include <string> 
#include "func.h"

using namespace std;

class Person{
    private:
        string fullName; 
        string telephone; 
        struct DateOfBirth{
            string day;
            string month;
            string year;
        };
        DateOfBirth birthDate;

    public:
        Person();
        void displayingPersonData() const;
        void inputDataFromConsole();
        void inputDataFromFile(const string& fileName); 
        static void nameCompare(const Person& person1, const Person& person2);
        static void birthDayCompare(const Person& person1, const Person& person2); 
        void daysUntilBirthday() const;
        string getName() const; 
        string getBirthDay() const; 
        string getBirthMonth() const; 
        string getBirthYear() const; 
    };

#endif