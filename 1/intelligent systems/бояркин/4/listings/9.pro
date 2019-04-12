implement main
    open core

class predicates
    buy_car : (symbol [out], symbol [out]) determ.
    car : (symbol [out], symbol [out], integer [out]) multi.
    color : (symbol, symbol) determ.

clauses
    car("москвич", "синий", 12000).
    car("жигули", "зеленый", 26000).
    car("вольво", "синий", 24000).
    car("волга", "синий", 20000).
    car("ауди", "зеленый", 20000).
    color("синий", "темный").
    color("зеленый", "светлый").

    buy_car(Model, Color) :-
        car(Model, Color, Price),
        color(Color, "светлый"),
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
