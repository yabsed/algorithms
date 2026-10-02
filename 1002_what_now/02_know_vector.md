# C++ `std::vector`를 이해하는 법
## 값, 참조, 복사, 소유권과 메모리

`std::vector`를 제대로 이해하려면 `push_back()` 같은 함수 목록보다 먼저 다음 질문에 답할 수 있어야 한다.

- `vector`를 다른 변수에 넣으면 복사되는가?
- 함수에 전달하면 복사되는가?
- `&`를 붙이면 무엇이 달라지는가?
- `vector<vector<int>>`의 한 행은 무엇인가?
- 한 행에 아예 다른 `vector`를 대입해도 되는가?
- shallow copy와 deep copy는 무엇인가?
- `push_back()` 이후 reference가 갑자기 위험해지는 이유는 무엇인가?
- `size()`와 `capacity()`는 왜 따로 있는가?
- `std::move`는 무엇을 움직이는가?

이 문제들은 모두 하나의 주제로 연결된다.

> **C++ 객체가 값을 어떻게 소유하고, 복사하고, 빌려주며, 언제까지 살아 있는가?**

---

# 1. `std::vector`는 무엇인가?

```cpp
vector<int> a = {10, 20, 30};
```

`vector<int>`는 크기를 실행 중에 변경할 수 있는 동적 배열이다.

개념적으로는 다음과 비슷하다.

```text
a라는 vector 객체

┌─────────────────┐
│ 데이터 위치     │───────┐
│ size = 3        │       │
│ capacity >= 3   │       │
└─────────────────┘       │
                          ▼
                    [10][20][30]
```

실제 구현이 반드시 이 모양이어야 하는 것은 아니지만 좋은 mental model이다.

중요한 것은 두 층이 있다는 것이다.

1. `vector` 객체 자체
2. `vector`가 관리하는 원소 저장공간

`vector`는 저장공간을 **소유**한다.

객체가 사라지면 자신이 관리하던 저장공간도 자동으로 해제한다.

이런 C++의 자원 관리 방식이 RAII의 대표적인 예다.

---

# 2. 원소들은 연속되어 있다

```cpp
vector<int> a = {10, 20, 30};
```

원소들은 메모리상 연속되어 있다.

```text
[10][20][30]
 ↑   ↑   ↑
 p  p+1 p+2
```

따라서

```cpp
int* p = a.data();

cout << p[0];  // 10
cout << p[1];  // 20
```

처럼 사용할 수 있다.

즉 `vector<int>`는 메모리 관점에서 일반적인 동적 배열처럼 사용할 수 있다.

그래서 C 스타일 함수에도

```cpp
f(a.data(), a.size());
```

처럼 넘길 수 있다.

---

# 3. C++의 기본은 value semantics다

다음 코드를 보자.

```cpp
vector<int> a = {1, 2, 3};
vector<int> b = a;
```

`b`가 `a`의 별명이 되는 것이 아니다.

새로운 `vector`가 만들어진다.

```text
a ───> [1][2][3]

b ───> [1][2][3]
```

저장공간도 서로 다르다.

따라서

```cpp
b[0] = 100;
```

후에도

```cpp
a[0] == 1
b[0] == 100
```

이다.

이것이 C++의 중요한 사고방식이다.

> 특별히 reference나 pointer를 사용하지 않았다면 보통 각 객체는 자기 값을 가진다.

---

# 4. Reference는 복사가 아니라 alias다

```cpp
vector<int>& b = a;
```

이번에는 새로운 `vector`가 만들어지지 않는다.

```text
a ──┐
    ├──> 하나의 vector
b ──┘
```

`b`는 `a`의 **다른 이름(alias)** 이다.

따라서

```cpp
b[0] = 100;
```

하면

```cpp
a[0] == 100
```

이다.

가장 중요한 차이는 이것이다.

```cpp
vector<int>  b = a;   // 새로운 객체
vector<int>& b = a;   // 기존 객체의 별명
```

`&` 하나가 객체의 의미를 바꾼다.

---

# 5. 함수 인자에서도 똑같다

## 값으로 받기

```cpp
void f(vector<int> v)
```

호출:

```cpp
f(a);
```

`a`를 이용해서 새로운 `v`가 만들어진다.

```text
caller              f()

a -> [1 2 3]        v -> [1 2 3]
```

