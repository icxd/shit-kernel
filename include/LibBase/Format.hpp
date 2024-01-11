#pragma once

#include <LibBase/Combinator.hpp>
#include <LibBase/Common.hpp>
#include <LibBase/Error.hpp>
#include <LibBase/NumericLimits.hpp>
#include <LibBase/String.hpp>

class FormatParser : public ParserCombinator {
  public:
    struct FormatSpecifier {
        String flags;
        size_t index;
    };

    explicit FormatParser(String input) : ParserCombinator(input) {}

    String consume_literal();
    bool consume_number(size_t &value);
    bool consume_specifier(FormatSpecifier &specifier);
    bool consume_replacement_field(size_t &index);
};

String FormatParser::consume_literal() {
    auto const begin = tell();
    while (!eof()) {
        if (consume_specific("{{")) continue;
        if (consume_specific("}}")) continue;

        if (next_is('{') || next_is('}'))
            return m_input.substring(begin, tell() - begin);

        consume();
    }

    return m_input.substring(begin);
}

bool FormatParser::consume_number(size_t &value) {}

bool FormatParser::consume_specifier(FormatSpecifier &specifier) {
    VERIFY(!next_is('}'));
    if (!consume_specific('{')) return false;
    if (!consume_number(specifier.index))
        specifier.index = NumericLimits<size_t>::max();

    if (consume_specific(':')) {
        auto const begin = tell();

        size_t level = 1;
        while (level > 0) {
            VERIFY(!eof());

            if (consume_specific('{')) {
                level++;
                continue;
            }

            if (consume_specific('}')) {
                level--;
                continue;
            }

            consume();
        }

        specifier.flags = m_input.substring(begin, tell() - begin - 1);
    } else {
        if (!consume_specific('}')) VERIFY_NOT_REACHED();

        specifier.flags = "";
    }

    return true;
}

bool FormatParser::consume_replacement_field(size_t &index) {
    if (!consume_specific('{')) return false;
    if (!consume_number(index)) index = NumericLimits<size_t>::max();
    if (!consume_specific('}')) VERIFY_NOT_REACHED();
    return true;
}

template <typename T> struct Foramttable {
    constexpr String format() virtual const = 0;
};

class FormatBuilder {
  public:
    enum class Alignment { Default, Left, Center, Right };
    enum class Sign { Default, Always, OnlyNegative };
    enum class RealFormat { Default, Fixed, Scientific };

    explicit FormatBuilder(StringBuilder &sb) : m_sb(sb) {}

    ErrorOr<void> put_padding(char fill, size_t amount);
    ErrorOr<void> put_literal(String literal);
    ErrorOr<void> put_string(String value,
                             Alignment alignment = Alignment::Left,
                             size_t min_width = 0,
                             size_t max_width = NumericLimits<size_t>::max(),
                             char fill = ' ');
    ErrorOr<void> put_u64(uint64_t value, uint8_t base = 10,
                          bool prefix = false, bool uppercase = false,
                          bool zero_pad = false, bool use_separator = false,
                          Alignment alignment = Alignment::Right,
                          size_t min_width = 0, char fill = ' ',
                          Sign sign = Sign::Default, bool is_negative = false);
    ErrorOr<void> put_i64(int64_t value, uint8_t base = 10, bool prefix = false,
                          bool uppercase = false, bool zero_pad = false,
                          bool use_separator = false,
                          Alignment alignment = Alignment::Right,
                          size_t min_width = 0, char fill = ' ',
                          Sign sign = Sign::Default, bool is_negative = false);

  private:
    StringBuilder &m_sb;
};