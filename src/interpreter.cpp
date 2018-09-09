//
// Created by fexolm on 08.09.18.
//

#include <memory>
#include <iostream>
#include <numeric>
#include "ast.hpp"
#include "utils.h"

std::shared_ptr<ast::value_node<int>> read_value() {
  auto res = std::make_shared<ast::value_node<int>>();
  std::cin >> res->value;
  return res;
}

std::shared_ptr<ast::value_node<std::string>> read_func() {
  auto res = std::make_shared<ast::value_node<std::string>>();
  std::cin >> res->value;
  return res;
}

std::shared_ptr<ast::list_node> read_list() {
  if (std::cin.get()!='(') return nullptr;

  int count = 1;
  std::shared_ptr<ast::list_node> res = std::make_shared<ast::list_node>();

  while (count) {
    while (std::cin.peek()==' ') {
      std::cin.get();
    }
    switch (std::cin.peek()) {
      case '(':;
        res->args.push_back(read_list());
        break;
      case ')':count--;
        std::cin.get();
        break;
      default:
        if (std::isdigit(std::cin.peek())) {
          res->args.push_back(read_value());
        } else {
          res->args.push_back(read_func());
        }
        break;
    }
  }
  return res;
}

int do_op(std::string op, std::vector<int> args) {
  if (op=="sum") {
    return std::accumulate(args.begin(), args.end(), 0);
  }
  if (op=="mul") {
    return std::accumulate(args.begin(), args.end(), 1, std::multiplies<int>());
  }
  return -100500;
}

int eval(std::shared_ptr<ast::list_node> root) {
  if (!root) throw std::runtime_error("invalid code");
  if (root->args.empty()) throw std::runtime_error("empty argument list");
  auto op = std::dynamic_pointer_cast<ast::value_node<std::string>>(root->args[0]);
  if (!op) throw std::runtime_error("no operation");

  std::vector<int> args;

  for (int i = 1; i < root->args.size(); i++) {
    utils::typecase(root->args[i],
    [&args](std::shared_ptr<ast::value_node<int>> node) {
      args.push_back(node->value);
    },
    [&args](std::shared_ptr<ast::list_node> node) {
      args.push_back(eval(node));
    });
  }

  return do_op(op->value, args);
}

int main() {
  std::shared_ptr<ast::list_node> root = read_list();

  std::cout << eval(root);

}