`v`를 수정해도 `a`에는 영향을 주지 않는다.

---

## reference로 받기

```cpp
void f(vector<int>& v)
```

`v`는 원본의 alias다.

```cpp
v[0] = 100;
```

하면 호출자의 vector도 바뀐다.

---

## const reference로 받기

```cpp
void f(const vector<int>& v)
```

복사하지 않지만 수정도 허용하지 않는다.

그래서 큰 입력 객체를 읽기만 할 때 가장 흔한 형태다.

```cpp
int solve(const vector<int>& a);
```

정리하면:

| 형태 | 복사 | 원본 수정 |
|---|---|---|
| `vector<int> v` | O | X |
| `vector<int>& v` | X | O |
| `const vector<int>& v` | X | X |

---

# 6. 작은 타입은 그냥 값으로 넘겨도 된다

```cpp
void f(int x);
void f(double x);
```

`int`, `double`, `bool` 같은 작은 타입까지

```cpp
const int& x
```

로 받을 필요는 보통 없다.

그래서 다음과 같은 함수가 자연스럽다.

```cpp
vector<int> sliding_max(
    const vector<int>& value,
    int k
);
```

- `value`: 큰 객체 → 복사하지 않고 읽음
- `k`: 작은 값 → 그냥 복사

---

# 7. 2차원 vector의 정체

```cpp
vector<vector<int>> a;
```

이것을 진짜 2차원 배열 하나라고 생각하면 약간 틀린다.

바깥 vector의 원소 타입이

```cpp
vector<int>
```

인 것이다.

즉:

```text
outer vector

[ vector<int> ][ vector<int> ][ vector<int> ]
       │              │              │
       ▼              ▼              ▼
   [1 2 3]        [4 5 6]        [7 8 9]
```

각 행은 하나의 독립된 `vector<int>` 객체다.

그래서 행의 길이가 달라도 된다.

```cpp
vector<vector<int>> a = {
    {1, 2},
    {3, 4, 5, 6},
    {7}
};
```

이것도 완전히 정상이다.

---

# 8. 2차원 vector 전체가 하나의 연속 메모리는 아니다

다음은 틀린 mental model이다.

```text
[1][2][3][4][5][6][7][8][9]
```

`vector<vector<int>>`에서 보장되는 것은 각각의 행 내부가 연속이라는 것이다.

```text
row 0 -> [1][2][3]

row 1 -> [4][5][6]

row 2 -> [7][8][9]
```

세 행은 서로 전혀 다른 곳에 있을 수 있다.

따라서 일반적으로

```cpp
&a[0][0] + 4
```

를 이용해서 다음 행까지 넘어갈 수 있다고 생각하면 안 된다.

---

# 9. 2차원 vector를 복사하면?

```cpp
vector<vector<int>> b = a;
```

바깥 vector가 자신의 원소인 `vector<int>`들을 복사한다.

그리고 각각의 `vector<int>`도 자신의 원소를 복사한다.

결과:

```text
a
 ├── [1 2 3]
 └── [4 5 6]

b
 ├── [1 2 3]
 └── [4 5 6]
```

각 행의 저장공간까지 별개다.

따라서

```cpp
b[0][0] = 999;
```

를 해도 `a`는 변하지 않는다.

---

# 10. 한 행을 reference로 잡을 수 있다

```cpp
auto& row = a[0];
```

`auto`가 추론하는 기본 타입은 `vector<int>`이고 `&`가 붙었으므로

```cpp
vector<int>& row = a[0];
```

와 같다.

따라서

```cpp
row[0] = 100;
```

은

```cpp
a[0][0] = 100;
```

과 같다.

반대로:

```cpp
auto row = a[0];
```

라고 하면 행 전체를 복사한다.

이 차이는 매우 중요하다.

```cpp
auto  row = a[0];  // copy
auto& row = a[0];  // alias
```

---

# 11. Range-for에서도 똑같다

```cpp
for (auto row : a)
```

각 행을 복사한다.

반면

```cpp
for (auto& row : a)
```

각 행 자체를 가리킨다.

읽기만 할 것이라면:

```cpp
for (const auto& row : a)
```

가 일반적이다.

즉:

```cpp
for (const auto& x : container)
```

는 C++에서 매우 흔한 패턴이다.

> 원소를 복사하지 않고 읽겠다.

---

# 12. 한 행에 아예 다른 vector를 대입해도 된다

