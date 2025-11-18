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

