#include "Table.h"

#include <iomanip>

Table::Table(int num_table) : table(num_table), flag_free(true), profit(0), active_time(0)
{ 
    time.hour = 0;
    time.minutes = 0;
}

void Table::set_num_table(int num_table)
{
    table = num_table;
}

int Table::get_num_table() const
{
    return table;
}

bool Table::isFree() const
{
    return flag_free;
}

void Table::free_place(time_stamp time_now)
{
    if(flag_free)
        return;
    
    profit += time_now.hour - time.hour;
    active_time += (time_now.hour*60+time_now.minutes - (time.hour*60+time.minutes));
    if(time_now.minutes > time.minutes)
        profit++;

    flag_free = true;
}

void Table::take_place(time_stamp time_now)
{
    if(!flag_free)
        return;

    flag_free = false;
    time = time_now;
}

int Table::get_profit() const
{
    return profit;
}

std::istream& operator>>(std::istream& is, time_stamp& obj)
{
    char val;
    is >> obj.hour >> val >> obj.minutes;
    return is;
}

std::ostream& operator<<(std::ostream& os, const time_stamp& obj)
{
    os << std::setfill('0') << std::setw(2) << obj.hour << ':' 
    << std::setfill('0') << std::setw(2) << obj.minutes;
    return os;
}

int Table::get_active_time() const
{
    return active_time;
}