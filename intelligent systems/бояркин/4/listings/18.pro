implement main
    open core

domains
    name = symbol.

class predicates
    student : (name) determ.
    student : (name [out]) multi.
    gorod : (name) determ.
    gorod : (name [out]) multi.
    velo : (name, name) determ.
    fact : (name, name) determ anyflow.
    fact1 : (name, name) determ anyflow.
    rodom : (name, name) nondeterm.
    rodom : (name [out], name) nondeterm.
    rodom_penza : (name) nondeterm.

clauses
    student(X) :-
        X = "Сергей"
        or
        X = "Борис"
        or
        X = "Виктор"
        or
        X = "Григорий"
        or
        X = "Леонид".

    gorod(Y) :-
        Y = "Пенза"
        or
        Y = "Львов"
        or
        Y = "Москва"
        or
        Y = "Харьков"
        or
        Y = "Рига".

    fact("Сергей", "Рига").
    fact("Борис", "Пенза").
    fact("Виктор", "Москва").
    fact("Григорий", "Харьков").

    velo(X, Y) :-
        student(X),
        gorod(Y),
        fact(X, Y),
        !
        or
        student(X),
        gorod(Y),
        not(fact(X, _)),
        not(fact(_, Y)).

    fact1("Борис", "Рига").
    fact1("Виктор", "Львов").

    rodom_penza(X) :-
        student(X),
        not(fact1(X, _)),
        gorod(U),
        not(U = "Пенза"),
        velo(X, U),
        rodom("Леонид", U).

    rodom(X, Z) :-
        student(X),
        gorod(Z),
        fact1(X, Z),
        !
        or
        student(X),
        not(X = "Леонид"),
        Z = "Пенза",
        rodom_penza(X),
        !
        or
        student(X),
        gorod(Z),
        not(fact1(_, Z)),
        X = "Леонид",
        not(Z = "Пенза"),
        student(K),
        not(fact1(K, _)),
        velo(K, Z)
        or
        student(X),
        not(X = "Леонид"),
        gorod(Z),
        not(Z = "Пенза"),
        not(fact1(_, Z)),
        not(fact1(X, _)),
        gorod(Y),
        not(Y = Z),
        velo(X, Y),
        not(rodom("Леонид", Z)),
        not(rodom("Леонид", Y)).

    run() :-
        console::init(),
        rodom(X, "Москва"),
        stdIO::writef("% родом из Москвы", X),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
