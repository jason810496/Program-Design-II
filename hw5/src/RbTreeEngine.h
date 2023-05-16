#ifndef _RBTREE_ENGINE_H_
#define _RBTREE_ENGINE_H_

#include <map>
#include <string>
#include <vector>
#include <set>

#include "BaseEngine.h"

class RbTreeEngine : public BaseEngine{
	private:
		std::multimap<std::string,int> db;
	public:
		RbTreeEngine();
		~RbTreeEngine();
		void insert(const int & id,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<int> & result);
};

#endif