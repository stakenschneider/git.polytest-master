implement main
    open core

domains
    number = integer.

class predicates
    write_number : (number) nondeterm.
clauses
    write_number(10).

    write_number(N) :-
        N < 10,
        stdIO::write(N),
        stdIO::nl(),
        write_number(N + 1).

    run() :-
        console::init(),
        stdIO::write("Это числа"),
        stdIO::nl(),
        main::write_number(1),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
