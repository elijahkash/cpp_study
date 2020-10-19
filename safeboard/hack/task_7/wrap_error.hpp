#ifndef SAFEBOARD_HACK_TASK_7_ERROR_HPP_
#define SAFEBOARD_HACK_TASK_7_ERROR_HPP_

#include <variant>
#include <list>
#include <string>

// tested on:
//  - Apple clang version 11.0.0 (clang-1100.0.33.17)
//  - g++-10 (Homebrew GCC 10.2.0) 10.2.0
// C++17

template<typename T>
class WrapError {
 public:
  // TODO: can't be marked as noexcept:
  //  - constructor T may throw
  //  - std::bad_alloc in std::list and std::string
  explicit WrapError(T& val);
  explicit WrapError(T&& val);
  explicit WrapError(std::string& error);
  explicit WrapError(std::string&& error);
  explicit WrapError(std::list<std::string>& nested);
  explicit WrapError(std::list<std::string>&& nested);
  WrapError(std::string& error, std::list<std::string>& nested);
  WrapError(std::string&& error, std::list<std::string>&& nested);

  explicit operator bool() const noexcept;
  [[nodiscard]] bool hasValue() const noexcept;
  [[nodiscard]] bool hasError() const noexcept;

  // undefined behavior if hasError()
  [[nodiscard]] T& operator ()() noexcept;
  // undefined behavior if hasValue()
  [[nodiscard]] std::list<std::string>& getErrors() noexcept;

 private:
  std::variant<T, std::list<std::string>> value;
};

template<typename T>
WrapError<T>::WrapError(T& val)
    : value(val)  {
}

template<typename T>
WrapError<T>::WrapError(T&& val)
: value(val) {
}

template<typename T>
WrapError<T>::WrapError(std::string& error)
: value(std::list<std::string>()) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::string&& error)
: value(std::list<std::string>()) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::string& error, std::list<std::string>& nested)
: value(nested) {
    (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::string&& error, std::list<std::string>&& nested)
: value(nested) {
    (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::list<std::string>& nested)
: value(nested) {
}

template<typename T>
WrapError<T>::WrapError(std::list<std::string>&& nested)
: value(nested) {
}

template<typename T>
WrapError<T>::operator bool() const noexcept {
  return std::get_if<T>(&value);
}

template<typename T>
bool WrapError<T>::hasValue() const noexcept {
  return static_cast<bool>(*this);
}

template<typename T>
bool WrapError<T>::hasError() const noexcept {
  return not static_cast<bool>(*this);
}

template<typename T>
T& WrapError<T>::operator()() noexcept {
  return *std::get_if<T>(&value);
}

template<typename T>
std::list<std::string>& WrapError<T>::getErrors() noexcept {
  return *std::get_if<std::list<std::string>>(&value);
}

#endif //SAFEBOARD_HACK_TASK_7_ERROR_HPP_
