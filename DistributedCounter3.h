//#ifndef distributed_counter_h
//#  define distributed_counter_h
//// add padding to avoid false sharing
//#include<mutex>
//#include<shared_mutex>
//#include<map>
//#include<numeric>
//#include<utility>
//#include<vector>
//namespace mpcs {
//	class distributedcounter {
//		typedef size_t value_type;
//
//		struct bucket {
//			std::shared_mutex sm;
//			value_type count;
//			char padding[256];
//		};
//		static size_t const buckets{ 128 };
//		std::vector<bucket> counts{ buckets };
//	public:
//
//		void operator++() {
//			size_t index = std::hash<std::thread::id>()(std::this_thread::get_id()) % buckets;
//			std::unique_lock ul(counts[index].sm);
//			counts[index].count++;
//		}
//		void operator++(int) {
//			++* this;
//		}
//
//		value_type get() {
//			return std::accumulate(counts.begin(), counts.end(), (value_type)0,
//				[](auto acc, auto& x) { std::shared_lock sl(x.sm); return acc + x.count; });
//		}
//	};
//}
//#endif