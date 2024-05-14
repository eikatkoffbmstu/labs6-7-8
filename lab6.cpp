#include <stdexcept>

using namespace std;
class DateOutOfRange : public out_of_range {
private:
    int day;
    int month;
    int year;

public:
    DateOutOfRange(int d, int m, int y) : out_of_range("NO VAALID DATA"), day(d), month(m), year(y) {}

    void printInvalidDate() const {
        std::cout << "ERROR NO SUCH DATA: " << day << "/" << month << "/" << year << endl;
    }
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        if (isValidDate()!=True) {
            throw DateOutOfRange(d, m, y);
        }
    }

    bool isValidDate() const {
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        if (month == 2) {
            if (isLeapYear()) {
                return day <= 29;
            } else {
                return day <= 28;
            }
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return day <= 30;
        }
        return day <= 31;
    }

    bool isLeapYear() const {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                return year % 400 == 0;
            } else {
                return true;
            }
        }
        return false;
    }

    void printDate() const {
        cout << day << "/" << month << "/" << year << endl;
    }
};

int main() {
    try {
        Date date1(31, 12, 2023);
        date1.printDate();
        Date date2(29, 2, 2023);
    } catch (const DateOutOfRange& d) {
        std::cout << "ERROR" << std::endl;
        d.printInvalidDate();
    }
    return 0;
}
