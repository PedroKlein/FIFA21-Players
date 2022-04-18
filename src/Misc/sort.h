#pragma once

namespace misc
{
    const size_t MAX_ISORT = 32;

    template <typename _IT, typename _PR>
    void sort(const _IT begin, const _IT end, _PR pred)
    {
        for (;;)
        {
            if (end - begin <= MAX_ISORT)
            { // small
                _Insertion_sort_unchecked(begin, end, _Pred);
                return;
            }

            // divide and conquer by quicksort
            auto _Mid = _Partition_by_median_guess_unchecked(begin, end, _Pred);

            _Ideal = (_Ideal >> 1) + (_Ideal >> 2); // allow 1.5 log2(N) divisions

            if (_Mid.first - begin < end - _Mid.second)
            { // loop on second half
                _Sort_unchecked(begin, _Mid.first, _Ideal, _Pred);
                begin = _Mid.second;
            }
            else
            { // loop on first half
                _Sort_unchecked(_Mid.second, end, _Ideal, _Pred);
                end = _Mid.first;
            }
        }
    }
}
