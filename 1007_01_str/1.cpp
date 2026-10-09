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


// test15 ~ test100 follow the same section numbers in 1.md.
// C++17 works; use -std=c++23 to also practice the newer APIs.
// Change the function called in main() to choose a practice.

void test15() {

    // insert: put new characters BEFORE pos
    string s = "abef";
    string other = "ABCDEFG";

    s.insert(2, "cd");
    cout << s << '\n'; // abcdef

    // using string
    s = "abef";
    s.insert(2, other);
    cout << s << '\n'; // abABCDEFGef

    // using part of another string: other[2], other[3], other[4]
    s = "abef";
    s.insert(2, other, 2, 3);
    cout << s << '\n'; // abCDEef

    // using buffer: only the first 3 characters
    s = "abef";
    const char buf[] = "CDEFG";
    s.insert(2, buf, 3);
    cout << s << '\n'; // abCDEef

    // using repeated char
    s = "abef";
    s.insert(2, 5, 'x');
    cout << s << '\n'; // abxxxxxef

    // using iterator: one char
    s = "abef";
    auto it = s.insert(s.begin() + 2, 'x');
    cout << *it << '\n'; // x: iterator to the inserted char
    cout << s << '\n'; // abxef

    // using iterator: repeated char
    s = "abef";
    s.insert(s.begin() + 2, 5, 'x');
    cout << s << '\n'; // abxxxxxef

    // using iterator range
    vector<char> v = {'c', 'd'};
    s = "abef";
    s.insert(s.begin() + 2, v.begin(), v.end());
    cout << s << '\n'; // abcdef

    // C++23: insert_range (if supported by the standard library)
    s = "abef";
#if defined(__cpp_lib_containers_ranges) && __cpp_lib_containers_ranges >= 202202L
    s.insert_range(s.begin() + 2, v);
#else
    s.insert(s.begin() + 2, v.begin(), v.end());
#endif
    cout << s << '\n'; // abcdef

    // pos == size() is valid: insert at the end
    s.insert(s.size(), "!");
    cout << s << '\n'; // abcdef!
    // Middle insertion moves the following characters: generally O(n).
}

void test16() {

    // erase: pos and COUNT, not an ending index
    string s = "abcdef";
    s.erase(2, 3);
    cout << s << '\n'; // abf

    // erase from pos to the end
    s = "abcdef";
    s.erase(2);
    cout << s << '\n'; // ab

    // erase one char using iterator
    s = "abcdef";
    auto it = s.erase(s.begin() + 2);
    cout << s << '\n'; // abdef
    cout << *it << '\n'; // d: the char following the erased char

    // erase range [first, last): indices 2, 3, 4
    s = "abcdef";
    s.erase(s.begin() + 2, s.begin() + 5);
    cout << s << '\n'; // abf

    s.erase();
    cout << s.empty() << '\n'; // 1
}

void test17() {

    // replace: remove count chars at pos, then insert the new content
    string s = "I like cats";
    s.replace(7, 4, "dogs");
    cout << s << '\n'; // I like dogs

    string other = "cute birds";
    s = "I like cats";
    s.replace(7, 4, other);
    cout << s << '\n'; // I like cute birds

    // using part of another string
    s = "I like cats";
    s.replace(7, 4, other, 5, 5);
    cout << s << '\n'; // I like birds

    // using buffer: first 3 chars
    s = "I like cats";
    s.replace(7, 4, "doghouse", 3);
    cout << s << '\n'; // I like dog

    // using repeated char
    s = "I like cats";
    s.replace(7, 4, 5, 'x');
    cout << s << '\n'; // I like xxxxx

    // using iterator range [first, last)
    s = "I like cats";
    s.replace(s.begin() + 7, s.end(), "dogs");
    cout << s << '\n'; // I like dogs

    vector<char> v = {'d', 'o', 'g', 's'};
    s = "I like cats";
    s.replace(s.begin() + 7, s.end(), v.begin(), v.end());
    cout << s << '\n'; // I like dogs

    // C++23: replace_with_range
    s = "I like cats";
#if defined(__cpp_lib_containers_ranges) && __cpp_lib_containers_ranges >= 202202L
    s.replace_with_range(s.begin() + 7, s.end(), v);
#else
    s.replace(s.begin() + 7, s.end(), v.begin(), v.end());
#endif
    cout << s << '\n'; // I like dogs
}

void test18() {

    string a = "hello", b = "world";

    a.swap(b);
    cout << a << ' ' << b << '\n'; // world hello

    swap(a, b);
    cout << a << ' ' << b << '\n'; // hello world
}

void test19() {

    string s = "abcdefgh";

    // second argument is COUNT: [2, 2 + 3)
    string t = s.substr(2, 3);
    cout << t << '\n'; // cde

    cout << s.substr(2) << '\n'; // cdefgh
    cout << s.substr(6, 100) << '\n'; // gh: stops at the end
    cout << s.substr(s.size()).empty() << '\n'; // 1

    // substr makes a copy
    t[0] = 'X';
    cout << t << '\n'; // Xde
    cout << s << '\n'; // abcdefgh
    // pos > size() throws out_of_range.
}

void test20() {

    string s = "abc---abc";
    string target = "abc";

    cout << s.find("abc") << '\n'; // 0
    cout << s.find('a') << '\n'; // 0
    cout << s.find(target) << '\n'; // 0
    cout << s.find("abc", 1) << '\n'; // 6: search from index 1

    auto pos = s.find("xyz");
    if (pos == string::npos) {
        cout << "not found\n";
    }

    pos = s.find(target, 1);
    if (pos != string::npos) {
        cout << s.substr(pos, target.size()) << '\n'; // abc
    }
}

