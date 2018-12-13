implement main
    open core

domains
    collector=symbol.
    title=symbol.
    author=symbol.
    publisher=symbol.
    year = integer.
    personal_library = book(title, author, publication).
    publication = publication(publisher, year).

class predicates
    collection : (collector[out], personal_library[out]).
    
clauses
    collection("Иванов", book("Война и мир", "Лев Толстой", publication("Просвещение",1990))).
        
clauses
    run():-
        console::init(),
        collection(X, Y),
        stdIO::writef("% - %\n", X, Y),
        fail.
    run().
end implement main

goal
    console::runUtf8(main::run).
