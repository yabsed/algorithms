된다. 오히려 **Segment Tree의 본질을 이해하기 아주 좋은 예**다.

문자열 concatenation을 연산

\[
a\circ b = a+b
\]

라고 하면,

\[
(a\circ b)\circ c = a\circ(b\circ c)
\]

이므로 **결합법칙**이 성립한다. 항등원도 빈 문자열

\[
e=""
\]

이므로

\[
(\text{String},\circ,e)
\]

는 monoid다. 따라서 Segment Tree를 만들 수 있다.

예를 들어

\[
[a,b,c,d,e]
\]

라면

\[
\text{tree}[root] = abcde
\]

이고 각 노드는 정확히

\[
\boxed{\text{node}=\text{left child}\circ\text{right child}}
\]

로 만든다.

중요한 점은 concat은 **교환법칙이 성립하지 않는다**는 것이다.

\[
ab\neq ba
\]

그래서 iterative 2N segment tree에서 query할 때 순서를 보존해야 한다.

```cpp
string query(int l, int r) { // [l, r)
    string left = "";
    string right = "";

    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            left = left + tree[l++];

        if (r & 1)
            right = tree[--r] + right;
    }

    return left + right;
}
```

왜 오른쪽은

```cpp
right = tree[--r] + right;
```

인가가 핵심이다. 오른쪽에서 뽑혀 나오는 노드는 **오른쪽 → 왼쪽 순서로 발견**되기 때문이다. 최종 문자열 순서는

\[
L_1L_2\cdots L_kR_k\cdots R_2R_1
\]

이어야 한다.

즉 Segment Tree는 사실

\[
\boxed{\text{commutative 연산용 자료구조가 아니라 associative 연산용 자료구조}}
\]

다.

그래서 다음도 전부 가능하다.

\[
\begin{aligned}
\min &: \text{associative}\\
\max &: \text{associative}\\
+ &: \text{associative}\\
\gcd &: \text{associative}\\
\text{matrix multiplication} &: \text{associative, noncommutative}\\
\text{string concat} &: \text{associative, noncommutative}
\end{aligned}
\]

다만 **실제로 문자열 자체를 저장하는 Segment Tree는 대개 비효율적**이다. 문자열을 복사해야 하므로 노드 연산이 \(O(1)\)이 아니기 때문이다. 전체 저장 문자 수도

\[
\boxed{O(n\log n)}
\]

이고, point update도 위로 올라가며 긴 문자열들을 다시 만들기 때문에 최악에는 \(O(n)\)에 가깝다.

그래서 코테에서는 문자열 자체보다 보통 **문자열의 요약값**을 Segment Tree에 넣는다. 예를 들어 hash, 문자 빈도, 괄호 정보, DFA 상태 변환 등이 대표적이다.

하지만 수학적으로는:

\[
\boxed{\text{String Concatenation은 완벽한 Segment Tree 연산이다.}}
\]

그리고 **교환법칙이 없는 Segment Tree query가 왜 left/right accumulator를 따로 가져야 하는지** 보여주는 가장 좋은 예 중 하나다.

---

본질은 거의 이것 하나다.

\[
\boxed{\text{구간의 정보를, 결합법칙이 성립하는 연산으로 합칠 수 있느냐}}
\]

즉 Segment Tree가 다루는 대상은 사실 “숫자”가 아니다. 어떤 집합 \(S\)와 연산

\[
\star:S\times S\to S
\]

가 있어서

\[
(a\star b)\star c=a\star(b\star c)
\]

만 성립하면 된다.

이때 배열의 각 원소를 \(S\)의 원소라고 보고, 구간

\[
[l,r)
\]

의 값을

\[
a_l\star a_{l+1}\star\cdots\star a_{r-1}
\]

로 정의한다.

Segment Tree는 이 값을 빠르게 계산하는 자료구조다.

---

문자열이 되는 이유도 정확히 이것이다.

\[
S=\{\text{모든 문자열}\}
\]

\[
x\star y = xy
\]

라고 하면

\[
(ab)c=a(bc)
\]

이므로 결합법칙이 성립한다.

따라서

\[
\boxed{\text{문자열도 Segment Tree의 대상}}
\]

이다.

중요한 건 **교환법칙은 필요 없다는 것**이다.

\[
a\star b=b\star a
\]

일 필요가 없다.

그래서 문자열 concatenation도 되고,

\[
AB\neq BA
\]

인 행렬곱도 되고,

\[
f\circ g\neq g\circ f
\]

인 함수 합성도 된다.

---

조금 더 수학적으로 말하면 Segment Tree는 보통 **monoid의 range product**를 계산한다.

\[
\boxed{(S,\star,e)}
\]

여기서

1. 닫힘
   \[
   a,b\in S\Rightarrow a\star b\in S
   \]

2. 결합법칙
   \[
   (a\star b)\star c=a\star(b\star c)
   \]

