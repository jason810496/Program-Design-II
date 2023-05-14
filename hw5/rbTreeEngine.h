#define RBTREE_ENGINE_INCLUDED
#ifdef RBTREE_ENGINE_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "BaseEngine.h"

class RbTreeEngine : public BaseEngine{
	private:
		std::multimap<std::string,int> db;
	public:
		RbTreeEngine();
		~RbTreeEngine();
		void insert(const int & ithLine,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<std::string> & result);
};

#endif