void test21() {

    string s = "abc---abc";

    cout << s.find("abc") << '\n'; // 0
    cout << s.rfind("abc") << '\n'; // 6
    cout << s.rfind('a') << '\n'; // 6

    // pos limits the START index of the match: search at or before pos
    cout << s.rfind("abc", 5) << '\n'; // 0
    cout << s.rfind("abc", 6) << '\n'; // 6
    cout << (s.rfind("xyz") == string::npos) << '\n'; // 1
}

void test22() {

    string s = "hello123";
    cout << s.find_first_of("0123456789") << '\n'; // 5

    // any character in the set, not the substring itself
    cout << s.find_first_of("321") << '\n'; // 5: '1'
    cout << (s.find("321") == string::npos) << '\n'; // 1
    cout << s.find_first_of("0123456789", 6) << '\n'; // 6
}

void test23() {

    string path = "/home/test/a.txt";
    auto pos = path.find_last_of('/');

    cout << pos << '\n'; // 10
    if (pos != string::npos) {
        cout << path.substr(pos + 1) << '\n'; // a.txt
    }

    // any character in the set
    cout << path.find_last_of("/.") << '\n'; // 12: '.'
}

void test24() {

    string s = "   hello";
    cout << s.find_first_not_of(' ') << '\n'; // 3

    s = " \t\n\rhello";
    auto pos = s.find_first_not_of(" \t\n\r");
    cout << pos << '\n'; // 4
    cout << s.substr(pos) << '\n'; // hello

    s = " \t\n\r";
    cout << (s.find_first_not_of(" \t\n\r") == string::npos) << '\n'; // 1
}

void test25() {

    string s = "hello   ";
    auto pos = s.find_last_not_of(' ');

    cout << pos << '\n'; // 4
    cout << s.substr(0, pos + 1) << '\n'; // hello

    s = "hello \t\n\r";
    cout << s.find_last_not_of(" \t\n\r") << '\n'; // 4
}

void test26() {

    // compare all six search functions on the same string
    string s = "--abc--abc--";

    cout << s.find("abc") << '\n'; // 2
    cout << s.rfind("abc") << '\n'; // 7
    cout << s.find_first_of("bc") << '\n'; // 3
    cout << s.find_last_of("bc") << '\n'; // 9
    cout << s.find_first_not_of('-') << '\n'; // 2
    cout << s.find_last_not_of('-') << '\n'; // 9
}

void test27() {

    string s = "hello";
    auto pos = s.find("xyz");

    cout << (pos == string::npos) << '\n'; // 1
    cout << (string::npos == string::size_type(-1)) << '\n'; // 1

    // keep the returned type; check npos BEFORE using it as an index
    if (pos != string::npos) {
        cout << s[pos] << '\n';
    } else {
        cout << "not found\n";
    }
}

void test28() {

    string a = "abc", b = "abd";

    cout << (a == b) << '\n'; // 0
    cout << (a != b) << '\n'; // 1
    cout << (a < b) << '\n'; // 1
    cout << (a > b) << '\n'; // 0
    cout << (a <= b) << '\n'; // 1
    cout << (a >= b) << '\n'; // 0

    vector<string> words = {"cat", "apple", "abc", "ab"};
    sort(words.begin(), words.end());
    for (const string& word : words) {
        cout << word << '\n'; // ab, abc, apple, cat (one per line)
    }
}

void test29() {

    string a = "abc", b = "abd";

    // only the sign is guaranteed, not exactly -1 or 1
    cout << (a.compare(b) < 0) << '\n'; // 1
    cout << (a.compare(a) == 0) << '\n'; // 1
    cout << (b.compare(a) > 0) << '\n'; // 1

    a = "XXhelloYY";
    b = "hello";
    cout << a.compare(2, 5, b) << '\n'; // 0

    b = "--hello--";
    cout << a.compare(2, 5, b, 2, 5) << '\n'; // 0
}

void test30() {

    string s = "abc---xyz";

    // C++20: prefix / suffix
#if __cplusplus >= 202002L
    cout << s.starts_with("abc") << '\n'; // 1
    cout << s.ends_with("xyz") << '\n'; // 1
    cout << s.starts_with('a') << '\n'; // 1
    cout << s.ends_with('z') << '\n'; // 1
#else
    cout << (s.compare(0, 3, "abc") == 0) << '\n'; // 1
    cout << (s.size() >= 3 && s.compare(s.size() - 3, 3, "xyz") == 0) << '\n'; // 1
    cout << (!s.empty() && s.front() == 'a') << '\n'; // 1
    cout << (!s.empty() && s.back() == 'z') << '\n'; // 1
#endif

    // C++23: contains
#if defined(__cpp_lib_string_contains) && __cpp_lib_string_contains >= 202011L
    cout << s.contains("abc") << '\n'; // 1
    cout << s.contains('x') << '\n'; // 1
    cout << s.contains("hello") << '\n'; // 0
#else
    cout << (s.find("abc") != string::npos) << '\n'; // 1
    cout << (s.find('x') != string::npos) << '\n'; // 1
    cout << (s.find("hello") != string::npos) << '\n'; // 0
#endif
}

