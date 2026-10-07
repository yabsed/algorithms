#include <bits/stdc++.h>
using namespace std; 

void test1(){

    // 문자 종류
    vector<char> samples = {
        'A', 'a', 
        'F', 'f', 
        'G', 'g', 
        
        '0', '1', '9', 

        '@', '!', '_', 

        ' ', 
        '\n', '\t'
    };

    sort(samples.begin(), samples.end()); 

    // helper 함수들
    using CharFunc = int (*)(int); 
    vector<pair<string, CharFunc>> tests = {
        {"isdigit", ::isdigit}, 
        {"isalpha", ::isalpha}, 
        {"isalnum", ::isalnum}, 
        {"islower", ::islower}, 
        {"isupper", ::isupper}, 
        {"isspace", ::isspace}, 
        {"ispunct", ::ispunct}, 
        {"isxdigit", ::isxdigit},
        {"iscntrl", ::iscntrl}, 
        {"isprint", ::isprint}, 
        {"isgraph", ::isgraph}
    }; 

    // 함수 이름 출력
    printf("%10s", "char"); 

    for(auto &[name, func] : tests)
        printf("%10s", name.c_str()); 
    
    printf("\n"); 

    // 각 문자 테스트
    for(char sample: samples){

        printf("%10s", [&]() -> string {
            switch(sample){
                case ' ': return "[space]"; 
                case '\t': return "[\\t]"; 
                case '\n': return "[\\n]"; 
                default:   return string(1, sample); 
            }
        }().c_str()); 

        for (auto &[name, func] : tests){
            bool result = func((unsigned char) sample) != 0; 
            printf("%10s", result ? "Yes" : ""); 
        }

        printf("\n"); 

    }

    // expected

    /*

      char   isdigit   isalpha   isalnum   islower   isupper   isspace   ispunct  isxdigit   iscntrl   isprint   isgraph
      [\t]                                                         Yes                           Yes                    
      [\n]                                                         Yes                           Yes                    
   [space]                                                         Yes                                     Yes          
         !                                                                   Yes                           Yes       Yes
         0       Yes                 Yes                                               Yes                 Yes       Yes
         1       Yes                 Yes                                               Yes                 Yes       Yes
         9       Yes                 Yes                                               Yes                 Yes       Yes
         @                                                                   Yes                           Yes       Yes
         A                 Yes       Yes                 Yes                           Yes                 Yes       Yes
         F                 Yes       Yes                 Yes                           Yes                 Yes       Yes
         G                 Yes       Yes                 Yes                                               Yes       Yes
         _                                                                   Yes                           Yes       Yes
         a                 Yes       Yes       Yes                                     Yes                 Yes       Yes
         f                 Yes       Yes       Yes                                     Yes                 Yes       Yes
         g                 Yes       Yes       Yes                                                         Yes       Yes

    */

}

void test2() {

    char c = 'A'; 
    
    c = tolower(c); 

    printf("%c\n", c); // a

    c = toupper(c); 

    printf("%c\n", c); // A

}

void test3(){
 
    // 기본적인 선언
    string a; 
    string b = "hello"; 
    string c("hello"); 

    // 같은 문자 반복
    string s(5, 'x'); 

    // 복사
    a = s; 
    a[1] = 'a'; 

    cout << a << endl; // xaxxx
    cout << s << endl; // xxxxx
    cout << endl; 

    // string의 일부
    s = "abcdefg";
    
    a = string(s, 2); // cdefg
    b = string(s, 2, 3); // cde

    cout << s << endl; // abcdefg
    cout << a << endl; //   cdefg
    cout << b << endl; //   cde
    cout << endl; 

    // buf의 일부
    char buf[] = "abcdefg"; 
    
    s = string(buf); // abcdefg
    a = string(buf, 3); // abc
    b = string(buf + 2, 3); // cde

    cout << s << endl; 
    cout << a << endl; 
    cout << b << endl; 
    cout << endl; 

}

void test4() {

    string s = "hello"; 
    vector<char> v; 
    
    // string -> vector
    v = vector(s.begin(), s.end());
    s = string(); 
    
    cout.write(v.data(), v.size()); // hello
    cout << endl; 
    cout << s << endl; // [empty]

    // vector -> string
    s = string(v.begin(), v.end()); 
    v.clear(); 

    cout.write(v.data(), v.size()); // [empty]
    cout << endl; 
    cout << s << endl; // hello
}

void test5(){

    
}

int main(){

    test5(); 
}