다음 코드가 핵심이다.

```cpp
for (auto& row : result) {
    row = sliding_max(row, k1);
}
```

`row`는

```cpp
vector<int>&
```

이다.

즉 `result` 안의 실제 `vector<int>` 객체를 가리킨다.

따라서:

```cpp
row = vector<int>{10, 20};
```

은 정상이다.

기존 행이

```text
[1 2 3 4 5]
```

였더라도

```text
[10 20]
```

으로 통째로 바뀔 수 있다.

`vector`는 고정 크기 배열이 아니다.

따라서 대입하는 vector의 크기가 같을 필요도 없다.

---

# 13. `row = sliding_max(row, k1)`에서는 무슨 일이 일어나는가?

예를 들어 현재

```text
row = [1 5 3 8 2]
```

라고 하자.

먼저

```cpp
sliding_max(row, k1)
```

가 새로운 `vector<int>` 결과를 만든다.

예:

```text
[5 8 8]
```

그리고 그것을

```cpp
row = ...
```

에 대입한다.

결과적으로 `result` 안의 해당 행이 바뀐다.

```text
before

result[i] -> [1 5 3 8 2]


after

result[i] -> [5 8 8]
```

`row`는 여전히 같은 **내부 vector 객체**를 가리킨다.

다만 그 vector가 소유하는 원소 저장공간은 바뀔 수 있다.

---

# 14. 이것이 매우 중요한 구분이다

```cpp
auto& row = result[i];
```

여기서 `row`는 `vector<int>` 객체를 가리킨다.

따라서

```cpp
row = other_vector;
```

이 실행되어도 `row`라는 reference는 살아 있다.

하지만:

```cpp
int& x = row[0];

row = other_vector;
```

이후 `x`는 위험하다.

왜냐하면 `row`의 기존 원소 저장공간은 사라졌을 가능성이 높기 때문이다.

```text
row
 │
 ▼
vector object                ← 그대로
 │
 └── old [1 2 3]
          ↑
          x

assignment

row
 │
 ▼
same vector object
 │
 └── new [7 8]

old storage destroyed
          ↑
          x  ← dangling reference
```

이 차이가 C++에서 아주 중요하다.

---

# 15. Iterator / reference invalidation

`vector`를 공부할 때 가장 중요한 함정 중 하나다.

```cpp
vector<int> v = {1,2,3};

int& x = v[0];

v.push_back(4);
```

`push_back()` 때문에 vector가 더 큰 메모리로 이동했다면:

```text
old:
[1][2][3]
 ↑
 x


new:
[1][2][3][4]
```

기존 메모리는 사라진다.

그러면 `x`는 더 이상 유효하지 않다.

이를 **reference invalidation**이라고 한다.

iterator와 pointer도 같은 문제가 발생한다.

---

# 16. 왜 vector가 이동하는가? `size`와 `capacity`

vector에는 중요한 두 숫자가 있다.

```cpp
v.size();
v.capacity();
```

예를 들어:

```text
size = 5
capacity = 8

[1][2][3][4][5][ ][ ][ ]
```

`size`는 실제 원소 개수다.

`capacity`는 현재 확보한 저장공간에 몇 개까지 넣을 수 있는지 나타낸다.

따라서

```cpp
v.push_back(6);
```

은 기존 공간을 그대로 쓸 수 있다.

하지만 capacity를 넘으면 새로운 큰 메모리를 확보해야 한다.

```text
old

[1][2][3][4]


new

[1][2][3][4][5][ ][ ][ ]
```

기존 원소들을 새 저장공간으로 옮긴 뒤 기존 저장공간을 버린다.

이것을 **reallocation**이라고 한다.

---

# 17. 그래서 `push_back()`이 amortized O(1)이다

대부분의 `push_back()`은:

```text
빈 자리 하나에 새 원소 추가
```

만 하면 되므로 \(O(1)\)이다.

가끔 capacity가 부족하면:

```text
새 메모리 확보
+
기존 n개 이동
```

때문에 \(O(n)\)이 걸린다.

하지만 이런 비싼 작업은 매번 발생하지 않는다.

전체 연산 횟수를 평균내면 원소 하나 추가당 비용이 상수 시간이 된다.

그래서:

\[
\boxed{\text{push\_back = amortized }O(1)}
\]

이라고 한다.

---

