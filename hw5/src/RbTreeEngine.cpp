#include "RbTreeEngine.h"

RbTreeEngine::RbTreeEngine(){
}

RbTreeEngine::~RbTreeEngine(){
}

void RbTreeEngine::insert(const int & ithLine,const std::string & word){
    db.insert(std::pair<std::string,int>(word,ithLine));
}

bool RbTreeEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    std::multimap<std::string,int>::iterator it;
    for(int i=0;i<search.size();i++){
        std::pair<std::multimap<std::string,int>::iterator,std::multimap<std::string,int>::iterator> ret;
        ret = db.equal_range(search[i]);
        for(it=ret.first;it!=ret.second;it++){
            result.push_back(it->second);
        }
    }
    
    if(result.empty() ){
        result.push_back(-1);
        return false;
    }

    return true;
}