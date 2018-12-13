implement main
    open core

domains
    person = symbol.

class predicates
    left : (person, person) nondeterm anyflow.
    pos : (person [out], person [out], person [out]) nondeterm.

clauses

    left("Vitya", "Ura").
    left("Ura", "Misha").

    pos(X, Y, Z) :-
        left(X, Y),
        left(Y, Z).

clauses
    run() :-
        console::init(),
        pos(X, Y, Z),
        stdIO::writef(X, " - ", Y, " - ", Z),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
