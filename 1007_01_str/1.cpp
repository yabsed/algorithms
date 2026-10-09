#include <bits/stdc++.h>
using namespace std; 

void test1(){

    // char samples

    vector<char> samples = {
        'A', 'a', 
        'F', 'f', 
        'G', 'g', 
        '0', '1', '9', 
        ' ', 
        '\t', '\n',
        '@', '_', '!'
    }; 

    sort(samples.begin(), samples.end()); 

    // helper functions

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

    // print names of functions

    printf("%10s", "char"); 
    for(auto [name, func]: tests){
        printf("%10s", name.c_str()); 
    }
    printf("\n"); 

    /*
    put c_str() otherwise you will see 
    strange characters
    */

    // test each characters

    for(char sample: samples){

        /*
        without specifying type
        lambda don't know its returning type -> crash
        */

        // print sample 
        printf("%10s", [sample]() -> string {
            switch(sample){
                case ' ': return "[space]"; // const char*
                case '\t': return "[\\t]"; // const char*
                case '\n': return "[\\n]"; // const char*
                default: return string(1, sample); // string
            }
        }().c_str()); 

        // print test results
        for(auto [name, func]: tests){
            bool isTrue = func(sample) != 0;  
            printf("%10s", isTrue ? "True" : "False"); 
            /*
            not using %s may occur error!
            */
        }
        printf("\n"); 
    }

}

void test2(){

    // magic spell
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char c = 'A'; 

    c = tolower(c); 

    cout << c << endl; 

    c = toupper(c); 

    cout << c << endl; 
}

void test3(){

    // magic spell
    ios::sync_with_stdio(false); // not ios.sync...
    cin.tie(nullptr); 

    // rotating string
    auto func = [](int n){
        string s; 
        for(int i=0;i<n;i++){
            s.push_back('A' + (i % 26)); 
        }
        return s; 
    }; 

    // print vector
    auto printVector = [](vector<char> v){
        for(auto value: v){
            printf("%c", value); 
        }
        printf("\n"); 
    };

    // --------------------------

    string a; 
    string b = "hello"; 
    string c("hello"); 

    // using char
    string s(5, 'x'); // xxxxx

    // copy
    a = s; 
    a[1] = 'a'; // xaxxx

    cout << a << endl; // xaxxx
    cout << s << endl; // xxxxx
    cout << endl; 

    // using string
    s =        func(7);       // ABCDEFG
    a = string(func(7), 1);    // BCDEFG
    b = string(func(7), 1, 2); // BC

    printf("%7s\n", s.c_str()); 
    printf("%7s\n", a.c_str());
    printf("%3s\n", b.c_str());  
    cout << endl; 

    // prepare buffer
    char buf[100]; 
    strcpy(buf, func(7).c_str()); // should use c_str()

    printf("%s\n", buf); // ABCDEFG
    printf("\n"); 

    // using buf
    s = string(buf);         // ABCDEFG
    a = string(buf, 3);      // ABC
    b = string(buf + 2, 3);     //CDE

    printf("%7s\n", s.c_str()); 
    printf("%3s\n", a.c_str());
    printf("%5s\n", b.c_str());  
    cout << endl; 

    // prepare vector
    s = func(7);

    vector<char> v(s.begin(), s.end());
    s.clear(); 

    printVector(v); // ABCDEFG
    printf("%s\n", s.c_str()); // [empty]

    // using vector
    s = string(v.begin(), v.end()); 
    v.clear(); 

    printVector(v); // [empty]
    printf("%s\n", s.c_str()); // ABCDEFG 

}

void test4() {

    // magic spell
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    string prev(100, 'd'); 
    char* old = prev.data(); 

    // move
    string curr = move(prev); 

    // curr takes over [original heap buf]
    cout << (old == curr.data()) << endl; // (mostly) true

    // prev becomes [vaild-but-unspecified]
    cout << (prev.data() == curr.data()) << endl; // (mostly) false; 

}

void test5(){

    string s = "hello"; 

    cout << s.size() << endl; // 5
    cout << s.length() << endl; // 5
    cout << s.empty() << endl; // false

}

void test6() {

    auto printString = [](string &s){
        printf("%d/%d\n", s.length(), s.capacity()); 
    };

    // init
    string s; 
    printString(s); /* 0/15 */

    // enlarge capacity
    s.reserve(1000); 
    printString(s); /* 0/1000 */

    // assign data
    s = "Google"; 
    printString(s); /* 6/1000 */

    // shrink_to_fit()
    s.shrink_to_fit(); 
    printString(s);  /* 6/15 */

}


void test7() {

    string s; 

    s.resize(5); // fill with '\0'
    cout << s.length() << endl; // 5

/*
    consider s.resize(5) after s = "abc"
    it feels natural to fill with '\0'

    but then strlen and s.size() diverge
*/
    
    s += "x"; 
    cout << s.length()        << endl; // 6
    cout << strlen(s.c_str()) << endl; // 0

    cout << s         << endl; // x
    cout << s.c_str() << endl; // [empty]

/*
    std::string -> '\0' is    just another char

    strlen      -> '\0' means the end of the string
*/

}