# 18. `reserve()`와 `resize()`는 전혀 다르다

```cpp
vector<int> v;

v.reserve(100);
```

이 경우:

```cpp
v.size() == 0
v.capacity() >= 100
```

이다.

원소는 하나도 없다.

단지 앞으로 100개 정도를 넣을 공간을 미리 확보한 것이다.

반면:

```cpp
v.resize(100);
```

하면 실제 원소가 100개 존재한다.

따라서:

```text
reserve = 저장공간 준비
resize  = 원소 개수 변경
```

이다.

예상 원소 개수를 알고 있고 `push_back()`을 많이 한다면:

```cpp
vector<int> result;
result.reserve(n);
```

이 효율적일 수 있다.

---

# 19. `shrink_to_fit()`

원소를 많이 지웠다고 해서 capacity가 반드시 줄어드는 것은 아니다.

```cpp
v.resize(10);
```

이어도:

```text
size = 10
capacity = 100000
```

일 수 있다.

```cpp
v.shrink_to_fit();
```

은 불필요한 capacity를 줄여달라는 요청이다.

다만 이름과 달리 표준적으로 강제 명령이라기보다는 **요청**에 가깝다.

일반적인 코테 코드에서는 거의 신경 쓸 필요가 없다.

---

# 20. 어떤 연산이 reference를 깨뜨리는가?

가장 중요한 원칙은:

> **vector 자체가 재할당되면 그 원소를 가리키던 reference, pointer, iterator는 대체로 전부 깨진다.**

예를 들어:

```cpp
auto& x = v[0];

v.push_back(...);
```

에서 reallocation이 발생하면 `x`는 무효다.

`reserve()`도 capacity를 실제로 변경하면 기존 reference들이 깨진다.

`insert()`나 `erase()`는 재할당이 없어도 원소들이 이동하기 때문에 삽입/삭제 지점 이후의 reference와 iterator가 무효화될 수 있다.

---

# 21. 2차원 vector에서는 두 층을 따로 생각해야 한다

```cpp
vector<vector<int>> a;
```

에는:

1. 바깥 vector
2. 각각의 안쪽 vector

가 있다.

따라서

```cpp
auto& row = a[0];
```

을 잡아둔 뒤

```cpp
a.push_back(...);
```

하면 바깥 vector가 재할당될 수 있다.

그러면 `row` 자체가 무효가 될 수 있다.

반면:

```cpp
row.push_back(123);
```

은 안쪽 vector만 변경한다.

이 경우 `row`라는 **vector 객체에 대한 reference**는 그대로 유효하지만, `row` 안 원소들에 대한 reference는 재할당 때문에 깨질 수 있다.

즉 invalidation에도 층이 있다.

---

# 22. 그래서 이 코드는 안전하다

```cpp
for (auto& row : result) {
    row = sliding_max(row, k1);
}
```

반복 중에 바깥 `result`에는:

```cpp
result.push_back(...)
result.erase(...)
result.resize(...)
```

같은 일을 하지 않는다.

각 `row`의 내부 내용만 바꾼다.

따라서 range-for가 사용하는 바깥 iterator와 `row` reference는 안전하다.

반대로:

```cpp
for (auto& row : result) {
    result.push_back(...);
}
```

은 위험하다.

바깥 vector가 재할당되면 현재 반복에 사용 중인 iterator/reference 자체가 깨질 수 있기 때문이다.

---

# 23. `result = transpose(result)`는?

```cpp
result = transpose(result);
```

우변의 `transpose(result)`가 새로운 2차원 vector를 만든다.

그 뒤 그것을 `result`에 대입한다.

기존 `result`의 원소들을 가리키던 reference와 iterator는 더 이상 사용해서는 안 된다.

하지만 네 코드에서는:

```cpp
result = transpose(result);

for (auto& row : result) {
    ...
}
```

처럼 대입이 끝난 **뒤에 새 reference를 생성**하므로 문제없다.

---

# 24. shallow copy와 deep copy

가장 단순한 예:

```cpp
struct A {
    int* p;
};
```

그리고:

```cpp
A b = a;
```

기본적인 멤버 복사는 pointer 값도 복사한다.

```text
a.p ──┐
      ▼
    int object
      ▲
b.p ──┘
```

두 pointer가 같은 객체를 가리킨다.

이런 형태를 흔히 **shallow copy**라고 한다.

---

# 25. Deep copy