void test31() {

    string s = "abcdefgh";
    char buf[100];

    // copy at most 5 chars from index 2; no automatic '\0'
    size_t n = s.copy(buf, 5, 2);
    buf[n] = '\0';

    cout << n << '\n'; // 5
    cout << buf << '\n'; // cdefg

    n = s.copy(buf, 5, 6);
    buf[n] = '\0';
    cout << n << '\n'; // 2
    cout << buf << '\n'; // gh
}

void test32() {

    string s = "hello";
    const char* p = s.c_str();

    printf("%s\n", p); // hello
    printf("%s\n", s.c_str()); // hello
    printf("%zu\n", strlen(p)); // 5

    // c_str() gives a read-only pointer. Do not write through p.
}

void test33() {

    string s = "hello";
    const char* read = s.data();
    cout << read << '\n'; // hello

    // C++17: non-const string gives char*
    char* write = s.data();
    write[0] = 'H';
    cout << s << '\n'; // Hello

    cout << (s.data() == s.c_str()) << '\n'; // 1
    // Modify only indices [0, size()); do not overwrite the terminator.
}

void test34() {

    string s = "hello";
    const char* p = s.c_str();
    cout << p << '\n'; // hello

    // Force a reallocation: exceed the current capacity.
    size_t oldCapacity = s.capacity();
    s.append(oldCapacity + 1, '!');

    // The old pointer is invalid now. Obtain a new pointer before use.
    p = s.c_str();
    cout << (s.capacity() > oldCapacity) << '\n'; // 1
    cout << string(p, 5) << '\n'; // hello

    // Use the current pointer directly when passing to a C function.
    printf("%.5s\n", s.c_str()); // hello
}

void test35() {

    cout << stoi("123") << '\n'; // 123
    cout << stol("123456") << '\n'; // 123456
    cout << stoll("1234567890123") << '\n'; // 1234567890123
    cout << stoul("123456") << '\n'; // 123456
    cout << stoull("1234567890123") << '\n'; // 1234567890123

    cout << stof("3.14") << '\n'; // 3.14
    cout << stod("3.14159") << '\n'; // 3.14159
    cout << stold("3.14159") << '\n'; // 3.14159

    // No number -> invalid_argument; too large -> out_of_range.
    try {
        cout << stoi("abc") << '\n';
    } catch (const invalid_argument&) {
        cout << "invalid_argument\n";
    }

    try {
        cout << stoi("999999999999999999999999999999") << '\n';
    } catch (const out_of_range&) {
        cout << "out_of_range\n";
    }
}

void test36() {

    cout << stoi("FF", nullptr, 16) << '\n'; // 255
    cout << stoi("1010", nullptr, 2) << '\n'; // 10
    cout << stoi("17", nullptr, 8) << '\n'; // 15

    // base 0: detect the base from the prefix
    cout << stoi("0xFF", nullptr, 0) << '\n'; // 255

    size_t idx = 0;
    int x = stoi("123abc", &idx);
    cout << x << '\n'; // 123
    cout << idx << '\n'; // 3

    string s = "123abc";
    cout << s.substr(idx) << '\n'; // abc: unparsed remainder
}

void test37() {

    string a = to_string(123);
    string b = to_string(123LL);
    string c = to_string(3.14);

    cout << a << '\n'; // 123
    cout << b << '\n'; // 123
    cout << c << '\n'; // 3.140000 (C++17 ~ C++23)
    cout << (a + b) << '\n'; // 123123: string concatenation
}

void test38() {

    string a = "abc", b = "def";

    cout << a + b << '\n'; // abcdef
    cout << a + "def" << '\n'; // abcdef
    cout << "XYZ" + a << '\n'; // XYZabc
    cout << a + 'Y' << '\n'; // abcY
    cout << 'X' + a << '\n'; // Xabc

    // Two literals cannot use operator+. Make one side a string.
    cout << string("abc") + "def" << '\n'; // abcdef
    cout << "abc" "def" << '\n'; // abcdef: adjacent literals
}

void test39() {

    using namespace std::string_literals;

    auto s = "hello"s; // string
    auto p = "hello"; // const char*

    s += " world";
    cout << s << '\n'; // hello world
    cout << p << '\n'; // hello
    cout << "abc"s + "def" << '\n'; // abcdef

    // string literal suffix keeps embedded '\0' in the length
    auto withNull = "a\0b"s;
    string withoutSuffix = "a\0b";
    cout << withNull.size() << '\n'; // 3
    cout << withoutSuffix.size() << '\n'; // 1
}

void test40() {

    string s = "banana";

    // C++20: non-member erase / erase_if
#if __cplusplus >= 202002L
    auto removed = std::erase(s, 'a');
    cout << removed << '\n'; // 3
    cout << s << '\n'; // bnn

    s = "a1b2c3";
    removed = std::erase_if(s, [](unsigned char c) {
        return isdigit(c) != 0;
    });
    cout << removed << '\n'; // 3
    cout << s << '\n'; // abc
#else
    // C++17: erase-remove idiom
    auto oldSize = s.size();
    s.erase(remove(s.begin(), s.end(), 'a'), s.end());
    cout << oldSize - s.size() << '\n'; // 3
    cout << s << '\n'; // bnn

    s = "a1b2c3";
    oldSize = s.size();
    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c) != 0;
    }), s.end());
    cout << oldSize - s.size() << '\n'; // 3
    cout << s << '\n'; // abc
#endif
}

