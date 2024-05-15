#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::sort
#include <cmath>
using namespace std;

struct Date
{
    int day, month, year;
    string meaning;

    bool isValidDate() const
    {
        if (month == 2 && day > 28)
        {
            return false;
        }
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
            return false;
        }
        else if (day > 31)
        {
            return false;
        }
        else if (month > 12)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void newDate(int d, int m, int y, const string& meaning)
    {
        day = d;
        month = m;
        year = y;
        this->meaning = meaning;
    }

    int getDayOfWeek() const
    {
        // Zeller's Congruence algorithm
        int m = month;
        int y = year;
        if (m < 3)
        {
            m += 12;
            y--;
        }
        int h = (day + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
        return (h + 5) % 7 + 1; // Convert to 1-indexed day of week (1 = Sunday, 2 = Monday, ..., 7 = Saturday)
    }

    int calculateDifference(const Date &date) const
    {
        // Convert both dates into days since a reference date (e.g., January 1, 0 AD)
        int thisDays = day + 31 * (month - 1) + 365 * year + year / 4 - year / 100 + year / 400;
        int otherDays = date.day + 31 * (date.month - 1) + 365 * date.year + date.year / 4 - date.year / 100 + date.year / 400;
        // Return the absolute difference between the two dates
        return abs(thisDays - otherDays);
    }

    void printDate() const
    {
        string monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        cout << monthNames[month - 1] << " " << day << ", " << year << ": " << meaning << endl;
    }

    bool operator<(const Date &other) const
    {
        if (year < other.year)
            return true;
        if (year > other.year)
            return false;
        if (month < other.month)
            return true;
        if (month > other.month)
            return false;
        return day < other.day;
    }
};


bool sortByDate(const Date &a, const Date &b)
{
    return a < b;
}

void printMenu()
{
    cout << "Main Menu:\n";
    cout << "1. Add Date\n";
    cout << "2. Print Dates\n";
    cout << "3. Compare Dates\n";
    cout << "4. Calculate Difference\n";
    cout << "5. Get Day of the Week\n";
    cout << "6. Sort Dates\n"; 
    cout << "7. Exit\n";
    
}

int main()
{
    vector<Date> dates;

    int choice;
    do
    {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int d, m, y;
            string meaning;
            cout << "Enter date (day month year): ";
            cin >> d >> m >> y;
            cout << "Enter the meaning of the date: ";
            cin.ignore(); // Ignore newline character
            getline(cin, meaning);
            Date date;
            date.newDate(d, m, y, meaning);
            if (date.isValidDate())
            {
                dates.push_back(date);
                cout << "Date added successfully." << endl;
            }
            else
            {
                cout << "Invalid date entered. Ignoring..." << endl;
            }
            break;
        }
        case 2:
        {
            cout << "Dates:\n";
            for (const auto &date : dates)
            {
                date.printDate();
            }
            break;
        }
        case 3:
        {
            int index1, index2;
            cout << "Enter the indices of two dates to compare: ";
            cin >> index1 >> index2;

            if (index1 < 0 || index1 >= dates.size() || index2 < 0 || index2 >= dates.size())
            {
                cout << "Invalid indices entered." << endl;
            }
            else
            {
                Date date1 = dates[index1];
                Date date2 = dates[index2];
                if (date1 < date2)
                    cout << "First date is earlier than the second date." << endl;
                else if (date2 < date1)
                    cout << "Second date is earlier than the first date." << endl;
                else
                    cout << "Both dates are the same." << endl;
            }
            break;
        }
        case 4:
        {
            int index1, index2;
            cout << "Enter the indices of two dates to calculate difference: ";
            cin >> index1 >> index2;

            if (index1 < 0 || index1 >= dates.size() || index2 < 0 || index2 >= dates.size())
            {
                cout << "Invalid indices entered." << endl;
            }
            else
            {
                Date date1 = dates[index1];
                Date date2 = dates[index2];
                cout << "Difference in days between the two dates: " << date1.calculateDifference(date2) << endl;
            }
            break;
        }
        case 5:
        {
            int index;
            cout << "Enter the index of the date to get the day of the week: ";
            cin >> index;

            if (index < 0 || index >= dates.size())
            {
                cout << "Invalid index entered." << endl;
            }
            else
            {
                Date date = dates[index];
                int dayOfWeek = date.getDayOfWeek();
                string dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                cout << "Day of the week: " << dayNames[dayOfWeek - 1] << endl;
            }
            break;
        }
        case 6: 
        {
            sort(dates.begin(), dates.end(), sortByDate);
            cout << "Dates sorted in chronological order." << endl;
            break;
        }
        case 7:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}
