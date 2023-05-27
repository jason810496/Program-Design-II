#include "RbTreeEngine.h"
#include<iostream>

RbTreeEngine::RbTreeEngine(const int & k){
    kTop = k;
}

RbTreeEngine::~RbTreeEngine(){
}

void RbTreeEngine::insert(const int & id,const std::string & word){
    db.insert(std::pair<std::string,int>(word,id));
}

bool RbTreeEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    
    std::map<int,double> id_idf_table;
    
    for(const auto & word : search){
        auto range = db.equal_range(word);
        double cnt = db.count(word);
        double idf = log10( (double)db.size() / (cnt) );

        int lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            if( it->second == lastId ){
                continue;
            }
            id_idf_table[it->second]+= idf;
            lastId = it->second;
        }
    }

    std::priority_queue<std::pair<double,int>> pq;
    for(const auto & id_idf : id_idf_table){
        pq.push(std::pair<double,int>(id_idf.second,id_idf.first));
        if( pq.size() > kTop ){
            pq.pop();
        }
    }

    while( !pq.empty() ){
        result.push_back(pq.top().second);
        pq.pop();
    }
    while( result.size() < kTop ){
        result.push_back(INT_MAX);
    }

    return true;
}