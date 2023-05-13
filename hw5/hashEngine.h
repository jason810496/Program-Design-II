#define HASH_ENGINE_INCLUDED
#ifdef HASH_ENGINE_INCLUDED

#include "BaseEngine.h"
#include <vector>
#include <string>
#include <unordered_map>

class HashEngine : public BaseEngine {
	private:
		std::unordered_multimap db;
	public:
		HashEngine();
		HashEngine(int reserverdSize);
		~HashEngine();
		void insert(const int & ithLine,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<std::string> & result);
};

#endif