implement main
    open core

class facts
    xpositive : (string, string).
    xnegative : (string, string).

class predicates
    expertiza : ().
    vopros : (string, string) determ.
    fish_is : (string [out]) nondeterm.
    positive : (string, string) determ.
    negative : (string, string) determ.
    remember : (string, string, string) determ.
    clear_facts : ().

clauses
    expertiza() :-
        fish_is(X),
        !,
        stdIO::write("u fish is ", X, " "),
        stdIO::nl,
        clear_facts().

    expertiza() :-
        stdIO::write("noname!"),
        stdIO::nl,
        clear_facts().

    vopros(X, Y) :-
        stdIO::write("question - ", X, " ", Y, "? (y/n)"),
        R = stdIO::readLine(),
        remember(X, Y, R).

    positive(X, Y) :-
        xpositive(X, Y),
        !.

    positive(X, Y) :-
        not(negative(X, Y)),
        !,
        vopros(X, Y).

    negative(X, Y) :-
        xnegative(X, Y),
        !.

    remember(X, Y, "y") :-
        assertz(xpositive(X, Y)).

    remember(X, Y, "n") :-
        assertz(xnegative(X, Y)),
        fail.

    clear_facts() :-
        retract(xpositive(_, _)),
        fail.

    clear_facts() :-
        retract(xnegative(_, _)),
        fail.

    clear_facts().

    fish_is("som") :-
        positive("fish have ", "weight > 40 kg").

    fish_is("som") :-
        positive("fish have ", "weight < 40 kg"),
        positive("fish have ", " mustache").

    fish_is("shchuka") :-
        positive("fish have ", "weight < 20 kg"),
        positive("fish have ", "long narrow body").

    fish_is("perch") :-
        positive("fish have ", "weight < 20 kg"),
        positive("fish have ", "wide body"),
        positive("fish have ", "dark hair").

    fish_is("roach") :-
        positive("fish have ", "weight < 20 kg"),
        positive("fish have ", "wide body"),
        positive("fish have ", "gray scales").

clauses
    run() :-
        console::init(),
        expertiza().

end implement main

goal
    console::run(main::run).
