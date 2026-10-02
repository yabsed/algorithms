# Segment Tree의 두 가지 대표적 구성 방식

Segment Tree의 본질은 단순하다.

배열의 어떤 구간 \([l,r]\)을 둘로 나누고, 두 자식의 정보를 합쳐 부모의 정보를 만든다.

\[
m=\left\lfloor\frac{l+r}{2}\right\rfloor
\]

\[
[l,r]
=
[l,m]\sqcup[m+1,r]
\]

그리고 어떤 결합 연산 \(\circ\)에 대해

\[
T_{[l,r]}
=
T_{[l,m]}
\circ
T_{[m+1,r]}
\]

를 저장한다.

따라서 Segment Tree의 본질은

\[
\boxed{
\text{hierarchical interval decomposition}
+
\text{aggregation}
}
\]

이다.

그런데 실제 트리를 구성할 때는 두 가지 대표적인 선택이 있다.

\[
\boxed{
\text{Power-of-two regularization}
\quad\text{vs}\quad
\text{Exact-}n\text{ decomposition}
}
\]

차이는 의외로 작다.

**트리를 처음 어떻게 구성하느냐가 다를 뿐, 일단 만들어진 뒤의 search와 update 논리는 거의 같다.**

---

# 1. Power-of-two로 맞추는 방법

실제 원소의 개수를 \(n\)이라 하자.

먼저

\[
N
=
2^{\lceil\log_2 n\rceil}
\]

을 잡는다.

즉

\[
N=\min\{2^k\mid 2^k\ge n\}
\]

이다.

그리고 실제 배열 \([0,n-1]\)을

\[
[0,N-1]
\]

까지 확장한다.

부족한

\[
[n,N-1]
\]

에는 결합 연산의 항등원 \(e\)를 넣는다.

예를 들어 \(n=5\)라면 \(N=8\)이다.

```text
                         [0,7]
                    /             \
                [0,3]             [4,7]
               /     \           /     \
           [0,1]     [2,3]   [4,5]     [6,7]
           /  \       /  \     / \       / \
         [0] [1]    [2] [3]  [4] [5]   [6] [7]

          a0  a1     a2  a3   a4  e     e   e
```

이 트리의 가장 큰 특징은 모든 구간의 길이가 2의 거듭제곱이라는 것이다.

\[
|[l,r]|=r-l+1=2^k
\]

따라서 모든 분할은 정확히

\[
\boxed{
2^k
\rightarrow
2^{k-1}+2^{k-1}
}
\]

이다.

예를 들어

\[
8\to4+4,
\qquad
4\to2+2,
\qquad
2\to1+1
\]

이다.

그래서 모든 형제는 같은 크기를 갖고, 모든 leaf는 같은 깊이에 도달한다.

\[
\boxed{\text{perfect binary tree}}
\]

가 만들어진다.

---

# 2. Exact-\(n\)으로 만드는 방법

굳이 2의 거듭제곱으로 늘리지 않고 실제 구간

\[
[0,n-1]
\]

을 그대로 root로 삼을 수도 있다.

분할 규칙은 전혀 달라지지 않는다.

\[
m=\left\lfloor\frac{l+r}{2}\right\rfloor
\]

\[
[l,r]
\rightarrow
[l,m],\ [m+1,r]
\]

이다.

예를 들어 \(n=5\)라면:

```text
                     [0,4]
                   /       \
               [0,2]       [3,4]
               /   \        /   \
           [0,1]   [2]    [3]   [4]
           /   \
         [0]   [1]
```

root의 길이는 \(5\)이다.

따라서 첫 분할은

\[
5\rightarrow3+2
\]

이다.

다시 길이 \(3\)인 구간은

\[
3\rightarrow2+1
\]

로 갈라진다.

일반적으로 구간 길이를

\[
s=r-l+1
\]

이라 하면

