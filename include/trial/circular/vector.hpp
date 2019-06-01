#ifndef TRIAL_CIRCULAR_VECTOR_HPP
#define TRIAL_CIRCULAR_VECTOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <trial/circular/span.hpp>

namespace trial
{
namespace circular
{

template <typename T, typename Allocator = typename std::vector<T>::allocator_type>
class vector
    : private std::vector<T, Allocator>,
      private circular::span<T>
{
    using storage = std::vector<T, Allocator>;
    using span = circular::template span<T>;

public:
    using value_type = typename span::value_type;
    using size_type = typename span::size_type;
    using reference = typename span::reference;
    using const_reference = typename span::const_reference;
    using const_iterator = typename span::const_iterator;
    using allocator_type = Allocator;

    //! @brief Creates an empty circular vector with no capacity.
    //!
    //! @post capacity() == 0
    //! @post size() == 0

    vector() noexcept(std::is_nothrow_default_constructible<storage>::value);

    //! @brief Creates empty circular vector with no capacity using allocator.
    //!
    //! @post capacity() == 0
    //! @post size() == 0

    explicit vector(const allocator_type&) noexcept(std::is_nothrow_constructible<storage, const allocator_type&>::value);

    //! @brief Creates circular vector by copy construction.

    vector(const vector&);

    //! @brief Creates circular vector by copy construction with allocator.

    vector(const vector&,
           const allocator_type&);

    //! @brief Creates circular vector by move construction.

    vector(vector&&) noexcept(std::is_nothrow_move_constructible<storage>::value) = default;

    //! @brief Creates circular vector by move construction with allocator.

    vector(vector&&,
           const allocator_type&) noexcept(std::is_nothrow_constructible<storage, storage&&, const allocator_type&>::value);

    //! @brief Recreates circular vector by copy assignment.

    vector& operator=(const vector&);

    //! @brief Recreates circular vector by move assignment.

    vector& operator=(vector&&) noexcept(std::is_nothrow_move_assignable<storage>::value) = default;

    //! @brief Creates empty circular vector with capacity.
    //!
    //! @pre T must be default constructible.
    //!
    //! @post capacity() == capacity
    //! @post size() == 0

    explicit vector(size_type capacity);

    //! @brief Creates empty circular vector with capacity using allocator.
    //!
    //! @pre T must be default constructible.
    //!
    //! @post capacity() == capacity
    //! @post size() == 0

    vector(size_type capacity,
           const allocator_type&);

    //! @brief Creates circular vector with element from initializer list.
    //!
    //! @post capacity() == input.size()
    //! @post size() == input.size()

    vector(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Creates circular vector with element from initializer list with allocator.
    //!
    //! @post capacity() == input.size()
    //! @post size() == input.size()

    vector(std::initializer_list<value_type> input,
           const allocator_type&) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Recreates circular vector from initializer list.
    //!
    //! @post capacity() == input.size()
    //! @post size() == input.size()

    vector& operator=(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Creates circular vector with elements from range.
    //!
    //! @post capacity() == std::distance(first, last)
    //! @post size() == capacity()

    template <typename InputIterator>
    vector(InputIterator first,
           InputIterator last) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Creates circular vector with elements from range using allocator.
    //!
    //! @post capacity() == std::distance(first, last)
    //! @post size() == capacity()

    template <typename InputIterator>
    vector(InputIterator first,
           InputIterator last,
           const allocator_type&) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Returns underlying allocator.

    allocator_type get_allocator() const;

    //! @brief Checks if circular vector is empty.

    using span::empty;

    //! @brief Checks if circular vector is full.

    using span::full;

    //! @brief Returns the maximum possible number of elements in circular vector.

    using span::capacity;

    //! @brief Returns the number of elements in circular vector.

    using span::size;

    //! @brief Returns the maximum number of possible elements in circular vector.

    size_type max_size() const noexcept;

    //! @brief Returns reference to first element in circular vector.

    using span::front;

    //! @brief Returns reference to last element in span.

    using span::back;

    //! @brief Returns reference to element at position.

    using span::operator[];

    //! @brief Clears the circular vector.

    using span::clear;

    //! @brief Clears circular vector and inserts element at end of circular vector.

    using span::assign;

    //! @brief Inserts element at beginning of circular vector.

    using span::push_front;

    //! @brief Inserts element at end of circular vector.

    using span::push_back;

    //! @brief Erases element from beginning of circular vector.

    using span::pop_front;

    //! @brief Erases element from end of circular vector.

    using span::pop_back;

    //! @brief Moves element from beginning of circular vector.

    using span::move_front;

    //! @brief Moves element from end of circular vector.

    using span::move_back;

    //! @brief Returns iterator to beginning of circular vector.

    using span::begin;

    //! @brief Returns iterator to ending of circular vector.

    using span::end;

    //! @brief Returns const iterator to beginning of circular vector.

    using span::cbegin;

    //! @brief Returns const iterator to ending of circular vector.

    using span::cend;
};

} // namespace circular
} // namespace trial

#include <trial/circular/detail/vector.ipp>

#endif // TRIAL_CIRCULAR_VECTOR_HPP