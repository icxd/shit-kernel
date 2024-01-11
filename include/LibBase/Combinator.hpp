#pragma once

#include <LibBase/Common.hpp>
#include <LibBase/String.hpp>
#include <LibC/stddef.h>

class ParserCombinator {
  public:
    explicit ParserCombinator(String input) : m_input(input) {}

    constexpr size_t tell() const { return m_index; }
    constexpr size_t tell_remaining() const {
        return m_input.length() - m_index;
    }

    String remaining() const { return m_input.substring(m_index); }
    String input() const { return m_input; }

    constexpr bool eof() const { return m_index >= m_input.length(); }

    constexpr char peek(size_t offset = 0) const {
        return (m_index + offset < m_input.length())
                   ? m_input.get(m_index + offset)
                   : '\0';
    }

    constexpr bool next_is(char expected) const { return peek() == expected; }
    constexpr bool next_is(const char *expected) const {
        return next_is(String(expected));
    }
    constexpr bool next_is(String expected) const {
        for (size_t i = 0; i < expected.length(); i++) {
            if (peek(i) != expected.get(i)) return false;
        }
        return true;
    }

    constexpr void retreat() {
        VERIFY(m_index > 0);
        m_index--;
    }

    constexpr void retreat(size_t amount) {
        VERIFY(m_index >= amount);
        m_index -= amount;
    }

    constexpr char consume() {
        VERIFY(!eof());
        return m_input.get(m_index++);
    }

    template <typename T> constexpr bool consume_specific(T const &next) {
        if (!next_is(next)) return false;

        if constexpr (requires { next.length(); }) ignore(next.length());
        else ignore(sizeof(next));

        return true;
    }

    constexpr bool consume_specific(char const *next) {
        return consume_specific(String(next, strlen(next)));
    }

    constexpr void ignore(size_t count = 1) {
        count = MIN(count, m_input.length() - m_index);
        m_index += count;
    }

    constexpr void ignore_until(char c) {
        while (!eof() && peek() != c)
            ignore();
    }

    template <typename Predicate>
    constexpr bool next_is(Predicate predicate) const {
        return predicate(peek());
    }

    template <typename Predicate> String consume_while(Predicate predicate) {
        size_t start = m_index;
        while (!eof() && predicate(peek()))
            ignore();
        size_t length = m_index - start;

        if (length == 0) return String();
        return m_input.substring(start, length);
    }

    template <typename Predicate> String consume_until(Predicate predicate) {
        size_t start = m_index;
        while (!eof() && !predicate(peek()))
            ignore();
        size_t length = m_index - start;

        if (length == 0) return String();
        return m_input.substring(start, length);
    }

    template <typename Predicate>
    constexpr void ignore_while(Predicate predicate) {
        while (!eof() && predicate(peek()))
            ignore();
    }

    template <typename Predicate>
    constexpr void ignore_until(Predicate predicate) {
        while (!eof() && !predicate(peek()))
            ignore();
    }

  protected:
    String m_input;
    size_t m_index{0};
};