/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnord-base/SHA1.h>
#include <fnord-base/stringutil.h>

namespace fnord {

SHA1Hash::SHA1Hash() {
  memset(hash, 0,sizeof(hash));
}

SHA1Hash::SHA1Hash(DeferInitialization) {
  /* initialize nothing, this ctor is private and can only be called by SHA1 */
}

SHA1Hash::SHA1Hash(const void* data, size_t size) {
  if (size != sizeof(hash)) {
    RAISE(kRuntimeError, "invalid SHA1Hash");
  }

  memcpy(&hash, data, sizeof(hash));
}

String SHA1Hash::toString() const {
  return StringUtil::hexPrint(hash, sizeof(hash), false);
}

SHA1Hash SHA1::compute(const Buffer& data) {
  SHA1Hash hash(SHA1Hash::DeferInitialization{});
  compute(data.data(), data.size(), &hash);
  return hash;
}

void SHA1::compute(const Buffer& data, SHA1Hash* out) {
  compute(data.data(), data.size(), out);
}

SHA1Hash SHA1::compute(const String& data) {
  SHA1Hash hash(SHA1Hash::DeferInitialization{});
  compute(data.data(), data.size(), &hash);
  return hash;
}

void SHA1::compute(const String& data, SHA1Hash* out) {
  compute(data.data(), data.size(), out);
}

SHA1Hash SHA1::compute(const void* data, size_t size) {
  SHA1Hash hash(SHA1Hash::DeferInitialization{});
  compute(data, size, &hash);
  return hash;
}

/**
 * SHA1 Implementation from
 *    https://code.google.com/p/smallsha1/source/browse/trunk/sha1.h
 *
 * Copyright (c) 2011, Micael Hildenborg
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of Micael Hildenborg nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY Micael Hildenborg ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Micael Hildenborg BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
static inline const unsigned int rol(
    const unsigned int value,
    const unsigned int steps) {
  return ((value << steps) | (value >> (32 - steps)));
}

// Sets the first 16 integers in the buffert to zero.
// Used for clearing the W buffert.
static inline void clearWBuffert(unsigned int* buffert) {
  for (int pos = 16; --pos >= 0;) {
    buffert[pos] = 0;
  }
}

static void innerHash(unsigned int* result, unsigned int* w) {
  unsigned int a = result[0];
  unsigned int b = result[1];
  unsigned int c = result[2];
  unsigned int d = result[3];
  unsigned int e = result[4];

  int round = 0;

  #define sha1macro(func,val) \
              { \
      const unsigned int t = rol(a, 5) + (func) + e + val + w[round]; \
                      e = d; \
                      d = c; \
                      c = rol(b, 30); \
                      b = a; \
                      a = t; \
              }

  while (round < 16) {
      sha1macro((b & c) | (~b & d), 0x5a827999)
      ++round;
  }
  while (round < 20) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro((b & c) | (~b & d), 0x5a827999)
      ++round;
  }
  while (round < 40) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro(b ^ c ^ d, 0x6ed9eba1)
      ++round;
  }
  while (round < 60) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro((b & c) | (b & d) | (c & d), 0x8f1bbcdc)
      ++round;
  }
  while (round < 80) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro(b ^ c ^ d, 0xca62c1d6)
      ++round;
  }

  #undef sha1macro

  result[0] += a;
  result[1] += b;
  result[2] += c;
  result[3] += d;
  result[4] += e;
}

void SHA1::compute(const void* data, size_t size, SHA1Hash* out) {
  // Init the result array.
  unsigned int result[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

  // Cast the void src pointer to be the byte array we can work with.
  const unsigned char* sarray = (const unsigned char*) data;

  // The reusable round buffer
  unsigned int w[80];

  // Loop through all complete 64byte blocks.
  const int endOfFullBlocks = size - 64;
  int endCurrentBlock;
  int currentBlock = 0;

  while (currentBlock <= endOfFullBlocks) {
    endCurrentBlock = currentBlock + 64;

    // Init the round buffer with the 64 byte block data.
    for (int roundPos = 0; currentBlock < endCurrentBlock; currentBlock += 4) {
      // This line will swap endian on big endian and keep endian on little endian.
      w[roundPos++] = (unsigned int) sarray[currentBlock + 3]
              | (((unsigned int) sarray[currentBlock + 2]) << 8)
              | (((unsigned int) sarray[currentBlock + 1]) << 16)
              | (((unsigned int) sarray[currentBlock]) << 24);
    }

    innerHash(result, w);
  }

  // Handle the last and not full 64 byte block if existing.
  endCurrentBlock = size - currentBlock;
  clearWBuffert(w);
  int lastBlockBytes = 0;
  for (;lastBlockBytes < endCurrentBlock; ++lastBlockBytes) {
    w[lastBlockBytes >> 2] |= (unsigned int) sarray[lastBlockBytes + currentBlock] << ((3 - (lastBlockBytes & 3)) << 3);
  }

  w[lastBlockBytes >> 2] |= 0x80 << ((3 - (lastBlockBytes & 3)) << 3);
  if (endCurrentBlock >= 56) {
      innerHash(result, w);
      clearWBuffert(w);
  }
  w[15] = size << 3;
  innerHash(result, w);

  // Store hash in result pointer, and make sure we get in in the correct order on both endian models.
  for (int hashByte = 20; --hashByte >= 0;) {
      out->hash[hashByte] = (result[hashByte >> 2] >> (((3 - hashByte) & 0x3) << 3)) & 0xff;
  }
}

}
