implement main
    open core

class predicates
    name : (symbol) determ.
    name : (symbol [out]) multi.
    animal : (symbol) determ.
    animal : (symbol [out]) multi.
    own : (symbol, symbol) nondeterm.
    solution : (symbol [out], symbol [out], symbol [out], symbol [out], symbol [out], symbol [out]) determ.

clauses
    name("Петя").
    name("Таня").
    name("Лена").
    animal("Кошка").
    animal("Собака").
    animal("Хомяк").

    own(X, Y) :-
        name(X),
        animal(Y),
        X = "Петя",
        not(Y = "Кошка"),
        not(Y = "Хомяк")
        or
        name(X),
        animal(Y),
        X = "Таня",
        Y = "Кошка"
        or
        name(X),
        animal(Y),
        not(X = "Петя"),
        not(X = "Таня").

    solution(X1, Y1, X2, Y2, X3, Y3) :-
        name(X1),
        name(X2),
        name(X3),
        animal(Y1),
        animal(Y2),
        animal(Y3),
        own(X1, Y1),
        own(X2, Y2),
        own(X3, Y3),
        X1 <> X2,
        X2 <> X3,
        X1 <> X3,
        Y1 <> Y2,
        Y2 <> Y3,
        Y1 <> Y3,
        !.

    run() :-
        console::init(),
        solution(X1, Y1, X2, Y2, X3, Y3),
        stdIO::writef("% гуляет с %\n", X1, Y1),
        stdIO::writef("% гуляет с %\n", X2, Y2),
        stdIO::writef("% гуляет с %\n", X3, Y3),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
