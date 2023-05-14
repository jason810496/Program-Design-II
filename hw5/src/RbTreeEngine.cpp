#include "RbTreeEngine.h"

RbTreeEngine::RbTreeEngine(){
}

RbTreeEngine::~RbTreeEngine(){
}

void RbTreeEngine::insert(const int & ithLine,const std::string & word){
    db.insert(std::pair<std::string,int>(word,ithLine));
}

bool RbTreeEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    int k = search.size();
    std::vector<int> bucket(lineCount+1);
    for(const auto & word : search){
        auto range = db.equal_range(word);
        for(auto it = range.first; it != range.second; ++it){
            bucket[it->second]++;
        }
    }


    for(int i=1;i<=lineCount;i++){
        if(bucket[i] == k){
            result.push_back(i);
        }
    }
    
    
    if(result.empty() ){
        result.push_back(-1);
        return false;
    }

    return true;
}