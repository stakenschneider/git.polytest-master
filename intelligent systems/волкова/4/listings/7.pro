implement main
    open core

class predicates
    gorod : (symbol [out]) multi.
clauses
    gorod("Moscow").
    gorod("Minsk").
    gorod("Kiev").
    gorod("Omsk").

    show() :-
        gorod(X),
        stdIO::write(X),
        stdIO::nl(),
        fail.

    show().

end implement main

goal
    console::init(),
    stdIO::write("cities:"),
    stdIO::nl(),
    main::show().

