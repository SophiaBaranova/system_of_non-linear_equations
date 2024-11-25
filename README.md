# C program for solving a system of non-linear equations
The system of $n$ non-linear equations is written in form $\overrightarrow{F}(\overrightarrow{x})=0$.

We create a a function of $n$ variables $U(\overrightarrow{x})=\sum_{i=1}^{n}F_i(\overrightarrow{x})^2$.

$U(\overrightarrow{x})=0$ when $\overrightarrow{x}$ is a root. So to solve the system we need to find a minimum of $U(\overrightarrow{x})$.

We use gradient descent method and at each step calculate $\overrightarrow{x}$ by formula $\overrightarrow{x}^{(k+1)}=\overrightarrow{x}^{(k)}-\mu_kW^T(\overrightarrow{x}^{(k)})\overrightarrow{F}(\overrightarrow{x}^{(k)})$,
where $W(\overrightarrow{x}^{(k)})$ is a Jacobian matrix for $\overrightarrow{F}(\overrightarrow{x}^{(k)})$ and 
$\mu=\frac{(\overrightarrow{F}(\overrightarrow{x}^{(k)}),W(\overrightarrow{x}^{(k)})W^T(\overrightarrow{x}^{(k)})\overrightarrow{F}(\overrightarrow{x}^{(k)}))}{(W(\overrightarrow{x}^{(k)})W^T(\overrightarrow{x}^{(k)})\overrightarrow{F}(\overrightarrow{x}^{(k)}),W(\overrightarrow{x}^{(k)})W^T(\overrightarrow{x}^{(k)})\overrightarrow{F}(\overrightarrow{x}^{(k)}))}$
is a stepsize.

We stop the process when $\parallel{grad(U(\overrightarrow{x}^{(k)}))}\parallel\leq\varepsilon$, where $\varepsilon$ is a given accuracy.
