#ifndef SALES_ITEMS_H_20181025
#define SALES_ITEMS_H_20181025

#include <string>
using std::string;

#include <iostream>
using std::istream;
using std::ostream;

class Sales_item
{
public:
	Sales_item();
	Sales_item(const Sales_item &rhs);

	friend istream& operator>>(istream &is, Sales_item &item);
	friend ostream& operator<<(ostream &os, const Sales_item &item);

	Sales_item& operator+=(const Sales_item &rhs);
	bool operator==(const Sales_item &rhs);
private:
	string m_isbn;
	int	   m_cnt;
	double m_price;
	double m_sum;
};


#endif

