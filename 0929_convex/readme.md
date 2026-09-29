### 신발끈 공식 — \(n\)각형의 넓이

꼭짓점이 경계 순서대로 주어졌다고 하자.

\[
\begin{array}{cc}
x_1 & y_1\\
x_2 & y_2\\
\vdots & \vdots\\
x_n & y_n
\end{array}
\]

단,

\[
(x_{n+1},y_{n+1})=(x_1,y_1)
\]

로 둔다.

\[
\boxed{
S=\sum_{i=1}^{n}
(x_i y_{i+1}-y_i x_{i+1})
}
\]

그러면

\[
\boxed{\text{Area}=\frac{|S|}{2}}
\]

부호는 꼭짓점을 도는 방향을 나타낸다.

- \(S>0\): **CCW (counterclockwise, 시계 반대방향)**
- \(S<0\): **CW (clockwise, 시계 방향)**
- \(S=0\): 넓이 \(0\)

즉,

\[
\boxed{
\frac12\sum_i P_i\times P_{i+1}
}
\]

는 부호 있는 넓이(signed area)다.

※ Convex일 필요는 없지만, 점들은 **다각형의 경계를 따라 순서대로** 주어져야 한다.