void test41() {

    string s = "caba321";

    cout << count(s.begin(), s.end(), 'a') << '\n'; // 2
    cout << count_if(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c) != 0;
    }) << '\n'; // 3

    sort(s.begin(), s.end());
    cout << s << '\n'; // 123aabc

    reverse(s.begin(), s.end());
    cout << s << '\n'; // cbaa321
}

void test42() {

    string s = "abcxdef";
    auto it = std::find(s.begin(), s.end(), 'x');

    if (it != s.end()) {
        cout << *it << '\n'; // x
        cout << distance(s.begin(), it) << '\n'; // 3
    }

    // member find -> index; std::find -> iterator
    cout << s.find('x') << '\n'; // 3
    cout << (std::find(s.begin(), s.end(), 'z') == s.end()) << '\n'; // 1
}

void test43() {

    string s = "abc1def2";
    auto it = find_if(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c) != 0;
    });

    if (it != s.end()) {
        cout << *it << '\n'; // 1 (the character)
        cout << distance(s.begin(), it) << '\n'; // 3 (the index)
    }

    // Cast to unsigned char before passing a char to <cctype> functions.
}

void test44() {

    auto isDigit = [](unsigned char c) {
        return isdigit(c) != 0;
    };

    string s = "123";
    cout << all_of(s.begin(), s.end(), isDigit) << '\n'; // 1
    cout << any_of(s.begin(), s.end(), isDigit) << '\n'; // 1
    cout << none_of(s.begin(), s.end(), isDigit) << '\n'; // 0

    s = "a1b";
    cout << all_of(s.begin(), s.end(), isDigit) << '\n'; // 0
    cout << any_of(s.begin(), s.end(), isDigit) << '\n'; // 1
    cout << none_of(s.begin(), s.end(), isDigit) << '\n'; // 0

    s.clear();
    cout << all_of(s.begin(), s.end(), isDigit) << '\n'; // 1
    cout << any_of(s.begin(), s.end(), isDigit) << '\n'; // 0
    cout << none_of(s.begin(), s.end(), isDigit) << '\n'; // 1
}

void test45() {

    string s = "banana";
    auto newEnd = remove(s.begin(), s.end(), 'a');

    cout << s.size() << '\n'; // 6: remove does not change the size
    cout << string(s.begin(), newEnd) << '\n'; // bnn
    // The characters in [newEnd, s.end()) are unspecified.

    s.erase(newEnd, s.end());
    cout << s << '\n'; // bnn
    cout << s.size() << '\n'; // 3
}

void test46() {

    string s = "a1b2c3";

    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c) != 0;
    }), s.end());
    cout << s << '\n'; // abc

    s = "a1b2c3";
#if __cplusplus >= 202002L
    // C++20: same result with erase_if
    std::erase_if(s, [](unsigned char c) {
        return isdigit(c) != 0;
    });
#else
    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c) != 0;
    }), s.end());
#endif
    cout << s << '\n'; // abc
}

void test47() {

    string s = "Hello 123!";

    // write the transformed chars back to the same string
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return static_cast<char>(toupper(c));
    });
    cout << s << '\n'; // HELLO 123!

    // write to a separate string (allocate enough space first)
    string lower(s.size(), '\0');
    transform(s.begin(), s.end(), lower.begin(), [](unsigned char c) {
        return static_cast<char>(tolower(c));
    });
    cout << lower << '\n'; // hello 123!
    cout << s << '\n'; // HELLO 123!
}

void test48() {

    string s = "aaabbbcca";

    auto newEnd = unique(s.begin(), s.end());
    s.erase(newEnd, s.end());
    cout << s << '\n'; // abca: only consecutive duplicates removed

    // remove all duplicate characters by sorting first
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    cout << s << '\n'; // abc
}

void test49() {

    string s = "abcdef";

    // make index 2 the new beginning: rotate left by 2
    rotate(s.begin(), s.begin() + 2, s.end());
    cout << s << '\n'; // cdefab

    // rotate right by 2
    rotate(s.begin(), s.end() - 2, s.end());
    cout << s << '\n'; // abcdef
}

void test50() {

    string s = "abc";

    cout << next_permutation(s.begin(), s.end()) << '\n'; // 1
    cout << s << '\n'; // acb

    cout << prev_permutation(s.begin(), s.end()) << '\n'; // 1
    cout << s << '\n'; // abc

    // all permutations in lexicographical order
    sort(s.begin(), s.end());
    do {
        cout << s << '\n'; // abc, acb, bac, bca, cab, cba
    } while (next_permutation(s.begin(), s.end()));

    cout << s << '\n'; // abc: reset when there is no next permutation
}

void test51() {

    // input: hello world
    string s;
    cin >> s;
    cout << s << '\n'; // hello: stops at whitespace

    cin >> s;
    cout << s << '\n'; // world: next token
}

void test52() {

    /* input (two lines):
    hello world
    apple,banana
    */
    string s;

    getline(cin, s);
    cout << s << '\n'; // hello world

    getline(cin, s, ',');
    cout << s << '\n'; // apple: ',' is consumed, not included

    getline(cin, s);
    cout << s << '\n'; // banana
}

void test53() {

    /* input (six lines; the last line starts with two spaces):
    3
    hello world
    3
    hello world
    3
      hello world
    */
    int n;
    string s;

    // pitfall: >> leaves the newline
    cin >> n;
    getline(cin, s);
    cout << '[' << s << "]\n"; // []
    getline(cin, s);
    cout << '[' << s << "]\n"; // [hello world]

    // discard the rest of the number's line, including '\n'
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s);
    cout << '[' << s << "]\n"; // [hello world]

    // ws also discards leading spaces and blank lines
    cin >> n;
    getline(cin >> ws, s);
    cout << '[' << s << "]\n"; // [hello world]
}

