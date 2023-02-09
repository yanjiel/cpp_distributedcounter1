//#include<thread>
//#include<iostream>
//#include<chrono>
//#include<vector>
//#include<algorithm>
//#include<iterator>
//#include<atomic>
//#include<mutex>
//#include<shared_mutex>
//#include<map>
//#include<numeric>
//#include<utility>
//using namespace std;
//
//
//class distributedcounter {
//public:
//	typedef long long value_type;
//private:
//	value_type count;
//	std::shared_mutex mutable mtx;
//	
//public:
//	distributedcounter() : count(0) {}
//	void operator++() {
//		std::unique_lock lock(mtx);
//		++count;
//	}
//	void operator++(int) {
//		std::unique_lock lock(mtx);
//		count++;
//	}
//	
//	value_type get() const {
//		std::shared_lock lock(mtx);
//		return count;
//	}
//};
//
//size_t const reps{ 100'000'000 };
//size_t const threadCount{ 10 };
//distributedcounter c;
//
//void countALot()
//{
//	for (size_t s = 0; s < reps; s++)
//		c++;
//}
//
//int main()
//{
//	vector<thread> threads;
//	auto start = chrono::high_resolution_clock::now();
//	for (size_t s = 0; s < threadCount; s++)
//		threads.emplace_back(countALot);
//	for (auto& thr : threads)
//		thr.join();
//	auto end = chrono::high_resolution_clock::now();
//	cout << "Count is " << c.get() << endl;
//	cout << "Elapsed time is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
//	return 0;
//}