#include "HashEngine.h"

HashEngine::HashEngine(){
}

HashEngine::~HashEngine(){
}

void HashEngine::insert(const int & id,const std::string & word){
    db.insert(std::pair<std::string,int>(word,id));
}

bool HashEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    int k = search.size();
    std::map<int,int> bucket;
    for(const auto & word : search){
        auto range = db.equal_range(word);
        int lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            if( it->second == lastId ){
                continue;
            }
            bucket[it->second]++;
            lastId = it->second;
        }
    }

    for(const auto & p : bucket){
        if(p.second == k){
            result.push_back(p.first);
        }
    }
    
    if(result.empty() ){
        result.push_back(-1);
        return false;
    }

    return true;
}

