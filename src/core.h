/*!
 * @author fexolm 
 * @date 09.09.18.
 */
#pragma once

#include <memory>
#include "ast.hpp"
#include "utils.h"
namespace core {

inline std::shared_ptr<ast::base_node>
eval_list(std::shared_ptr<ast::list_node> list) {

}

inline std::shared_ptr<ast::base_node>
eval_atom(std::shared_ptr<ast::atom_node> atom) {

}

inline std::shared_ptr<ast::base_node>
eval(std::shared_ptr<ast::base_node> node) {
  std::shared_ptr<ast::base_node> result;
  bool success = utils::typecase(node,
                  [&result](std::shared_ptr<ast::list_node> node) {
                    result = eval_list(node);
                  },
                  [&result](std::shared_ptr<ast::atom_node> node) {
                    result = eval_atom(node);
                  }
  );

  if(!success) throw std::runtime_error("can not evaluate expr");

  return result;
}
}
