#include <iostream>
#include <cstring>
using namespace std;

char* add_two_string(char *p, char *q)
{
	char *res=new char [601];
    int plen=0,qlen=0;
    plen=strlen(p);
    qlen=strlen(q);
//    while(p[plen]) plen++;
//    while(q[qlen]) qlen++;

    int i=0;
    int carry=0;
    while(i<max(plen,qlen)){
        if (i>=plen){
            if(q[i]-'0'+carry>9){
                carry=1;
                res[i]='0';
            } else{
                res[i]=q[i]+carry;
                carry=0;
            }
        }
        else if(i>=qlen){
            if(p[i]-'0'+carry>9){
                carry=1;
                res[i]='0';
            } else{
                res[i]=p[i]+carry;
                carry=0;
            }
        }
        else{
            int num=p[i]-'0'+q[i]-'0'+carry;
            if(num>9){
                res[i]=num%10+'0';
                carry=1;
            }
            else{
                res[i]=num+'0';
                carry=0;
            }
        }
        i++;
    }
    if(carry==1){
        res[i]='1';
        res[i+1]='\0';
    }
    else res[i]='\0';
    return res;
}

int main()
{
	int m, n;
	cin >> m >> n;
	char *p = new char[m];
	char *q = new char[n];
	cin >> p;
	cin >> q;

	char *res = add_two_string(p, q);
	cout << res << endl;

	delete[] p;
	delete[] q;
	delete[] res;

	return 0;
}