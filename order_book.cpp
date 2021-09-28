#include "order_book.h"

#include <algorithm>

OrderBook::OrderBook()
{

}

void OrderBook::initOrderBook(std::vector<Order> order_book_dump)
{
    clear();
    std::sort(order_book_dump.begin(),
              order_book_dump.end(),
              [](Order ord1, Order ord2){return (ord1.price < ord2.price);});
    for (auto it = order_book_dump.begin(); it != order_book_dump.end(); ++it){
        if (it->type == Order::BID){
            updateBidBook(*it);
        }
    }
    for (auto it = order_book_dump.rbegin(); it != order_book_dump.rend(); ++it){
        if (it->type == Order::ASK){
            updateAskBook(*it);
        }
    }
}

std::vector<Order> OrderBook::dumpOrderBook()
{
    std::vector<Order> order_book_dump;
    for (auto it = ask_book.rbegin(); it != ask_book.rend(); ++it){
        order_book_dump.push_back(it->second);
    }
    for (auto it = bid_book.begin(); it != bid_book.end(); ++it){
        order_book_dump.push_back(it->second);
    }
    return order_book_dump;
}

void OrderBook::clear()
{
    bid_book.clear();
    ask_book.clear();
}

int OrderBook::updateOrderBook(Order order)
{

    if(order.type == Order::BID){
        updateBidBook(order);
    } else if (order.type == Order::ASK){
        updateAskBook(order);
    } else {
        return -1;
    }
    return 0;
}

int OrderBook::bestBid(int skipping_amount)
{
    int best_bid = -1;
    for(auto &bid: bid_book){
        skipping_amount -= bid.second.amount;
        if (skipping_amount < 0){
            best_bid = bid.first;
            break;
        }
    }
    return best_bid;
}

int OrderBook::bestAsk(int skipping_amount)
{
    int best_ask = -1;
    for(auto ask: ask_book){
        skipping_amount -= ask.second.amount;
        if (skipping_amount < 0){
            best_ask = ask.first;
            break;
        }
    }
    return best_ask;
}

void OrderBook::updateBidBook(Order order)
{
    if (bestAsk() < order.price){
        auto range = bid_book.equal_range(order.price);
        auto it = std::find_if(range.first, range.second,
                               [&order](std::pair<int,Order> item){return item.second.owner == order.owner;});
        if (it != range.second){
            // deleted order
            bid_book.erase(it);
        }
        if (order.amount > 0){
            // new oreder
            bid_book.emplace(order.price, order);
        }
    } else {
        int remaining_amount = order.amount;
        while (true) {
            if (ask_book.empty()){
                break;
            }
            auto it = ask_book.begin();
            if (it->first < order.price){
                break;
            }
            remaining_amount -= it->second.amount;
            if (remaining_amount < 0){
                // partial order execution
                it->second.amount = -remaining_amount;
                remaining_amount = 0;
                break;
            } else {
                // order execution
                ask_book.erase(it);
            }
        }
        order.amount = remaining_amount;
        if (order.amount > 0){
            // new oreder
            bid_book.emplace(order.price, order);
        }
    }
}

void OrderBook::updateAskBook(Order order)
{
    if (bestBid() > order.price || bestBid() == -1){
        auto range = ask_book.equal_range(order.price);
        auto it = std::find_if(range.first, range.second,
                               [&order](std::pair<int,Order> item){return item.second.owner == order.owner;});
        if (it != range.second){
            // delete order
            ask_book.erase(it);
        }
        if (order.amount > 0){
            // new oreder
            ask_book.emplace(order.price, order);
        }
    } else {
        int remaining_amount = order.amount;
        while (true) {
            if (bid_book.empty()){
                break;
            }
            auto it = bid_book.begin();
            if (it->first > order.price){
                break;
            }
            remaining_amount -= it->second.amount;
            if (remaining_amount < 0){
                // partial order execution
                it->second.amount = -remaining_amount;
                remaining_amount = 0;
                break;
            } else {
                // order execution
                bid_book.erase(it);
            }
        }
        order.amount = remaining_amount;
        if (order.amount > 0){
            // new oreder
            ask_book.emplace(order.price, order);
        }
    }
}
