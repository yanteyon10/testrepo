#include <iostream>
#include <string>
#include <util>
#include "exfunction.hpp"

template <typename T>
struct Addconst {
private:
    T c;
public:
    Addconst(const T& c_)
    : c(c_)
    {
    }
    T operator()(const T& x)
    {
        return x + c;
    }
};

template <typename Result, typename ... Args>
std::function<Result(Args...)> operator+(const std::function<Result(Args...)> &f, const std::function<Result(Args...)> &g)
{
    return [&](Args... args){return f(args...) + g(args...);};
}

int main(int argc, char const *argv[])
{
    using var_type = double;

    using project_type = std::function<var_type(const int, const var_type, const var_type, const var_type)>;
    auto project = project_type([](const int n, const var_type x0, const var_type x1 = 0, const var_type x2 = 0)->var_type
    {
        if (n <= 0) {
            return x0;
        } else if (n == 1) {
            return x1;
        } else if (n >= 2) {
            return x2;
        } else {
            return 0;
        }
    });
    //
    // using _1_type = std::function<int()>;
    // auto _1 = _1_type([]()->int{return 1;});
    //
    // using result_type = std::function<double(const std::string&)>;
    // using f_type = std::function<double(const int)>;
    // using g_type = std::function<int(const std::string&)>;
    //
    // f_type f = f_type([](const int x)->double{return 0.1 + x;});
    // g_type g = g_type([](const std::string& str)->int{return std::stoi(str);});
    // f_type f_multi = f_type([](const int x)->double{return 0.1 + x;});
    // g_type g_multi = g_type([](const std::string& str)->int{return std::stoi(str);});
    // result_type fg = std::Composite<0>::eval(f, g);
    // _DISPLAY(fg("1991"))
    // _DISPLAY(std::Composite<0>::eval(project, _1)(0, 1, 2))
    //
    //
    // using Addconst_type = std::function<int(const int&)>;
    // Addconst_type addconst = Addconst_type(Addconst<int>(1));
    // auto hoge = std::Composite<0>::eval(project, addconst);
    // _DISPLAY(hoge(0, 0, 1, 2))
    // auto addconst2 = std::Composite<0>::eval(addconst, addconst);
    // auto piyo = std::Composite<0>::eval(project, addconst2);
    // _DISPLAY(piyo(0, 0, 1, 2))
    //
    //
    // _DISPLAY(std::Composite<0>::eval(project, Addconst_type(Addconst<int>(1)))(1, 0, 1, 2))

    project_type triple_project = project + project + project;
    _DISPLAY(triple_project(2, 0, 1, 2));

    return 0;
}
