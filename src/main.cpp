#include <iostream>
#include <string>
#include <variant>

#include <tao/pegtl.hpp>

#include <ast.hpp>
#include <parser.hpp>

namespace pegtl = tao::pegtl;

int main( int argc, char** argv )
{
   using namespace scheme;

   pegtl::memory_input in( "(define (hello world) (+ hello world))", "" );

   if( pegtl::parse< scheme::grammar< program > >( in ) ) {
      std::cout << "I see" << std::endl;
   }
   else {
      std::cerr << "I don't understand." << std::endl;
   }
}