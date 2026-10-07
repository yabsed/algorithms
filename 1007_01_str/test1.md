있음. 다만 **두 층으로 나눠서 생각해야** 명확해져.

1. `isdigit`, `isalpha` 같은 함수에는 **표준이 정한 의미**가 있다.
2. 실제 어떤 문자가 그 범주에 들어가는지는 일부 함수에서 **현재 locale**에 영향을 받을 수 있다.

네가 코테에서 거의 항상 보는 기본 `"C"` locale + ASCII 문자라고 생각하면 기준은 아주 명확하다.

핵심 구조는 이렇게 보면 된다.

```text
모든 ASCII 문자
│
├─ control
│    └─ iscntrl
│
└─ printable
     └─ isprint
          │
          ├─ space ' '
          │
          └─ graph
               └─ isgraph
                    │
                    ├─ alnum
                    │    ├─ alpha
                    │    │    ├─ lower
                    │    │    └─ upper
                    │    │
                    │    └─ digit
                    │
                    └─ punct
```

즉 ASCII `"C"` locale에서는 거의 다음 관계라고 보면 된다.

$$
\text{isgraph}
=
\text{isalnum}\cup\text{ispunct}
$$

그리고

$$
\text{isprint}
=
\text{isgraph}\cup\{' '\}
$$

---

### 각 함수의 정확한 의미

| 함수 | `"C"` locale에서의 기준 |
|---|---|
| `isdigit(c)` | `'0'` ~ `'9'` |
| `isalpha(c)` | `'A'` ~ `'Z'`, `'a'` ~ `'z'` |
| `isalnum(c)` | `isalpha(c) || isdigit(c)` |
| `islower(c)` | `'a'` ~ `'z'` |
| `isupper(c)` | `'A'` ~ `'Z'` |
| `isxdigit(c)` | `'0'~'9'`, `'A'~'F'`, `'a'~'f'` |
| `isspace(c)` | `' '`, `'\t'`, `'\n'`, `'\v'`, `'\f'`, `'\r'` |
| `iscntrl(c)` | 제어 문자 |
| `isprint(c)` | 화면에 출력 가능한 문자. **space 포함** |
| `isgraph(c)` | 출력 가능한 문자 중 **space 제외** |
| `ispunct(c)` | `isgraph(c)` 중 영문자/숫자가 아닌 것 |

특히 헷갈리는 셋이 이거야.

---

## `isprint` vs `isgraph`

`isprint`는 말 그대로 **printing character**.

ASCII에서는

```text
' ' ~ '~'
```

즉 ASCII 코드 32~126이다.

따라서:

```cpp
isprint(' ')   // true
isprint('A')   // true
isprint('!')   // true
isprint('\n')  // false
```

반면 `isgraph`는 **화면에 실제로 무언가 보이는 문자(graphical character)** 다.

```cpp
isgraph(' ')   // false
isgraph('A')   // true
isgraph('!')   // true
```

즉

```text
isprint = isgraph + space
```

라고 기억하면 거의 끝이다.

---

## `ispunct`

이름 때문에 "마침표나 쉼표 같은 문장부호"라고 생각하면 조금 틀린다.

정확히는:

> **출력 가능한 non-space 문자 중 alphanumeric이 아닌 것**

즉 `"C"` locale에서는

```cpp
ispunct('!')   // true
ispunct('@')   // true
ispunct('_')   // true
ispunct('#')   // true
ispunct('(')   // true

ispunct('A')   // false
ispunct('3')   // false
ispunct(' ')   // false
```

그래서 `_`나 `@`도 punctuation이다.

수식으로 보면:

$$
\boxed{
\text{ispunct}(c)
=
\text{isgraph}(c)
\land
\neg\text{isalnum}(c)
}
$$

이게 제일 명확한 정의다.

---

## `isspace`

이것도 `" "`만 뜻하지 않는다.

기본 locale에서는 정확히 6개다.

```cpp
' '   // space
'\t'  // horizontal tab
'\n'  // newline
'\v'  // vertical tab
'\f'  // form feed
'\r'  // carriage return
```

