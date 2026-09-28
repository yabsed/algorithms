응. **네 코드도 SCC를 올바르게 찾는다.** 다만 `low`라는 숫자가 의미하는 바가 표준 Tarjan과 약간 달라진다. 표준 Tarjan은 이미 방문한 `u`로 직접 가는 간선에서는 `disc[u]`를 쓰고, `low[u]`를 쓰는 변형도 SCC root 판정은 여전히 맞는다. :chatgpt-content-reference{index="0"}

근본 차이는 이거야.

표준 Tarjan에서

```cpp
else if (in_stack[u])
    low[v] = min(low[v], disc[u]);
```

라고 하는 건,

> `v -> u`라는 **직접 간선 하나가 증명해 주는 것은 일단 u에 도달할 수 있다는 사실뿐**

이라고 아주 보수적으로 정의하는 거야.

즉

```text
v → u
```

를 발견했다면 확실히 증명된 것은

\[
v\leadsto u
\]

이므로 `disc[u]`까지만 반영한다.

반면 네 방식은

```cpp
low[v] = min(low[v], low[u]);
```

니까 이렇게 말하는 셈이야.

> 나는 u에 갈 수 있고, u가 이미 어떤 더 옛날의 살아 있는 정점 x까지 갈 수 있다는 것도 알고 있으니, 나도 x까지 갈 수 있다고 하자.

즉

```text
v → u → ... → x
```

를 한 번에 전파한다.

### 실제로 값이 달라지는 예

방향 그래프를 이렇게 하자.

```text
1 → 2
↑   |
|   |
└───┘

1 → 4 → 2
```

즉 간선:

```text
1 → 2
2 → 1
1 → 4
4 → 2
```

DFS 순서가

```text
1, 2, 4
```

라고 하자.

`2 → 1` 때문에:

```text
disc[1] = 1
disc[2] = 2
low[2] = 1
```

이 된다.

이제 `4 → 2`를 본다.

표준 Tarjan은:

```cpp
low[4] = min(low[4], disc[2]);
```

이므로

\[
low[4]=2
\]

이다.

반면 네 방식은:

```cpp
low[4] = min(low[4], low[2]);
```

이므로

\[
low[4]=1
\]

이다.

즉 결과가 다르다.

```text
              표준        네 방식

disc[4]         3            3
low[4]          2            1
```

그런데 SCC는?

```text
1 → 4 → 2 → 1
```

이므로 사실

\[
\{1,2,4\}
\]

전부 같은 SCC다.

따라서 어느 쪽이든 `4`를 SCC root라고 잘못 판단하지 않는다.

```text
표준:   low[4]=2 != 3
변형:   low[4]=1 != 3
```

둘 다 `4`를 pop하지 않는다.

결국 `1`에 도달했을 때 전부 같이 pop된다.

---

그래서 차이를 아주 정확히 표현하면:

**표준 `low`**

> `v`에서 Tarjan이 정의한 형태의 경로로 도달할 수 있는 가장 작은 discovery index

를 엄밀하게 유지한다.

그래서 direct edge `v→u`에서는:

\[
disc[u]
\]

만 가져온다.

**네 변형의 `low`**

> 아직 stack에 살아 있는 정점들 사이의 이미 알려진 도달성 정보를 더 적극적으로 전파한 값

이라서,

\[
low[u]
\]

까지 가져올 수 있다.

따라서 표준보다 `low[v]`가 **더 작아질 수 있다.**

하지만 중요한 건 SCC 알고리즘이 최종적으로 요구하는 것이 정확한 `low` 숫자 그 자체가 아니라:

\[
\boxed{low[v]=disc[v]\text{인가?}}
\]

즉

> `v`가 SCC의 root인가?

라는 판정이라는 점이야.

`low[u]`를 더 공격적으로 전파해도 **진짜 SCC root를 가짜로 내려버리는 일은 생기지 않고**, non-root는 여전히 non-root로 남기 때문에 SCC 분해 자체는 맞는다. 이 변형이 root test를 보존한다는 점은 Tarjan 알고리즘 설명에서도 명시되어 있다. :chatgpt-content-reference{index="1"}

그리고 네 코드에는 한 가지가 더 들어가 있었지:

```cpp
if (!disc[u])
    dfs(u);

if (in_stack[u])
    low[v] = min(low[v], low[u]);
```

즉 tree child `u`가 DFS 도중 이미 자기 SCC로 pop됐다면 아예 `low[u]`를 받지 않는다.

이것도 괜찮다. `u`가 pop됐다는 건 `u`의 SCC가 `v`와 다른 SCC로 이미 완성됐다는 뜻이고, 그런 SCC의 `low[u]`는 `v`의 root 여부를 낮출 수 없는 값이라서 무시해도 결과가 변하지 않는다. 이 tree-edge stack check를 넣어도 lowlink/root 판정에 영향을 주지 않는다는 설명도 있다. :chatgpt-content-reference{index="2"}

그래서 네 코드:

```cpp
if (!disc[u]) {
    dfs(u);
}

if (in_stack[u])
    low[v] = min(low[v], low[u]);
```

는 **맞다.**

다만 나는 코테 템플릿으로는 여전히:

```cpp
if (!disc[u]) {
    dfs(u);
    low[v] = min(low[v], low[u]);
}
else if (in_stack[u]) {
    low[v] = min(low[v], disc[u]);
}
```

를 추천한다.

이유는 correctness 때문이라기보다 **의미가 bridge/BCC와 정확히 대응해서 기억하기 쉽기 때문**이다.

```text
tree edge
    → 자식이 발견한 모든 정보
    → low[u]

직접 만난 이미 방문한 edge
    → 내가 직접 도달한 정점
    → disc[u]
```

이 원칙이 bridge, articulation/BCC, SCC에 거의 공통으로 적용된다.

즉 **네 것은 맞는 변형이고, 표준 것은 `low` 자체의 의미까지 깔끔하게 보존하는 버전**이라고 보면 된다.