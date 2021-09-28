#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order{
public:
    Order(std::string _owner, uint _type, uint _amount, uint _price);

    std::string owner;
    uint price;
    uint amount;
    uint type;
    
    enum OrderType {
        BID = 0,
        ASK = 1
    };

};

#endif // ORDER_H
