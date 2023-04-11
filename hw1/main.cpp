#include <iostream>
#include <string>
using namespace std;
int main(int argc, char** argv){
	int n=stoi(argv[1]);
	long long mx = 0;

	for(int i=0;i<=n;i++){
		printf("(%d,%d)\n",i,n-i);
		mx = max( mx , (long long)i * (long long)(n-i));
	}

	printf("%lld\n",mx);
	return 0;
}