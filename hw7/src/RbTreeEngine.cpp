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
    word_cnt_table[id]++;
}

bool RbTreeEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
    
    std::map<int,double> rank_table;
    std::map<int,int> term_freq_table;
    
    for(const auto & word : search){
        auto range = db.equal_range(word);
        int apperance = 0;

        int lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            term_freq_table[it->second]++;
            if( it->second == lastId ){
                continue;
            }
            apperance++;
            lastId = it->second;
        }

        double idf = log10( (double)lineCount / (double)apperance );

        // std::cout<<"word:"<<word<<std::endl;
        // std::cout<<"idf:"<<idf<<std::endl;
        
        // std::cout<<"lineCount:"<<lineCount<<std::endl;
        // std::cout<<word<<' '<<cnt<<' '<<idf<<std::endl;
        lastId = -1;
        for(auto it = range.first; it != range.second; ++it){
            if( it->second == lastId ){
                continue;
            }

            double new_tf =(double)term_freq_table[it->second]/(double)word_cnt_table[it->second];
            rank_table[it->second]+= idf * new_tf;

            // std::cout<<"id:"<<it->second<<std::endl;
            // std::cout<<"word cnt:"<<word_cnt_table[it->second]<<std::endl;
            // std::cout<<"tf:"<<term_freq_table[it->second]<<std::endl;
            // std::cout<<"new tf:"<<new_tf<<std::endl;
            // std::cout<<"idf:"<<idf<<std::endl;


            lastId = it->second;
        }
    }

    // std::cout<<"Term Frequency Table:\n";
    // for(const auto & id_freq : term_freq_table){
    //     std::cout<<id_freq.first<<' '<<id_freq.second<<'\n';
    // }
    // std::cout<<"Rank Table:\n";
    // for(const auto & id_rk : rank_table){
    //     std::cout<<id_rk.first<<' '<<id_rk.second<<'\n';
    // }

    int idx=0;
    std::vector<std::pair<int,double>> tmp((int)rank_table.size());
    for(const auto & id_rk : rank_table){
        tmp[idx++] = std::pair<int,double>(id_rk.first,id_rk.second);
    }
    std::sort(tmp.begin(),tmp.end(),[](const std::pair<int,double> & a,const std::pair<int,double> & b){
        return a.second == b.second ? a.first<b.first: a.second > b.second;
    });


    for(int i=0;i<tmp.size() && i<kTop;++i){
        // std::cout<<tmp[i].first<<' '<<tmp[i].second<<'\n';
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