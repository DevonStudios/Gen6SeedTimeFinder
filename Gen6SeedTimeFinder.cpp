#include<iostream>
#include<sstream>
#include<fstream>
#include <iomanip>

using namespace std;

int days, hours, minutes, seconds, year, month, day, hour, minute, second;
int substraction = 1;
bool repeat_digit = false;
int months_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void is_hex(string hex) {
    for (int i = 0; i < hex.length(); i++) {
        if (!isxdigit(hex[i])) {
            repeat_digit = true;
            return;
        }
    }

    repeat_digit = false;
}

void is_dec(string dec) {
    for (int i = 0; i < dec.length(); i++) {
        if (!isdigit(dec[i])) {
            repeat_digit = true;
            return;
        }
    }

    repeat_digit = false;
}

void time_modify() {
    second += substraction;

    if (second < 0 || second == 60) {
        minute += substraction;
        second -= 60 * substraction;
    }

    if (minute < 0 || minute == 60) {
        hour += substraction;
        minute -= 60 * substraction;
    }

    if (hour < 0 || hour == 24) {
        day += substraction;
        hour -= 24 * substraction;
    }

    if (day < 1 || day > months_days[month - 1]) {
        month += substraction;

        if (month < 1) {
            day = 31;
        }
        else if (month > 12) {
            day = 1;
        }
        else {
            day = months_days[month - 1];
        }
    }

    if (month < 1 || month > 12) {
        year += substraction;
        month -= 12 * substraction;
    }
}

void time_difference() {
    seconds++;

    if (seconds == 60) {
        minutes++;
        seconds = 0;
    }

    if (minutes == 60) {
        hours++;
        minutes = 0;
    }

    if (hours == 24) {
        days++;
        hours  = 0;
    }
}

