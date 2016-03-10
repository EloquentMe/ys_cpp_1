#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int monthsSizes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string weekDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

bool isLeapYear(int);

int main()
{
    int intDay, intMonth, intYear;
    scanf("%d.%d.%d", &intDay, &intMonth, &intYear);
    if (intDay < 1)
    {
        cout << "Insufficient day: " << intDay << endl;
        return -1;
    }
    if (intMonth < 1 || intMonth > 12)
    {
        cout << "Insufficient month: " << intMonth << endl;
        return -1;
    }
    if (intYear < 1)
    {
        cout << "Insufficient year: " << intYear << endl;
        return -1;
    }
    if (intMonth == 2)
    {
        if (isLeapYear(intYear))
        {
            if (intDay > 29)
            {
                cout << "Insufficient day in month." << endl;
                return -1;
            }
        }
        else
        {
            if (intDay > 28)
            {
                cout << "Insufficient day in month." << endl;
                return -1;
            }
        }
    }
    else
    {
        if (intDay > monthsSizes[intMonth - 1])
        {
            cout << "Insufficient day in month." << endl;
            return -1;
        }
    }
    int intCentury = intYear / 100;
    int dayOfWeek = (intDay += intMonth < 3 ? intYear-- : intYear -2,23 * intMonth / 9 + intDay + 4 + intYear / 4 - intYear/100 + intYear/400 - 1) % 7;
    cout << weekDays[dayOfWeek] << endl;
    return 0;
}

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

