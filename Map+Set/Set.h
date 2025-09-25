#include "RBTRee.h"

namespace omen 
{
    template<class T>
    class Set {
        struct SetKeyOfT {
            const T& operator()()
            {

            }
        };

    private:
        RBTree<T, T, SetKeyOfT> _t;
    };
}