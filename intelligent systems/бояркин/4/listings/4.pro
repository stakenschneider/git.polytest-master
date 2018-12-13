implement main
    open core

class predicates
    add : (integer, integer).
    fadd : (real, real).
    maximum : (real, real, real [out]) nondeterm.

clauses
    add(X, Y) :-
        Z = X + Y,
        stdIO::write("Summary=", Z),
        stdIO::nl.

    fadd(X, Y) :-
        Z = X + Y,
        stdIO::write("FloatSummary=", Z),
        stdIO::nl.

    maximum(X, X, X).

    maximum(X, Y, X) :-
        X > Y.

    maximum(X, Y, Y) :-
        X < Y.

clauses
    run() :-
        console::init(),
        add(25, 11),
        fadd(3.1223, 5.1111),
        maximum(49, 5, Z),
        stdIO::write(Z),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
