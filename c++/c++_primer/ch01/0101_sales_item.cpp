#include "0101_sales_item.h"

Sales_item::Sales_item()
{
}

Sales_item::Sales_item(const Sales_item &rhs)
{
	m_isbn = rhs.m_isbn;
	m_cnt = rhs.m_cnt;
	m_price = rhs.m_price;
	m_sum = rhs.m_sum;
}

istream& operator>>(istream &is, Sales_item &item)
{
	is >> item.m_isbn >> item.m_cnt >> item.m_price;
	item.m_sum = item.m_cnt * item.m_price;

	return is;
}

ostream& operator<<(ostream &os, const Sales_item &item)
{
	os << item.m_isbn << ' ' << item.m_cnt << ' ' << item.m_sum 
		<< ' ' << item.m_price;

	return os;
}

Sales_item& Sales_item::operator+=(const Sales_item &rhs)
{
	m_cnt += rhs.m_cnt;
	m_sum += rhs.m_sum;
	m_price = m_sum / m_cnt;

	return *this;
}

bool Sales_item::operator==(const Sales_item &rhs)
{
	return m_isbn == rhs.m_isbn;
}