3. 항등원
   \[
   e\star a=a\star e=a
   \]

이 있으면 monoid다.

항등원은 query에서 “아무것도 없는 구간”을 처리하기 위해 편하다.

예를 들면:

\[
\begin{array}{c|c|c}
S & \star & e\\
\hline
\mathbb Z & + & 0\\
\mathbb Z & \min & +\infty\\
\mathbb Z & \max & -\infty\\
\mathbb Z & \gcd & 0\\
\text{string} & \text{concat} & ""\\
\text{matrix} & \times & I\\
\text{functions} & \circ & \mathrm{id}
\end{array}
\]

전부 Segment Tree가 된다.

---

그런데 더 깊은 핵심은 이거다.

Segment Tree는 원래 배열의 원소를 저장하는 게 아니라,

\[
\boxed{\text{구간에 대한 summary}}
\]

를 저장한다.

예를 들어 괄호 문자열이라면 노드 하나가 단순한 문자 하나가 아니라

\[
(\text{unmatched open},\text{unmatched close})
\]

를 저장할 수도 있다.

두 구간의 summary가

\[
A=(o_1,c_1),\qquad B=(o_2,c_2)
\]

라면 경계에서

\[
m=\min(o_1,c_2)
\]

만큼 매칭시키고

\[
A\star B
=
(o_1+o_2-m,\;c_1+c_2-m)
\]

처럼 합칠 수 있다.

이렇게 하면 문자열 전체를 저장하지 않고도 구간이 올바른 괄호열인지 등을 판단할 수 있다.

즉 원소가 문자열이냐 숫자냐는 별로 중요하지 않다.

중요한 건

\[
\boxed{
\text{summary}(A+B)
=
\text{summary}(A)\star\text{summary}(B)
}
\]

를 만들 수 있느냐이다.

---

이게 Segment Tree를 바라보는 가장 일반적인 관점이다.

배열의 연속 구간을

\[
A=A_1A_2\cdots A_k
\]

라고 할 때, 어떤 함수 \(F\)가 있고

\[
\boxed{
F(XY)=F(X)\star F(Y)
}
\]

가 성립하면, Segment Tree에 \(F\)를 저장할 수 있다.

예를 들어 문자열 \(s\)에 대해:

- 길이
  \[
  F(s)=|s|
  \]

- 문자 빈도 벡터
  \[
  F(s)=(c_a,c_b,\ldots,c_z)
  \]

- rolling hash

- 괄호 matching 상태

- finite automaton을 통과시켰을 때의 상태 변환

등을 저장할 수 있다.

특히 마지막은 꽤 강력하다. 문자열 조각 하나를 단순한 문자열이 아니라

\[
f:S_{\text{state}}\to S_{\text{state}}
\]

라는 **상태 변환 함수**로 볼 수 있다.

그러면 두 문자열 \(XY\)의 효과는

\[
f_{XY}=f_Y\circ f_X
\]

이다.

함수 합성은 결합법칙이 있으므로 Segment Tree가 된다.

그래서 꽤 복잡한 문자열 문제도 사실

\[
\boxed{\text{구간을 함수로 압축하고, 함수 합성을 Segment Tree로 한다}}
\]

로 바뀔 수 있다.

---

반대로 Segment Tree가 직접 처리하기 어려운 것은

\[
\boxed{\text{두 구간의 답만 보고 합친 구간의 답을 결정할 수 없는 것}}
\]

이다.

예를 들어 어떤 정보 \(F\)를 저장한다고 했는데

\[
F(X),F(Y)
\]

만으로

\[
F(XY)
\]

를 구할 수 없다면 그 정보만 가지고는 Segment Tree를 만들 수 없다.

그러면 summary를 더 풍부하게 만들어야 한다.

예를 들어 maximum subarray sum은 단순히

\[
\max(X),\max(Y)
\]

만 저장해서는 안 된다.

그래서 노드에

\[
(\text{sum},\text{prefix max},\text{suffix max},\text{best})
\]

를 저장한다.

그러면 두 노드만 보고 부모를 계산할 수 있다.

이게 중요한 사고방식이다.

\[
\boxed{
\text{“이 문제에 Segment Tree를 쓸 수 있나?”}
}
\]

라는 질문은 사실

\[
\boxed{
\text{“구간을 어떤 유한한 summary로 압축하면,
두 summary를 associative하게 merge할 수 있나?”}
}
\]

라는 질문이다.

그래서 Segment Tree의 본질을 한 문장으로 줄이면:

\[
\boxed{
\text{Segment Tree}
=
\text{associative interval summarization}
}
\]

혹은 더 수학적으로:

\[
\boxed{
\text{Segment Tree는 배열 위의 monoid product를 빠르게 계산하는 자료구조다.}
}
\]

문자열 concatenation이 된다는 사실이 바로 “Segment Tree는 숫자 자료구조가 아니다”라는 걸 가장 잘 보여준다.