복사하면서 가리키는 대상까지 새로 생성하면:

```text
a.p ───> int object A

b.p ───> int object B
```

가 된다.

이것을 deep copy라고 한다.

하지만 C++에서는 이 용어를 너무 단순하게 사용하면 안 된다.

더 정확한 질문은:

> **그 타입의 copy constructor / copy assignment가 무엇을 복사하도록 정의되어 있는가?**

이다.

---

# 26. `vector<int>`의 copy는 독립적인 저장공간을 만든다

```cpp
vector<int> b = a;
```

하면 각 vector가 자기 저장공간을 가진다.

따라서 흔히 `vector<int>`는 deep-copy한다고 말할 수 있다.

하지만 이것이 항상 "모든 깊이를 복제한다"는 뜻은 아니다.

---

# 27. `vector<int*>`는 다르다

```cpp
int x = 10;

vector<int*> a = {&x};
vector<int*> b = a;
```

vector 저장공간 자체는 별개다.

```text
a -> [ pointer ] ──┐
                   ▼
                  x
                   ▲
b -> [ pointer ] ──┘
```

하지만 vector의 원소가 pointer이므로 복사되는 것은 **주소값**이다.

그래서:

```cpp
*b[0] = 100;
```

하면 `a[0]`으로 봐도 100이다.

즉:

> vector는 자신의 **원소를 복사**한다.  
> 그 원소가 내부적으로 무엇을 공유하는지는 원소 타입의 semantics에 달려 있다.

이것이 가장 정확하다.

---

# 28. `vector<vector<int>>`가 독립적으로 복사되는 이유

바깥 vector의 원소는:

```cpp
vector<int>
```

이다.

바깥 vector가 복사될 때 각 `vector<int>`가 복사된다.

각 `vector<int>`는 다시 자신의 `int` 원소들을 복사한다.

그래서:

```cpp
vector<vector<int>> b = a;
```

는 결과적으로 모든 행이 독립적이다.

하지만:

```cpp
vector<vector<int*>> b = a;
```

라면 마지막 `int` 객체들은 공유될 수 있다.

---

# 29. Copy construction과 copy assignment

```cpp
vector<int> b = a;
```

는 새 객체를 만드는 중이므로 **copy construction**이다.

```cpp
vector<int> b;
b = a;
```

는 이미 존재하는 객체의 값을 바꾸므로 **copy assignment**다.

결과적으로 둘 다 독립적인 vector 내용을 만들지만 객체 생명주기 관점에서는 다른 연산이다.

---

# 30. Move semantics

```cpp
vector<int> a = {1,2,3};

vector<int> b = std::move(a);
```

복사를 한다면 원소를 새 저장공간에 복제해야 한다.

하지만 vector는 저장공간 자체를 소유하고 있으므로 그것을 `b`에게 넘길 수 있다.

개념적으로:

```text
before

a ─────> [1 2 3]


after

b ─────> [1 2 3]

a = valid but unspecified state
```

이를 **move**라고 한다.

중요:

```cpp
std::move(a)
```

자체가 데이터를 움직이는 함수는 아니다.

`a`를

> "이 객체의 자원을 가져가도 된다"

고 취급할 수 있도록 만드는 표현이다.

실제 이동은 move constructor나 move assignment가 수행한다.

---

# 31. moved-from vector는 무엇인가?

```cpp
vector<int> b = std::move(a);
```

이후 `a`는 여전히 파괴 가능한 정상 C++ 객체다.

하지만 구체적인 내용은 일반적으로 의존하면 안 된다.

즉:

> valid but unspecified state

다.

보통 구현에서는 비어 있게 되는 경우가 많지만:

```cpp
assert(a.empty());
```

같은 가정을 일반적인 move semantics 규칙으로 생각해서는 안 된다.

---

# 32. 함수에서 vector를 반환해도 된다

```cpp
vector<int> make() {
    vector<int> result;
    ...
    return result;
}
```

초보자는 흔히:

> "엄청 큰 vector 전체를 복사하지 않나?"

라고 걱정한다.

현대 C++에서는 copy elision과 move semantics 덕분에 이런 반환은 자연스럽고 효율적인 패턴이다.

따라서:

```cpp
return result;
```

라고 쓰면 된다.

괜히:

```cpp
return std::move(result);
```

라고 쓰는 것이 오히려 최적화를 방해할 수도 있다.

