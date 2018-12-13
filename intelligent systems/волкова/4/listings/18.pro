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
        X = "Sergey"
        or
        X = "Boris"
        or
        X = "Viktor"
        or
        X = "Gregory"
        or
        X = "Leonid".

    gorod(Y) :-
        Y = "Penza"
        or
        Y = "L'vov"
        or
        Y = "Moscow"
        or
        Y = "Har'kov"
        or
        Y = "Riga".

    fact("Sergey", "Riga").
    fact("Boris", "Penza").
    fact("Viktor", "Moscow").
    fact("Gregory", "Har'kov").

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

    fact1("Boris", "Riga").
    fact1("Viktor", "L'vov").

    rodom_penza(X) :-
        student(X),
        not(fact1(X, _)),
        gorod(U),
        not(U = "Penza"),
        velo(X, U),
        rodom("Leonid", U).

    rodom(X, Z) :-
        student(X),
        gorod(Z),
        fact1(X, Z),
        !
        or
        student(X),
        not(X = "Leonid"),
        Z = "Penza",
        rodom_penza(X),
        !
        or
        student(X),
        gorod(Z),
        not(fact1(_, Z)),
        X = "Leonid",
        not(Z = "Penza"),
        student(K),
        not(fact1(K, _)),
        velo(K, Z)
        or
        student(X),
        not(X = "Leonid"),
        gorod(Z),
        not(Z = "Penza"),
        not(fact1(_, Z)),
        not(fact1(X, _)),
        gorod(Y),
        not(Y = Z),
        velo(X, Y),
        not(rodom("Leonid", Z)),
        not(rodom("Leonid", Y)).

    run() :-
        console::init(),
        rodom(X, "Moscow"),
        stdIO::writef("% from Moscow", X),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
