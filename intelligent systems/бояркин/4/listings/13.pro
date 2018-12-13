implement main
    open core

domains
    dog_list = symbol*.

class predicates
    dogs : (dog_list [out]).
    print_list : (dog_list).

clauses
    dogs(["лайка", "борзая", "дог", "болонка"]).

    print_list([]).

    print_list([X | Y]) :-
        stdIO::write(X),
        stdIO::nl(),
        print_list(Y).

    run() :-
        console::init(),
        dogs(X),
        stdIO::write(X),
        stdIO::nl(),
        print_list(X).

end implement main

goal
    console::runUtf8(main::run).
