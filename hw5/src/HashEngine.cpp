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

