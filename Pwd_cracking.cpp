#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long 
string InputIndex;
string InputBit;
string arr[40];
string index_string;
string result;
string name;
string value;
string res;
string ans;
string mang;
string r;
string sumbit;
string S="abcdefghijklmnopqrstuvwxyz012345";
int firstBit,secondBit;
int length;
int AmountCharacter;

queue<int> index_int;
unordered_map<string,string> Hash[60];
char Cout(string x);
int find(char x);
int makeEqualLength(string &str1, string &str2);
string addBitStrings( string first, string second );
string Bit(int n);
string CreateBit(string base);
string SumBit(string res);
string ReceateBit(string sum);
queue<int> StringToIndex(string index);
string CipherToPlain(queue<int> q);

void Print_Permutation(vector<vector<int> > v);
class Solution {
public:
   vector < vector <int> > res;
   void solve(int n, int k, vector <int> temp, int start = 1){
      if(temp.size() == k){
         res.push_back(temp);  return;
      }
      for(int i = start; i <= n; i++){
         temp.push_back(i);
         solve(n, k, temp, i + 1);
         temp.pop_back();
      }
   }
   
   vector<vector<int> > combine(int n, int k) {
      res.clear();
      vector <int> temp;
      solve(n ,k, temp);  return res;
   }
};

int main(){
    cin>>AmountCharacter;
    string a;
    for(int j=0;j<AmountCharacter*5;j++){
        cin>>a;
        for(int i=0;i<AmountCharacter;i++){
            arr[j] += Bit(find(a[i]));
        }
    }
    string input;  cin>>input;  
    for(int i=0;i<AmountCharacter;i++){
        InputBit+=Bit(find(input[i]));
    }

    int c=0;
    for(int i=0;i<5*AmountCharacter;i++){
        if(InputBit[i]=='0')
          c++;
    }
    if(c==5*AmountCharacter){
        cout<<input<<'\n';
    }
    // for(int i=0;i<AmountCharacter*5;i++){
    //     cout<<"arr["<<i<<"]"<<'\t'<<arr[i]<<'\n';
    // }
    Solution ob;

    for(int i=1;i<5*AmountCharacter;i++)
      Print_Permutation(ob.combine(AmountCharacter*5,i));

    // for(int i=0;i<5*AmountCharacter;i++)
    //   for(auto x : Hash[i])
    //     cout<<x.first<<"\t"<<x.second<<'\n';
    queue<int> q;
    cout<<endl;
    for(int i=0;i<AmountCharacter*5;i++){
      unordered_map<string,string>::const_iterator got = Hash[i].find(InputBit);
       if(got != Hash[i].end())  {  
           q = StringToIndex(got->second);
           //string Ketqua(5*AmountCharacter,'0');
           cout<<ReceateBit(CipherToPlain(q))<<'\n';
       }
    }
    return 0;
}

void Print_Permutation(vector<vector<int> > v){
   for(int i = 0; i<v.size(); i++){
       value="";  name="";
           for(int j = 0; j <v[i].size(); j++){
             name+=to_string(v[i][j]-1);
             name+=".";
           }
             for(int j=0;j<v[i].size();j++){
               value=addBitStrings(value,arr[v[i][j]-1]);
             }
              Hash[v[i].size()-1][value] = name;
   }
}

string CreateBit(string base){
    res="";
    int v;
    for(int i=0;i<AmountCharacter;i++){
        v = find(base[i]);
        res += Bit(v);
    }
    return res;
}

string SumBit(string res){
    sumbit = "";
    for(int i=0;i<AmountCharacter*5;i++){
        if(res[i]=='1'){
            sumbit = addBitStrings(sumbit,arr[i]);
        }
    }
    return sumbit;
}

string ReceateBit(string sum){
     ans="";
     mang = "";
    for(int i=0;i<AmountCharacter*5;i++){
        mang +=sum[i];
        if((i+1)%5==0){
            ans +=Cout(mang);
            mang = "";
        }
    }
    return ans;
}

int find(char x){
    for(int i=0;i<32;i++){
        if(x == S[i])
              return i;
    }
    return -1;
}

string Bit(int n){
     r="";
    for(int i=4;i>=0;i--){
        if((n>>i)&1)
            r+='1';
        else 
            r+='0';
    }
    return r;
}

string addBitStrings( string first, string second )
{
    firstBit = 0;
    secondBit = 0;
    length = 0;
    result = "";
    length = makeEqualLength(first, second);
 
    int carry = 0;  // Initialize carry
    for (int i = length-1; i >= 0 ; i--)
    {
        firstBit = first.at(i) - '0';
        secondBit = second.at(i) - '0';
        int sum = (firstBit ^ secondBit ^ carry)+'0';
 
        result = (char)sum + result;
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
    return result;
}

int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1;
}

char Cout(string x){
    int d = 0;
    for(int i=4;i>=0;i--){
        if(x[i]=='1')
              d+=pow(2,4-i);
    }
    return S[d];
}

queue<int> StringToIndex(string index){
    queue<int> q;
    int num = 0;
    for(int i=0;i<index.length();i++){
        if(index[i]=='.'){
            q.push(num);
            num = 0;
            continue;
        }
        num = num*10+index[i]-'1'+1;
    }
    return q;
}

string CipherToPlain(queue<int> q){
    string plaintex(AmountCharacter*5,'0');
    int x = q.front();
    for(int i=0;i<AmountCharacter*5;i++){
        if(i==x)  {  plaintex[i] = '1';  q.pop();  x=q.front();  }
    }
    return plaintex;
}