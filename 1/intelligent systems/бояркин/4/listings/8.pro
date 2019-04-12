implement main
    open core

domains
    person = symbol.

class predicates
    deti : (person [out]) multi.
    make_cut : (person) determ.

clauses
    deti("Петя").
    deti("Вася").
    deti("Олег").
    deti("Маша").
    deti("Оля").
    deti("Наташа").

    show() :-
        deti(X),
        stdIO::write(X),
        stdIO::nl(),
        make_cut(X),
        !.

    show().

    make_cut(X) :-
        X = "Олег".

end implement main

goal
    console::init(),
    stdIO::write("Это мальчики:"),
    stdIO::nl(),
    main::show().
