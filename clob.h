#ifndef CLOB_H
#define CLOB_H

#include <iostream>
#include <queue>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>

using namespace std;

//Defining codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\x1B[36m"
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

void clearScreen();
buy_order generate_new_buy();
sell_order generate_new_sell();
match generate_new_match(buy_order b, sell_order s);
void print_clob_table (vector<buy_order>& orders_buy, vector<sell_order>& orders_sell, vector<match>& matches, int spread);

#endif