\[
\boxed{
s
\rightarrow
\left\lceil\frac{s}{2}\right\rceil
+
\left\lfloor\frac{s}{2}\right\rfloor
}
\]

이다.

즉 가능한 한 절반으로 자르되, \(s\)가 홀수라면 한쪽이 하나 더 크다.

따라서 트리는 여전히 균형 잡혀 있지만 perfect하지는 않다.

\[
\boxed{\text{balanced, but not perfect}}
\]

어떤 leaf는 다른 leaf보다 한 단계 먼저 끝날 수 있다.

---

# 3. 구조적으로 무엇이 다른가

차이는 이것뿐이다.

### Power-of-two

모든 분할이

\[
\boxed{2k\rightarrow k+k}
\]

이다.

따라서

- 모든 형제의 구간 길이가 같다.
- 같은 depth의 모든 구간 길이가 같다.
- 모든 leaf의 depth가 같다.

### Exact-\(n\)

분할이

\[
\boxed{
s
\rightarrow
\left\lceil\frac{s}{2}\right\rceil
+
\left\lfloor\frac{s}{2}\right\rfloor
}
\]

이다.

따라서

- 형제의 크기가 \(1\) 차이날 수 있다.
- 같은 depth에서도 구간 길이가 다를 수 있다.
- leaf depth가 다를 수 있다.

하지만 두 방식 모두 중요한 성질은 그대로 유지한다.

\[
\boxed{
node\leftrightarrow[l,r]
}
\]

모든 node는 정확히 하나의 연속 구간을 나타내며,

\[
[l,r]
=
[l,m]\sqcup[m+1,r]
\]

가 항상 성립한다.

즉 둘 다 완전히 정상적인 Segment Tree다.

---

# 4. Construction에서 차이가 커진다

논리적 차이는 작지만, 트리를 배열에 저장하려고 하면 power-of-two의 규칙성이 큰 이점을 준다.

## Power-of-two

root가

\[
[0,N-1]
\]

이고 \(N=2^k\)이므로 모든 leaf가 정확히 같은 depth에 있다.

heap-style indexing을 사용하면 leaf들이 정확히

\[
\boxed{[N,2N)}
\]

에 모인다.

따라서

\[
tree[N+i]=a_i
\]

라고 바로 놓을 수 있다.

padding에는 항등원 \(e\)를 넣는다.

그다음 부모를 역순으로 계산하면 된다.

```cpp
for (int i = 0; i < n; i++)
    tree[N + i] = value[i];

for (int i = n; i < N; i++)
    tree[N + i] = ID;

for (int i = N - 1; i >= 1; i--)
    tree[i] = op(tree[2*i], tree[2*i+1]);
```

즉

\[
\boxed{\text{leaf layer를 직접 채우고 아래에서 위로 한 번에 계산}}
\]

할 수 있다.

Build는

\[
O(N)=O(n)
\]

이다.

---

## Exact-\(n\)

Exact-\(n\)에서는 leaf들이 같은 depth에 있지 않다.

\(n=5\)라면:

```text
                 1:[0,4]
               /         \
          2:[0,2]       3:[3,4]
          /    \         /    \
     4:[0,1] 5:[2]   6:[3]  7:[4]
       / \
   8:[0] 9:[1]
```

실제 원소의 leaf는

\[
8,9,5,6,7
\]

처럼 흩어진다.

따라서

\[
tree[base+i]=a_i
\]

와 같은 단순한 공식은 존재하지 않는다.

그래서 보통 직접 구간을 따라 내려간다.

```cpp
void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = value[l];
        return;
    }

    int m = (l + r) / 2;

    build(2*node, l, m);
    build(2*node+1, m+1, r);

    tree[node]
        = op(tree[2*node], tree[2*node+1]);
}
```

최초 호출은

```cpp
build(1, 0, n - 1);
```

이다.

이 경우 heap indexing에는 빈 위치가 생길 수 있으므로 흔히

