#include <iostream>
#include <queue>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "clob.h"

using namespace std;

//Defining codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

struct buy_order 
{
    int bid;
    int size;
    time_t time;
    
    //Overloading the < operator for the priority queue to work
    bool operator<(const buy_order& other) const 
    {
        return bid < other.bid;
    }
    //Overloading the == for the remove to work
    bool operator==(const buy_order& other) const {
    return bid == other.bid && size == other.size && time == other.time;
}
};

struct sell_order 
{
    int ask;
    int size;
    time_t time;

    //Overloading the < operator for the priority queue to work
    bool operator<(const sell_order& other) const 
    {
        return ask < other.ask;
    }
    //Overloading the == for the remove to work
    bool operator==(const sell_order& other) const {
    return ask == other.ask && size == other.size && time == other.time;
}
};

struct match
{
    buy_order buy;
    sell_order sell;
    time_t time;
};

void clearScreen() {
#ifdef _WIN32 // Check if compiling on Windows
    system("cls");
#else // Assume Unix-based system
    system("clear");
#endif
}

buy_order generate_new_buy()
{
    time_t timestamp;
    time(&timestamp);
    buy_order order{rand()%50+50, rand()%1000+1000, timestamp};
    return order;
}

sell_order generate_new_sell()
{
    time_t timestamp;
    time(&timestamp);
    sell_order order{rand()%50+50, rand()%100+1000, timestamp};
    return order;
}

match generate_new_match(buy_order b, sell_order s)
{
    time_t timestamp;
    time(&timestamp);
    match order{b, s, timestamp};
    return order;
};

void print_clob_table (vector<buy_order>& orders_buy, vector<sell_order>& orders_sell, vector<match>& matches)
{
    struct
    {
        bool operator()(const buy_order l, const buy_order r) const 
        { 
            bool a;
            if (l.bid == r.bid)
            {
                return l.time > r.time;
            }
            else
            {
                return l.bid > r.bid;
            }
        }
    } customBuyOrder;
    priority_queue cpq_buy(orders_buy.begin(), orders_buy.end(), customBuyOrder);

    struct
    {
        bool operator()(const sell_order l, const sell_order r) const 
        { 
            bool a;
            if (l.ask == r.ask)
            {
                return l.time > r.time;
            }
            else
            {
                return l.ask > r.ask;
            }
        }
    } customSellOrder;
    priority_queue cpq_sell(orders_sell.begin(), orders_sell.end(), customSellOrder);

    struct
    {
        bool operator()(const match l, const match r) const 
        {
                return l.time < r.time;
        }
    } customMatch;
    priority_queue cpq_match(matches.begin(), matches.end(), customMatch);

    int i = 0;

    clearScreen();
    cout << MAGENTA << "\n\t\t\t\tCLOB\n" << RESET << endl;
    cout << GREEN << "  BUY ORDERS\t\t" << RESET << RED << " SELL ORDERS\t\t " << RESET << BLUE << "LATEST MATCHES\n" << RESET << GREEN << "Shares\tPrice\t\t" << RESET << RED << "Shares\tPrice\t\t" << RESET << BLUE << "Price\tDate/Time" << RESET <<endl;
    while (!cpq_buy.empty() && !cpq_sell.empty() && i<=20)
    {
        if(cpq_buy.top().bid == cpq_sell.top().ask)
        {
            match m = generate_new_match(cpq_buy.top(), cpq_sell.top());
            matches.push_back(m);
            cpq_match = priority_queue<match, vector<match>, decltype(customMatch)>(
                matches.begin(), matches.end(), customMatch
            );

            cout << GREEN << cpq_buy.top().size << "\t" << cpq_buy.top().bid << RESET << RED << "\t\t" << cpq_sell.top().size << "\t" << cpq_sell.top().ask << RESET << BLUE << "\t\t MATCH FOUND" << RESET;

            auto newEnd_buy = remove(orders_buy.begin(), orders_buy.end(), cpq_buy.top());
            orders_buy.erase(newEnd_buy, orders_buy.end());
            auto newEnd_sell = remove(orders_sell.begin(), orders_sell.end(), cpq_sell.top());
            orders_sell.erase(newEnd_sell, orders_sell.end());
            cpq_buy.pop();
            cpq_sell.pop();
            i = 100;
            continue;
        }
        if (cpq_match.empty())
        {
            cout << GREEN << cpq_buy.top().size << "\t" << cpq_buy.top().bid << RESET << RED << "\t\t" << cpq_sell.top().size << "\t" << cpq_sell.top().ask << RESET << endl;

        }
        else
        {
            cout << GREEN << cpq_buy.top().size << "\t" << cpq_buy.top().bid << RESET << RED << "\t\t" << cpq_sell.top().size << "\t" << cpq_sell.top().ask << RESET << BLUE << "\t\t" << cpq_match.top().buy.bid << "\t" << ctime(&cpq_match.top().time) << RESET;
            cpq_match.pop();
        }
        cpq_buy.pop();
        cpq_sell.pop();
        i++;
    }
}

int main()
{
    srand(time(NULL));
    vector<buy_order> orders_buy;
    vector<sell_order> orders_sell;
    vector<match> matches;
    orders_buy.push_back(generate_new_buy());
    orders_sell.push_back(generate_new_sell());

    bool running = true;

    while (running)
    {
        print_clob_table(orders_buy, orders_sell, matches);
        orders_buy.push_back(generate_new_buy());
        orders_sell.push_back(generate_new_sell());

        if (orders_buy.size() >= 100)
        {
            running = false;
        }
        usleep(500000);
    }

    return 0;
}