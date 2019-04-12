implement main
    open core

domains
    nazvanie = symbol.
    stolica = symbol.
    naselenie = integer.
    territoria = real.

class predicates
    strana : (nazvanie [out], naselenie [out], territoria [out], stolica [out]) multi.
clauses
    strana("kitai", 1200, 9597000, "pekin").
    strana("belgia", 10, 30000, "brussel").
    strana("peru", 20, 1285000, "lima").

clauses
    run() :-
        console::init(),
        strana(X, _, Y, _),
        Y > 1000000,
        stdIO::writef("% - %\n", X, Y),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