---

# 33. `operator[]`와 `at()`

```cpp
v[i]
```

는 범위를 검사하지 않는다.

잘못된 인덱스를 사용하면 undefined behavior가 발생할 수 있다.

반면:

```cpp
v.at(i)
```

는 범위를 확인하고 잘못되면 예외를 던진다.

코테에서는 성능과 간결성 때문에 대부분:

```cpp
v[i]
```

를 사용한다.

대신 programmer가 범위를 보장해야 한다.

---

# 34. `front()`와 `back()`

```cpp
v.front()
v.back()
```

는 각각 첫 번째와 마지막 원소를 가리킨다.

하지만 빈 vector에 사용하면 안 된다.

```cpp
if (!v.empty()) {
    cout << v.back();
}
```

처럼 사용한다.

---

# 35. Iterator란?

```cpp
vector<int>::iterator it = v.begin();
```

iterator는 container의 원소 위치를 나타내는 추상화다.

vector iterator는 random-access가 가능하다.

```cpp
it + 5
it - 2
it[3]
```

같은 연산이 된다.

그래서:

```cpp
sort(v.begin(), v.end());
```

처럼 STL algorithm과 연결된다.

vector가 contiguous container이기 때문에 iterator의 성능 특성은 pointer와 매우 비슷하다.

---

# 36. `const_iterator`

```cpp
vector<int>::const_iterator
```

를 사용하면 iterator를 통해 값을 수정할 수 없다.

보통은 직접 타입을 쓰기보다:

```cpp
for (const auto& x : v)
```

또는

```cpp
auto it = v.cbegin();
```

같이 사용한다.

---

# 37. `vector<bool>`은 특이하다

```cpp
vector<bool>
```

은 일반적인 `vector<T>`와 조금 다르다.

메모리를 절약하기 위해 bool 하나를 한 byte씩 저장하지 않고 bit 단위로 압축할 수 있도록 특별히 정의되어 있다.

따라서:

```cpp
v[0]
```

이 진짜 `bool&`가 아니라 proxy 객체일 수 있다.

대부분의 간단한 코드에서는 문제가 없지만 template이나 reference를 정교하게 다룰 때 예상치 못한 행동을 만들 수 있다.

그래서 `vector<bool>`은 `vector`의 유명한 예외다.

---

# 38. Allocator는 무엇인가?

정의가:

```cpp
template<
    class T,
    class Allocator = std::allocator<T>
>
class vector;
```

인 이유다.

Allocator는 vector가:

- 메모리를 어디서 얻고
- 어떻게 해제하며
- 그곳에 객체를 어떻게 생성할지

관리하는 추상화다.

대부분의 프로그램에서는 기본:

```cpp
std::allocator<T>
```

만 사용하기 때문에 신경 쓰지 않는다.

`std::pmr::vector` 같은 것은 메모리 자원 관리 전략을 직접 조절해야 하는 고성능 시스템에서 중요해진다.

코테에서는 거의 필요 없다.

---

# 39. `vector<T>`가 가능한지는 `T`의 성질에도 달려 있다

vector는 원소를 이동하거나 복사하거나 파괴해야 할 수 있다.

따라서 수행하려는 연산에 따라 `T`에 요구되는 능력도 달라진다.

예를 들어:

```cpp
vector<unique_ptr<int>>
```

는 가능하다.

`unique_ptr`은 move할 수 있기 때문이다.

하지만:

```cpp
auto b = a;
```

처럼 vector 전체를 복사하려 하면 문제가 생긴다.

`unique_ptr` 자체가 복사 불가능하기 때문이다.

반면:

```cpp
vector<shared_ptr<int>>
```

는 복사가 가능하고, 복사하면 pointee를 공유한다.

다시 한 번 중요한 원칙:

\[
\boxed{
\text{vector의 semantics는 원소 타입 }T\text{의 semantics 위에 만들어진다.}
}
\]

---

# 40. 네 코드에 적용하기

네 코드:

```cpp
vector<vector<int>> sliding_max_2d(
    const vector<vector<int>>& value,
    int k1,
    int k2
) {
    vector<vector<int>> result;

    for (const auto& row : value) {
        result.push_back(sliding_max(row, k2));
    }

    result = transpose(result);

    for (auto& row : result) {
        row = sliding_max(row, k1);
    }

    return transpose(result);
}
```

