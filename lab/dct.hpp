﻿/*! @file
    @brief DCT（離散コサイン変換）．DCT-1とDCT-2がある
    @author yanteyon10
    @date 12/29
*/
#ifndef DCT_HPP
#define DCT_HPP

#include <fft>

namespace Eigen {
    /*! @brief DCT-1用の偶拡張メタ関数．abcdeからabcdedcbを作る
    */
    template <typename T, int Option = Eigen::ColMajor>
    struct Evenize1;

    /*! @brief 縦ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Evenize1 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor> {
        using type = typename Eigen::Expand<typename Eigen::Scaleup<Matrix<Scalar, Rows, Cols>, 2, 1>::type, -2, 0>::type;
    };

    /*! @brief 横ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Evenize1 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::RowMajor> {
        using type = typename Eigen::Expand<typename Eigen::Scaleup<Matrix<Scalar, Rows, Cols>, 1, 2>::type, 0, -2>::type;
    };

    /*! @brief DCT-1用の偶拡張関数．abcdeからabcdedcbを作る
    */
    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::ColMajor>::type* = nullptr>
    typename Evenize1<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type evenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Evenize1<param_type, Option>::type;
        result_type retval;
        retval.template block<Rows, Cols>(0, 0, rows, cols) = M;
        retval.template block<Eigen::Size::sub(Rows, 2), Cols>(rows, 0, rows-2, cols) = M.colwise().reverse().template block<Eigen::Size::sub(Rows, 2), Cols>(1, 0, rows-2, cols);
        return retval;
    }

    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::RowMajor>::type* = nullptr>
    typename Evenize1<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type evenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Evenize1<param_type, Option>::type;
        result_type retval;
        retval.template block<Rows, Cols>(0, 0, rows, cols) = M;
        retval.template block<Rows, Eigen::Size::sub(Cols, 2)>(0, cols, rows, cols-2) = M.rowwise().reverse().template block<Rows, Eigen::Size::sub(Cols, 2)>(0, 1, rows, cols-2);
        return retval;
    }

    template <typename Scalar, int Rows, int Cols>
    typename Evenize1<Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor>::type evenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        return evenize1<Eigen::ColMajor>(M);
    }

    template <typename Scalar, size_t N>
    typename std::array<Scalar, 2*N-2> evenize1(const std::array<Scalar, N> &x)
    {
        using param_type = std::array<Scalar, N>;
        using result_type = std::array<Scalar, 2*N-2>;
        result_type retval;
        std::copy(x.begin(), x.end(), retval.begin());
        std::reverse_copy(x.begin()+1, x.end()-1, retval.begin()+N);
        return retval;
    }

    template <typename Scalar>
    typename std::vector<Scalar> evenize1(const std::vector<Scalar> &x)
    {
        using param_type = std::vector<Scalar>;
        using result_type = std::vector<Scalar>;
        const int N = x.size();
        result_type retval(2*N-2);
        std::copy(x.begin(), x.end(), retval.begin());
        std::reverse_copy(x.begin()+1, x.end()-1, retval.begin()+N);
        return retval;
    }

    /*! @brief DCT-1用の偶拡張から情報を取り出すメタ関数．abcdedcbからabcdeを作る
    */
    template <typename T, int Option = Eigen::ColMajor>
    struct Deevenize1;

    /*! @brief 縦ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Deevenize1 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor> {
        using type = typename Eigen::Scaledown<typename Eigen::Expand<Matrix<Scalar, Rows, Cols>, 2, 0>::type, 2, 1>::type;
    };

    /*! @brief 横ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Deevenize1 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::RowMajor> {
        using type = typename Eigen::Scaledown<typename Eigen::Expand<Matrix<Scalar, Rows, Cols>, 0, 2>::type, 1, 2>::type;
    };

    /*! @brief DCT-1用の偶拡張から情報を取り出す関数．abcdedcbからabcdeを作る
    */
    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::ColMajor>::type* = nullptr>
    typename Deevenize1<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type deevenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Deevenize1<param_type, Option>::type;
        return M.template block<result_type::RowsAtCompileTime, result_type::ColsAtCompileTime>(0, 0, (rows+2)/2, cols).eval();
    }

    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::RowMajor>::type* = nullptr>
    typename Deevenize1<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type deevenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Deevenize1<param_type, Option>::type;
        return M.template block<result_type::RowsAtCompileTime, result_type::ColsAtCompileTime>(0, 0, rows, (cols+2)/2).eval();
    }

    template <typename Scalar, int Rows, int Cols>
    typename Deevenize1<Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor>::type deevenize1(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        return deevenize1<Eigen::ColMajor>(M);
    }

    template <typename Scalar, size_t Neven>
    typename std::array<Scalar, (Neven+2)/2> deevenize1(const std::array<Scalar, Neven> &x)
    {
        constexpr int N = (Neven+2)/2;
        using param_type = std::array<Scalar, Neven>;
        using result_type = std::array<Scalar, N>;
        result_type retval;
        std::copy(x.begin(), x.begin()+N, retval.begin());
        return retval;
    }

    template <typename Scalar>
    typename std::vector<Scalar> deevenize1(const std::vector<Scalar> &x)
    {
        const int Neven = x.size();
        const int N = (Neven+2)/2;
        using param_type = std::vector<Scalar>;
        using result_type = std::vector<Scalar>;
        result_type retval(N);
        std::copy(x.begin(), x.begin()+N, retval.begin());
        return retval;
    }

    /*! @brief 1変量時系列のDCT-1
        @tparam To 実数型または複素数型．指定しないと実数型になる
        @tparam From 実数型または複素数型
        @tparam N 系列の長さ
        @param x 1変量時系列
    */

    /*! @brief std::array用
    */

    /*! @brief dct1<std::complex<double>>の場合を担保
    */
    template <typename To, typename From, size_t N, typename std::enable_if <std::is_same <To, typename std::complexify <To>::type>::value>::type * = nullptr>
    std::array <To, N> dct1(const std::array <From, N> &x)
    {
        using param_type = std::array<From, N>;
        using tmp_param_type = std::array<From, 2*N-2>;
        using tmp_result_type = std::array<To, 2*N-2>;
        using result_type = std::array <To, N>;

        tmp_result_type tmp_retval;
        result_type retval;
        Eigen::FFT <typename std::decomplexify <To>::type> fft;
        fft.fwd(tmp_retval.data(), evenize1(x).data(), 2*N-2);

        return deevenize1(tmp_retval);
    }

    /*! @brief dct<double>の場合を担保
    */
    template <typename To, typename From, size_t N, typename std::enable_if <!std::is_same <To, typename std::complexify <To>::type>::value>::type * = nullptr>
    std::array <To, N> dct1(const std::array <From, N> &x)
    {
        using tmp_result_type = std::array <typename std::complexify<To>::type, N>;
        using result_type = std::array <To, N>;

        const tmp_result_type tmp_retval(dct1<typename std::complexify<To>::type>(x));
        result_type retval;
        std::transform(tmp_retval.begin(), tmp_retval.end(), retval.begin(), [](const typename std::complexify<To>::type c)->To{return c.real();});
        return retval;
    }

    /*! @brief 型指定しない場合を担保
    */
    template <size_t N, typename From>
    std::array <typename std::decomplexify<From>::type, N> dct1(const std::array <From, N> &x)
    {
        return dct1<typename std::decomplexify<From>::type>(x);
    }

    /*! @brief std::vector用
    */
    template <typename T>
    std::vector <typename std::complexify <T>::type> dct(const std::vector <T> &x)
    {
        using result_type = std::vector <typename std::complexify <T>::type>;
        result_type                                       retval;
        Eigen::FFT <typename std::decomplexify <T>::type> dct;
        dct.fwd(retval, x);

        return retval;
    }

    /*! @brief 多変量時系列のDCT-1
        @tparam To 実数型または複素数型
        指定しないと複素数型になる
        @tparam From 実数型または複素数型
        @tparam Rows 行数
        @tparam Cols 列数
        @param X データ行列
        @param transpose 通常のデータ行列（時間方向が行方向）から転置する
        デフォルト値はfalse
    */

    /*! @brief Eigen::Matrix用
    */

    /*! @brief dct<std::complex<double>>の場合を担保
    */
    template <typename To, typename From, int Rows, int Cols, typename std::enable_if <std::is_same <To, typename std::complexify <To>::type>::value>::type * = nullptr>
    Eigen::Matrix <To, Rows, Cols> dct(const Eigen::Matrix <From, Rows, Cols> &X, const bool transpose=false)
    {
        const int                                         rows = X.rows();
        const int                                         cols = X.cols();
        using result_type = Eigen::Matrix <To, Rows, Cols>;
        result_type                                       retval(rows, cols);
        Eigen::FFT <typename std::decomplexify <To>::type> dct;
        if (transpose) {
            for (int i = 0; i < rows; i++) {
                retval.row(i) = dct.fwd(X.row(i).eval());
            }
        } else {
            for (int j = 0; j < cols; j++) {
                retval.col(j) = dct.fwd(X.col(j).eval());
            }
        }

        return retval;
    }

    /*! @brief 型指定しない場合を担保
    */
    template <int Rows, int Cols, typename From>
    Eigen::Matrix <typename std::complexify <From>::type, Rows, Cols> dct(const Eigen::Matrix <From, Rows, Cols> &X, const bool transpose=false)
    {
        return dct<typename std::complexify<From>::type>(X, transpose);
    }

    /*! @brief dct<double>の場合を担保
    */
    template <typename To, typename From, int Rows, int Cols, typename std::enable_if <!std::is_same <To, typename std::complexify <To>::type>::value>::type * = nullptr>
    Eigen::Matrix <To, Rows, Cols> dct(const Eigen::Matrix <From, Rows, Cols> &X, const bool transpose=false)
    {
        return std::real(dct<typename std::complexify<To>::type>(X, transpose));
    }








    /*! @brief DCT-2用の偶拡張メタ関数．abcdeからabcdedcbを作る
    */
    template <typename T, int Option = Eigen::ColMajor>
    struct Evenize2;

    /*! @brief 縦ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Evenize2 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor> {
        using type = typename Eigen::Scaleup<Matrix<Scalar, Rows, Cols>, 4, 1>::type;
    };

    /*! @brief 横ベクトル
    */
    template <typename Scalar, int Rows, int Cols>
    struct Evenize2 <Eigen::Matrix<Scalar, Rows, Cols>, Eigen::RowMajor> {
        using type = typename Eigen::Scaleup<Matrix<Scalar, Rows, Cols>, 1, 4>::type;
    };

    /*! @brief DCT-2用の偶拡張関数．abcdeから0a0b0c0d0e0e0d0c0b0aを作る
    */
    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::ColMajor>::type* = nullptr>
    typename Evenize2<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type evenize2(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Evenize2<param_type, Option>::type;
        result_type retval;
        for (int i = 0; i < rows; i++) {
            retval.row(2*i).fill(0);
            retval.row(2*i+1) = M.row(i);
        }
        for (int i = rows; i < 2*rows; i++) {
            retval.row(2*i).fill(0);
            retval.row(2*i+1) = M.row(2*rows-1-i);
        }
        return retval;
    }

    template <int Option, typename Scalar, int Rows, int Cols, typename std::enable_if<Option == Eigen::RowMajor>::type* = nullptr>
    typename Evenize2<Eigen::Matrix<Scalar, Rows, Cols>, Option>::type evenize2(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        const int rows = M.rows();
        const int cols = M.cols();
        using param_type = Eigen::Matrix<Scalar, Rows, Cols>;
        using result_type = typename Evenize2<param_type, Option>::type;
        result_type retval;
        for (int j = 0; j < cols; j++) {
            retval.col(2*j).fill(0);
            retval.col(2*j+1) = M.col(j);
        }
        for (int j = cols; j < 2*cols; j++) {
            retval.col(2*j).fill(0);
            retval.col(2*j+1) = M.col(2*cols-1-j);
        }
        return retval;
    }

    template <typename Scalar, int Rows, int Cols>
    typename Evenize2<Eigen::Matrix<Scalar, Rows, Cols>, Eigen::ColMajor>::type evenize2(const Eigen::Matrix<Scalar, Rows, Cols> &M)
    {
        return evenize2<Eigen::ColMajor>(M);
    }
}

#endif