그래서 네 출력에서

```text
[\t]  isspace = Yes
[\n]  isspace = Yes
[space] isspace = Yes
```

가 나온다.

재밌는 점은:

```cpp
iscntrl('\t')  // true
isspace('\t')  // true

iscntrl('\n')  // true
isspace('\n')  // true
```

즉 **분류들은 서로 배타적이지 않다.**

이게 꽤 중요하다.

---

# `iscntrl`

ASCII에서 제어문자는 대략

```text
0x00 ~ 0x1F
0x7F
```

이다.

그래서:

```cpp
iscntrl('\n')  // true
iscntrl('\t')  // true
iscntrl('A')   // false
iscntrl(' ')   // false
```

`\n`, `\t`는 whitespace이면서 control character다.

즉

```text
space ' '
    isspace = true
    iscntrl = false
    isprint = true

'\n'
    isspace = true
    iscntrl = true
    isprint = false
```

이 차이를 이해하면 `ctype` 함수들이 상당히 정리된다.

---

# `isxdigit`은 좀 특이하다

이건 문자 분류라기보다 사실상

> hexadecimal 숫자를 구성할 수 있는 문자냐

이다.

따라서:

```text
0 1 ... 9
A B C D E F
a b c d e f
```

만 해당한다.

그래서 네 테스트에서

```text
F → Yes
G → No

f → Yes
g → No
```

가 정확하다.

---

# 전체를 집합으로 보면

ASCII `"C"` locale에서

```text
alpha
= A-Z ∪ a-z

digit
= 0-9

alnum
= alpha ∪ digit

xdigit
= 0-9 ∪ A-F ∪ a-f
```

그리고

```text
graph
= 모든 보이는 non-space 문자

punct
= graph - alnum

print
= graph ∪ {' '}
```

이다.

`space`와 `cntrl`은 조금 별도 축이다.

```text
isspace:
    ' ', \t, \n, \v, \f, \r

iscntrl:
    ASCII 0~31, 127
```

그래서 교집합이 있다.

```text
isspace ∩ iscntrl
= { \t, \n, \v, \f, \r }
```

단 `' '`만 control character가 아니다.

---

## 네 코드 기준으로 가장 중요한 그림

```text
                    isprint
        ┌────────────────────────────┐
        │                            │
        │ ' '                        │
        │                            │
        │       isgraph              │
        │ ┌────────────────────────┐ │
        │ │                        │ │
        │ │  isalnum    ispunct    │ │
        │ │ ┌────────┐             │ │
        │ │ │ alpha  │  ! @ _ ... │ │
        │ │ │ digit  │             │ │
        │ │ └────────┘             │ │
        │ └────────────────────────┘ │
        └────────────────────────────┘
```

별도로:

```text
iscntrl:
    \0 ... \t \n ... DEL

isspace:
    ' ', \t, \n, \v, \f, \r
```

라고 보면 된다.

그리고 네 코드의 이것:

```cpp
bool result = func((unsigned char) sample) != 0;
```

는 **아주 제대로 쓴 것**이다. `std::isalpha` 같은 `<cctype>` 함수에는 인자로 **`EOF` 또는 `unsigned char`로 표현 가능한 값만** 넣어야 해서, 일반 `char`를 직접 전달하면 음수 `char` 환경에서 undefined behavior가 생길 수 있다.

그래서 습관적으로

```cpp
isalpha((unsigned char)c)
```

형태로 쓰는 게 안전하다.

---

# 함수 간 관계 — 수식으로 정리

앞에서 본 것처럼 `"C"` locale + ASCII에서는 모든 ctype 함수를 서로의 조합으로 표현할 수 있다.

## 포함 관계 (합)

$$
\text{isalnum}(c)
=
\text{isalpha}(c)
\lor
\text{isdigit}(c)
$$

$$
\text{isalpha}(c)
=
\text{islower}(c)
\lor
\text{isupper}(c)
$$

$$
\text{isgraph}(c)
=
\text{isalnum}(c)
\lor
\text{ispunct}(c)
$$

$$
\text{isprint}(c)
=
\text{isgraph}(c)
\lor
(c = \text{space})
$$

