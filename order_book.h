#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <vector>

#include "order.h"

class OrderBook{
public:
    OrderBook();

    void initOrderBook(std::vector<Order> order_book_dump);
    std::vector<Order> dumpOrderBook();
    void clear();

    int updateOrderBook(Order order);

    int bestBid(int skipping_amount = 0);
    int bestAsk(int skipping_amount = 0);
    
private:
    std::multimap<int,Order> bid_book;
    std::multimap<int,Order,std::greater<int>> ask_book;

    void updateBidBook(Order order);
    void updateAskBook(Order order);

};

#endif // ORDER_BOOK_H
