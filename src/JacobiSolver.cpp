#include "JacobiSolver.h"

JacobiSolver::JacobiSolver():SLESolver(),precision(0.01)
{
}
JacobiSolver::JacobiSolver(const size_t normType, const MyType _presicion,
const MyType epsilon):SLESolver(normType,epsilon),
precision(_presicion)
{
}
Matrix JacobiSolver::solve(Matrix &problem, Matrix &xStart)
{

    problem.setPresision(epsilon);
    Matrix rs=problem.popCol(problem.getCols()-1);
    Matrix C(problem.getCols(),(int)problem.getRows());
    C.setPresision(epsilon);
/*     Matrix L(problem.getCols(),problem.getRows());
    Matrix U(problem.getCols(),problem.getRows());
    Matrix D(problem.getCols(),problem.getRows()); */
    Matrix y(1,(int)problem.getRows());

    y.setPresision(epsilon);
    for(int i = 0; i < C.getCols(); ++i) {
        for(int j = 0; j < C.getRows(); ++j) {
/*             if(i==j)D(i,j)=problem(i,j);
            if(i<j)L(i,j)=problem(i,j);
            if(i>j)U(i,j)=problem(i,j); */
            if(i!=j) {
                C(j,i)=(problem(j,i)/problem(i,i))*(-1);
                y(i)=rs(i)/problem(i,i);
            }
        }
    }
      if(C.norm(normType)<1) {
        Matrix x= C*xStart+y;
        while((x-xStart).norm(normType)>
        ((1-C.norm(normType))* precision)
        /C.norm(normType)) {
            xStart = x;
            x=C*xStart+y;
        }
        return x;
      } 
    else{
        //TODO tau
    }
    return Matrix();
}

Matrix JacobiSolver::solve(Matrix &problem)
{
    problem.setPresision(epsilon);
    Matrix startX(1,(int)problem.getRows());
    return (*this).solve(problem, startX);
}

Matrix JacobiSolver::solve(Matrix &&problem)
{
    return (*this).solve(problem);
}