이제 각 줄을 정확히 읽을 수 있다.

### `const vector<vector<int>>& value`

원본 2차원 vector를 복사하지 않고 읽는다.

---

### `for (const auto& row : value)`

각 행도 복사하지 않고 읽는다.

`row`의 타입은 사실상:

```cpp
const vector<int>&
```

이다.

---

### `result.push_back(sliding_max(row, k2))`

`sliding_max()`가 새로운 vector를 반환한다.

그 결과가 `result`의 새로운 행이 된다.

---

### `result = transpose(result)`

새로운 2차원 vector를 생성한 뒤 `result`의 내용을 교체한다.

기존 `result` 내부 원소를 가리키던 reference/iterator는 더 이상 사용하면 안 된다.

---

### `for (auto& row : result)`

각 실제 행을 reference로 잡는다.

```cpp
row
```

은 복사본이 아니다.

---

### `row = sliding_max(row, k1)`

현재 행을 읽어서 새로운 vector를 만든 뒤 그 vector로 행 전체를 교체한다.

크기가 달라도 아무 문제가 없다.

---

### `return transpose(result)`

transpose된 새로운 vector를 반환한다.

현대 C++의 move/copy-elision 메커니즘 덕분에 자연스러운 코드다.

---

# 41. 네 코드에서 별도로 조심해야 할 부분

`transpose()`에는:

```cpp
int n = a.size();
int m = a[0].size();
```

가 있다.

따라서 `a`가 비어 있다면:

```cpp
a[0]
```

이 invalid access가 된다.

또한 `vector<vector<T>>`는 반드시 직사각형이라는 보장이 없다.

```cpp
{
    {1,2,3},
    {4},
    {5,6}
}
```

도 합법이다.

현재 `transpose()`는 모든 행의 길이가 `a[0].size()`와 같다고 가정한다.

즉 네 함수에는 암묵적인 precondition이 있다.

> `a`는 비어 있지 않은 rectangular matrix다.

코테에서는 문제가 이 조건을 보장한다면 충분하다.

---

# 42. 마지막 mental model

`vector`를 보면 세 층으로 생각하면 거의 모든 문제가 풀린다.

```text
C++ variable
     │
     ▼
vector object
     │
     │ owns
     ▼
element storage
     │
     ▼
T objects
```

그리고 항상 네 가지 질문을 하면 된다.

### 1. 지금 새로운 객체를 만드는가?

```cpp
vector<int> b = a;
```

→ 그렇다. copy.

### 2. 기존 객체의 별명을 만드는가?

```cpp
vector<int>& b = a;
```

→ 그렇다. reference.

### 3. 누가 메모리를 소유하는가?

`vector`가 자신의 element storage를 소유한다.

### 4. 그 객체/reference가 언제까지 유효한가?

vector가 파괴되거나, 원소 저장공간이 재할당되거나, 관련 원소가 erase되면 기존 pointer/reference/iterator가 무효가 될 수 있다.

---

# 핵심 요약

```cpp
vector<int> b = a;
```

**복사**

```cpp
vector<int>& b = a;
```

**같은 객체의 alias**

```cpp
const vector<int>& b = a;
```

**같은 객체를 읽기 전용으로 빌림**

```cpp
auto row = matrix[i];
```

**행 복사**

```cpp
auto& row = matrix[i];
```

**실제 행**

```cpp
row = another_vector;
```

**해당 행의 내용을 통째로 교체**

```cpp
vector<vector<int>> b = a;
```

**각 내부 vector도 복사되어 독립적**

```cpp
vector<int*> b = a;
```

**vector는 복사되지만 pointer가 가리키는 대상은 공유될 수 있음**

```cpp
v.push_back(...)
```

**capacity가 부족하면 reallocation → 기존 element reference/pointer/iterator가 깨질 수 있음**

```cpp
v.reserve(n);
```

**원소를 만들지 않고 capacity만 확보**

```cpp
v.resize(n);
```

**실제 size를 변경**

그리고 이 모든 것을 한 문장으로 압축하면:

\[
\boxed{
\text{C++에서는 객체는 기본적으로 자기 값을 소유하고, }
\&\text{를 사용하면 기존 객체를 참조한다.}
}
\]

`std::vector`는 이 C++의 **value semantics + ownership + lifetime**을 가장 잘 보여주는 타입 중 하나다.