void test54() {

    // input: one space followed by A
    char c;
    if (!cin.get(c)) return;
    cout << (c == ' ') << '\n'; // 1: get reads whitespace

    if (!(cin >> c)) return;
    cout << c << '\n'; // A: >> skips whitespace
}

void test55() {

    // input: ABC
    int c = cin.peek();
    if (c == char_traits<char>::eof()) return;

    cout << static_cast<char>(c) << '\n'; // A
    cout << static_cast<char>(cin.peek()) << '\n'; // A: still not consumed

    char consumed;
    cin.get(consumed);
    cout << consumed << '\n'; // A
    cout << static_cast<char>(cin.peek()) << '\n'; // B
}

void test56() {

    /* input:
    Xhello
    discard this line
    world
    */
    string s;

    cin.ignore(); // discard only X
    getline(cin, s);
    cout << s << '\n'; // hello

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s);
    cout << s << '\n'; // world
}

void test57() {

    // Use a string stream so failure and EOF are reproducible.
    // cin has the same good(), fail(), eof(), bad(), clear() functions.
    istringstream input("abc\n42");

    cout << input.good() << '\n'; // 1
    int n = 0;
    input >> n; // cannot parse abc as an integer
    cout << input.fail() << '\n'; // 1
    cout << input.eof() << '\n'; // 0
    cout << input.bad() << '\n'; // 0

    input.clear(); // reset flags; does not discard the invalid input
    input.ignore(numeric_limits<streamsize>::max(), '\n');
    input >> n;
    cout << n << '\n'; // 42
    cout << input.eof() << '\n'; // 1: reached the end while reading 42
    cout << input.fail() << '\n'; // 0: that extraction succeeded

    input >> n;
    cout << input.fail() << '\n'; // 1: no next integer
}

void test58() {

    string s = "hello";
    char c = '!';

    cout << s << c << '\n'; // hello!
    cout << s << endl; // hello, then flush the stream
    // Prefer '\n' when flushing is unnecessary.
}

void test59() {

    // Put these at the start of main(), before any I/O.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // input: hello world
    string s;
    while (cin >> s) {
        cout << s << '\n'; // hello, world (one per line)
    }
    // Finish input with EOF. Use only cin/cout in this mode.
}

void test60() {

    string s = "hello";
    // printf("%s\n", s); // wrong: %s expects a C string pointer
    printf("%s\n", s.c_str()); // hello
}

void test61() {

    string s = "hello world";

    printf("[%s]\n", s.c_str()); // [hello world]
    printf("[%10s]\n", "hello"); // [     hello]
    printf("[%-10s]\n", "hello"); // [hello     ]
    printf("[%.5s]\n", s.c_str()); // [hello]

    int len = 5;
    printf("[%.*s]\n", len, s.c_str()); // [hello]
}

void test62() {

    // input: hello world
    char buf[100];
    // Leave one byte for '\0'. Never pass a string object to scanf %s.
    if (scanf("%99s", buf) != 1) return;

    string s = buf;
    printf("%s\n", s.c_str()); // hello
}

void test63() {

    // input: one space followed by A
    char c;

    if (scanf("%c", &c) != 1) return;
    printf("%d\n", c == ' '); // 1: %c does not skip whitespace

    if (scanf(" %c", &c) != 1) return;
    printf("%c\n", c); // A: leading space skips whitespace
}

void test64() {

    // input: abc123 hello world
    char letters[100], rest[100];

    if (scanf("%99[a-z]", letters) != 1) return;
    printf("%s\n", letters); // abc

    // Stops before '\n'; spaces are included, '\n' remains in stdin.
    if (scanf("%99[^\n]", rest) != 1) return;
    printf("%s\n", rest); // 123 hello world
    // A scanset must match at least one char to succeed.
}

void test65() {

    string s = "123 456";
    int a = 0, b = 0;

    int count = sscanf(s.c_str(), "%d %d", &a, &b);
    printf("%d\n", count); // 2: number of successful assignments
    printf("%d %d\n", a, b); // 123 456
}

void test66() {

    int x = 10;
    double y = 3.14159;
    char buf[100];

    int n = snprintf(buf, sizeof(buf), "x=%d y=%.2f", x, y);
    string s = buf;
    printf("%s\n", s.c_str()); // x=10 y=3.14
    printf("%d\n", n); // 11: required chars, excluding '\0'
}

void test67() {

    // input: hello world followed by Enter
    char buf[1000];
    if (fgets(buf, sizeof(buf), stdin) == nullptr) return;

    string s = buf;
    printf("%d\n", !s.empty() && s.back() == '\n'); // 1

    if (!s.empty() && s.back() == '\n') {
        s.pop_back();
    }
    printf("%s\n", s.c_str()); // hello world
}

void test68() {

    string s = "hello world";

    fputs(s.c_str(), stdout);
    fputs("\n", stdout); // hello world: fputs adds no newline itself
}

void test69() {

    // Echo all characters until EOF, including whitespace.
    // input: hello world (then EOF)
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    // int is needed to distinguish every byte value from EOF.
}

void test70() {

    char buf[] = "hello";
    printf("%zu\n", strlen(buf)); // 5

    string s("ab\0cd", 5);
    printf("%zu\n", s.size()); // 5: '\0' is a character in string
    printf("%zu\n", strlen(s.c_str())); // 2: stops at the first '\0'
}

