#include <tao/pegtl.hpp>

namespace scheme
{
   namespace pegtl = tao::pegtl;

   using spacesP = pegtl::plus< pegtl::space >;
   using spacesS = pegtl::star< pegtl::space >;
   using newline = pegtl::string< '\n' >;
   using tab = pegtl::string< '\t' >;
   using whitespace = pegtl::sor< pegtl::space, newline, tab >;
   using whitespaces = pegtl::star< whitespace >;
   using tabnewline = pegtl::star< pegtl::sor< tab, newline > >;

   // ensure at least one space
   using whitespaceE = pegtl::seq< tabnewline, pegtl::space, whitespaces >;

   using T = pegtl::string< '#', 't' >;
   using F = pegtl::string< '#', 'f' >;
   using Quote = pegtl::string< '\\', '"' >;
   using Escape = pegtl::string< '\\', '\\' >;
   using Dot = pegtl::string< '.' >;
   using Plus = pegtl::string< '+' >;
   using Minus = pegtl::string< '-' >;
   using Exclamation = pegtl::string< '!' >;
   using Dollar = pegtl::string< '$' >;
   using Percent = pegtl::string< '%' >;
   using Ambersand = pegtl::string< '&' >;
   using Slash = pegtl::string< '/' >;
   using Colon = pegtl::string< ':' >;
   using LT = pegtl::string< '<' >;
   using EQ = pegtl::string< '=' >;
   using GT = pegtl::string< '>' >;
   using Question = pegtl::string< '?' >;
   using Tilde = pegtl::string< '~' >;
   using Underscore = pegtl::string< '_' >;
   using Caret = pegtl::string< '^' >;
   using LParen = pegtl::string< '(' >;
   using RParen = pegtl::string< ')' >;
   using SQuote = pegtl::string< '\'' >;
   using Define = pegtl::string< 'd', 'e', 'f', 'i', 'n', 'e' >;

   using boolean = pegtl::sor< T, F >;

   using AsciiQuote = pegtl::string< '"' >;
   using AsciiEscape = pegtl::string< '\\' >;
   using string_char = pegtl::sor< Quote,
                                   Escape,
                                   pegtl::minus< pegtl::seven,
                                                 pegtl::sor< AsciiQuote,
                                                             AsciiEscape > > >;

   using string = pegtl::seq< AsciiQuote, pegtl::star< string_char >, AsciiQuote >;

   using integer = pegtl::plus< pegtl::digit >;

   using decimal = pegtl::seq< integer, Dot, integer >;

   using number = pegtl::sor< decimal, integer >;

   using letter = pegtl::lower;

   using initial = pegtl::sor< letter,
                               Exclamation,
                               Dollar,
                               Percent,
                               Ambersand,
                               Slash,
                               Colon,
                               LT,
                               EQ,
                               GT,
                               Question,
                               Tilde,
                               Underscore,
                               Caret >;

   using subsequent = pegtl::sor< initial, pegtl::digit, Dot, Plus, Minus >;

   using initsub = pegtl::seq< initial, pegtl::star< subsequent > >;

   using identifier = pegtl::sor< Dot, Plus, Minus, initsub >;

   struct list;

   using datum = pegtl::sor< number, string, boolean, list, identifier >;

   struct list : pegtl::seq< LParen,
                             whitespaces,
                             datum,
                             pegtl::star< pegtl::seq< whitespaceE,
                                                      datum > >,
                             whitespaces,
                             RParen >
   {};

   using expressionA = pegtl::seq< LParen,
                                   whitespaces,
                                   identifier,
                                   whitespaceE,
                                   datum,
                                   pegtl::plus< pegtl::seq< whitespaceE, datum > >,
                                   whitespaces,
                                   RParen >;

   using expressionQ = pegtl::seq< SQuote, list >;

   using expression = pegtl::sor< expressionA, expressionQ, datum >;

   using body = pegtl::seq< LParen,
                            whitespaces,
                            expression,
                            pegtl::plus< pegtl::seq< whitespaceE,
                                                     expression > >,
                            whitespaces,
                            RParen >;

   using parameter_name = identifier;

   using definition = pegtl::sor< pegtl::seq< LParen,
                                              whitespaces,
                                              Define,
                                              whitespaceE,
                                              LParen,
                                              whitespaces,
                                              identifier,
                                              whitespaceE,
                                              pegtl::plus< parameter_name >,
                                              whitespaces,
                                              RParen,
                                              whitespaceE,
                                              body,
                                              whitespaces,
                                              RParen >,
                                  pegtl::seq< LParen,
                                              whitespaces,
                                              Define,
                                              whitespaceE,
                                              identifier,
                                              whitespaceE,
                                              datum,
                                              whitespaces,
                                              RParen > >;

   using form = pegtl::sor< definition, expression >;

   using program = pegtl::seq< form,
                               pegtl::star< pegtl::seq< whitespaceE,
                                                        form > >,
                               whitespaces >;

   using grammar = pegtl::seq< program, pegtl::eof >;

   template< typename Rule >
   using selector = pegtl::parse_tree::selector<
      Rule,
      pegtl::parse_tree::store_content::on<
         identifier,
         Define,
         body,
         number,
         string > >;

}  // namespace scheme