void test8(){

    string a = "abc"; 

    // enlarge
    a.resize(5, 'x'); 
    cout << a << endl; // abcxx 

    // enshrink
    a.resize(2); 
    cout << a << endl; // ab

}

void test9(){

    string s = "not empty"; 

    s.clear(); 

    cout << s.empty() << endl; // 1

}

void test10() {

    string s = "hello"; 

    cout << s[2]    << endl; // l
    cout << s.at(2) << endl; // l
    
/*
    .at() -> is the given idx valid?
*/

    cout << s.front() << endl; // h 
    cout << s.back()  << endl; // o 

    s.front() = toupper(s.front()); 
    s.back () = toupper(s.back ()); 

    cout << s << endl; // HellO

/* 
    do not call 
    either front() or back()

    when given string is empty()
*/
}

void test11(){

    string s = []() -> string {
        string s; 
        for(char c='A';c<='K';c++){
            s += c; 
        }
        return s; 
    }(); // ABCDEFGHIJK

    // magic spell
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    // ABCDEFGHIJK
    for(auto it = s.begin(); it != s.end(); it++){
        cout << *it; 
    }
    cout << endl; 

    // KJIHGFEDCBA
    for(auto it = s.rbegin(); it != s.rend(); it++){
        cout << *it; 
    }
    cout << endl; 

    // KJIHGFEDCBA
    sort(s.begin(), s.end(), greater<>()); 
    cout << s << endl; 

    // ABCDEFGHIJK
    reverse(s.begin(), s.end()); 
    cout << s << endl; 

    // ABCDEFGHIJK
    for(char c: s){
        cout << c; 
    }
    cout << endl; 

    // ZYXWVUTSRQP
    for(char &c: s){
        c = ('Z' + 'A') - c; 
    }
    cout << s << endl; 
}

void test12(){

    string s; 
    string other = "helloworld"; 

    other = [other](){
        string result = other; 
        for(auto &c : result){
            c = ('z' + 'a') - c; 
        }
        return result; 
    }(); 
    
    s += "abc ";
    s += other;  
    cout << s << endl; // abc svooldliow

    s.push_back('!'); 
    cout << s << endl; // abc svooldliow!

    s.pop_back(); 
    cout << s << endl; // abc svooldliow

}

void test13() {

    // rotating string
    auto func = [](int n) {
        string s;
        for (int i = 0; i < n; i++) {
            s.push_back('A' + (i % 26));
        }
        return s;
    };

    // print vector
    auto printVector = [](const vector<char>& v) {
        for (auto value : v) {
            cout << value;
        }
        cout << '\n';
    };

    // --------------------------

    string s = "OLD|";
    string a = "OLD|", b = "OLD|";

    // using char
    s.append(5, 'x');
    cout << s << '\n'; // OLD|xxxxx
    cout << '\n';

    // using string
    s = a = b = "OLD|";

    s.append(func(7));       // OLD|ABCDEFG
    a.append(func(7), 1);    // OLD|BCDEFG
    b.append(func(7), 1, 2); // OLD|BC

    cout << s << '\n';
    cout << a << '\n';
    cout << b << '\n';
    cout << '\n';

    // prepare buffer
    char buf[100];
    strcpy(buf, func(7).c_str());

    cout << buf << '\n'; // ABCDEFG
    cout << '\n';

    // using buf
    s = a = b = "OLD|";

    s.append(buf);        // OLD|ABCDEFG
    a.append(buf, 3);     // OLD|ABC
    b.append(buf + 2, 3); // OLD|CDE

    cout << s << '\n';
    cout << a << '\n';
    cout << b << '\n';
    cout << '\n';

    // prepare vector
    s = func(7);

    vector<char> v(s.begin(), s.end());
    printVector(v); // ABCDEFG

    // using vector
    s = "OLD|";

    s.append(v.begin(), v.end());
    cout << s << '\n'; // OLD|ABCDEFG
}

void test14() {

    // rotating string
    auto func = [](int n) {
        string s;
        for (int i = 0; i < n; i++) {
            s.push_back('A' + (i % 26));
        }
        return s;
    };

    // print vector
    auto printVector = [](const vector<char>& v) {
        for (auto value : v) {
            cout << value;
        }
        cout << '\n';
    };

    // --------------------------

    string s = "OLD|";
    string a = "OLD|", b = "OLD|";

    // using char
    s.assign(5, 'x');
    cout << s << '\n'; // xxxxx
    cout << '\n';

    // using string
    s = a = b = "OLD|";

    s.assign(func(7));       // ABCDEFG
    a.assign(func(7), 1);    // BCDEFG
    b.assign(func(7), 1, 2); // BC

    cout << s << '\n';
    cout << a << '\n';
    cout << b << '\n';
    cout << '\n';

    // prepare buffer
    char buf[100];
    strcpy(buf, func(7).c_str());

    cout << buf << '\n'; // ABCDEFG
    cout << '\n';

    // using buf
    s = a = b = "OLD|";

    s.assign(buf);        // ABCDEFG
    a.assign(buf, 3);     // ABC
    b.assign(buf + 2, 3); // CDE

    cout << s << '\n';
    cout << a << '\n';
    cout << b << '\n';
    cout << '\n';

    // prepare vector
    s = func(7);

    vector<char> v(s.begin(), s.end());
    printVector(v); // ABCDEFG

    // using vector
    s = "OLD|";

    s.assign(v.begin(), v.end());
    cout << s << '\n'; // ABCDEFG
}

