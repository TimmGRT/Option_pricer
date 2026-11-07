# Option Pricer (C++17)

An object-oriented option pricing library in modern C++. A single abstract `Option` interface supports two kinds of pricing:

- **closed form**: Black–Scholes premium, analytic Greeks, implied volatility;
- **simulation**: a generic path-dependent Monte Carlo engine that prices any payoff defined on a simulated path.

Adding a new product only requires defining its payoff. The engine, the Greeks and the reporting are inherited.

## Features

| Product | Pricing | Greeks | Implied vol |
|---|---|---|---|
| European call / put | Black–Scholes closed form | Analytic Δ, Γ, ν, Θ, ρ | Newton–Raphson on vega |
| European call / put | Monte Carlo (exact GBM step) | Bump-and-reprice, central differences | – |
| Arithmetic Asian, fixed strike | Monte Carlo, 252 monitoring dates | Bump-and-reprice | – |
| Arithmetic Asian, floating strike | Monte Carlo, 252 monitoring dates | Bump-and-reprice | – |

## Model

Under the risk-neutral measure the underlying follows geometric Brownian motion,

$$dS_t = r S_t\,dt + \sigma S_t\,dW_t ,$$

and is simulated with the exact log-Euler scheme (there is no discretisation bias for the terminal value):

$$S_{t+\Delta t} = S_t \exp\!\Big(\big(r - \tfrac{1}{2}\sigma^2\big)\Delta t + \sigma\sqrt{\Delta t}\,Z\Big), \qquad Z \sim \mathcal N(0,1).$$

The price is the discounted mean payoff over $N$ paths, $\hat V = e^{-rT}\,\frac{1}{N}\sum_{i=1}^{N} h\big(S^{(i)}\big)$.

**Payoffs.** With $A_T = \frac{1}{n+1}\sum_{j=0}^{n} S_{t_j}$ the arithmetic average:

| Product | Call | Put |
|---|---|---|
| European | $(S_T-K)^+$ | $(K-S_T)^+$ |
| Asian, fixed strike | $(A_T-K)^+$ | $(K-A_T)^+$ |
| Asian, floating strike | $(S_T-A_T)^+$ | $(A_T-S_T)^+$ |

**Greeks by finite differences.** Central differences are used for Δ, Γ, ν and ρ, and a one-sided difference for Θ. Every bumped revaluation reuses the same seed (*common random numbers*). The noise in $V(S+h)$ and $V(S-h)$ is then highly correlated and largely cancels in the difference, so Monte Carlo Greeks stay stable at a modest path count.

**Implied volatility.** Newton–Raphson on $f(\sigma) = V_{BS}(\sigma) - V_{mkt}$, using the analytic vega as the derivative. Convergence is quadratic near the root.

## Build and run

```bash
make        # builds ./pricer with g++ -std=c++17
make run    # builds and runs the examples in main.cpp
make clean
```

## Example output

Inputs: $S_0 = K = 100$, $r = 5\%$, $\sigma = 20\%$, $T = 1$ year. Θ is per year.

| | Premium | Δ | Γ | Vega | Θ | ρ |
|---|---|---|---|---|---|---|
| EU call, Black–Scholes | 10.4506 | 0.6368 | 0.0188 | 37.52 | −6.414 | 53.23 |
| EU call, Monte Carlo (10⁵ paths) | 10.4085 | 0.6373 | 0.0193 | 37.26 | −6.411 | 53.28 |
| EU put, Black–Scholes | 5.5735 | −0.3632 | 0.0188 | 37.52 | −1.658 | −41.89 |
| EU put, Monte Carlo (10⁵ paths) | 5.4938 | −0.3631 | 0.0193 | 37.23 | −1.649 | −41.84 |
| Asian call, fixed strike (MC) | 5.6867 | 0.5836 | 0.036 | 21.44 | −3.378 | 24.44 |

The Monte Carlo Greeks agree with the analytic Greeks to within simulation error. Implied volatility recovers σ = 20.00% from a market price of 10.4506, and gives σ = 21.46% for a market price of 11.00.

## Design

```
include/
  option.hpp            abstract base: market data, payoff interface, FD Greeks, reporting
  european_option.hpp   OptionEUBS (closed form + IV), OptionEUMC (simulation)
  asian_option.hpp      OptionAsian (fixed / floating strike)
  solver.hpp            normal CDF/PDF, RNG, generic Monte Carlo engine
src_cpp/                implementations
main.cpp                usage examples
```

- `Option` is an abstract class. Each product implements `payoff(path)`, `premium()` and `greeks()`.
- `MonteCarloPricer` takes a `const Option&` and depends only on the payoff interface, so it is product-agnostic.
- Seeds are fixed by default (seed 42) so results are reproducible.

## Roadmap

- [ ] Report the standard error and a 95% confidence interval with every MC price
- [ ] Variance reduction: antithetic variates, and a geometric-Asian control variate (closed form, Kemna–Vorst)
- [ ] Pathwise and likelihood-ratio Greeks
- [ ] Barrier options (up/down, in/out) with a Brownian-bridge crossing correction
- [ ] Multi-asset products (basket, worst-of) with Cholesky-correlated paths, as a step towards autocallables
- [ ] Unit tests (put–call parity, BS limits, MC convergence at rate $N^{-1/2}$)

## License

MIT
