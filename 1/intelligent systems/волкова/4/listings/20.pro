implement main
    open core

domains
    name = symbol.
    rost = integer.
    ves = integer.

class facts
    dplayer : (name, rost, ves).

class predicates
    player : (name [out], rost [out], ves [out]) multi.
    assert_database : ().

clauses
    player("M", 180, 87).
    player("P", 187, 93).
    player("H", 177, 80).

    assert_database() :-
        player(N, R, V),
        assertz(dplayer(N, R, V)),
        fail.

    assert_database().

clauses
    run() :-
        console::init(),
        assert_database(),
        dplayer(N, R, V),
        R > 180,
        stdIO::writef("% % sm % kg", N, R, V),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
