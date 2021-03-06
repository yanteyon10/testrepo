#ifndef DATA_STRUCT
#define DATA_STRUCT
#include <iostream>
#include "pdist.hpp"

namespace statistic {

    template <int dim, class distribution>
    using PD = Probability_distribution<dim, distribution>;

    template <int dim, int num> class Data_series;

    template <int dim, int num>
    class Data_series
    {
    public:
        Data_series() = delete;
        Data_series(std::istream& datain, const statistic_util::FORMAT &format);  // ファイルから読み込む場合
        template <class distribution>
        Data_series(PD<dim, distribution>& pd);  // 生成器から作る場合

        void output(std::ostream& os, const statistic_util::FORMAT& format) const;  // ファイルに書き出す

        const std::array<dvector<dim>, num>& dataset() const;
    private:
        int _dim;
        int _num;
        std::array<dvector<dim>, num> _x;  // 次元はdim，要素数はnum
    };

    void test_data_series_gaussian();
    void test_data_series_gaussian_mixtures();

}
#include "detail/data_struct.hpp"

#endif
