#include <iostream>
#include <stdexcept>

class Date {
private:
    int day, month, year;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) const {
        static const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return daysInMonth[month - 1];
    }

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year)) {
            throw std::invalid_argument("Invalid date");
        }
    }

    bool operator<(const Date& other) const {
        return (year < other.year) || (year == other.year && month < other.month) || (year == other.year && month == other.month && day < other.day);
    }

    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Date& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    Date& operator++() {
        if (day < daysInMonth(month, year)) {
            ++day;
        } else {
            day = 1;
            if (month < 12) {
                ++month;
            } else {
                month = 1;
                ++year;
            }
        }
        return *this;
    }

    Date operator+(int daysToAdd) const {
        Date result = *this;
        for (int i = 0; i < daysToAdd; ++i) {
            ++result;
        }
        return result;
    }

    int daysElapsedInYear() const {
        int days = 0;
        for (int m = 1; m < month; ++m) {
            days += daysInMonth(m, year);
        }
        days += day;
        return days;
    }

    operator int() const {
        return daysElapsedInYear();
    }

    void display() const {
        std::cout << day << "/" << month << "/" << year << std::endl;
    }
};

int main() {
    try {
        Date date1(28, 2, 2024); // Leap year test
        date1.display();

        Date date2(1, 3, 2024);
        std::cout << "date1 < date2: " << (date1 < date2) << std::endl;
        std::cout << "date1 == date2: " << (date1 == date2) << std::endl;

        ++date1;
        date1.display();

        Date date3 = date1 + 30;
        date3.display();

        int daysInYear = date3;
        std::cout << "Days elapsed in the year: " << daysInYear << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
