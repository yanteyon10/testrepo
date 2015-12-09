#include <iostream>
#include "fft.hpp"
#include <eigen_io>
#include <array_io>
#include <vector_io>
#include <debug>

int main(int argc, char const *argv[])
{
    using T = double;
    constexpr int N = 10;
    constexpr int p = 2;
    Eigen::Matrix<T, N, p> x;
    // 正弦波でテストする
    constexpr double period = 2. * M_PI;
    constexpr double interval = period / N;
    for (size_t i = 0; i < N; i++) {
        x(i, 0) = std::sin(i * interval);
        x(i, 1) = std::cos(i * interval);
    }
    _PRINT(x)
    auto X1 = Eigen::fft<T>(x);
    _PRINT(X1)
    auto X2 = Eigen::fft<std::complex<T>>(x);
    _PRINT(X2)
    auto X3 = Eigen::fft(x);
    _PRINT(X3)
    auto X4 = Eigen::ifft<T>(x);
    _PRINT(X4)
    auto X5 = Eigen::ifft<std::complex<T>>(x);
    _PRINT(X5)
    auto X6 = Eigen::ifft(x);
    _PRINT(X6)
    // auto y = Eigen::ifft<std::complex<T>>(X);
    // _PRINT(y)
    return 0;
}
