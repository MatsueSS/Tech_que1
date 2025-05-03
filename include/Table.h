#ifndef _TABLE_H_
#define _TABLE_H_

//profit подсчитывает количество часов, далее в выводе это будет умножаться
//на коэффициент деньги/час

#include <iostream>

//контролирует часы:минуты
struct time_stamp{
    int hour;
    int minutes;

    friend std::istream& operator>>(std::istream&, time_stamp&);
    friend std::ostream& operator<<(std::ostream&, const time_stamp&);
};

class Table{
public:
    explicit Table(int = 0);

    void set_num_table(int); //задать номер стола
    int get_num_table() const; //вывести номер стола

    bool isFree() const; //проверка на то, что стол свободен
    void take_place(time_stamp); //сесть за стол
    void free_place(time_stamp); //освободить стол

    int get_profit() const; //вывод profit
    int get_active_time() const; //количество минут, которое был активен стол

private:
    int table;
    bool flag_free; //true - свободен
    time_stamp time;
    int profit; //выручка в условных единицах
    int active_time; //время пользованием

};

#endif //_TABLE_H_