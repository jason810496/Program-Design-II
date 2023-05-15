#include "RbTreeEngine.h"

RbTreeEngine::RbTreeEngine(){
}

RbTreeEngine::~RbTreeEngine(){
}

void RbTreeEngine::insert(const int & id,const std::string & word){
    db.insert(std::pair<std::string,int>(word,id));
}

bool RbTreeEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    int k = search.size();
    std::unordered_map<int,int> bucket;
    for(const auto & word : search){
        auto range = db.equal_range(word);
        for(auto it = range.first; it != range.second; ++it){
            bucket[it->second]++;
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

    sort(result.begin(),result.end());
    return true;
}