## 동치 정리

$$
\boxed{
\text{ispunct}(c)
=
\text{isgraph}(c)
\land
\neg\text{isalnum}(c)
}
$$

$$
\boxed{
\text{isgraph}(c)
=
\text{isprint}(c)
\land
(c \ne \text{space})
}
$$

즉 `ispunct`, `isgraph`, `isalnum` 셋 중 둘만 알면 나머지 하나가 자동으로 따라온다.

$$
\text{isdigit}(c)
=
\text{isxdigit}(c)
\land
\neg\text{isalpha}(c)
$$

(`A`~`F`는 xdigit지만 digit가 아니므로 이렇게 분리된다.)

## ASCII에서 control과 print는 서로 여집합

$$
\text{isprint}(c)
\Longleftrightarrow
\neg\text{iscntrl}(c)
$$

$$
\text{iscntrl}(c)
\Longleftrightarrow
0 \le \text{code}(c) \le 31
\;\lor\;
\text{code}(c) = 127
$$

## 배타적 관계

$$
\text{islower}(c)
\land
\text{isupper}(c)
=
\text{false}
$$

$$
\text{isalpha}(c)
\land
\text{isdigit}(c)
=
\text{isalpha}(c)
\land
\text{ispunct}(c)
=
\text{isdigit}(c)
\land
\text{ispunct}(c)
=
\text{false}
$$

즉 `isalpha`, `isdigit`, `ispunct`는 **서로 배타적**이고, 셋의 합이 `isgraph`다.

$$
\boxed{
\text{isgraph}
=
\text{isalpha}
\;\sqcup\;
\text{isdigit}
\;\sqcup\;
\text{ispunct}
}
$$

($\sqcup$은 서로소 합집합.)

## space / cntrl 축

$$
\text{isspace}(c)
\Longleftrightarrow
c \in
\{
\text{space},
\backslash\text{t},
\backslash\text{n},
\backslash\text{v},
\backslash\text{f},
\backslash\text{r}
\}
$$

$$
\text{isspace}(c)
\land
\text{iscntrl}(c)
\Longleftrightarrow
c \in
\{
\backslash\text{t},
\backslash\text{n},
\backslash\text{v},
\backslash\text{f},
\backslash\text{r}
\}
$$

즉 space 6개 중 **공백(space)만 control이 아니다.**

$$
\text{isspace}(c)
\land
\neg\text{iscntrl}(c)
\Longleftrightarrow
c = \text{space}
$$

## 대소문자 변환과의 관계

$$
\text{islower}(c)
\Longleftrightarrow
\text{a} \le c \le \text{z}
$$

$$
\text{islower}(c)
\Longrightarrow
\text{toupper}(c) = c - 32
$$

$$
\text{isupper}(c)
\Longleftrightarrow
\text{A} \le c \le \text{Z}
$$

$$
\text{isupper}(c)
\Longrightarrow
\text{tolower}(c) = c + 32
$$

주의:

$$
\neg\text{isupper}(c)
\not\Rightarrow
\text{islower}(c)
$$

`'3'`, `'!'`처럼 둘 다 아닌 문자가 많다.

## 한눈에 보는 최종 정리

$$
\begin{aligned}
\text{isprint} &= \text{isgraph} \cup \{\text{space}\} \\
\text{isgraph} &= \text{isalnum} \;\sqcup\; \text{ispunct} \\
\text{isalnum} &= \text{isalpha} \;\sqcup\; \text{isdigit} \\
\text{isalpha} &= \text{islower} \;\sqcup\; \text{isupper}
\end{aligned}
$$

그리고 별도 축:

$$
\begin{aligned}
\text{iscntrl} &\perp \text{isprint} \quad \text{(ASCII에서 서로 여집합)} \\
\text{isxdigit} &= \text{isdigit} \;\sqcup\; \{\text{A-F},\ \text{a-f}\}
\end{aligned}
$$

이 표만 기억하면 `1.cpp`의 결과표에서 임의의 칸을 **순수 논리로** 채워넣을 수 있다.
