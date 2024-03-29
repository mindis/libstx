/**
 * This file is part of the "libstx" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * libstx is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _STX_STDTYPES_H
#define _STX_STDTYPES_H
#include <ctime>
#include <deque>
#include <inttypes.h>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

namespace stx {

using String = std::string;
using WString = std::wstring;
using UTF32String = std::string;

template <typename T>
using ScopedPtr = std::unique_ptr<T>;

template <typename T>
using ScopedLock = std::unique_lock<T>;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Set = std::set<T>;

template <typename T>
using List = std::list<T>;

template <typename T>
using Deque = std::deque<T>;

template <typename T>
using Function = std::function<T>;

template <typename T1, typename T2>
using Pair = std::pair<T1, T2>;

template <typename... T>
using Tuple = std::tuple<T...>;

template <typename T1, typename T2>
using HashMap = std::unordered_map<T1, T2>;

template <typename T1, typename T2>
using OrderedMap = std::map<T1, T2>;

template <typename T>
using Stack = std::stack<T>;

using StandardException = std::exception;

} // namespace stx
#endif
