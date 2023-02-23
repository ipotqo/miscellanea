/**
 * \file   lambda.cpp
 * \brief  Multi-Step Methods using Lambda Functions
 */

#include <array>
#include <chrono>

using lattice_t = std::size_t;

template< typename ArithmeticT, lattice_t RowsN, lattice_t ColsN >
class field : public std::array< ArithmeticT, RowsN * ColsN > {

};

int main () {
}