void test71() {

    const char* a = "abc";
    const char* b = "abd";

    // Check the sign; the magnitude is not guaranteed.
    printf("%d\n", strcmp(a, b) < 0); // 1
    printf("%d\n", strcmp(a, a) == 0); // 1
    printf("%d\n", strcmp(b, a) > 0); // 1

    printf("%d\n", strncmp(a, b, 2) == 0); // 1: ab == ab
    printf("%d\n", strncmp(a, b, 3) < 0); // 1: abc < abd
}

void test72() {

    char dest[100];
    const char* src = "hello";

    strcpy(dest, src); // copies '\0' too; destination must be large enough
    printf("%s\n", dest); // hello

    char prefix[4];
    strncpy(prefix, src, 3);
    prefix[3] = '\0'; // strncpy did not append '\0' in this case
    printf("%s\n", prefix); // hel

    char padded[8];
    strncpy(padded, "hi", sizeof(padded)); // remaining bytes become '\0'
    printf("%s\n", padded); // hi
    printf("%d\n", padded[7] == '\0'); // 1
}

void test73() {

    char dest[100] = "hello";

    strcat(dest, " world");
    printf("%s\n", dest); // hello world

    strcpy(dest, "hello");
    strncat(dest, " world", 3); // at most 3 SOURCE chars, then '\0'
    printf("%s\n", dest); // hello wo
    // Need space for old length + appended length + 1.
}

void test74() {

    const char* s = "banana";
    const char* first = strchr(s, 'a');
    const char* last = strrchr(s, 'a');

    if (first != nullptr) printf("%td\n", first - s); // 1
    if (last != nullptr) printf("%td\n", last - s); // 5

    printf("%d\n", strchr(s, 'x') == nullptr); // 1
    // Subtract only a found pointer; never subtract nullptr.
}

void test75() {

    const char* text = "abc---abc";
    const char* pattern = "abc";
    const char* found = strstr(text, pattern);

    if (found != nullptr) {
        printf("%td\n", found - text); // 0
        printf("%s\n", found); // abc---abc: pointer into text
    }
    printf("%d\n", strstr(text, "xyz") == nullptr); // 1
}

void test76() {

    const char* s = "hello123";
    const char* found = strpbrk(s, "0123456789");

    if (found != nullptr) {
        printf("%td\n", found - s); // 5
        printf("%c\n", *found); // 1
    }
    printf("%d\n", strpbrk(s, "XYZ") == nullptr); // 1
}

void test77() {

    // length of the starting run containing ONLY characters in the set
    printf("%zu\n", strspn("12345abc", "0123456789")); // 5
    printf("%zu\n", strspn("abc123", "0123456789")); // 0
    printf("%zu\n", strspn("321123", "123")); // 6: set, not substring
}

void test78() {

    // length before the first character belonging to the set
    printf("%zu\n", strcspn("abc,def", ",")); // 3
    printf("%zu\n", strcspn("abc;def,ghi", ",;")); // 3
    printf("%zu\n", strcspn("abcdef", ",;")); // 6: none found
}

void test79() {

    // strtok modifies a writable char array, never a string literal.
    char s[] = "a,b,,c";
    char* token = strtok(s, ",");

    while (token != nullptr) {
        printf("%s\n", token); // a, b, c: empty tokens are skipped
        token = strtok(nullptr, ",");
    }

    printf("%s\n", s); // a: first delimiter was replaced with '\0'
    // strtok keeps internal state; do not interleave unrelated splits.
}

void test80() {

    // raw memory: byte counts; these functions do not stop at '\0'
    char src[] = "ab\0cd";
    char dest[sizeof(src)];
    memcpy(dest, src, sizeof(src)); // non-overlapping buffers
    printf("%d\n", memcmp(dest, src, sizeof(src)) == 0); // 1
    printf("%c\n", dest[3]); // c: copied past the embedded '\0'

    // memmove supports overlapping source/destination
    char s[10] = "abcdef";
    memmove(s + 2, s, 4);
    printf("%s\n", s); // ababcd

    char buf[5];
    memset(buf, 0, sizeof(buf));
    printf("%d\n", buf[4] == '\0'); // 1
    // memset fills bytes; memset(intArray, 1, ...) does not set each int to 1.

    const char* found = static_cast<const char*>(memchr(src, 'c', sizeof(src)));
    if (found != nullptr) printf("%td\n", found - src); // 3
}

void test81() {

    stringstream ss("10 apple 3.14");
    int x = 0;
    string word;
    double y = 0;

    ss >> x >> word >> y;
    cout << x << '\n'; // 10
    cout << word << '\n'; // apple
    cout << y << '\n'; // 3.14
}

void test82() {

    istringstream ss("10 20 30");
    int a = 0, b = 0, c = 0;

    ss >> a >> b >> c;
    cout << a << ' ' << b << ' ' << c << '\n'; // 10 20 30
}

void test83() {

    ostringstream ss;
    ss << "x=" << 10 << ", y=" << 20;

    string result = ss.str();
    cout << result << '\n'; // x=10, y=20
}

void test84() {

    stringstream ss("10 20");
    int n = 0;
    while (ss >> n) {
        cout << n << '\n'; // 10, 20
    }
    cout << ss.fail() << '\n'; // 1

    // str(newText) changes the content, but does not reset fail/eof flags.
    ss.str("30 40");
    cout << ss.fail() << '\n'; // 1

    ss.clear();
    cout << ss.str() << '\n'; // 30 40
    while (ss >> n) {
        cout << n << '\n'; // 30, 40
    }
}

