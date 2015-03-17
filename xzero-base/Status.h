// This file is part of the "libxzero" project, http://xzero.io/
//   (c) 2009-2015 Christian Parpart <trapni@gmail.com>
//   (c) 2014-2015 Paul Asmuth
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#pragma once

#include <xzero-base/Api.h>
#include <system_error>

namespace xzero {

enum class Status {
  BufferOverflowError = 1,
  EncodingError,
  ConcurrentModificationError,
  DivideByZeroError,
  FlagError,
  IOError,
  IllegalArgumentError,
  IllegalFormatError,
  IllegalStateError,
  IndexError,
  InvalidOptionError,
  KeyError,
  MallocError,
  NoSuchMethodError,
  NotImplementedError,
  NotYetImplementedError,
  NullPointerError,
  ParseError,
  RangeError,
  ReflectionError,
  ResolveError,
  RPCError,
  RuntimeError,
  TypeError,
  UsageError,
  VersionMismatchError,
  WouldBlockError,
  FutureError,

  InvalidArgumentError,
  InternalError,
  InvalidUriPortError,
  CliTypeMismatchError,
  CliUnknownOptionError,
  CliMissingOptionError,
  CliMissingOptionValueError,
  CliFlagNotFoundError,
  SslPrivateKeyCheckError,
  OptionUncheckedAccessToInstance,
  CaughtUnknownExceptionError,
};

class StatusCategory : public std::error_category {
 public:
  static StatusCategory& get();

  const char* name() const noexcept override;
  std::string message(int ec) const override;
};

XZERO_API std::error_code makeErrorCode(Status ec);

enum StatusCompat { // {{{
  kBufferOverflowError = (int) Status::BufferOverflowError,
  kEncodingError = (int) Status::EncodingError,
  kConcurrentModificationError = (int) Status::ConcurrentModificationError,
  kDivideByZeroError = (int) Status::DivideByZeroError,
  kFlagError = (int) Status::FlagError,
  kIOError = (int) Status::IOError,
  kIllegalArgumentError = (int) Status::IllegalArgumentError,
  kIllegalFormatError = (int) Status::IllegalFormatError,
  kIllegalStateError = (int) Status::IllegalStateError,
  kIndexError = (int) Status::IndexError,
  kInvalidOptionError = (int) Status::InvalidOptionError,
  kKeyError = (int) Status::KeyError,
  kMallocError = (int) Status::MallocError,
  kNoSuchMethodError = (int) Status::NoSuchMethodError,
  kNotImplementedError = (int) Status::NotImplementedError,
  kNotYetImplementedError = (int) Status::NotYetImplementedError,
  kNullPointerError = (int) Status::NullPointerError,
  kParseError = (int) Status::ParseError,
  kRangeError = (int) Status::RangeError,
  kReflectionError = (int) Status::ReflectionError,
  kResolveError = (int) Status::ResolveError,
  kRPCError = (int) Status::RPCError,
  kRuntimeError = (int) Status::RuntimeError,
  kTypeError = (int) Status::TypeError,
  kUsageError = (int) Status::UsageError,
  kVersionMismatchError = (int) Status::VersionMismatchError,
  kWouldBlockError = (int) Status::WouldBlockError,
  kFutureError = (int) Status::FutureError
}; // }}}

}  // namespace xzero
