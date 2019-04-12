implement main
    open core

domains
    loc = right; middle; left.

class predicates
    hanoi : (integer).
    move : (integer, loc, loc, loc).
    inform : (loc, loc).

clauses
    hanoi(N) :-
        move(N, left, middle, right).

    move(1, A, _, C) :-
        inform(A, C),
        !.

    move(N, A, B, C) :-
        move(N - 1, A, C, B),
        inform(A, C),
        move(N - 1, B, A, C).

    inform(Loc1, Loc2) :-
        stdIO::write("Disk C ", Loc1, " in ", Loc2),
        stdIO::nl().

    run() :-
        console::init(),
        hanoi(5).

end implement main

goal
    console::runUtf8(main::run).
