implement main
    open core

domains
    person = symbol.

class predicates
    otec : (person, person) nondeterm anyflow.
    man : (person) nondeterm.
    brat : (person [out], person [out]) nondeterm.

clauses
    man(X) :-
        otec(X, _).

    brat(X, Y) :-
        otec(Z, Y),
        otec(Z, X),
        man(X),
        X <> Y.

    otec("ivan", "igor").
    otec("ivan", "sidor").
    otec("sidor", "lisa").

clauses
    run() :-
        console::init(),
        brat(X, Y),
        stdIO::writef("% is brother of %\n", X, Y),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
