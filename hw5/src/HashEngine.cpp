#include "HashEngine.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

HashEngine::HashEngine(){
}

HashEngine::~HashEngine(){
}

void HashEngine::insert(const int & ithLine,const std::string & word){
    db.insert(std::pair<std::string,int>(word,ithLine));
}

bool HashEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    std::unordered_multimap<std::string,int>::iterator it;
    for(int i=0;i<search.size();i++){
        std::pair<std::unordered_multimap<std::string,int>::iterator,std::unordered_multimap<std::string,int>::iterator> ret;
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

