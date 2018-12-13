implement main
    open core

class predicates
    connection : (string [out], string [out]) multi.
    connection : (string, string [out]) nondeterm.
    connection : (string [out], string) nondeterm.
    path : (string, string, string*) nondeterm.
    member : (string, string*) nondeterm.
    reverse : (string*, string* [out], string*) nondeterm anyflow.

clauses
    connection("entrance", "room 1").

    connection("entrance", "room 4").

    connection("room 1", "gold").

    connection("room 1", "robbers").

    connection("room 1", "room2").

    connection("room2", "exit").

    connection("room 3", "exit").

    connection("room 4", "room2").

    connection("gold", "monster").

    connection("gold", "room 3").

    connection("monster", "exit").

    connection("robbers", "exit").

    member(X, [Y | T]) :-
        X = Y
        or
        member(X, T).

    reverse([], Z, Z).

    reverse([H | T], Z, A) :-
        reverse(T, Z, [H | A]).

    path(Y, Y, _).

    path(X, Y, T) :-
        connection(X, Z),
        not(member(Z, T)),
        path(Z, Y, [Z | T]).

    path(X, Y, T) :-
        connection(Z, X),
        not(member(Z, T)),
        path(Z, Y, [Z | T]).

    path(_, _, [F | O]) :-
        reverse([F | O], [L | V], []),
        if F = "exit" and L = "entrance" and not(member("robbers", O)) and not(member("monster", O)) and member("gold", O) then
            stdIO::writef("%\n", [L | V])
        else
        end if.

    run() :-
        console::init(),
        connection(X, Y),
        path(X, Y, []),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
