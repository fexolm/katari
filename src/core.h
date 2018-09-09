/*!
 * @author fexolm 
 * @date 09.09.18.
 */
#pragma once

#include <memory>
#include "ast.hpp"

namespace core {

inline std::shared_ptr<ast::base_node>
eval(std::shared_ptr<ast::base_node> node) {
  auto typeinfo = typeid(node);
  std::dynamic_pointer_cast()
}

}
