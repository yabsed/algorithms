#include <bits/stdc++.h>
using namespace std;

int main() {

    // ============================================================
    // 1. cctype
    // ============================================================

    char c = 'A';

    isdigit((unsigned char)c);
    isalpha((unsigned char)c);
    isalnum((unsigned char)c);
    islower((unsigned char)c);
    isupper((unsigned char)c);
    isspace((unsigned char)c);
    ispunct((unsigned char)c);
    isxdigit((unsigned char)c);
    iscntrl((unsigned char)c);
    isprint((unsigned char)c);
    isgraph((unsigned char)c);

    c = tolower((unsigned char)c);
    c = toupper((unsigned char)c);


    // ============================================================
    // 2. construction
    // ============================================================

    string s;
    string a = "hello";
    string b("hello");
    string x(5, 'x'); // xxxxx

    string src = "abcdef";
    string p(src, 2); // cdef
    string q(src, 2, 3); // cde

    char buf[] = "abcdef";
    string r(buf);  // abcdef
    string t(buf, 3); // abc
    string u(buf + 2, 3); // cde


    // ============================================================
    // 3. string <-> vector<char>
    // ============================================================

    vector<char> v(s.begin(), s.end());
    s = string(v.begin(), v.end());

    // ============================================================
    // 4. copy / move
    // ============================================================

    string original(1000, 'x');

    string copy = original; // deep copy
    string moved = move(original); // original: valid but unspecified

    // ============================================================
    // 5. size / capacity
    // ============================================================

    s.size();
    s.length();
    s.empty();

    s.capacity();
    s.reserve(1000);
    s.shrink_to_fit();

    s.resize(10); // 새 char는 '\0'
    s.resize(20, 'x');
    s.clear();


    // ============================================================
    // 6. access
    // ============================================================

    s = "hello";

    s[1];
    s.at(1); // bounds check
    s.front();
    s.back();

    s.front() = 'H';

    // ============================================================
    // 7. iterator
    // ============================================================

    for (char c : s)
        cout << c;

    for (char& c : s)
        c = toupper((unsigned char)c);

    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());

    // ============================================================
    // 8. append
    // ============================================================

    s.clear();

    s += "abc";
    s += 'x';

    s.append("abcdef"); // abcdef
    s.append("abcdef", 2, 3); // cde
    s.append(buf, 3); // abc
    s.append(5, 'x'); // xxxxx
    s.append(v.begin(), v.end());

    s.push_back('!');
    s.pop_back();

    // ============================================================
    // 9. assign
    // ============================================================

    s.assign("abcdef");
    s.assign(src, 2, 3);                // cde
    s.assign(buf, 3);                   // abc
    s.assign(buf + 2, 3);               // cde
    s.assign(v.begin(), v.end());
    s.assign(5, 'x');                   // xxxxx

    // ============================================================
    // 10. insert / erase
    // ============================================================

    s = "abcdef";

    s.insert(2, "XX"); // abXXcdef

    s.erase(2, 2); // abcdef
    s.erase(s.begin());
    s.erase(s.begin(), s.begin() + 2);


    // ============================================================
    // 11. common idiom
    // ============================================================

    s = "ddddaaaaabbbc";

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    cout << s << '\n'; // abcd
}