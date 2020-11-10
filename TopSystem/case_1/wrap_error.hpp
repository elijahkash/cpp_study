#ifndef CASE_1_ERROR_HPP_
#define CASE_1_ERROR_HPP_

#include <variant>
#include <list>
#include <string>

template<typename T>
class WrapError {
 public:
  // Constructors can't be marked as noexcept:
  //  - constructor T may throw
  //  - std::bad_alloc in std::list and std::string

  // store value without error
  explicit WrapError(const T& val);
  explicit WrapError(T&& val);
  // store single error
  explicit WrapError(const std::string& error);
  explicit WrapError(std::string&& error);
  // inherit nested errors from existing WrapError (WrapError::getErrors())
  explicit WrapError(const std::list<std::string>& nested);
  explicit WrapError(std::list<std::string>&& nested);
  // inherit nested errors from existing WrapError (WrapError::getErrors())
  // and add new error (to errors list head)
  WrapError(const std::string& error, const std::list<std::string>& nested);
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
WrapError<T>::WrapError(const T& val)
  : value(val)  {
}

template<typename T>
WrapError<T>::WrapError(T&& val)
  : value(val) {
}

template<typename T>
WrapError<T>::WrapError(const std::string& error)
  : value(std::list<std::string>()) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::string&& error)
  : value(std::list<std::string>()) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(const std::string& error,
                        const std::list<std::string>& nested)
  : value(nested) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(std::string&& error, std::list<std::string>&& nested)
  : value(nested) {
  (std::get_if<std::list<std::string>>(&value))->emplace_front(error);
}

template<typename T>
WrapError<T>::WrapError(const std::list<std::string>& nested)
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
  // is hasError - undefined behavior (NULL-pointer dereference)
  return *std::get_if<T>(&value);
}

template<typename T>
std::list<std::string>& WrapError<T>::getErrors() noexcept {
  // is hasValue - undefined behavior (NULL-pointer dereference)
  return *std::get_if<std::list<std::string>>(&value);
}

#endif  // CASE_1_ERROR_HPP_
