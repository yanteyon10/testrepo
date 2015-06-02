﻿#ifndef EM_ALGORITHM
#define EM_ALGORITHM

#include <iostream>
#include <deque>
#include <array>
#include <boost/numeric/ublas/lu.hpp>
#include "statistic_util.hpp"
#include "data_struct.hpp"

namespace EM {
    // エイリアステンプレート
    template <int dim>
    using dvector = statistic_util::dvector <dim>;

    template <int dim>
    using dmatrix = statistic_util::dmatrix <dim>;

    // EM_estimatorはインスタンスを持たない推定器．

    // プライマリテンプレート
    template <int dim, class distribution>
    struct EM_estimator
    {
    };

    // 混合正規分布のEMアルゴリズム
    template <int dim, int mixture_num>
    struct EM_estimator <dim, statistic::GAUSSIAN_MIXTURES <mixture_num> >
    {
        // レコードは {混合比，平均，分散}
        using Record = std::tuple <std::array <double, mixture_num>, std::array <dvector <dim>, mixture_num>, std::array <dmatrix <dim>, mixture_num> >;

        // パラメータを更新し，対数尤度を返す関数
        template <int num>
        static std::tuple <Record, double> update(const Record &record, const statistic::Data_series <dim, num> &data_series);

        // 対数尤度を返す関数
        template <int num>
        static double logL(const Record &record, const statistic::Data_series <dim, num> &data_series);

        // レコードを出力する関数
        static void output(std::ostream& os, const Record& record);
    };

    void test_EM_gaussian_mixtures();
}

#include "detail/EM_algorithm.hpp"

#endif