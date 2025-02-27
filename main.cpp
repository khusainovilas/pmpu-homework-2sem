#include <iostream>
#include <string> 
#include "Person.h"

using namespace std;

int main() {
        
    Person person1, person2;
    person1.inputDataFromFile("123.txt");
    person1.displayingPersonData();
    person1.daysUntilBirthday();
        
    person2.inputDataFromConsole();
    person2.displayingPersonData();
    person2.daysUntilBirthday();

    Person::nameCompare(person1, person2);
    Person::birthDayCompare(person1, person2);
}
