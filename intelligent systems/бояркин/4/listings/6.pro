implement main
    open core

clauses
    hello() :-
        console::init(),
        stdIO::write("Hello!").

end implement main

goal
    main::hello().
