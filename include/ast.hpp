#pragma once

#include <variant>
#include <vector>
#include <deque>
#include <memory>

#include <cstdint>

using std::variant;
using std::shared_ptr;
using std::vector;
using std::deque;

struct List;

using String = std::string;

using Identifier = String;

using Number = variant<float, int64_t, uint64_t>;

using Boolean = bool;

using Datum = variant<Number, String, Boolean, Identifier, List>;

struct List {
  vector<Datum> datum;
};

struct ExpressionApp {
  Identifier id;
  vector<Datum> datum;
};

using ExpressionQuote = vector<Datum>;

using Expression = variant<ExpressionApp, ExpressionQuote, Datum>;

using ParameterName = Identifier;

using Body = vector<Expression>;

struct DefinitionVar {
  Identifier id;
  Datum datum;
};

struct DefinitionFun {
  Identifier id;
  vector<ParameterName> param_names;
  Body body;
};

using Definition = variant<DefinitionVar, DefinitionFun>;

using Format = variant<Definition, Expression>;

using Program = vector<Format>;

