#include <xzero/net/ByteArrayEndPoint.h>
#include <gtest/gtest.h>

using namespace xzero;

TEST(ByteArrayEndPoint, setInput_cstr) {
  ByteArrayEndPoint ep(nullptr);
  ep.setInput("foo bar");

  ASSERT_EQ("foo bar", ep.input());
}

TEST(ByteArrayEndPoint, setInput_buf_moved) {
  Buffer input = "foo bar";
  ByteArrayEndPoint ep(nullptr);
  ep.setInput(std::move(input));

  ASSERT_EQ("foo bar", ep.input());
}

TEST(ByteArrayEndPoint, flush) {
  ByteArrayEndPoint ep(nullptr);

  ep.flush("foo");
  ASSERT_EQ("foo", ep.output());

  ep.flush(" bar");
  ASSERT_EQ("foo bar", ep.output());
}

TEST(ByteArrayEndPoint, fill) {
  ByteArrayEndPoint ep(nullptr);
  Buffer input = "foo ";

  ep.setInput("bar");
  ep.fill(&input);
  ASSERT_EQ("foo bar", input);
}

TEST(ByteArrayEndPoint, DISABLED_close) {
  ByteArrayEndPoint ep(nullptr);
  Buffer output;

  ep.setInput("foo");

  ASSERT_EQ(true, ep.isOpen());
  ep.close();
  ASSERT_EQ(false, ep.isOpen());

  ssize_t rv = ep.fill(&output);
  ASSERT_EQ(0, rv);
  ASSERT_EQ("", output);

  rv = ep.flush("bar");
  ASSERT_EQ(0, rv);
  ASSERT_EQ("", ep.output());
}
