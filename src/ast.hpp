#pragma once

#include <variant>
#include <vector>
#include <memory>
#include <cstdint>

using std::variant;
using std::shared_ptr;
using std::vector;

struct List;

struct Identifier {
  std::string str;
};

using Number = variant<shared_ptr<float>, shared_ptr<int64_t>, shared_ptr<uint64_t>>;

using Booean = bool;

using Datum = variant<shared_ptr<Number>, shared_ptr<String>, shared_ptr<Boolean>, shared_ptr<Identifier>, shared_ptr<List>>;

struct List {
  vector<shared_ptr<Datum>> datum;
};

struct ExpressionApp {
  shared_ptr<Identifier> id;
  vector<shared_ptr<Datum>> datum;
};

using ExpressionQuote = vector<shared_ptr<Datum>>;

using Expression = variant<shared_ptr<ExpressionApp>, shared_ptr<ExpressionQuote>, shared_ptr<Datum>>;

using ParameterName = shared_ptr<Identifier>;

using Body = vector<shared_ptr<Expression>>;

struct DefinitionVar {
  shared_ptr<Identifier> id;
  shared_ptr<Datum> datum;
};

struct DefinitionFun {
  shared_ptr<Identifier> id;
  vector<shared_ptr<ParameterName>> param_names;
  shared_ptr<Body> body;
};

using Definition = variant<shared_ptr<DefinitionVar>, shared_ptr<DefinitionFun>>;

using Form = variant<shared_ptr<Definition>, shared_ptr<Expression>>;

using Program = vector<shared_ptr<Form>>;

