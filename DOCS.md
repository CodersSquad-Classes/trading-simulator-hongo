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

---

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

---

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

---

#### struct match

This is a structure used for all matching orders, these are the elements used in said structure:

- Buy:
    - This stores a buy_order object that matched with a sell order.
- Sell:
    - This stores the previously sell_order stated that matched with the buy order.
- Time:
    - This stores a "time_t" variable that states at which time the match was made.

---

#### void clearScreen()

This function clears the screen every time the CLOB updates, readying it for the next printing.

---

#### buy_order generate_new_buy()

This function generates a new buy_order object with random values, adn the current timestamp, and returns it.

---

#### buy_order generate_new_sell()

This function generates a new sell_order object with random values, adn the current timestamp, and returns it.

---

#### match generate_new_match(buy_order b, sell_order s)

This function generates a new match object with the given buy_order and sell_order objects, and takes the current timestamp, and then returns the generated object.

---

#### void print_clob_table (vector<buy_order>& orders_buy, vector<sell_order>& orders_sell, vector<match>& matches, int spread)

This function prints the entire Central Limit Order Book (CLOB) in a structured format, showing buy orders, sell orders, and the latest matches aligned side-by-side. It also executes the matching logic whenever a buy and sell order satisfy the spread condition.

###### Priority Queues and Custom Comparators

Inside the function, three custom comparators are defined to properly order the elements in the priority queues:

- Buy Orders Comparator
  - Orders buy orders so that:
    - Higher bids appear first.
    - If bids are equal, older orders (lower timestamp) appear first.
  
- Sell Orders Comparator
  - Orders sell orders so that:
    - Lower asks appear first.
    - If asks are equal, older orders appear first.

- Match Comparator
  - Orders matches so that:
    - Most recent matches appear first.

These comparators initialize the following priority queues:
- `cpq_buy`
- `cpq_sell`
- `cpq_match`

###### Preparing the Display

Before printing the CLOB:

- `clearScreen()` is called to wipe the terminal so the updated book is printed cleanly.
- The function prints:
  - A magenta CLOB header
  - Green section for buy orders
  - Red section for sell orders
  - Cyan section for match information

The color codes ensure the table is visually easy to follow.

###### Main Processing Loop

The function enters a loop that prints up to 20 rows or terminates early if buy or sell queues empty.

Each iteration performs the following:

1. Match Evaluation

    The function checks whether the best buy and best sell orders satisfy the matching rules:

    - Compute  
    `difference = cpq_buy.top().bid - cpq_sell.top().ask`
    
    - A match occurs when:
    - `difference <= spread`
    - AND `difference >= 0`

    If a match is found:

    - `generate_new_match()` is called to create a match object.
    - The match is added to the `matches` vector.
    - The corresponding buy and sell orders are removed from:
    - `orders_buy`
    - `orders_sell`
    - Both priority queues
    - A line is printed showing `"MATCH FOUND"` in cyan.
    - The loop iteration is skipped using `continue`.

2. Normal Printing (No Match)

    If no match occurred:

    - The function prints:
    - Buy size and bid (green)
    - Sell size and ask (red)
    
    - If the match queue has entries:
    - Prints the latest match:
        - Sell ask price
        - Buy bid price
        - Match timestamp

After printing, the function pops one buy and one sell order from their priority queues.

###### Iteration Control

A counter ensures that no more than 20 rows of data are printed.  
The loop ends if:

- A match forces an early stop, or
- Either priority queue becomes empty.

This function ties together the display and the operational logic of the CLOB, ensuring that both the most recent state of the order book and the latest transaction matches are clearly presented each time it is called.

## Conclusions and Learnings

During this challenge I had the oportunity to learn the importance of the proper implementation of queues and priority queues in these order books, most importantly how essential it is to make the proper desicions and the right displays to assure the proper functionality of the CLOB.

I also got the chance to practice overloading operators again, it has been long since I overloaded operators properly and it was pretty fun to figure out that this was actually very useful in this scenario.

In the same boat I also learned a lot from the main focus of this challenge, the use of priority queues can be very varied and useful. The way priority queues can be used and customized is very helpful in a lot of ways, you can practically make anything a priority in any way, and the use in this challenge is a prove of that, thanks to this customization I could implement these with the use of unique structures.

I learned a lot from this challenge and I'm sure that all of these learnings will certainly be useful in my future projects and career.