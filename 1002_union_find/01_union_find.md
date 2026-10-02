좋아. Union-Find를 그냥 “집합 합치기”가 아니라 **그래프 위의 상대관계를 압축해서 저장하는 구조**로 설명해보자.

## 1. 기본 설정

그래프를

\[
\Gamma=(V,E)
\]

라 하자.

각 간선이 표현하는 상대관계는 어떤 군

\[
(G,\cdot)
\]

의 원소라고 하자. 항등원은 \(e\), 역원은 \(g^{-1}\).

두 정점 \(u,v\) 사이의 상대관계를

\[
\boxed{\rho(u,v)\in G}
\]

라고 정의한다.

이 관계는 경로를 따라 합성된다.

\[
\boxed{\rho(u,v)\rho(v,w)=\rho(u,w)}
\]

따라서

\[
\rho(u,u)=e
\]

이고 자연스럽게

\[
\boxed{\rho(v,u)=\rho(u,v)^{-1}}
\]

이다.

즉 한 방향의 관계를 알면 반대 방향도 유일하게 안다.

---

# 2. Union-Find가 실제로 저장하는 것

DSU의 parent를

\[
p(v)
\]

root를

\[
r(v)
\]

라고 하자.

일반 Union-Find는 사실 parent만 저장한다.

Weighted Union-Find에서는 한 가지를 더 저장한다.

\[
\boxed{\omega(v)=\rho(p(v),v)}
\]

즉 parent에서 자기 자신으로 오는 관계다.

예를 들어

\[
r\to x\to y\to v
\]

라면

\[
\omega(x)=\rho(r,x)
\]

\[
\omega(y)=\rho(x,y)
\]

\[
\omega(v)=\rho(y,v)
\]

이다.

따라서 root에서 \(v\)까지의 누적 관계를

\[
\boxed{\phi(v)=\rho(r(v),v)}
\]

라고 하면

\[
\phi(v)
=
\omega(x)\omega(y)\omega(v).
\]

\(\phi(v)\)가 사실 DSU가 캐싱하고 싶은 핵심 정보다.

---

# 3. 같은 component의 두 노드 사이 관계

\(u,v\)가 같은 root \(r\)를 가진다고 하자.

우리는

\[
\phi(u)=\rho(r,u)
\]

\[
\phi(v)=\rho(r,v)
\]

를 안다.

그러면

\[
u\to r\to v
\]

를 따라가면

\[
\rho(u,v)
=
\rho(u,r)\rho(r,v).
\]

그런데

\[
\rho(u,r)=\phi(u)^{-1}
\]

이므로

\[
\boxed{
\rho(u,v)=\phi(u)^{-1}\phi(v)
}
\]

이다.

이 식이 Weighted Union-Find의 핵심이다.

원래 그래프에서 \(u\)와 \(v\) 사이에 수천 개의 간선이 있어도, 실제 경로를 다시 탐색하지 않는다.

root에 대한 두 potential만 알면 된다.

---

# 4. `find`는 root와 potential을 동시에 계산한다

평범한 DSU에서

\[
v\to p(v)\to\cdots\to r
\]

를 따라 root를 찾는다.

Weighted DSU에서는 그와 동시에 관계도 합성한다.

현재

\[
p(v)=x
\]

이고

\[
\omega(v)=\rho(x,v)
\]

라고 하자.

재귀적으로 `find(x)`를 수행한 뒤

\[
\phi(x)=\rho(r,x)
\]

를 알게 되면

\[
\rho(r,v)
=
\rho(r,x)\rho(x,v)
\]

이므로

\[
\boxed{
\phi(v)=\phi(x)\omega(v)
}
\]

이다.

그래서 path compression을 할 때

\[
p(v)\leftarrow r
\]

로 바꾸면서 동시에

\[
\boxed{
\omega(v)\leftarrow\phi(v)
}
\]

로 바꾼다.

즉 path compression은 단순히 tree를 납작하게 만드는 게 아니라,

> 중간 좌표계를 제거하고 root 좌표계에 대한 관계를 직접 캐싱하는 것

이라고 볼 수 있다.

---

# 5. 새로운 관계가 들어온다

새 정보가

\[
\boxed{\rho(a,b)=g}
\]

라고 하자.

이것이 Weighted DSU의 `union(a,b,g)`에 해당한다.

두 경우가 있다.

---

## 경우 1: 이미 같은 component

\[
r(a)=r(b)
\]

이면 DSU는 이미 \(a\)와 \(b\) 사이 관계를 알고 있다.

그 값은

\[
\boxed{
\rho(a,b)
=
\phi(a)^{-1}\phi(b)
}
\]

이다.

따라서 새 정보 \(g\)와 비교한다.

\[
\boxed{
\phi(a)^{-1}\phi(b)\stackrel{?}{=}g
}
\]

같으면 기존 정보와 일관적이다.

다르면 contradiction이다.

즉 같은 component에 들어오는 새 edge는 **새로운 연결 정보를 주는 것이 아니라 기존 관계를 검증하는 constraint**가 된다.

---

# 6. 경우 2: 서로 다른 component

이제

\[
r_a=r(a),\qquad r_b=r(b)
\]

이고

\[
r_a\neq r_b
\]

라고 하자.

두 component 사이 관계는 아직 정의되지 않았다.

하지만 새 조건

\[
\rho(a,b)=g
\]

