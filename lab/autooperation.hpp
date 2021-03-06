﻿/*! @file
    @brief 演算子の自動実装のためのCRTP基底クラス
    @auther templateaholic10
    @date 12/30
*/

#ifndef AUTOOPERATION_HPP
#define AUTOOPERATION_HPP

namespace devel {
    /*! @brief 加減乗除の複合代入演算子から2項演算子を生成する
    */
    template <class Derived, class Rhs = Derived>
    class Four_operations {
    public:
        Derived operator+(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval += rhs;
            return retval;
        }
        Derived operator-(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval -= rhs;
            return retval;
        }
        Derived operator*(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval *= rhs;
            return retval;
        }
        Derived operator/(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval /= rhs;
            return retval;
        }
    };

    /*! @brief 加減乗除余の複合代入演算子から2項演算子を生成する
    */
    template <class Derived, class Rhs = Derived>
    class Five_operations {
    public:
        Derived operator+(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval += rhs;
            return retval;
        }
        Derived operator-(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval -= rhs;
            return retval;
        }
        Derived operator*(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval *= rhs;
            return retval;
        }
        Derived operator/(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval /= rhs;
            return retval;
        }
        Derived operator%(const Rhs &rhs) const
        {
            Derived retval(static_cast<const Derived &>(*this));
            retval %= rhs;
            return retval;
        }
    };

    /*! @brief <=から残りの関係演算子を生成する
    */
    template <class Derived>
    class Order_operations1 {
    public:
        bool operator>=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return rhs <= dthis;
        }
        bool operator==(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return dthis <= rhs && dthis >= rhs;
        }
        bool operator!=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return !(dthis == rhs);
        }
        bool operator<(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return dthis <= rhs && dthis != rhs;
        }
        bool operator>(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return dthis >= rhs && dthis != rhs;
        }
    };

    /*! @brief <から残りの関係演算子を生成する
    */
    template <class Derived>
    class Order_operations2 {
    public:
        bool operator>(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return rhs < dthis;
        }
        bool operator!=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return dthis < rhs || dthis > rhs;
        }
        bool operator==(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return !(dthis != rhs);
        }
        bool operator<=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return (dthis < rhs) || (dthis == rhs);
        }
        bool operator>=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return (dthis > rhs) || (dthis == rhs);
        }
    };

    /*! @brief ==から!=を生成する
    */
    template <class Derived>
    class Equi_operations {
    public:
        bool operator!=(const Derived &rhs) const
        {
            const Derived &dthis = static_cast <const Derived &>(*this);
            return !(dthis == rhs);
        }
    };
};

#endif
