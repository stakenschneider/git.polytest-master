implement main
    open core

class predicates
    gorod : (symbol [out]) multi.
clauses
    gorod("Москва").
    gorod("Минск").
    gorod("Киев").
    gorod("Омск").

    show() :-
        gorod(X),
        stdIO::write(X),
        stdIO::nl(),
        fail.

    show().

end implement main

goal
    console::init(),
    stdIO::write("Это города:"),
    stdIO::nl(),
    main::show().

