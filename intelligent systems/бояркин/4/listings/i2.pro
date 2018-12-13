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
    connection("вход", "комната1").

    connection("вход", "комната4").

    connection("комната1", "золото").

    connection("комната1", "разбойники").

    connection("комната1", "комната2").

    connection("комната2", "выход").

    connection("комната3", "выход").

    connection("комната4", "комната2").

    connection("золото", "монстр").

    connection("золото", "комната3").

    connection("монстр", "выход").

    connection("разбойники", "выход").

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
        if F = "выход" and L = "вход" and not(member("разбойники", O)) and not(member("монстр", O)) and member("золото", O) then
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
