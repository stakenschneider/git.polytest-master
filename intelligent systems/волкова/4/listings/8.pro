implement main
    open core

domains
    person = symbol.

class predicates
    deti : (person [out]) multi.
    make_cut : (person) determ.

clauses
    deti("Peter").
    deti("Vasya").
    deti("Oleg").
    deti("Masha").
    deti("Olyay").
    deti("Natasha").

    show() :-
        deti(X),
        stdIO::write(X),
        stdIO::nl(),
        make_cut(X),
        !.

    show().

    make_cut(X) :-
        X = "Oleg".

end implement main

goal
    console::init(),
    stdIO::write("Boys:"),
    stdIO::nl(),
    main::show().
