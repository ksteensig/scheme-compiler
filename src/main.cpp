#include <iostream>
#include <string>
#include <variant>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>

#include <ast.hpp>
#include <parser.hpp>

namespace pegtl = tao::pegtl;

int main( int argc, char** argv )
{
   using namespace scheme;

   pegtl::memory_input in( "(define (hello world) (+ \"hello, world! this is a string inside scheme.\" 1))", "" );

   auto root = tao::pegtl::parse_tree::parse< scheme::grammar, scheme::selector >( in );

   if( root ) {
      std::cout << "I see: " << root->children[ 3 ]->children[ 1 ]->string() << std::endl;
   }
   else {
      std::cerr << "I don't understand." << std::endl;
   }

   return 0;
}