가 들어왔으므로 이제 두 root 사이 관계를 결정할 수 있다.

\(r_b\)를 \(r_a\) 밑에 붙인다고 하자.

필요한 값은

\[
\rho(r_a,r_b)
\]

이다.

경로를 그대로 쓰면

\[
r_a\to a\to b\to r_b
\]

이다.

각 조각은

\[
\rho(r_a,a)=\phi(a)
\]

\[
\rho(a,b)=g
\]

\[
\rho(b,r_b)=\phi(b)^{-1}.
\]

따라서

\[
\boxed{
\rho(r_a,r_b)
=
\phi(a)\,g\,\phi(b)^{-1}
}
\]

이다.

그러므로 union은

\[
\boxed{
p(r_b)=r_a
}
\]

와 동시에

\[
\boxed{
\omega(r_b)
=
\phi(a)\,g\,\phi(b)^{-1}
}
\]

를 저장하면 끝난다.

이게 generalized weighted union이다.

---

# 7. 그래서 Union-Find가 하고 있는 일

본질적으로 각 connected component마다 임의의 root를 하나 잡는다.

그 root를 component의 **원점 / 기준 좌표계**라고 생각할 수 있다.

각 노드는

\[
\boxed{\phi(v)=\rho(r,v)}
\]

를 통해 그 원점에 대한 상대좌표를 가진다.

그러면 같은 component의 두 점 사이 관계는

\[
\boxed{\rho(u,v)=\phi(u)^{-1}\phi(v)}
\]

로 바로 나온다.

즉 DSU는 원래 그래프 전체를 저장하는 것이 아니라

\[
\boxed{
\text{component마다 하나의 좌표계와
각 노드의 상대좌표만 저장한다}
}
\]

고 볼 수 있다.

---

# 8. 왜 group인가

이 구조에 필요한 성질은 정확히 다음이다.

### 합성 가능

\[
\rho(u,v)\rho(v,w)=\rho(u,w)
\]

### 결합법칙

\[
(ab)c=a(bc)
\]

그래야 path compression으로 괄호 구조가 바뀌어도 결과가 같다.

### 항등원

\[
\rho(v,v)=e
\]

### 역원

\[
\rho(v,u)=\rho(u,v)^{-1}
\]

그래야 tree edge를 어느 방향으로든 지나갈 수 있다.

따라서 **교환법칙은 필요 없다.**

\[
ab=ba
\]

일 필요는 없다.

그래서 비가환군도 가능하다.

---

# 9. Abelian group이면

만약 군이 가환군이면

\[
ab=ba
\]

이므로 덧셈 표기를 쓰는 것이 자연스럽다.

\[
(G,+)
\]

라고 하면 inverse는 \(-x\)이고,

\[
\boxed{
\rho(u,v)=-\phi(u)+\phi(v)
}
\]

이다.

union 역시

\[
\boxed{
\omega(r_b)
=
\phi(a)+g-\phi(b)
}
\]

가 된다.

우리가 처음 보았던 숫자의 차이 DSU가 바로 이것이다.

---

# 10. Parity DSU는 더 작은 특수 사례

\[
G=\mathbb Z_2
\]

이고 연산이 XOR라면

\[
x^{-1}=x
\]

이다.

따라서

\[
\boxed{
\rho(u,v)=\phi(u)\oplus\phi(v)
}
\]

가 된다.

Bipartite 문제에서

\[
\rho(u,v)=1
\]

은 “둘의 색이 다르다”는 뜻이었다.

즉

\[
\text{Parity DSU}
\subset
\text{Abelian Weighted DSU}
\subset
\text{Group-valued Weighted DSU}.
\]

---

# 11. 그래프 전체에서의 일관성

모든 constraint가 동시에 참일 수 있으려면 임의의 cycle

\[
v_0\to v_1\to\cdots\to v_k=v_0
\]

에 대해

\[
\boxed{
\rho(v_0,v_1)
\rho(v_1,v_2)
\cdots
\rho(v_{k-1},v_0)
=
e
}
\]

여야 한다.

왜냐하면 출발점으로 다시 돌아왔으므로 전체 transformation이 identity여야 하기 때문이다.

Weighted DSU는 새로운 edge가 cycle을 만들 때 바로 이 조건을 검사하는 셈이다.

---

# 12. 가장 압축하면

Union-Find의 일반형은 사실 다음 세 식으로 거의 끝난다.

\[
\boxed{
\rho(u,v)\rho(v,w)=\rho(u,w)
}
\]

\[
\boxed{
\phi(v)=\rho(r(v),v)
}
\]

\[
\boxed{
\rho(u,v)=\phi(u)^{-1}\phi(v)
}
\]

그리고 새 constraint

\[
\rho(a,b)=g
\]

가 들어오면:

\[
\boxed{
r(a)=r(b)
\Rightarrow
\phi(a)^{-1}\phi(b)\stackrel{?}{=}g
}
\]

\[
\boxed{
r(a)\neq r(b)
\Rightarrow
\omega(r_b)
=
\phi(a)g\phi(b)^{-1}
}
\]

이다.

결국 **Union-Find는 connected component를 관리하는 자료구조이고, Weighted Union-Find는 그 component 내부의 상대관계까지 root를 기준으로 캐싱하는 자료구조**다.

그리고 그 상대관계가 군을 이루기만 하면, 숫자 차이든 XOR든 회전이든 permutation이든 같은 원리로 처리할 수 있다.