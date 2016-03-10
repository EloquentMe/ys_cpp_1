bool IsLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

int DayByDate(int day, int month, int year)
{
    int monthsSizes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1)
        return -1;
    if (month < 1 || month > 12)
        return -1;
    if (year < 1)
        return -1;
    if (month == 2)
    {
        if (IsLeapYear(year))
        {
            if (day > 29)
                return -1;
        }
        else
        {
            if (day > 28)
                return -1;
        }
    }
    else
    {
        if (day > monthsSizes[month - 1])
            return -1;
    }
    int dayOfWeek = (day += month < 3 ? year-- : year -2,23 * month / 9 + day + 4 + year / 4 - year/100 + year/400) % 7;
    return dayOfWeek;
}
