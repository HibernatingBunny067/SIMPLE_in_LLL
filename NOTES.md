# What is SIMPLE and Why do we need it ?
- the stready 2D incompressible Navier-Stokes equations with constant viscosity can be realized as 
$$
\begin{aligned}
\frac{\partial{u}}{\partial{x}} + \frac{\partial{v}}{\partial{y}}=0 \\
\frac{\partial{uu}}{\partial{x}} + \frac{\partial{uv}}{\partial{y}} = -\frac{1}{\rho}\frac{\partial{p}}{\partial{x}} + \nu(\frac{\partial^2{u}}{\partial^2{x}}+\frac{\partial^2{u}}{\partial^2{y}})
\end{aligned}
$$

- The problem arrives when we try to see the evolution of pressure, as from these equations we don't have any equation to link pressure.
- for compressible flows the equation of state (Ideal Gas law $p=\rho RT$ can be used linking pressure to density and temperature but with incompressible flows where density is constant, pressure purely acts as a kinematic lagrange multiplier
- In the context of storing everything at the cell center, this is not possible and recommended because it may lead to checker board patterns and zero gradients even when pressure oscillates.
- **OpenFOAM uses  collocated grids and Rhie-Chow momentum interpolation at the cell faces to handle this.**
- What I am going to implement is *Harlow-Chow* staggered grid.

# What is Harlow-Welch (MAC) Staggered Grid ?
- The scalar quantities are stored at the cell center $(i,j)$
- The four faces (in 2 dimensional case) store the vector quantities at the faces $(i±\frac{1}{2},j)$ 
- 