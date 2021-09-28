#include <iostream>
#include <string>
#include <vector>

#include "order_book.h"
#include "order.h"

using namespace std;

void print_dump(vector<Order> dump){
    for (auto it = dump.rbegin(); it != dump.rend(); it++){
        cout << it->price  << " " << it->owner << " " << (it->type == 0 ? "BID" : "ASK") << " " << it->amount  << endl;
    }
    cout << endl;
}

int main(){
    // Simple test of OrderBook
    OrderBook ob;

    // bestAsk bestBid test (-1, -1)
    cout << "best ask: " << ob.bestAsk() << ", best bid:" << ob.bestBid() << endl;
    cout << endl;

    // update test
    ob.updateOrderBook(Order(string("anonim3"), Order::ASK, 11, 105));
    ob.updateOrderBook(Order(string("anonim1"), Order::ASK, 14, 111));
    ob.updateOrderBook(Order(string("anonim2"), Order::ASK, 10, 99));
    ob.updateOrderBook(Order(string("anonim2"), Order::BID, 10, 130));
    ob.updateOrderBook(Order(string("anonim1"), Order::BID, 10, 131));
    ob.updateOrderBook(Order(string("anonim3"), Order::BID, 10, 120));
    ob.updateOrderBook(Order(string("anonim4"), Order::BID, 10, 120));

    print_dump(ob.dumpOrderBook());

    // bestAsk bestBid test (111 120)
    cout << "best ask: " << ob.bestAsk() << ", best bid:" << ob.bestBid() << endl;
    cout << endl;

    // bestAsk bestBid skepping amount test (105 130) , (-1 -1)
    cout << "best ask: " << ob.bestAsk(14) << ", best bid:" << ob.bestBid(25) << endl;
    cout << "best ask: " << ob.bestAsk(140) << ", best bid:" << ob.bestBid(130) << endl;
    cout << endl;

    // Testing order deletion

    ob.updateOrderBook(Order(string("anonim4"), Order::BID, 0, 120));
    ob.updateOrderBook(Order(string("anonim3"), Order::ASK, 0, 105));

    print_dump(ob.dumpOrderBook());


    // Testing order update

    ob.updateOrderBook(Order(string("anonim3"), Order::BID, 50, 120));
    ob.updateOrderBook(Order(string("anonim1"), Order::ASK, 50, 111));

    print_dump(ob.dumpOrderBook());

    // Buy test

    ob.updateOrderBook(Order(string("anonim5"), Order::ASK, 55, 130));

    print_dump(ob.dumpOrderBook());

    // Sell test

    ob.updateOrderBook(Order(string("anonim6"), Order::BID, 80, 105));

    print_dump(ob.dumpOrderBook());

    // init from dump test
    OrderBook od2;
    od2.initOrderBook(ob.dumpOrderBook());
    print_dump(od2.dumpOrderBook());

    return 0;
}
