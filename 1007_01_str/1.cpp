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

    string prev(1000, 'd'); 

    auto old = prev.data(); // char *

    string curr = move(prev); 
    
    // heap buffer를 curr가 그대로 인수
    cout << (old == curr.data()) << '\n'; // (mostly) true

    // prev는 별도의 valid-but-unspecified 상태
    cout << (prev.data() == curr.data()) << '\n'; // (mostly) false

/*

move 전

prev
 └──────► [ d d d d ... d \0 ]
            ^
            old


move 후

curr
 └──────► [ d d d d ... d \0 ]
            ^
            old

prev
 └──────► 다른 저장소/빈 문자열 등

*/

}

void test6(){

    string s = "hello"; 

    cout << s.size() << endl; // 5
    cout << s.length() << endl; // 5
    cout << s.empty() << endl; // false

}

void test7(){

    // string has capacity
    string s; 
    cout << s.capacity() << endl; // (example) 15

    // reserve to enlarge or enshrink
    s.reserve(1000); 
    cout << s.capacity() << endl; // 1000
    cout << endl; 

    // length() different with capacity()
    s = "Good"; 
    cout << s.length() << endl; // 4
    cout << s.capacity() << endl; // 1000
    cout << endl; 

    // shrink_to_fit()
    s.shrink_to_fit(); 
    cout << s.length() << endl; // 4
    cout << s.capacity() << endl; // (example) 15
}

void test8(){

    string s; 

    // s = string({'\0', '\0', '\0', '\0', '\0'}); 
    s.resize(5);

    cout << s.length() << endl; // 5
    cout << endl; 

    s.append("x"); 
    cout << s << endl; // x
    cout << s.length() << endl; // 6
    cout << endl; 

    cout << s.c_str() << endl; // [empty] 
    cout << strlen(s.c_str()) << endl; // 0


/*

    think this: there is no reason not to place \0

    consider s.resize(5) after s = "abc" 

    it feels natural to fill \0
    
    but after that moment strlen and s.size() start to diverge

    so you have to be causious

*/

/*

    in std::string \0 is just another char

    but in strlen it means the end of the string

*/

}

void test9(){

    string s = "abc"; 

    // 확대

    s.resize(5, 'x');
    
    cout << s << endl; // abcxx

    // 축소
    s.resize(2); 

    cout << s << endl; // ab

}

void test10(){

    string s = "not empty"; 

    s.clear(); 

    // empty
    cout << (s.empty() ? "empty" : "not empty") << endl; 

}

void test11(){

    string s = "hello"; 

    cout << s[2] << endl; // l
    cout << s.at(2) << endl; // l

    cout << endl; 

/*
    at() checks 
    whehter the given idx is valid
*/

    cout << s.front() << endl; // h
    cout << s.back() << endl; // o
    cout << endl; 

    s.front() = 'H', s.back() = 'O';
    cout << s; // HellO
    cout << endl; 

/*

    Warning: do not call

    either front() or back()

    when given string is empty

*/

}

void test12(){

/*
    use iterator to traverse
*/
    string s = "abcdefghijk";
    
    // abcdefghijk
    for(auto it = s.begin(); it != s.end(); it++){
        cout << *it; 
    }
    cout << endl; 

    // kjihgfedcba
    for(auto it = s.rbegin(); it != s.rend(); it++){
        cout << *it; 
    }
    cout << endl; 

    // kjihgfedcba
    sort(s.begin(), s.end(), greater<>()); 
    cout << s << endl; 

    // abcdefghijk
    reverse(s.begin(), s.end()); 
    cout << s << endl; 

    // abcdefghijk
    for(char c: s){
        cout << c; 
    }
    cout << endl; 

    // zyxwvutsrqp
    for(char& c: s){
        c = ('z' + 'a') - c; 
    }
    cout << s << endl; 
}

void test13(){

    string s; 
    
    string other = "helloworld"; 

    s += "abc "; 

    s += [other]() -> string {

        string result = other; 
        
        for(auto &c : result){
            c = ('z' + 'a') - c; 
        }

        return result; 
    }(); 

    // abc svooldliow
    cout << s << endl;
    
    s.push_back('!'); 

    // abc svooldliow!
    cout << s << endl; 

}


int main(){

    test13(); 
}