#ifndef QRSOLVER_H
#define QRSOLVER_H
#include "LinearSolver.h"
class QRSolver :public LinearSolver {
    private:
        Matrix Q;
        Matrix R;
    public:
        QRSolver();
        QRSolver(const size_t _normType);
        QRSolver( Matrix& A);
        std::pair<Matrix,Matrix> calcQR(Matrix& A);
        std::pair<Matrix,Matrix> getQR();
        std::pair<Matrix,Matrix> getQR(Matrix& A);
        Matrix solve(Matrix& rs);
};
#endif //QRSOLVER_H