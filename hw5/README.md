# Search Engine

## Project Structure 
```
.
├── hw5
├── main.cpp
├── makefile
├── obj
│   ├── BaseEngine.o
│   ├── Constant.o
│   ├── HashEngine.o
│   ├── Parser.o
│   ├── RbTreeEngine.o
│   ├── SearchEngine.o
│   ├── TrieEngine.o
│   └── main.o
└── src
    ├── BaseEngine.h
    ├── Constant.h
    ├── HashEngine.cpp
    ├── HashEngine.h
    ├── Parser.cpp
    ├── Parser.h
    ├── RbTreeEngine.cpp
    ├── RbTreeEngine.h
    ├── SearchEngine.cpp
    ├── SearchEngine.h
    ├── TrieEngine.cpp
    └── TrieEngine.h
```

- Interface : 
    ```cpp
    class BaseEngine{
        protected:
            int lineCount;
        public:
            BaseEngine() = default;
            ~BaseEngine() = default;
            void setLineCount(const int & count){ lineCount = count; };
            virtual void insert(const int & id,const std::string & word){};
            virtual bool search(const std::vector<std::string> & search , std::vector<int> & result){};
    };
    ```
    - `BaseEngine.h` is an interface for all type of search engine .
    - methods : 
        - `void insert(const int & id,const std::string & word){};`
        - `bool search(const std::vector<std::string> & search , std::vector<int> & result){};`
- Implementation : 
    - `HashEngine.h` : implement engine in `Hash Map`
    - `RbTreeEngine.h` : implement engine in `Red-Black Tree`
    - `TrieEngine.h` : implement engine in `Trie`
- `Parser` Class : 
    ```cpp
    class Parser{
        private:
            std::stringstream pars;
            std::fstream ifs;
        public:
            Parser();
            ~Parser();
            std::string trim(const std::string & str);
            void readCorpus(const std::string & filename);
            void readCorpus(const std::string & filename, BaseEngine* engine);
            void answerQuery(const std::string & filename, BaseEngine* engine);
    };
    ```
    - `std::string trim(const std::string & str)`
        - trim string helper function 
    - `void readCorpus(const std::string & filename, BaseEngine* engine);`
        - insert word list in to `engine` by `engine->insert(id,word)`
    - `void answerQuery(const std::string & filename, BaseEngine* engine);`
        - get serach result from `engine->(search,result)`
- `SearchEngine` Class : 
    ```cpp
    class SearchEngine{
        private:
            Parser parser;
            std::string type;
            BaseEngine* engine;
            int lineCount;
        public:
            SearchEngine(const std::string & engineType);
            ~SearchEngine();
            void readCorpus(const std::string & filename);
            void answerQuery(const std::string & filename);
            void insert(const int & id,const std::string & word);
            bool search(const std::vector<std::string> & search , std::vector<int> & result);
    };
    ```
    - `BaseEngine *engine;`
        - the `engine` pointer will be allocate by constructor
    - `SearchEngine(const std::string & engineType)`;
        - the `engine` poiner is specified by `engineType`
        
        

## Note 

### multi file compile command
```
g++ -c main.cpp -o main.o # create object files
g++ -c SearchEngine.cpp -o SearchEngine.o
g++ -c TrieEngine.cpp -o TrieEngine.o
g++ -c HashEngine.cpp -o HashEngine.o
g++ main.o SearchEngine.o TrieEngine.o HashEngine.o -o main # link object files
```

### Interface in C++

Implement as `BaseEngine.h` in this project .

Interface : 
- main target : 
    - the `interface class` **pointer variable** can be allocate with `inherit class` pointer
    ```cpp
    InterfaceExample *base;
    base = new InheritOne();
    base = new InheritTwo("This is a inhert class constructor");
    ```
- pure virtual function 
    - the pure virtual function **must** be implemented by inherit class
- protected data 
    - just like private data , it would also be inherted

### How to include header in C++ multi-file project

- Include only`xxx.h` ( implement class in `xxx.cpp` but dont't include `xxx.cpp` )
- If implementation in `xxx.cpp` needs standard header ( `string` , `vector` ... ) include them in `xxx.h`

### Fix `redefinition` Bug

add the following marco in `xxx.h`
```cpp
#ifndef _XXX_H_
#define _XXX_H_
#endif
```

[ use marco to fix redefinition error (csdn)](https://blog.csdn.net/leowinbow/article/details/82884518)

### Makefile

[`Makefile` syntax by jserv ]( https://hackmd.io/@sysprog/SySTMXPvl)

[`Makefile` syntax](https://www.tutorialspoint.com/makefile/makefile_suffix_rules.htm)

[check `Makefile` syntax without executing](https://stackoverflow.com/questions/7728848/how-can-i-check-syntax-for-make-but-be-sure-i-am-not-executing)