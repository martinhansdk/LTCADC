#include "ltc_utility.h"
#include "gtest/gtest.h"

namespace {

// Tests that the Foo::Bar() method does Abc.
TEST(ConvertTest, convertsRawCorrectly) {
  // from table 3 in the LTC2439-1 data sheet
  EXPECT_EQ(     0, interpretADCResult(0b0010000000000000000, 16, 0xffff)); // 0
  EXPECT_EQ(     1, interpretADCResult(0b0010000000000000001, 16, 0xffff)); // +1LSB
  EXPECT_EQ(    -1, interpretADCResult(0b0001111111111111111, 16, 0xffff)); // -1LSB
  EXPECT_EQ( 32767, interpretADCResult(0b0010111111111111111, 16, 0xffff)); // largest value
  EXPECT_EQ(-32768, interpretADCResult(0b0001000000000000000, 16, 0xffff)); // smallest value
  EXPECT_EQ( 16384, interpretADCResult(0b0010100000000000000, 16, 0xffff)); // 0.25*Vref
  EXPECT_EQ(-16384, interpretADCResult(0b0001100000000000000, 16, 0xffff)); // -0.25*Vref
  EXPECT_EQ( 16383, interpretADCResult(0b0010011111111111111, 16, 0xffff)); // 0.25*Vref - 1LSB
  EXPECT_EQ(-16385, interpretADCResult(0b0001011111111111111, 16, 0xffff)); // -0.25*Vref - 1LSB
  EXPECT_EQ( 32768, interpretADCResult(0b0011000000000000000, 16, 0xffff)); // overflow
  EXPECT_EQ(-32769, interpretADCResult(0b0000111111111111111, 16, 0xffff)); // underflow
}

}  // namespace

