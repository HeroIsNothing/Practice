target	:= 0101_sales_item
cc	:= g++

$(target) : 0101_sales_item.o 0101_book_store.o
	@$(cc) -o $@ $^
0101_sales_item.o : 0101_sales_item.cpp 0101_sales_item.h
	@$(cc) -c $<
0101_book_store.o : 0101_book_store.cpp 0101_sales_item.h
	@$(cc) -c $<

.PHONY:clean
clean:
	@rm -f *.o
	@rm -f $(target)

