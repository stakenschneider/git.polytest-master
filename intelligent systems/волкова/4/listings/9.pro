implement main
    open core

class predicates
    buy_car : (symbol [out], symbol [out]) determ.
    car : (symbol [out], symbol [out], integer [out]) multi.
    color : (symbol, symbol) determ.

clauses
    car("moskwich", "blue", 12000).
    car("jiguli", "green", 26000).
    car("volvo", "blue", 24000).
    car("volga", "blue", 20000).
    car("audi", "green", 20000).
    color("blue", "dark").
    color("green", "light").

    buy_car(Model, Color) :-
        car(Model, Color, Price),
        color(Color, "light"),
        !,
        Price < 25000.

    run() :-
        console::init(),
        buy_car(X, Y),
        stdIO::writef("% - %\n", X, Y),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
