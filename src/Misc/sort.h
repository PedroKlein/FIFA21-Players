#pragma once

#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>
namespace misc
{
    const size_t MAX_ISORT = 32;

    inline int randomNumber(int start, int end)
    {
        srand((size_t)time(NULL));
        return rand() % end + start;
    }

    template <typename Iterator, typename _PR>
    inline void quickSort(Iterator begin, Iterator end, _PR pred)
    {
        int size = (end - begin);
        if (size <= 0)
            return;

        // TODO: improve pivot selection
        int pivotIndex = misc::randomNumber(0, size);
        typename std::iterator_traits<Iterator>::value_type pivot = *(begin + pivotIndex);

        if (pivotIndex != 0)
            std::swap(*(begin + pivotIndex), *begin);

        int i = 1;
        for (int j = 1; j < size; j++)
        {
            if (pred(*(begin + j), pivot))
            {
                std::swap(*(begin + j), *(begin + i));
                i++;
            }
        }

        std::swap(*begin, *(begin + i - 1));

        quickSort(begin, begin + i - 1, pred);
        quickSort(begin + i, end, pred);
    }

    // TODO: improve sort with multiple algorithms
    template <typename _IT, typename _PR>
    inline void sort(const _IT begin, const _IT end, _PR pred)
    {
        misc::quickSort(begin, end, pred);
    }

}
