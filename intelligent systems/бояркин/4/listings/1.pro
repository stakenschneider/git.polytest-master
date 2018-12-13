implement main
    open core

class predicates
    situ : (string Gorod, string Strana) nondeterm anyflow.
clauses
    situ("london", "england").
    situ("petersburg", "russia").
    situ("kiev", "ukraine").
    situ("pekin", "asia").
    situ("warszawa", "poland").
    situ("berlin", "europe").
    situ(X, "europe") :-
        situ(X, "russia").
    situ(X, "europe") :-
        situ(X, "poland").
		
clauses
    run() :-
        console::init(),
        situ(X, Y),
        stdIO::writef("% - %\n", X, Y),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
