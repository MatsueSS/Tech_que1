#include "Table.h"
#include "Session.h"
#include "FileException.h"
#include "BadValueExcept.h"

#include <sstream>
#include <vector>
#include <algorithm>

Session::Session(const std::string& filename)
{
    file.open(filename);
    if(!file.is_open())
        throw FileException(filename);

    int count_table;
    char v;

    file >> count_table >> start >> end >> mph >> v;

    if(count_table <= 0)
        throw BadValueExcept("Count table isn't natural value");

    std::cout << start << '\n';
    tables.reserve(count_table);
    for(int i = 1; i <= count_table; i++)
        tables.emplace(i, Table(i));
}

void Session::start_day()
{
    std::string line;
    while(std::getline(file, line)){
        std::istringstream ss(line);
        std::string name;
        int id, num_table = 0;
        time_stamp time;
        ss >> time >> id >> name >> num_table;
        std::cout << time << ' ' << id << ' ' << name;
        if(num_table == 0)
            std::cout << '\n';
        else
            std::cout << ' ' << num_table << '\n';

        if(id == 1){
            if(time.hour < start.hour || (time.hour == start.hour && time.minutes < start.minutes))
                std::cout << time << " 13 NotOpenYet\n";
            else if(customers.find(name) != customers.end())
                std::cout << time << " 13 YouShallNotPass\n";
            else
                customers[name] = 0;
            continue;
        }

        if(id == 3){
            bool flag = false;
            for(auto it = tables.begin(); it != tables.end(); it++){
                if(it->second.isFree()){
                    flag = true;
                    break;
                }
            }
            if(flag){
                std::cout << time << " 13 ICanWaitNoLonger\n";
                continue;
            }

            if(waiters.size() >= tables.size()){
                std::cout << time << " 11 " << name << '\n';
                customers.erase(name);
            }
            else{
                waiters.push(name);
            }
        }

        if((id == 2 || id == 4) && customers.find(name) == customers.end()){
            std::cout << time << " 13 ClientUnknown\n";
            continue;
        }

        if(id == 4){
            tables[customers[name]].free_place(time);
            if(!waiters.empty()){
                customers[waiters.front()] = customers[name];
                tables[customers[name]].take_place(time);
                std::cout << time << " 12 " << waiters.front() << ' ' << customers[name] << '\n';
                waiters.pop();
            }
            customers.erase(name);
        }

        if(id == 2){
            if(!tables[num_table].isFree())
                std::cout << time << " 13 PlaceIsBusy\n";
            else{
                if(customers[name] != 0)
                    tables[customers[name]].free_place(time);
                customers[name] = num_table;
                tables[num_table].take_place(time);
            }
        }
    }
    make_result();
}

void Session::make_result()
{
    std::vector<std::string> all_clients;
    while(!waiters.empty()){
        waiters.pop();
    }

    for(auto it = customers.begin(); it != customers.end(); it++){
        all_clients.emplace_back(it->first);
        if(tables.find(it->second) != tables.end())
            tables[it->second].free_place(end);
    }

    std::sort(all_clients.begin(), all_clients.end());

    for(const auto& s : all_clients)
        std::cout << end << " 11 " << s << '\n';

    customers.clear();

    std::cout << end << '\n';

    for(auto it = tables.begin(); it != tables.end(); it++)
        std::cout << it->first << ' ' << it->second.get_profit()*mph << ' ' << time_stamp{it->second.get_active_time()/60, it->second.get_active_time()%60} << '\n';
}

Session::~Session()
{
    file.close();
}