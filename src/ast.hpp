//
// Created by fexolm on 08.09.18.
//

#pragma once
#include <memory>
#include <vector>

namespace ast {

enum class types {
  Int8,
  Int16,
  Int32,
  Int64,
  Uint8,
  Uint16,
  Uint32,
  Uint64,
  Float32,
  Float64,
  Ufloat32,
  Ufloat64,
  String,
  Pointer,
};

struct base_node {
  virtual ~base_node() = default;
};

struct atom_node : base_node {

};

struct symbol_node : atom_node {
  std::string name;
};
template <typename T>
struct value_node : atom_node {
  using value_type = T;
  T value;
  types type;
};

struct list_node : base_node{
  std::vector<std::shared_ptr<base_node>> args;
};

}
