//
// Created by lukaszlampart on 24.12.15.
//

#ifndef FUNCTION_SPACE_FUNCTIONAL_SPACE_H
#define FUNCTION_SPACE_FUNCTIONAL_SPACE_H

#include <functional>

template<typename T>
class functional_space {
public:
    /*
     * Declarations of function objects types in the space
     * class basic_function implements simple one-argument functional object
     * class multiplicative implements function object being multiplication of other two objects
     * class addictive implements function object being addition of other two objects
     */
    class basic_function;

    class multiplicative;

    class addictive;

    class basic_function {
    public:
        //templated constructor for class, implements
        template<typename F>
        basic_function(const F &init) : inner_function(init) { }

        //This method allows for easy multiplication of the object with any viable type
        template<typename function_obj>
        multiplicative operator*(const function_obj &f) const {
            return multiplicative(*this, f);
        }

        //This method allows for addition
        template<typename functions_obj>
        addictive operator+(const functions_obj &f) const {
            return addictive(*this, f);
        }

        T operator()(const T &x) const {
            return inner_function(x);
        }

    private:
        //functional object for inner function calling
        const std::function<T(const T &)> inner_function;
    };

    class multiplicative {
        friend class basic_function;

        friend class addictive;

    public:
        //operator for function behaviour
        T operator()(const T &x) const {
            return a(x) * b(x);
        }

        // multiplication of functions
        template<typename function_obj>
        multiplicative operator*(const function_obj &f) const {
            return multiplicative(*this, f);
        }

        //addition of functions
        template<typename function_obj>
        addictive operator+(const function_obj &f) const {
            return addictive(*this, f);
        }

    private:
        //templated constructor for class (types F,G has to be derived from function)
        template<typename F, typename G>
        multiplicative(const F &f, const G &g) : a(f), b(g) { }

        //templated constructor for class allowing multiplying by constant
        template<typename F>
        multiplicative(const F &f, const T &val) : a(f), b([&val](const T &x) -> T {
            return val;
        }) { }

        //inner functions in object
        std::function<T(const T &)> a;
        std::function<T(const T &)> b;
    };

    class addictive {
        friend class multiplicative;

        friend class basic_function;

    public:

        T operator()(const T &x) const {
            return a(x) + b(x);
        }

        //multiplication of functions
        template<typename function_obj>
        multiplicative operator*(const function_obj &f) const {
            return multiplicative(*this, f);
        }

        //addition of functions
        template<typename function_obj>
        addictive operator+(const function_obj &f) const {
            return addictive(*this, f);
        }

    private:
        //templated constructor for class (types F,G has to be derived from function)
        template<typename F, typename G>
        addictive(const F &f, const G &g) : a(f), b(g) { }

        //templated constructor for class allowing adding constant
        template<typename F>
        addictive(const F &f, const T &val) : a(f), b([&val](const T &x) -> T {
            return val;
        }) { }

        //inner functions
        std::function<T(const T &)> a;
        std::function<T(const T &)> b;
    };


    // functional_space is pure virtual, it serves only as "templated" namespace
    virtual ~functional_space() = 0;
};

#endif //FUNCTION_SPACE_FUNCTIONAL_SPACE_H