\[
\boxed{4n}
\]

정도의 배열을 잡는다.

---

# 5. 중요한 점: Power-of-two도 재귀로 만들 수 있다

여기서 혼동하면 안 되는 것이 있다.

Power-of-two와 recursion은 반대 개념이 아니다.

Power-of-two tree 역시 그냥

```cpp
build(1, 0, N - 1);
```

로 만들 수 있다.

Exact-\(n\)과 완전히 같은 재귀 코드를 사용할 수 있다.

차이는 최초 root가

\[
[0,N-1]
\]

이냐

\[
[0,n-1]
\]

이냐뿐이다.

Power-of-two의 특별한 점은 재귀가 필요 없다는 것이 아니라,

\[
\boxed{
\text{perfect tree이기 때문에 훨씬 단순한 bottom-up construction도 가능하다}
}
\]

는 것이다.

---

# 6. 그런데 Search는 두 방식이 같다

트리가 일단 만들어지고 나면 power-of-two인지 exact-\(n\)인지는 거의 중요하지 않다.

현재 node가

\[
[l,r]
\]

를 담당하고 query가

\[
[q_l,q_r]
\]

라고 하자.

## 겹치지 않는 경우

\[
r<q_l
\quad\text{or}\quad
q_r<l
\]

이면 항등원을 반환한다.

## 완전히 포함되는 경우

\[
q_l\le l
\quad\text{and}\quad
r\le q_r
\]

이면

\[
tree[node]
\]

를 그대로 반환한다.

## 일부만 겹치는 경우

\[
m=\left\lfloor\frac{l+r}{2}\right\rfloor
\]

을 계산하고 두 자식을 탐색한다.

```cpp
return op(
    query(2*node, l, m, ql, qr),
    query(2*node+1, m+1, r, ql, qr)
);
```

Power-of-two에서는 최초 호출이

```cpp
query(1, 0, N - 1, ql, qr);
```

이고,

Exact-\(n\)에서는

```cpp
query(1, 0, n - 1, ql, qr);
```

인 것만 다르다.

그 이후 논리는 완전히 같다.

\[
\boxed{
\text{Search는 tree가 perfect인지 아닌지 신경 쓰지 않는다.}
}
\]

필요한 것은 오직 현재 node가 정확한 \([l,r]\)을 나타낸다는 사실이다.

---

# 7. Point Update도 같다

위치 \(p\)를 값 \(x\)로 바꾼다고 하자.

현재 구간이

\[
[l,r]
\]

이면:

- \(l=r\)이면 leaf이므로 수정한다.
- 아니면 \(m=(l+r)/2\)를 계산한다.
- \(p\le m\)이면 왼쪽으로 간다.
- 아니면 오른쪽으로 간다.
- 돌아오면서 부모를 다시 계산한다.

```cpp
void update(int node, int l, int r, int p, int x) {
    if (l == r) {
        tree[node] = x;
        return;
    }

    int m = (l + r) / 2;

    if (p <= m)
        update(2*node, l, m, p, x);
    else
        update(2*node+1, m+1, r, p, x);

    tree[node]
        = op(tree[2*node], tree[2*node+1]);
}
```

역시 최초 호출만 다르다.

\[
[0,N-1]
\quad\text{vs}\quad
[0,n-1]
\]

이다.

---

# 8. Lazy Propagation도 같다

Lazy Propagation 역시 tree가 perfect인지 아닌지를 본질적으로 신경 쓰지 않는다.

현재 구간이

\[
[l,r]
\]

이라는 사실만 알면 된다.

```text
no overlap
    → return

full overlap
    → apply

partial overlap
    → push
    → update left
    → update right
    → pull
```

구간의 길이가 필요하면

\[
r-l+1
\]

을 계산하면 된다.

자식도 항상

\[
[l,m],
\qquad
[m+1,r]
\]

이다.

따라서

