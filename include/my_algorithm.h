#ifndef MY_OPTIONAL_H
#define MY_OPTIONAL_H

#include <type_traits>
#include <iterator>
#include <cstring>
#include <functional>

template <typename InputIterator, typename OutputIterator>
OutputIterator my_copy(InputIterator srcFirst, InputIterator srcLast, OutputIterator destFirst)
{
    using ValueType = typename std::iterator_traits<InputIterator>::value_type;

    if constexpr (std::contiguous_iterator<InputIterator>
        && std::contiguous_iterator<OutputIterator>
        && std::is_trivially_copyable_v<ValueType>
        && !std::is_void_v<decltype(*destFirst = *srcFirst)>)
    {
        std::memmove(&(*destFirst), &(*srcFirst), std::distance(srcFirst, srcLast) * sizeof(ValueType));
        std::advance(destFirst, std::distance(srcFirst, srcLast));
        return destFirst;
    }

    while (srcFirst != srcLast)
    {
        *(destFirst++) = *(srcFirst++);
    }

    return destFirst;
}

template <typename InputIterator, typename OutputIterator, typename UnaryFunction>
OutputIterator my_transform(
    InputIterator srcFirst, InputIterator srcLast,
    OutputIterator destFirst, UnaryFunction transformFunc)
{
    while (srcFirst != srcLast)
    {
        *(destFirst++) = transformFunc(*(srcFirst++));
    }

    return destFirst;
}

template <typename FirstInputIterator, typename SecondInputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator my_transform(
    FirstInputIterator firstSrcFirst, FirstInputIterator firstSrcLast,
    SecondInputIterator secondSrcFirst, OutputIterator destFirst, BinaryFunction transformFunc)
{
    while (firstSrcFirst != firstSrcLast)
    {
        *(destFirst++) = transformFunc(*(firstSrcFirst++), *(secondSrcFirst++));
    }

    return destFirst;
}

template <typename InputIterator, typename T, typename BinaryFunction>
T my_map_reduce(
    InputIterator srcFirst, InputIterator srcLast,
    T&& init, BinaryFunction reduceFunc)
{
    while (srcFirst != srcLast)
    {
        init = reduceFunc(init, *(srcFirst++));
    }

    return init;
}

template <typename InputIterator, typename T>
T my_map_reduce(InputIterator srcFirst, InputIterator srcLast, T&& init)
{
    using IterType = typename std::iterator_traits<InputIterator>::value_type;

    while (srcFirst != srcLast)
    {
        init = std::plus<std::common_type_t<T, IterType>>{}(init, *(srcFirst++));
    }

    return init;
}

template <typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type my_map_reduce(
    InputIterator srcFirst, InputIterator srcLast)
{
    using IterType = typename std::iterator_traits<InputIterator>::value_type;

    IterType init{};

    while (srcFirst != srcLast)
    {
        init = std::plus<IterType>{}(init, *(srcFirst++));
    }

    return init;
}

#endif
