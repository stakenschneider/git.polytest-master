implement main
    open core

class predicates
    name : (symbol) determ.
    name : (symbol [out]) multi.
    mesto : (symbol) determ.
    mesto : (symbol [out]) multi.
    prizer : (symbol, symbol) nondeterm.
    solution : (symbol [out], symbol [out], symbol [out], symbol [out], symbol [out], symbol [out]) determ.

clauses
    name("Alex").
    name("Pier").
    name("Nike").
    mesto("first").
    mesto("second").
    mesto("third").

    prizer(X, Y) :-
        name(X),
        mesto(Y),
        X = "Pier",
        not(Y = "second"),
        not(Y = "third")
        or
        name(X),
        mesto(Y),
        X = "Nike",
        not(Y = "third")
        or
        name(X),
        mesto(Y),
        not(X = "Pier"),
        not(X = "Nike").

    solution(X1, Y1, X2, Y2, X3, Y3) :-
        name(X1),
        name(X2),
        name(X3),
        mesto(Y1),
        mesto(Y2),
        mesto(Y3),
        prizer(X1, Y1),
        prizer(X2, Y2),
        prizer(X2, Y3),
        Y1 <> Y2,
        Y2 <> Y3,
        Y1 <> Y3,
        X1 <> X2,
        X2 <> X3,
        X1 <> X3,
        !.

    run() :-
        console::init(),
        solution(X1, Y1, X2, Y2, X3, Y3),
        stdIO::writef("% - %\n% - %\n% - %\n", X1, Y1, X2, Y2, X3, Y3),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