void test85() {

    string s = "apple,banana,cherry";
    stringstream ss(s);
    string token;

    while (getline(ss, token, ',')) {
        cout << token << '\n'; // apple, banana, cherry
    }

    // Empty fields between delimiters are retained by getline.
    ss.clear();
    ss.str("a,,b");
    while (getline(ss, token, ',')) {
        cout << '[' << token << "]\n"; // [a], [], [b]
    }
}

void test86() {

    stringstream ss("  hello\tworld\n123  ");
    string token;

    while (ss >> token) {
        cout << token << '\n'; // hello, world, 123
    }
    // >> skips whitespace runs; no empty tokens.
}

void test87() {

    // C++17: string_view does not own or copy the characters
    string s = "hello world";
    string_view empty;
    string_view v = s;

    cout << empty.empty() << '\n'; // 1
    cout << v << '\n'; // hello world
    cout << (v.data() == s.data()) << '\n'; // 1

    s[0] = 'H'; // no reallocation: the view observes the change
    cout << v << '\n'; // Hello world
    // Keep s alive. Reallocation of s can invalidate v.
}

void test88() {

    string_view v = "hello world";

    cout << v.size() << '\n'; // 11
    cout << v.empty() << '\n'; // 0
    cout << v[1] << '\n'; // e
    cout << v.front() << '\n'; // h
    cout << v.back() << '\n'; // d

    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it;
    }
    cout << '\n'; // hello world

    cout << v.substr(6, 5) << '\n'; // world: another view
    cout << v.find("world") << '\n'; // 6
    cout << v.rfind('l') << '\n'; // 9
    cout << v.find_first_of("aeiou") << '\n'; // 1
    cout << v.find_last_of("aeiou") << '\n'; // 7
    cout << v.find_first_not_of("helo ") << '\n'; // 6
    cout << v.find_last_not_of("world") << '\n'; // 5: space
    cout << v.compare("hello world") << '\n'; // 0
    cout << *v.data() << '\n'; // h

#if __cplusplus >= 202002L
    cout << v.starts_with("hello") << '\n'; // 1 (C++20)
    cout << v.ends_with("world") << '\n'; // 1 (C++20)
#else
    cout << (v.substr(0, 5) == "hello") << '\n'; // 1
    cout << (v.substr(v.size() - 5) == "world") << '\n'; // 1
#endif
#if defined(__cpp_lib_string_contains) && __cpp_lib_string_contains >= 202011L
    cout << v.contains(' ') << '\n'; // 1 (C++23)
#else
    cout << (v.find(' ') != string_view::npos) << '\n'; // 1
#endif
    // No push_back/insert/erase/replace: a string_view cannot modify text.
}

void test89() {

    string s = "<<<hello>>";
    string_view v = s;

    v.remove_prefix(3);
    cout << v << '\n'; // hello>>

    v.remove_suffix(2);
    cout << v << '\n'; // hello
    cout << s << '\n'; // <<<hello>>: original text is unchanged

    // O(1): only changes pointer/length. Count must not exceed v.size().
}

void test90() {

    string source = "hello world";
    string_view v(source.data(), 5);

    string s(v); // copy the characters into an owning string
    source[0] = 'H';

    cout << v << '\n'; // Hello
    cout << s << '\n'; // hello: independent copy
}

void test91() {

    string s = "hello world";
    string_view v(s.data(), 5); // view ends before the space, without '\0'

    printf("[%.*s]\n", static_cast<int>(v.size()), v.data()); // [hello]
    // printf("%s", v.data()) would also print the text after this view.
    // %.*s still stops at embedded '\0'; use cout.write for arbitrary bytes.
}

void test92() {

    hash<string> h;
    string s = "hello";
    size_t x = h(s);

    cout << (x == h(string("hello"))) << '\n'; // 1
    // Exact hash values depend on the implementation; collisions are possible.

    unordered_set<string> words = {"hello", "world", "hello"};
    cout << words.size() << '\n'; // 2
    cout << words.count("hello") << '\n'; // 1

    unordered_map<string, int> counts;
    counts["hello"]++;
    counts["hello"]++;
    cout << counts["hello"] << '\n'; // 2
}

void test93() {

    vector<string> words = {"banana", "apple", "banana", "cherry"};

    set<string> ordered(words.begin(), words.end());
    for (const string& word : ordered) {
        cout << word << '\n'; // apple, banana, cherry
    }

    unordered_set<string> uniqueWords(words.begin(), words.end());
    cout << uniqueWords.size() << '\n'; // 3: iteration order is unspecified

    map<string, int> orderedCounts;
    unordered_map<string, int> counts;
    for (const string& word : words) {
        orderedCounts[word]++;
        counts[word]++;
    }

    for (const auto& [word, count] : orderedCounts) {
        cout << word << ':' << count << '\n'; // apple:1, banana:2, cherry:1
    }
    cout << counts["banana"] << '\n'; // 2
}

void test94() {

    // string has no split(), trim(), join(), or replace_all() member.
    // Build them by combining existing functions.
    stringstream ss("apple,banana,cherry");
    vector<string> words;
    string token;

    while (getline(ss, token, ',')) {
        words.push_back(token);
    }
    cout << words.size() << '\n'; // 3: split

    string joined;
    for (const string& word : words) {
        if (!joined.empty()) joined += " / ";
        joined += word;
    }
    cout << joined << '\n'; // apple / banana / cherry: join
    // trim and replace_all are practiced in test95 and test96.
}