void test15(){

    string s; 
    string a, b; 

    // use string
    s = "ab__ef"; 
    s.insert(3, "cd"); 
    cout << s << endl; // ab_cd_ef

    // use partial string
    s = "ab__gh"; 
    s.insert(3, "abcdefg", 2, 4); 
    cout << s << endl; // ab_cdef_gh

    // use char
    s = "ab__de"; 
    s.insert(3, 5, 'c'); 
    cout << s << endl; // ab_ccccc_de

    // use iterator pos 
    s = "ab__de"; 
    s.insert(s.begin()+3, 'c'); 
    cout << s << endl;  // ab_c_de

    s = "ab__de"; 
    s.insert(s.begin()+3, 5, 'c'); 
    cout << s << endl;  // ab_ccccc_de

    // use vector
    vector <char> v = {'C', 'C'}; 
    s = "ab__de"; 
    s.insert(s.begin()+3, v.begin(), v.end()); 
    cout << s << endl; // ab_CC_de

}

void test16(){

    string s; 

    // using idx
    s = "AB___C"; 
    s.erase(2, 3);
    cout << s << endl; // ABC

    s = "AB_____"; 
    s.erase(2); 
    cout << s << endl; // AB

    // using it
    s = "AB_CDE"; 
    s.erase(s.begin() + 2); 
    cout << s << endl; // ABCDE

    s = "A_____BC"; 
    s.erase(s.begin()+1, s.end()-2); 
    cout << s << endl; // ABC

}

void test17(){

    string s; 
/*
    replace(pos, count, other); 
*/
    s = "Ilike_andcats"; 
    s.replace(5, 1, "DOGS"); 
    cout << s << endl; // IlikeDOGSandcats
/*
    replace(pos, count,
            other, other_pos, other_count); 
*/
    s = "Ilike___andcats"; 
    s.replace(5, 3, "__DOGS_", 2, 4); 
    cout << s << endl; // IlikeDOGSandcats

    // use char
    s = "Ilike____andcats"; 
    s.replace(5, 4, 8, 'X'); 
    cout << s << endl; // IlikeXXXXXXXXandcats

    // use iterator
    s = "Ilike___andcats"; 
    s.replace(s.begin()+5, s.begin()+8, 5, '?'); 
    cout << s << endl; // Ilike?????andcats
}

void test18(){

    // magic source
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    string a = "AAAA"; 
    string b = "BBBB"; 

    swap(a, b); 

    cout << a << endl; // BBBB 
    cout << b << endl; // AAAA

    a.swap(b); 

    cout << a << endl; // AAAA
    cout << b << endl; // BBBB

}

void test19(){

    string s; 
    string a, b; 

    s = "_____abCD"; 

    a = s.substr(5, 2); 
    cout << a << endl; // ab

    b = s.substr(5); 
    cout << b << endl; // abCD 

}

void test20(){

    string s; 
    size_t pos; 

    s = "...345....012..."; 
    pos = 0; 

    while((pos = s.find("...", pos)) != string::npos){
        cout << pos++ << endl; 
    }
/*
    0
    6
    7
    13
*/
    s = "...345..."; 
    pos = 0; 
        while((pos = s.find('.', pos)) != string::npos){
        cout << pos++ << endl; 
    }
/*
    0
    1
    2
    6
    7
    8
*/
}

void test21(){

    string s; 
    size_t pos; 

    s = "...345....012..."; 
    pos = s.size(); 

    while(pos && ((pos = s.rfind("...", pos-1)) != string::npos)){
        cout << pos << endl; 
    }
/*
    13
    7
    6
    0
*/
}

void test22(){

    string s, q; 
    size_t pos; 

    s = "012__56__9"; 
    q = "9876543210"; 

    pos = 0; 

    while((pos = s.find_first_of(q, pos)) != string::npos){
        cout << pos++ << endl; 
    }

/*
    0
    1
    2
    5
    6
    9
*/
}

void test23(){

    string s, q; 
    size_t pos; 

    s = "012__56__9"; 
    q = "9876543210"; 

    pos = s.size(); 

    while(pos && ((pos = s.find_last_of(q, pos-1)) != string::npos)){
        cout << pos << endl; 
    }
/*
    9
    6
    5
    2
    1
    0
*/
}



int main(){

    test21();

}
