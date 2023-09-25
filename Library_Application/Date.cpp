#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"

// Global variable (for testing purposes).
    bool test = false;
    int year = 2023;
    int mon = 12;
    int day = 25;

//////////Private function of Date Class//////////

/*Returns number of days passed since the date 0001 / 1 / 1.*/
int Date::daysSince0001_1_1()const {
    int ty = m_year;
    int tm = m_mon;
    if (tm < 3) {
        ty--;
        tm += 12;
    }
    return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
}

/*Validates the date setting the error code and then returns true, if valid, and false if invalid.*/
bool Date::validate() {
    //Set errCode to "0"
    errCode(NO_ERROR);

    //Condition for set the error code to its error type (Year, month or day)
    if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
        errCode(YEAR_ERROR);
    }
    else if (m_mon < 1 || m_mon > 12) {
        errCode(MON_ERROR);
    }
    else if (m_day < 1 || m_day > mDays()) {
        errCode(DAY_ERROR);
    }

    //Return Status of the validation.
    return !bad();
}

/*Sets the error code value.*/
void Date::errCode(int readErrorCode) {
    m_ErrorCode = readErrorCode;
}

/*Returns the current system year.*/
int Date::systemYear()const {
    int theYear = year;
    if (!test) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        theYear = lt.tm_year + 1900;
    }
    return theYear;
}

/*Returns true if the Date is in an erroneous state.*/
bool Date::bad()const {
    return m_ErrorCode != 0;
}

/*Returns the number of days in current month(the month stored in m_mon attribute)*/
int Date::mDays()const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
    mon--;
    return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
}

/*Sets the date to the current date(system date)*/
void Date::setToToday() {
    if (test) {
           m_day = day;
           m_mon = mon;
           m_year = year;
       }
       else {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           m_day = lt.tm_mday;
           m_mon = lt.tm_mon + 1;
           m_year = lt.tm_year + 1900;
       }
       errCode(NO_ERROR);
}

//////////Public function of Date Class//////////

/*Default Constructor. Creates a date with current date.*/
Date::Date() :m_CUR_YEAR(systemYear()) {
    setToToday();
}

/*Constructor. Creates a date with assigned values then validates the date and sets the error code accordingly.*/
Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
    m_year = year;
    m_mon = mon;
    m_day = day;
    validate();
}

/*Returns the error code or zero if date is valid.*/
int Date::errCode()const {
    return m_ErrorCode;
}

/*Returns a string stating the current status of the date.*/
const char* Date::dateStatus()const {
    return DATE_ERROR[errCode()];
}

/*Returns the m_CUR_YEAR attribute value.*/
int Date::currentYear()const {
    return m_CUR_YEAR;
}

/*This function reads a date from the console in the following format YYYY/MM/DD */
std::istream& Date::read(std::istream& is) {
    //Sets errCode to "0"
    errCode(NO_ERROR);

    //Gets input from user separated by non numeric character.
    is >> m_year;
    is.ignore();
    is >> m_mon;
    is.ignore();
    is >> m_day;

    //Condition to checks if the istream is valid.
    if (!is.fail()) {
        //Checks the valid format. If not valid, then sets errCode to its error type.
        if (!validate()) {
            errCode(m_ErrorCode);
        }
    }
    //If istream has failed, then set the error code to CIN_FAILED and clears the istream.
    else {
        errCode(CIN_FAILED);
        is.clear();
        is.ignore();
    }

    //Return the istream object.
    return is;
}

/*This function writes a date in the following format YYYY/MM/DD*/
std::ostream& Date::write(std::ostream& os)const {

    //If Date is in "bad" state, then print the date status.
    if (bad()) {
        os << dateStatus();
    }
    //If is valid, then print in the format.
    else {
        os << std::setw(4) << std::setfill('0') << m_year << '/'
            << std::setw(2) << std::setfill('0') << m_mon << '/'
            << std::setw(2) << std::setfill('0') << m_day;
    }
    return os;
}

/*Overload operator "==". Return true if two Date are equal.*/
bool Date::operator==(const Date& rhs) const {
    return daysSince0001_1_1() == rhs.daysSince0001_1_1();
}

/*Overload operator "!=". Return true if two Date are not equal.*/
bool Date::operator!=(const Date& rhs) const {
    return daysSince0001_1_1() != rhs.daysSince0001_1_1();
}

/*Overload operator ">=". Return true if first Date is more than or equal another Date.*/
bool Date::operator>=(const Date& rhs) const {
    return daysSince0001_1_1() >= rhs.daysSince0001_1_1();
}

/*Overload operator "<=". Return true if first Date is less than or equal another Date.*/
bool Date::operator<=(const Date& rhs) const {
    return daysSince0001_1_1() <= rhs.daysSince0001_1_1();
}

/*Overload operator ">". Return true if first Date is more than another Date.*/
bool Date::operator>(const Date& rhs) const {
    return daysSince0001_1_1() > rhs.daysSince0001_1_1();
}

/*Overload operator "<". Return true if first Date is less than another Date.*/
bool Date::operator<(const Date& rhs) const {
    return daysSince0001_1_1() < rhs.daysSince0001_1_1();
}

/*Overload operator "-". Returns the difference between two Dates in days.*/
int Date::operator-(const Date& rhs) const {
    int days1 = daysSince0001_1_1();
    int days2 = rhs.daysSince0001_1_1();

    return days1 - days2;
}

/*Overload operator boolean type. Return true if the date is valid and false if it is not.*/
Date::operator bool() const {
    return !bad();
}

//////////Helper Operator//////////
/*Overload helper operator "<<". This function will call write function.*/
std::ostream& operator<<(std::ostream& os, const Date& RO) {
    return RO.write(os);
}

/*Overload helper operator "<<". This function will call read function.*/
std::istream& operator>>(std::istream& is, Date& RO) {
    return RO.read(is);
}