좋아. 지금까지 본 세 문제를 하나의 틀로 묶으면 이거야.

\[
\boxed{\text{DFS를 하면서 }disc\text{와 }low\text{를 구하고, low가 경계를 알려준다}}
\]

세 문제는:

1. 무방향 그래프의 **bridge**
2. 무방향 그래프의 **articulation point / vertex-biconnected component**
3. 방향 그래프의 **SCC**

이 셋이다.

공통 출발점부터 보자.

`disc[v]`는

> DFS에서 `v`를 몇 번째로 발견했는가

이고,

`low[v]`는 대충

> `v` 아래쪽에서 DFS tree를 따라 내려갔다가, 다른 간선을 이용해서 얼마나 옛날 정점까지 돌아갈 수 있는가

를 나타낸다.

즉 모든 문제에서 질문은 비슷하다.

```text
v 아래쪽 세계가
v보다 위쪽 세계와
얼마나 연결되어 있나?
```

---

## 1. Bridge 찾기

무방향 그래프.

부모 `v`, DFS 자식 `u`가 있다고 하자.

```text
    ... 조상
       |
       v
       |
       u
      / \
   subtree
```

`u` 쪽에서 위로 돌아가는 우회로가 있다면

\[
low[u] \le disc[v]
\]

이다.

그런데

\[
\boxed{low[u] > disc[v]}
\]

라면?

`u` subtree에서는 `v`조차도 다른 길로 못 돌아온다는 뜻이다.

즉 `v-u`가 유일한 연결이다.

따라서

\[
\boxed{low[u] > disc[v] \Rightarrow (v,u)\text{는 bridge}}
\]

이게 첫 번째 문제.

그리고 bridge를 다 제거하면 남은 connected components가 2-edge-connected components다.

---

## 2. Articulation point / Vertex-BCC

이것도 무방향 그래프다.

이번에는 간선 하나가 아니라 **정점 `v`를 없앴을 때 갈라지는가**를 본다.

부모 `v`, 자식 `u`에 대해

\[
\boxed{low[u] \ge disc[v]}
\]

라면 `u` subtree는 `v`보다 위의 조상으로 갈 수 없다.

중요한 건 `=`도 포함된다는 거야.

예를 들어

```text
u subtree → ... → v
```

까지는 돌아올 수 있어도 `v`보다 위에는 못 간다면,

`v`를 삭제하는 순간 그 길도 사라진다.

그래서 일반 정점에 대해

\[
\boxed{low[u] \ge disc[v]}
\]

인 자식이 하나라도 있으면 `v`는 articulation point다.

단 DFS root는 별도:

\[
\boxed{\text{root의 DFS child 수} \ge 2}
\]

이면 articulation point.

그리고 **vertex-biconnected component 자체를 구하려면 edge stack**을 쓴다.

DFS하면서 간선을 stack에 넣고,

\[
low[u] \ge disc[v]
\]

가 되는 순간 `(v,u)`까지 pop하면 하나의 BCC다.

즉 두 번째 문제는

```text
low[child] >= disc[parent]
```

가 경계다.

---

## 3. SCC

이번에는 방향 그래프다.

여기서는 의미가 조금 바뀐다.

`low[v]`는

> `v`의 DFS subtree에서, 아직 SCC가 확정되지 않아 stack에 살아 있는 정점 중 얼마나 옛날 정점까지 도달할 수 있는가

다.

그래서 정점 stack을 쓴다.

```text
stack = 방문했지만 아직 SCC가 확정되지 않은 정점들
```

그리고

\[
\boxed{low[v] = disc[v]}
\]

이면 `v`가 현재 SCC의 root다.

왜냐하면 `v` 아래의 살아 있는 정점들이 `v`보다 더 이전의 미확정 정점으로는 못 올라가기 때문이다.

그래서 stack에서 `v`가 나올 때까지 pop:

```text
x
y
z
v
```

→ `{v,z,y,x}` 하나의 SCC.

즉 세 번째 문제는

\[
\boxed{low[v]=disc[v]}
\]

가 component 경계다.

---

세 개를 한 표로 보면 아주 깔끔하다.

| 문제 | 그래프 | low가 묻는 것 | 판정 |
|---|---|---|---|
| Bridge | 무방향 | 자식 subtree가 얼마나 위로 우회 가능한가 | `low[u] > disc[v]` |
| Articulation / BCC | 무방향 | 자식 subtree가 `v` 없이 위로 갈 수 있는가 | `low[u] >= disc[v]` |
| SCC | 방향 | 현재 미확정 정점 중 어디까지 되돌아갈 수 있는가 | `low[v] == disc[v]` |

그리고 stack도 정리하면:

```text
Bridge
    stack 필요 없음

Vertex-BCC
    edge stack

SCC
    vertex stack
```

가 된다.

---

가장 중요한 공통 철학은 이것이다.

DFS tree에서 항상

```text
        과거 / 위쪽
             |
             v
            / \
           u  ...
          / \
      미래 / 아래쪽
```

이런 구조를 만든다.

그다음 `low`가 말해준다.

> "이 아래쪽 세계가 위쪽 세계와 별도의 길로 연결되어 있나?"

그리고 그 답에 따라:

```text
완전히 연결 안 됨
→ bridge

v까지만 연결됨
→ v가 articulation 경계

방향 그래프에서 더 옛날 미확정 정점으로 못 감
→ SCC 경계
```

가 되는 거야.

그래서 세 알고리즘을 사실 따로 외울 필요가 별로 없다.

핵심 하나만 기억하면 된다:

\[
\boxed{\text{disc는 내가 언제 태어났는지, low는 내 subtree가 얼마나 과거까지 닿는지}}
\]

그리고 문제마다 **“얼마나 과거까지 닿아야 같은 덩어리냐”**의 기준만 달라진다.