int main() {
    char answer = 'y';
    unsigned long long initial, new_initial, save_parameter, new_save_parameter, base_time, target, difference;
    int frame, log_year, log_month, log_day, log_hour, log_minute, log_second;
    string input;

    while (answer == 'y' || answer == 'Y') {
        days = 0;
        hours = 0;
        minutes = 0;
        seconds = 0;

        cout << "(Base Time calculation)" << endl;

        do {
            cout << "Insert your Frame: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> frame;
            }
        }
        while (repeat_digit == true);

        do {
            cout << "Insert your current Initial Seed: ";
            cin >> input;
            is_hex(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::hex >> initial;
            }
        }
        while (repeat_digit == true);

        do {
            cout << "Insert your current Save Parameter: ";
            cin >> input;
            is_hex(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::hex >> save_parameter;
            }
        }
        while (repeat_digit == true);

        base_time = (initial - save_parameter) & 0xFFFFFFFF;

        std::cout << "Base Time: " << uppercase << std::hex << base_time << endl << endl;

        cout << "(RTC calculation)" << endl;

        do {
            cout << "Insert your new Save Parameter: ";
            cin >> input;
            is_hex(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::hex >> new_save_parameter;
            }
        }
        while (repeat_digit == true);

        new_initial = (base_time + new_save_parameter) & 0xFFFFFFFF;

        do {
            cout << "Insert your Target Seed: ";
            cin >> input;
            is_hex(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::hex >> target;
            }
        }
        while (repeat_digit == true);

        do {
            cout << "Current Citra RTC year: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> year;
                log_year = year;
            }
        }
        while (repeat_digit == true || year < 2000 || year > 2999);

        if ((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
            months_days[1] = 29;
        }
        else {
            months_days[1] = 28;
        }

        do {
            cout << "Current Citra RTC months: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> month;
                log_month = month;
            }
        }
        while (repeat_digit == true || month < 1 || month > 12);

        do {
            cout << "Current Citra RTC days: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> day;
                log_day = day;
            }
        }
        while (repeat_digit == true || day < 1 || day > months_days[month - 1]);

        do {
            cout << "Current Citra RTC hours: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> hour;
                log_hour = hour;
            }
        }
        while (repeat_digit == true || hour < 0 || hour > 23);

        do {
            cout << "Current Citra RTC minutes: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> minute;
                log_minute = minute;
            }
        }
        while (repeat_digit == true || minute < 0 || minute > 59);

        do {
            cout << "Current Citra RTC seconds: ";
            cin >> input;
            is_dec(input);

            if (repeat_digit == false) {
                stringstream ss;
                ss << input;
                ss >> std::dec >> second;
                log_second = second;
            }
        }
        while (repeat_digit == true || second < 0 || second > 59);

        if (target > new_initial) {
            difference = target - new_initial;
            substraction = 1;
        }
        else {
            difference = new_initial - target;
            substraction = -1;
        }

        while (difference >= 1000) {
            time_difference();
            time_modify();
            difference -= 1000;
        }

        cout << endl;

        if (target > new_initial) {
            cout << "+ ";
        }
        else {
            cout << "- ";
        }

        std::cout << std::dec << days << "d " << hours << "h : " << minutes << "m : " << seconds << "s" << endl << endl;
        std::cout << std::dec << "RTC: " << year << "-";
        std::cout << std::setfill('0') << std::setw(2) << month << "-";
        std::cout << std::setfill('0') << std::setw(2) << day << "T";
        std::cout << std::setfill('0') << std::setw(2) << hour << ":";
        std::cout << std::setfill('0') << std::setw(2) << minute << ":";
        std::cout << std::setfill('0') << std::setw(2) << second << endl << endl;
        std::cout << std::dec << "Frame: " << frame << endl << endl;

        cout << "Write results in log file? Y/N: ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            ofstream output;
            output.open("log.txt", std::ios::app);

            output << "(Base Time calculation)" << endl;
            output << "Insert your Frame: " << std::dec << frame << endl;
            output << "Insert your actual Initial Seed: " << uppercase << std::hex << initial << endl;
            output << "Insert your actual Save Parameter: " << uppercase << std::hex << save_parameter << endl;
            output << "Base Time: " << uppercase << std::hex << base_time << endl << endl;
            output << "(RTC + Frame calculation)" << endl;
            output << "Insert your new Save Parameter: " << uppercase << std::hex << new_save_parameter << endl;
            output << "Insert your Target Seed: " << uppercase << std::hex << target << endl;
            output << "Current Citra RTC year: " << std::dec << log_year << endl;
            output << "Current Citra RTC months: " << std::setfill('0') << std::setw(2) << log_month << endl;
            output << "Current Citra RTC days: " << std::setfill('0') << std::setw(2) << std::dec << log_day << endl;
            output << "Current Citra RTC hours: " << std::setfill('0') << std::setw(2) << std::dec << log_hour << endl;
            output << "Current Citra RTC minutes: " << std::setfill('0') << std::setw(2) << std::dec << log_minute << endl;
            output << "Current Citra RTC seconds: " << std::setfill('0') << std::setw(2) << std::dec << log_second << endl << endl;

            if (target > new_initial) {
                output << "+ ";
            }
            else {
                output << "- ";
            }

            output << std::dec << days << "d " << hours << "h : " << minutes << "m : " << seconds << "s" << endl << endl;
            output << std::dec << "RTC: " << year << "-";
            output << std::setfill('0') << std::setw(2) << month << "-";
            output << std::setfill('0') << std::setw(2) << day << "T";
            output << std::setfill('0') << std::setw(2) << hour << ":";
            output << std::setfill('0') << std::setw(2) << minute << ":";
            output << std::setfill('0') << std::setw(2) << second << endl << endl;
            output << std::dec << "Frame: " << frame << endl << endl;
            output << "-----------------------------------------------" << endl << endl;
        }

        cout << "Continue? Y/N: ";
        cin >> answer;
        cout << endl;
    }
}