\[
\boxed{
\text{Power-of-two 여부는 lazy propagation의 논리와 무관하다.}
}
\]

---

# 9. 결국 어디에서 차이가 나는가

두 구조를 재귀적으로 다룬다면 search와 update는 사실상 같은 알고리즘이다.

차이는 construction과 representation의 규칙성에서 나타난다.

| | Power-of-two | Exact-\(n\) |
|---|---|---|
| root | \([0,N-1]\) | \([0,n-1]\) |
| 구간 길이 | 항상 \(2^k\) | 임의의 자연수 |
| 분할 | 정확한 \(1:1\) | 최대한 \(1:1\) |
| tree 형태 | perfect | balanced |
| leaf depth | 동일 | 다를 수 있음 |
| leaf 위치 | \([N,2N)\) | 흩어짐 |
| padding | 필요 | 없음 |
| 단순 bottom-up build | 가능 | 일반적으로 불가능 |
| recursive build | 가능 | 가능 |
| recursive query | 동일 | 동일 |
| recursive update | 동일 | 동일 |
| lazy | 동일 | 동일 |

---

# 10. Power-of-two가 주는 진짜 이점

Power-of-two로 맞춘다고 Segment Tree의 search 능력이 강해지는 것은 아니다.

Update가 더 본질적으로 쉬워지는 것도 아니다.

Lazy propagation이 가능해지는 것도 아니다.

그 모든 것은 exact-\(n\) tree에서도 동일하게 가능하다.

Power-of-two regularization이 주는 진짜 이점은

\[
\boxed{
\text{tree shape을 완전히 규칙적으로 만든다}
}
\]

는 것이다.

그 결과

\[
\boxed{
\text{모든 leaf가 }[N,2N)\text{에 모인다}
}
\]

라는 강한 성질을 얻는다.

따라서

\[
\boxed{
\text{fixed leaf position}
+
\text{simple bottom-up construction}
+
\text{perfect-tree geometry}
}
\]

를 얻는다.

그 대가로

\[
N-n
\]

개의 padding을 둔다.

Exact-\(n\)은 반대로 padding을 하지 않는다.

실제 데이터의 크기를 그대로 보존하는 대신 tree의 모양이 약간 불규칙해진다.

---

# 결론

두 방식의 논리적 차이는 생각보다 작다.

Power-of-two 방식은

\[
\boxed{
[0,n-1]
\longrightarrow
[0,N-1]
}
\]

로 domain을 확장하여 모든 분할을

\[
2k\rightarrow k+k
\]

로 만든다.

Exact-\(n\) 방식은 실제 domain을 그대로 두고

\[
s
\rightarrow
\left\lceil\frac{s}{2}\right\rceil
+
\left\lfloor\frac{s}{2}\right\rfloor
\]

로 나눈다.

그 결과 전자는 perfect tree가 되고 후자는 balanced tree가 된다.

하지만 두 구조 모두

\[
\boxed{
node\leftrightarrow[l,r]
}
\]

이라는 동일한 구간 구조를 유지한다.

그래서 일단 construction이 끝나면

\[
\boxed{
\text{Search}
,\quad
\text{Point Update}
,\quad
\text{Lazy Propagation}
}
\]

의 재귀 논리는 거의 동일하다.

결국 가장 중요한 차이는 이것이다.

\[
\boxed{
\begin{aligned}
\text{Power-of-two}
&:\quad
\text{padding을 지불하고 구조의 규칙성을 얻는다}\\[2mm]
\text{Exact-}n
&:\quad
\text{padding 없이 실제 크기를 유지하고 약간의 구조적 불규칙성을 받아들인다}
\end{aligned}
}
\]

그리고 그 규칙성이 주는 가장 실질적인 보너스가 바로

\[
\boxed{
\text{leaf를 }[N,2N)\text{에 직접 놓고 bottom-up으로 construct할 수 있다는 것}
}
\]

이다.