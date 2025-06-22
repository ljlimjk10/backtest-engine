#include <iostream>

#include "include/engine/data/BarFeed.h"
#include "include/engine/data/CsvBarSource.h"
#include "include/engine/data/DataLoader.h"
#include "libs/OrderBook/include/threadPool.h"
#include "libs/OrderBook/include/orderBookManager.h"

int main()
{
	ThreadPool threadPool;
	OrderBookManager orderBookMgr(threadPool);

	DataLoader barLoader("bar.csv");
	CsvBarSource csvBarSource(barLoader.begin(), barLoader.end());
	BarFeed<CsvBarSource> barFeed(std::move(csvBarSource));
	return 0;
}
