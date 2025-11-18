# Documentation

## Introduction

In this evidence the challenge was to implement a pretty basic form of a continuous limit order book (CLOB) in C++, in the code it creates random buying and selling orders to simulate the actual trading look, and then it displays them in a real-time updating dashboard in the terminal.

Once started, the code will create this random orders (either buying or selling) and displays them in the dashboard, separating them with colors:
- Green: Buying orders
- Red: Selling orders
- Cyan: Matching orders

Once it starts, every half a second a new buying and selling order are created and displayed in the dashboard, once two orders are in the same row and have matching prices (Both bids and asks) they will be removed from the buying and selling orders tables and combine to make a matching order moving them into the matching orders tables.

This was achieved thanks to the use of queues, specifically priority queues, to display them in the tables in the correct order, this being the lower prices first and if more than one have the same price it will order them by longevity. Also for the same priority queues I had to do some overloading of certain operators to get it functioning on structures.

## Research on stocks exchange (CLOB)

The CLOB is a very important component in the modern world of financial markets, it acts as the central hub for buyers and sellers to interact and finalize trades. The CLOB is responsible for mantaining an organized and trasnparent record of all open buy and sell orders for a particular security, this record is continously updated in real time, providing all participants with essential information about the supply and demand dynamics of the market.

Each order in CLOB contains sepcific information, including the price at which the buyer or seller is willing to trade, the numberof shares they wish to trade, adn the time at wich the order was placed. This information is very important for traders and investors as it provides a clear picture of the market's current state and potential movements in the future.

The CLOB operates on a price-time priority basis, this means that orders are first ranked according to their price, with the best bid and ask orders given the highest priority. If multiple orders have the same price, they are then ranked according to their longevity, with earlier orders given priority over later ones.

By providing real-time information on the supply and demand dynamics of a security, the CLOB can also help traders and investors make informed desicions about their trading strategies. 

The CLOB is a fundamental component of modern financial markets, providing a transparent and efficient platformfor the execution of trades. By understanding the working of the CLOB, and make more informed trading desicions.

## Software Designed and Implementation

I designed the software by parts, and designing the base of the code first then focusing on the actual functionality and visual design of it. I first started to implement the structures of the orders, then I overloaded some operators to get the priority queues working with the structures. 

After that I finally started to try to make out the display of the CLOB, at first I started testing with printing the first structure of orders, then all of them, I implemented a while function to print all of the queue (up to 20 rows). Then inside the while function I implemented an if statement to make sure the proper orders into the mathcing orders structure and vector.

Finally I implemented the more visual elements, like using identation to make it seem like a table, implementing the different colors, aswell as making it auto update.

### Code Functions and elements

#### Color codes

These are the colors I used for the different tables in the terminal:

- Red
- Green
- Cyan
- Magenta
- Reset (Not a color but also defined here, it resets the color to the original)

#### struct buy_order

This is the structure used for all buy orders, these are the elements used in said structure:

- Bid: 
    - An integer to store the price willing to pay for.
- Size: 
    - An integer to store how many shares there are in the order.
- Time: 
    - A "time_t" variable that will be used to store the time the order was placed.
- bool operator<(const buy_order& other) const:
    - Overloads the "<" operator to make sure the priority queues work with the structure.
- bool operator==(const buy_order& other) const:
    - Overloads the "==" to make sure the future function "remove" works well for future implementations.

#### struct sell_order

This is the structure used for all sell orders, these are the elements used in said structure:

- Ask: 
    - An integer to store the price willing to get paid for.
- Size: 
    - An integer to store how many shares there are in the order.
- Time: 
    - A "time_t" variable that will be used to store the time the order was placed.
- bool operator<(const buy_order& other) const:
    - Overloads the "<" operator to make sure the priority queues work with the structure.
- bool operator==(const buy_order& other) const:
    - Overloads the "==" to make sure the future function "remove" works well for future implementations.

#### struct match