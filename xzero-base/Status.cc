// This file is part of the "libxzero" project, http://xzero.io/
//   (c) 2009-2015 Christian Parpart <trapni@gmail.com>
//   (c) 2014-2015 Paul Asmuth
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include <xzero-base/Status.h>
#include <string>

namespace xzero {

std::error_code makeErrorCode(Status ev) {
  return std::error_code((int) ev, StatusCategory::get());
}

StatusCategory& StatusCategory::get() {
  static StatusCategory cat;
  return cat;
}

const char* StatusCategory::name() const noexcept {
  return "XzeroStatus";
}

std::string StatusCategory::message(int ec) const {
  switch (static_cast<Status>(ec)) {
    case Status::BufferOverflowError: return "BufferOverflowError";
    case Status::EncodingError: return "EncodingError";
    case Status::ConcurrentModificationError: return "ConcurrentModificationError";
    case Status::DivideByZeroError: return "DivideByZeroError";
    case Status::FlagError: return "FlagError";
    case Status::IOError: return "IOError";
    case Status::IllegalArgumentError: return "IllegalArgumentError";
    case Status::IllegalFormatError: return "IllegalFormatError";
    case Status::IllegalStateError: return "IllegalStateError";
    case Status::IndexError: return "IndexError";
    case Status::InvalidOptionError: return "InvalidOptionError";
    case Status::KeyError: return "KeyError";
    case Status::MallocError: return "MallocError";
    case Status::NoSuchMethodError: return "NoSuchMethodError";
    case Status::NotImplementedError: return "NotImplementedError";
    case Status::NotYetImplementedError: return "NotYetImplementedError";
    case Status::NullPointerError: return "NullPointerError";
    case Status::ParseError: return "ParseError";
    case Status::RangeError: return "RangeError";
    case Status::ReflectionError: return "ReflectionError";
    case Status::ResolveError: return "ResolveError";
    case Status::RPCError: return "RPCError";
    case Status::RuntimeError: return "RuntimeError";
    case Status::TypeError: return "TypeError";
    case Status::UsageError: return "UsageError";
    case Status::VersionMismatchError: return "VersionMismatchError";
    case Status::WouldBlockError: return "WouldBlockError";
    case Status::FutureError: return "FutureError";
    //.
    case Status::InvalidArgumentError: return "Invalid Argument Error";
    case Status::InternalError: return "Internal Error";
    case Status::InvalidUriPortError: return "Invalid URI-Port Error";
    case Status::CliTypeMismatchError: return "Type Mismatch Error";
    case Status::CliUnknownOptionError: return "Unknown Option Error";
    case Status::CliMissingOptionError: return "Missing Option Error";
    case Status::CliMissingOptionValueError: return "Missing Option Value Error";
    case Status::CliFlagNotFoundError: return "Flag Not Found Error";
    case Status::SslPrivateKeyCheckError: return "Private Key Check Error";
    case Status::OptionUncheckedAccessToInstance: return "Unchecked access to Option instance";
    case Status::CaughtUnknownExceptionError: return "Caught Unknown exception Error";
    //.
    default: return "Unknown Xzero Status Code";
  }
}

} // namespace xzero
