#include <bits/stdc++.h>
#include <cctype>
#include <random>
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
    s = "012345"; 
    s.insert(3, "__"); 
    cout << s << endl; // 012__345

    // use partial string
    s = "012345"; 
    s.insert(3, "abcdef", 2, 4); 
    cout << s << endl; // 012cdef345

    // use char
    s = "012345"; 
    s.insert(3, 5, '_'); 
    cout << s << endl; // 012_____345

    // use iterator pos
    s = "012345"; 
    s.insert(s.begin()+3, '_'); // 012_345
    cout << s << endl; 

    s = "012345"; 
    s.insert(s.begin()+3, 5, '_'); 
    cout << s << endl; // 012_____345

    // use set
    set <char> mySet = {'a', 'b', 'c'}; 
    s = "012345"; 
    s.insert(s.begin()+3, mySet.begin(), mySet.end()); // 012abc345
    cout << s << endl; 
}

void test16(){

    string s; 

    // using idx
    s = "0123456789"; 
    s.erase(7, 2); 
    cout << s << endl; // 01234569

    s = "0123456789"; 
    s.erase(7); 
    cout << s << endl; // 0123456

    // using iterator
    s = "0123456789"; 
    s.erase(s.begin() + 7); 
    cout << s << endl; // 012345689

    s = "0123456789"; 
    s.erase(s.begin() + 7, s.begin() + 9); 
    cout << s << endl; // 01234569
    cout << endl; 

    // ----------------------------

    // example: remove duplicate
    s = "ccddbbaaff"; 

    // step 1. sort
    sort(s.begin(), s.end()); 
    cout << s << endl; 
    
    // step 2. unique
    auto it = unique(s.begin(), s.end()); 
    cout << s << endl; 

    // step 3. erase
    s.erase(it, s.end()); 
    cout << s << endl; 
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

void test24(){

    string s, q; 
    size_t pos; 

    s = "___34_67__"; 
    q = "0123456789"; 

    pos = 0; 
    
    while((pos = s.find_first_not_of(q, pos)) != string::npos){
        cout << pos++ << endl; 
    }
/*
    0
    1
    2
    5
    8
    9
*/
}

void test25(){
    string s, q; 
    size_t pos; 

    s = "___34_67__"; 
    q = "0123456789"; 

    pos = s.size(); 
    
    while(pos && (pos = s.find_last_not_of(q, pos-1)) != string::npos){
        cout << pos << endl; 
    }
/*
    9
    8
    5
    2
    1
    0
*/
}

void test26(){

    vector<string> samples = {
        "baby", 
        "zoo", 
        "usa", 
        "apple"
    }; 

    sort(samples.begin(), samples.end()); 

    for(auto sample: samples){
        cout << sample << endl; 
    }
/*
    apple
    baby
    usa
    zoo
*/
    cout << ("abc"s < "abd"s) << endl; // 1
    cout << ("cat"s < "apple"s) << endl; // 0
/*
    do not "abc" < "abd"
    comparison between two arrays is deprecated in C++20
*/
    cout << ("abc"s != "abc"s) << endl; // 0
}


void test27() {

    const char* a = "notString";
    string b = a; // const char* -> string (copy)

    printf("%s\n", a);
    printf("%s\n", b.c_str());

/*
    const char* comparison
    
    ==, != : compare pointer addresses
    <, >   : compare pointer ordering
    
    They do NOT compare string contents.
*/

    const char* x = "abc";
    const char* y = "abd";

    cout << (x == y) << endl; // compares addresses
    cout << (x < y) << endl;  // NOT lexicographical

/*
    std::string comparison
    
    ==, != : compare string contents
    <, >   : lexicographical comparison
*/

    string p = "abc";
    string q = "abd";

    cout << (p == q) << endl; // false
    cout << (p < q) << endl;  // true

/*
    C-style lexicographical comparison
*/

    cout << (strcmp(x, y) < 0) << endl; // true
}

void test28() {

    // naive 
    cout << ("A"s.compare("Z")  < 0) << endl; // true
    cout << ("A"s.compare("A") == 0) << endl; // true
    cout << ("Z"s.compare("A")  > 0) << endl; // true
    
    // because AAAA < ZZZZ
    string a = "AAAAZZZZ"; 
    auto result1 = a.compare(0, 4, a, 4, 4); 
    // (pos1, count1, b, pos2, count2)
    cout << (result1 < 0) << endl; // true
    
    // because AAAA == AAAA
    string b = "AAAA"; 
    auto result2 = a.compare(0, 4, b); 
    // (pos, count, b)
    cout << (result2 == 0) << endl; // true
}

void test29() {

    string s = "0123456789"; 

    // C++20
    cout << (s.starts_with('0')) << endl; 
    cout << (s.ends_with  ("789")) << endl; 
    // older
    cout << (s. find('0') == 0) << endl; 
    cout << (s.size() >= 3 && s.rfind("789") == s.size() - 3) << endl; 
/*
    consider s.size() can be < 3
*/
    // contains?
    cout << (s.find("456") != string::npos) << endl; 
}

void test30(){

    char buf[100]; 
    string s; 
    size_t idx; 

    // strcpy: copies including '\0'
    s = "0123"; 
    strcpy(buf, s.c_str()); 
    cout << buf << endl; // 0123

    // string::copy: does NOT append '\0'
    s = "0123456789"; 
    idx = s.copy(
        buf+4, 
        4,
        4
    ); 
    (buf+4)[idx] = '\0';
    cout << buf << endl; // 01234567
}

void test31() {
/*
    printf("%s") accepts both
    char* and const char*.
    
    The character sequence must be null-terminated.
*/
    string s = "hello world"; 

    // read-only
    printf("%s\n", s.c_str()); 

    // writable since C++17
    s.data()[0] = 'H'; 
    printf("%s\n", s.data()); 

    // both are null-terminated since C++11
}

void test32() {
/*
    consider lifespan of memory space
    when using either c_str() or data()
*/
    string s = "hello"; 

    const char* p = s.c_str(); 

    s += string(1000, 'c'); // very long string

    p = s.c_str(); // Refresh before dereferencing (otherwise UB)

    cout << (p[0] == 'h') << endl; // true
}

void test33() {

    // int
    cout << stoi("2147483647") << endl;
    cout << stoi("-2147483648") << endl;

    // long
    cout << stol("9223372036854775807") << endl;
    cout << stol("-9223372036854775808") << endl;

    // long long
    cout << stoll("9223372036854775807") << endl;
    cout << stoll("-9223372036854775808") << endl;

    // unsigned long
    cout << stoul("18446744073709551615") << endl;

    // unsigned long long
    cout << stoull("18446744073709551615") << endl;

    // floating point
    cout << scientific << setprecision(18);

    // float
    cout << stof("3.4e38") << endl;
    cout << stof("-3.4e38") << endl;

    // double
    cout << stod("1.7e308") << endl;
    cout << stod("-1.7e308") << endl;

    // long double
    cout << stold("1e4000") << endl;
    cout << stold("-1e4000") << endl;
}

bool test34(){

    string ip = "125.5.1.12"; 

    // collect dots
    size_t pos = 0; 
    vector<int> points = {-1, }; 
    while((pos = ip.find('.', pos)) != string::npos){
        points.push_back(pos++); 
    }
    points.push_back(ip.size()); 

    // has three dots?
    if(points.size() != 5){
        return false; 
    }

    // split into four chunks
    for(int i=0;i<4;i++){

        int pos1 = points[i]; 
        int pos2 = points[i+1]; 

        // chunk length valid?
        int delta = (pos2 - pos1) - 1; 
        if (!(1 <= delta && delta <= 3)){
            return false; 
        }

        // deduct chunk
        string chunk = ip.substr(pos1+1, delta); 

        // only numbers?
        if(chunk.find_first_not_of("0123456789") != string::npos){
            return false; 
        }

        // int(chunk) value valid?
        int value = stoi(chunk); 
        if(!(0 <= value && value <= 255)){
            return false; 
        }

        // str(int(chunk)) == chunk?
        if(to_string(value) != chunk){
            return false; 
        }

    }

    return true; 
}

void test35(){

    string s; 
    int n; 

    auto plain = [](int n, int base) -> string {
        if (n == 0){
            return "0"; 
        }

        // construct digits : 0...9 a...z 
        string digits; 
        for(char c='0';c<='9';c++) digits += c; 
        for(char c='a';c<='z';c++) digits += c; 

        // construct s
        string s; 
        while(n > 0){
            s += (digits[n % base]); 
            n /= base; 
        }
        reverse(s.begin(), s.end()); 
        return s; 
    }; 

    s = plain(100, 32); 
    n = stoi(s, nullptr, 32); 

    printf("%3s(32) %3d(10)\n", s.c_str(), n); 

    // ----------------------

    char buf[200]; 

    auto [ptr, ec] = to_chars(buf, buf+200, 63, 32); 
    
    s = string(buf, ptr); 
    n = stoi(s, nullptr, 32); 

    printf("%3s(32) %3d(10)\n", s.c_str(), n); 

}

void test36(){

    int n; 
    size_t idx; 

    n = stoi("012_is_it_future?", &idx, 10); 

    cout << n << endl; // 12
    cout << idx << endl; // 3

    n = stoi("012345", &idx); 

    cout << n << endl; // 12345
    cout << idx << endl; // 6

}

void test37(){

    cout << to_string(123LL) << endl; 
    cout << to_string(3.14) << endl; 

}

void test38(){

    int n; 
    
    n = stoi("-123##"); 
    cout << n << endl; // -123

    try {
        n = stoi("###123"); 
    } catch (const exception&) {
        cout << "can raise exception when prefix is not valid" << endl; 
    }

    // that is why you still need
    // find_first_not_of in IP parsing

}

void test39(){

    string a = "012"; 
    string b = "345"; 

    const char* c = "abc"; 

    cout << a + b << endl; // 012345
    cout << a + c << endl; // 012abc
    cout << c + a << endl; // abc012

    cout << a + '_' << endl; // 012_
    cout << '_' + a << endl; // _012


    // cout << ("012" + "345") << endl; 
    
    // invalid operands of types ‘const char*’ and 
    // ‘const char*’ to binary ‘operator+’

    // ------------

    auto s1 = "string"s; 
    printf("%s\n", s1.c_str()); 

    auto s2 = "const char*"; 
    printf("%s\n", s2); 

}

void test40(){

    auto rndStr = [](int n){

        static mt19937 gen(random_device{}()); 
        uniform_int_distribution<> distrib('a', 'z'); 

        string s; 
        for(int i=0;i<n;i++){
            s.push_back(distrib(gen)); 
        }

        return s; 

    }; 

    string s = rndStr(20); 
    printf("original: %s\n", s.c_str()); 

    // count
    int cnt = count(s.begin(), s.end(), 'a'); 
    printf("# of a: %d\n", cnt); 

    // count_if
    int cnt_xdigit = count_if(s.begin(), s.end(), [](char c){
        return isxdigit(c); 
    }); 
    printf("# of xdigits: %d\n", cnt_xdigit); 

    // sort
    sort(s.begin(), s.end()); 
    printf("sorted: %s\n", s.c_str()); 
    
    // reverse
    reverse(s.begin(), s.end()); 
    printf("reverse: %s\n", s.c_str()); 
    
}

void test41(){

    string s = "...34.."; 

    // use &s instead of s
    // to prevent copying value

    [&s](){
        size_t pos = 0; 
        while((pos = s.find('.', pos)) != string::npos){
            cout << pos++ << endl; 
        }
    }(); 
/*
    0
    1
    2
    5
    6
*/
    [&s](){

        auto pos = s.begin();
        while((pos = find(pos, s.end(), '.')) != s.end()){
            cout << (pos++ - s.begin()) << endl; 
        }

    }(); 
/*
    0
    1
    2
    5
    6
*/
}

void test42(){

    auto rndStr = [](int length){
        static mt19937 rnd(random_device{}()); 
        uniform_int_distribution<int> distrib('a', 'x'); 

        string s; 
        for(int i=0;i<length;i++){
            s.push_back(distrib(rnd)); 
        }

        return s; 
    }; 

    string s = rndStr(20); 
    printf("%s\n", s.c_str());
    
    [&s]() {

        auto it = s.begin(); 
        auto prev = s.begin(); 

        while((it = find_if(it, s.end(), [](char c){
            return isxdigit(c); 
        })) != s.end()){

            cout << string((it - prev), ' '); 
            cout << *(it);
            
            prev = ++it; 
        }

        cout << endl; 

    }(); 

}

int main(){

    test42();

}
