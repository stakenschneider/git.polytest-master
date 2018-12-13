implement main
    open core

class predicates
    summa : (integer, integer [out]).
clauses
    summa(X, Y) :-
        X < 10,
        Y = X,
        !.

    summa(X, Y) :-
        X1 = X div 10,
        summa(X1, Y1),
        Y = Y1 + X mod 10.

    run() :-
        console::init(),
        summa(138965, Y),
        stdIO::write(Y),
        stdIO::nl().

end implement main

goal
    console::runUtf8(main::run).
