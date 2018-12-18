#include <iostream>
#include <string>
#include "0101_sales_item.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	Sales_item total;
	if (cin >> total)
	{
		Sales_item trans;
		while (cin >> trans)
		{
			if (total == trans)
				total += trans;
			else
			{
				cout << total << endl;
				total = trans;
			}
		}
		cout << total << endl;	// Print last book
	}

	return 0;
}