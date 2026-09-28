정의가 두 종류로 섞여서 그래. 네 코드가 구하는 것은 정확히 말하면 **block decomposition**에 가까워.

예를 들어 그래프가

```text
1 --- 2 --- 3
```

이라고 하자. 두 간선 모두 bridge다.

네 DFS에서는 `2 -> 3`을 보고 돌아올 때

\[
low[3] \ge disc[2]
\]

이므로 stack에서 `(2,3)`을 pop해서

```text
BCC = {(2,3)}
정점 집합 = {2,3}
```

을 하나 만든다.

그리고 `(1,2)`도 똑같이

```text
BCC = {1,2}
```

가 된다.

그래서 네 코드의 결과는

```text
{1,2}
{2,3}
```

이다.

### 그런데 `{1,2}`를 정말 "2-vertex-connected"라고 부를 수 있나?

여기서 정의가 갈린다.

엄격한 **2-vertex-connected graph** 정의는 보통:

> 적어도 3개의 정점이 있고, 어떤 정점 하나를 제거해도 그래프가 연결되어 있다.

이다.

그러면

```text
1 --- 2
```

는 정점이 2개뿐이므로 **2-vertex-connected라고 하지 않는다.**

또 직관적으로 1에서 2로 가는 서로 독립적인 경로도 하나뿐이다.

```text
1 ---- 2
```

간선 하나밖에 없으니까.

반면 삼각형은:

```text
  1
 / \
2---3
```

1과 2 사이에

```text
1 → 2
1 → 3 → 2
```

처럼 내부 정점을 공유하지 않는 두 경로가 있다.

이게 진짜 우리가 생각하는 **vertex-biconnected** 구조다.

---

## 그런데 왜 bridge를 BCC처럼 pop하냐?

**block decomposition**이라는 조금 더 넓은 개념에서는 bridge도 하나의 block으로 취급하기 때문이다.

예를 들어:

```text
      1
     / \
    2---3
        |
        4
       / \
      5---6
```

구조적으로는

```text
삼각형 {1,2,3}
        |
      bridge 3-4
        |
삼각형 {4,5,6}
```

이다.

block decomposition에서는 깔끔하게:

```text
Block 1 = {1,2,3}
Block 2 = {3,4}       // bridge 하나
Block 3 = {4,5,6}
```

라고 놓는다.

그러면 articulation point인 `3`, `4`를 매개로 전체 그래프를 **block-cut tree**로 표현하기 아주 편하다.

즉 이 문맥에서 "block"은:

> 더 이상 합칠 수 없는, 내부에 articulation point가 없는 조각

이라는 약간 확장된 의미라서 bridge `K2`도 조각 하나로 인정한다.

---

그래서 용어를 이렇게 구분하면 안 헷갈린다.

| 용어 | bridge 한 개 `{u,v}` 포함? |
|---|---|
| **2-vertex-connected graph** (엄격한 의미) | 보통 ❌ |
| **vertex-biconnected component** | 정의에 따라 다름 |
| **block / block decomposition** | ✅ |
| 네 edge-stack 코드가 뽑는 것 | ✅ |

네 알고리즘 자체는 틀린 게 아니다. 오히려 **Tarjan의 standard block decomposition**으로 아주 자연스럽다.

예를 들어:

```text
A---B---C
    / \
   D---E
```

라면 네 코드가 대략

```text
{A,B}        ← bridge block
{B,D,E}      ← 진짜 2-connected 부분
{B,C}        ← bridge block
```

을 모두 뽑는다.

만약 코테 문제가

> "크기 3 이상의 실제 biconnected components만 출력하라"

라고 하면 pop한 뒤 정점 수를 세서 `>= 3`인 것만 취하면 되는 식이다.

즉 내가 앞에서 말한 핵심은:

> **네 stack 알고리즘은 경계마다 모든 block을 뽑기 때문에 bridge도 2정점짜리 block으로 나온다. 문제에서 BCC를 어떤 정의로 쓰는지만 확인하면 된다.**