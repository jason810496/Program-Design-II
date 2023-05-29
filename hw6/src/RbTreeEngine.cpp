#include "RbTreeEngine.h"
#include<iostream>
#include<algorithm>

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
        int apperance = 0;

        int lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            if( it->second == lastId ){
                continue;
            }
            apperance++;
            lastId = it->second;
        }

        double idf = log10( (double)lineCount / (double)apperance );
        
        // std::cout<<"lineCount:"<<lineCount<<std::endl;
        // std::cout<<word<<' '<<cnt<<' '<<idf<<std::endl;
        lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            if( it->second == lastId ){
                continue;
            }
            id_idf_table[it->second]+= idf;
            lastId = it->second;
        }
    }

    int idx=0;
    std::vector<std::pair<int,double>> tmp((int)id_idf_table.size());
    for(const auto & id_idf : id_idf_table){
        tmp[idx++] = std::pair<int,double>(id_idf.first,id_idf.second);
    }
    std::sort(tmp.begin(),tmp.end(),[](const std::pair<int,double> & a,const std::pair<int,double> & b){
        return a.second == b.second ? a.first<b.first: a.second > b.second;
    });


    for(int i=0;i<tmp.size() && i<kTop;++i){
        if( std::abs(tmp[i].second) < 1e-6 ){
            break;
        }
        result.push_back(tmp[i].first);
    }

    while(result.size() < kTop){
        result.push_back(-1);
    }

    return true;
}