void test95() {

    auto trimLeft = [](string& s) {
        auto pos = s.find_first_not_of(" \t\n\r");
        if (pos == string::npos) {
            s.clear();
        } else {
            s.erase(0, pos);
        }
    };

    auto trimRight = [](string& s) {
        auto pos = s.find_last_not_of(" \t\n\r");
        if (pos == string::npos) {
            s.clear();
        } else {
            s.erase(pos + 1);
        }
    };

    string s = " \t hello world \r\n";
    trimLeft(s);
    cout << (s.front() == 'h') << '\n'; // 1
    trimRight(s);
    cout << '[' << s << "]\n"; // [hello world]

    s = " \t\n\r";
    trimLeft(s);
    trimRight(s);
    cout << s.empty() << '\n'; // 1: all whitespace

    s.clear();
    trimLeft(s);
    trimRight(s);
    cout << s.empty() << '\n'; // 1: empty input is also safe
}

void test96() {

    auto replaceAll = [](string& s, const string& oldStr, const string& newStr) {
        // An empty pattern must not enter this loop.
        if (oldStr.empty()) return;

        size_t pos = 0;
        while ((pos = s.find(oldStr, pos)) != string::npos) {
            s.replace(pos, oldStr.size(), newStr);
            pos += newStr.size(); // skip the replacement text
        }
    };

    string s = "cat and cat";
    replaceAll(s, "cat", "dog");
    cout << s << '\n'; // dog and dog

    s = "aaa";
    replaceAll(s, "a", "aa");
    cout << s << '\n'; // aaaaaa: does not search inside replacements

    s = "banana";
    replaceAll(s, "a", "");
    cout << s << '\n'; // bnn: empty replacement removes matches

    replaceAll(s, "", "x");
    cout << s << '\n'; // bnn: empty pattern is ignored
}

void test97() {

    string s = "aaaa";
    string target = "aa";
    // Require a non-empty target so advancing by target.size() makes progress.
    if (target.empty()) return;

    // non-overlapping occurrences
    size_t pos = 0;
    while ((pos = s.find(target, pos)) != string::npos) {
        cout << pos << '\n'; // 0, 2
        pos += target.size();
    }

    cout << "overlapping\n";

    // overlapping occurrences
    pos = 0;
    while ((pos = s.find(target, pos)) != string::npos) {
        cout << pos << '\n'; // 0, 1, 2
        pos++;
    }
}

void test98() {

    string a = "hello"; // basic_string<char>
    basic_string<char> same = a;
    wstring b = L"hello"; // wchar_t
    u16string c = u"hello"; // char16_t
    u32string d = U"hello"; // char32_t

    cout << same << '\n'; // hello
    cout << b.size() << '\n'; // 5
    cout << c.size() << '\n'; // 5
    cout << d.size() << '\n'; // 5

#if __cplusplus >= 202002L
    u8string e = u8"hello"; // C++20: char8_t
#else
    string e = u8"hello"; // C++17: UTF-8 literals use char
#endif
    cout << e.size() << '\n'; // 5

    // UTF-8 string size counts bytes, not necessarily displayed characters.
    string utf8 = "\xEA\xB0\x80"; // UTF-8 for 가
    cout << utf8.size() << '\n'; // 3
}

void test99() {

    // C++17: choose the memory resource used by the string
    // Declare the resource before the string so it outlives the string.
    alignas(max_align_t) byte buffer[1024];
    pmr::monotonic_buffer_resource resource(buffer, sizeof(buffer));
    pmr::string s(&resource);

    s.assign(100, 'x'); // long enough to use allocated storage
    s += "hello";

    cout << s.size() << '\n'; // 105
    cout << s.substr(100) << '\n'; // hello
    cout << (s.get_allocator().resource() == &resource) << '\n'; // 1
    // Do not release/destroy the resource while s still uses its storage.
}

void test100() {

    // string = basic_string<char, char_traits<char>, allocator<char>>
    using Traits = char_traits<char>;

    cout << Traits::eq('a', 'a') << '\n'; // 1
    cout << Traits::lt('a', 'b') << '\n'; // 1
    cout << (Traits::compare("abc", "abd", 3) < 0) << '\n'; // 1
    cout << Traits::length("hello") << '\n'; // 5

    const char* text = "hello";
    const char* found = Traits::find(text, 5, 'l');
    if (found != nullptr) cout << found - text << '\n'; // 2

    // Raw character operations: terminate the result yourself.
    char buf[10] = {};
    Traits::copy(buf, "abc", 3); // non-overlapping
    cout << buf << '\n'; // abc

    Traits::move(buf + 1, buf, 3); // overlapping is allowed
    cout << buf << '\n'; // aabc

    Traits::assign(buf, 3, 'x');
    buf[3] = '\0';
    cout << buf << '\n'; // xxx

    char c = 'a';
    Traits::assign(c, 'Z');
    cout << c << '\n'; // Z

    Traits::int_type value = Traits::to_int_type('A');
    cout << Traits::to_char_type(value) << '\n'; // A
    cout << Traits::eq_int_type(Traits::eof(), Traits::eof()) << '\n'; // 1
    cout << (!Traits::eq_int_type(Traits::not_eof(Traits::eof()), Traits::eof())) << '\n'; // 1
}


int main(){

    // Choose the section to practice: test15() ~ test100().
    test15();

}
