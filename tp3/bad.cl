
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "myparser bad.cl" to see the error messages that your parser
 *  generates
 *)


Class A {
};


class B inherits a {
};

class C {
   foo():Int{{ 
   	while True loop 1 pool;
	while false looo 1 pool;
    }};
};

class D {

   foo:Int <- 25;
   
   foo(A:Int): Int  {
      a - b
   };
    
};