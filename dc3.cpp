#include<thread>
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<iterator>
#include<mutex>
#include<shared_mutex>
#include<map>
#include<numeric>
#include<utility>

using namespace std;

class distributedcounter {
	typedef size_t value_type;

	struct bucket {
		std::shared_mutex sm;
		value_type count;
		char padding[256];
	};
	static size_t const buckets{ 128 };
	std::vector<bucket> counts{ buckets };
public:

	void operator++() {
		size_t index = std::hash<std::thread::id>()(std::this_thread::get_id()) % buckets;
		std::unique_lock ul(counts[index].sm);
		counts[index].count++;
		//cout << sizeof(counts[index])<<endl;
	}
	void operator++(int) {
		++* this;
	}

	value_type get() {
		return std::accumulate(counts.begin(), counts.end(), (value_type)0,
			[](auto acc, auto& x) { std::shared_lock sl(x.sm); return acc + x.count; });
	}
};

size_t const reps{ 100'000'000 };
size_t const threadCount{ 10 };

distributedcounter c;

void countALot()
{
    for (size_t s = 0; s < reps; s++)
        c++;
}

int main()
{
    vector<thread> threads;
    auto start = chrono::high_resolution_clock::now();
    for (size_t s = 0; s < threadCount; s++)
        threads.emplace_back(countALot);
    for (auto& thr : threads)
        thr.join();
    auto end = chrono::high_resolution_clock::now();
    cout << "Count is " << c.get() << endl;
    cout << "Elapsed time is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    return 0;
}