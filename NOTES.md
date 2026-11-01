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


# Review of the FVM method and discretisation schemes.
- The general family of equations concerned here are the incompressible Navier STokes equations which are variants of the general convection-diffusion-source transport equations of the form
$
\begin{aligned}
\nabla (\rho u \phi) = \nabla (\Tau \nabla \phi) + S_{\phi}
\end{aligned}
$
- where the left hand side is the convective flux associated with bulk fluid motion (velocity)
- the right hand side is made up of diffusion component inside the nabla operator and the source term
- This general equation is integrated over a small volume in FVM and converted to area integrals using the *Gauss's DIvergenece Theorem* yielding the equations which can be discretised and solved numerically 
- The discretised equation takes this form

$
\begin{aligned}
[(\rho u \phi)_e - (\rho u \phi)_w]\Delta y + [(\rho v \phi)_n - (\rho v \phi))_s]\Delta x = [(\Gamma \frac{\partial{\phi}}{\partial{x}})_e -  (\Gamma \frac{\partial{\phi}}{\partial{x}})_w]\Delta y + [(\Gamma \frac{\partial{\phi}}{\partial{x}})_n -  (\Gamma \frac{\partial{\phi}}{\partial{x}})_s]\Delta x + S_{\phi}V
\end{aligned}
$

- to keep the algebra clean and simple, some additional terms are defined, namely $\text{Convective Flux F}: (\rho u)_f \Delta x$   and 
- $ \text{Diffusive Conductance D }: \frac{\Gamma_f \Delta x}{\delta x}$ 
- further the gradients on the right hand side are discretised to difference between nodal values represented by capital letters, finally we acheive the equation


### NOTE: the other notes on physics and derivations were written by hand and may be attached as pdf in this project, after this all the notes are on implementation and codingin c++.


# ".hpp" files 
- Unlike dynamically typed langauges like Python and Javascript, c++ is a statically typed language, so functions have to defined with strict input and output datatype before they are used.
- hpp files are like blueprints of the code which we write in the .cpp file.
- they share a common name
- 


