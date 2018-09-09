/*!
 * @author fexolm 
 * @date 09.09.18.
 */
#pragma once
#include <memory>
#include <functional>
#include <cassert>
namespace utils {

namespace internal {
template<typename T> struct remove_class { };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...)> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) volatile> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const volatile> { using type = R(A...); };

template<typename T>
struct get_signature_impl { using type = typename remove_class<
      decltype(&std::remove_reference<T>::type::operator())>::type; };
template<typename R, typename... A>
struct get_signature_impl<R(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(&)(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(*)(A...)> { using type = R(A...); };
template<typename T> using get_signature = typename get_signature_impl<T>::type;

template<typename Base, typename T>
bool typecaseHelper( std::shared_ptr<Base> base, std::function<void(std::shared_ptr<T>)> func) {
  if (std::shared_ptr<T> first = std::dynamic_pointer_cast<T>(base)) {
    func(first);
    return true;
  }
  else {
    return false;
  }
}

}
template<typename Base>
void typecase(std::shared_ptr<Base>) {
  assert(false);
}

template<typename Base, typename FirstSubclass, typename... RestOfSubclasses>
void typecase(
    std::shared_ptr<Base> base,
    FirstSubclass &&first,
    RestOfSubclasses &&... rest) {

  using Signature = internal::get_signature<FirstSubclass>;
  using Function = std::function<Signature>;

  if (internal::typecaseHelper(base, (Function)first)) {
    return;
  }
  else {
    typecase(std::forward<std::shared_ptr<Base>>(base), rest...);
  }
}

}