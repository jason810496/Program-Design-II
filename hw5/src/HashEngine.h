#ifndef _HASH_ENGINE_H_
#define _HASH_ENGINE_H_

#include "BaseEngine.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>


class HashEngine : public BaseEngine {
	private:
		std::unordered_multimap<std::string,int> db;
	public:
		HashEngine();
		~HashEngine();
		void insert(const int & id,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<int> & result);
};

#endif