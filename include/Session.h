#ifndef _SESSION_H_
#define _SESSION_H_

#include "Table.h"

#include <unordered_map>
#include <queue>
#include <fstream>

struct time_stamp;

class Session{
public:
    Session(const std::string& filename);

    void start_day(); //обрабатывает все записи за день

    ~Session(); //закрывает дескриптор файла

private:
    std::unordered_map<int, Table> tables; //конкретные столы
    std::unordered_map<std::string, int> customers; //пользователи
    std::queue<std::string> waiters; //очередь
    std::ifstream file; //дескриптор файла

    int mph; //коэффициент денег за час
    time_stamp start, end; //начало и конец рабочего лня

    void make_result(); //подводит общий итог
};

#endif //_SESSION_H_