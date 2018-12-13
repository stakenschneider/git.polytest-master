implement main
    open core

domains
    loc = east; west.
    state = state(loc, loc, loc, loc).
    path = state*.

class predicates
    go : (state, state).
    path : (state, state, path, path [out]) determ.
    move : (state, state [out]) nondeterm.
    opposite : (loc, loc) determ anyflow.
    unsafe : (state) nondeterm.
    member : (state, path) nondeterm.
    write_path : (path) determ.
    write_move : (state, state) determ.

clauses
    go(S, G) :-
        path(S, G, [S], L),
        stdIO::write("Решение:"),
        stdIO::nl(),
        write_path(L),
        fail.

    go(_, _).

    path(S, G, L, L1) :-
        move(S, S1),
        not(unsafe(S1)),
        not(member(S1, L)),
        path(S1, G, [S1 | L], L1),
        !.

    path(G, G, T, T) :-
        !.

    move(state(X, X, G, C), state(Y, Y, G, C)) :-
        opposite(X, Y).

    move(state(X, W, X, C), state(Y, W, Y, C)) :-
        opposite(X, Y).

    move(state(X, W, G, X), state(Y, W, G, Y)) :-
        opposite(X, Y).

    move(state(X, W, G, C), state(Y, W, G, C)) :-
        opposite(X, Y).

    opposite(east, west).

    opposite(west, east) :-
        !.

    unsafe(state(F, X, X, _)) :-
        opposite(F, X).

    unsafe(state(F, _, X, X)) :-
        opposite(F, X).

    member(X, [X | _]).

    member(X, [_ | L]) :-
        member(X, L).

    write_path([H1, H2 | T]) :-
        !,
        write_move(H1, H2),
        write_path([H2 | T]).

    write_path([]).

    write_move(state(X, W, G, C), state(Y, W, G, C)) :-
        !,
        stdIO::write("Мужик пересекает реку с ", X, " на ", Y),
        stdIO::nl().

    write_move(state(X, X, G, C), state(Y, Y, G, C)) :-
        !,
        stdIO::write("Мужик везет волка с ", X, " берега на ", Y),
        stdIO::nl().

    write_move(state(X, W, X, C), state(Y, W, Y, C)) :-
        !,
        stdIO::write("Мужик везет козу с ", X, " берега на ", Y),
        stdIO::nl().

    write_move(state(X, W, G, X), state(Y, W, G, Y)) :-
        !,
        stdIO::write("Мужик везет капусту с ", X, " берега на ", Y),
        stdIO::nl().

clauses
    run() :-
        console::init(),
        go(state(east, east, east, east), state(west, west, west, west)).

end implement main

goal
    console::runUtf8(main::run).
