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
        stdIO::write("ваша рыба это ", X, " "),
        stdIO::nl,
        clear_facts().

    expertiza() :-
        stdIO::write("это неизвестная рыба!"),
        stdIO::nl,
        clear_facts().

    vopros(X, Y) :-
        stdIO::write("вопрос – ", X, " ", Y, "? (да/нет)"),
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

    remember(X, Y, "да") :-
        assertz(xpositive(X, Y)).

    remember(X, Y, "нет") :-
        assertz(xnegative(X, Y)),
        fail.

    clear_facts() :-
        retract(xpositive(_, _)),
        fail.

    clear_facts() :-
        retract(xnegative(_, _)),
        fail.

    clear_facts().

    fish_is("сом") :-
        positive("у рыбы", "вес > 40 кг").

    fish_is("сом") :-
        positive("у рыбы", "вес < 40 кг"),
        positive("у рыбы", "есть усы").

    fish_is("щука") :-
        positive("у рыбы", "вес < 20 кг"),
        positive("у рыбы", "длинное узкое тело").

    fish_is("окунь") :-
        positive("у рыбы", "вес < 20 кг"),
        positive("у рыбы", "широкое тело"),
        positive("у рыбы", "темные полосы").

    fish_is("плотва") :-
        positive("у рыбы", "вес < 20 кг"),
        positive("у рыбы", "широкое тело"),
        positive("у рыбы", "серебристая чешуя").

clauses
    run() :-
        console::init(),
        expertiza().

end implement main

goal
    console::run(main::run).