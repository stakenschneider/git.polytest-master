implement main
    open core

domains
    s = symbol.

class predicates
    st_A : (s [out]) multi.
    st_D : (s [out]) multi.
    st_B : (s [out]) multi.
    st_V : (s [out]) multi.
    st_G : (s [out]) multi.
    ogr1 : (s, s, s, s, s) determ.
    ogr2 : (s, s, s, s, s) determ.
    spisok : (s [out], s [out], s [out], s [out], s [out]) nondeterm.
    norm1 : (s, s, s, s, s) determ.
    norm2 : (s, s, s, s, s) determ.
    norm3 : (s, s, s, s, s) determ.
    norm4 : (s, s, s, s, s) determ.

clauses
    st_A(A) :-
        A = "Andrey"
        or
        A = "no‚".

    st_D(D) :-
        D = "Dmitry"
        or
        D = "no‚".

    st_B(B) :-
        B = "Boris"
        or
        B = "no‚".

    st_V(V) :-
        V = "Viktor"
        or
        V = "no‚".

    st_G(G) :-
        G = "Gregory"
        or
        G = "no‚".

    ogr1("Andrey", _, _, "no‚", _).
    ogr1("no‚", _, _, "Viktor", _).
    ogr2(_, "Dmitry", _, _, "no‚").
    ogr2(_, "no‚", _, _, _).
    norm1("Andrey", "Dmitry", "no‚", _, _).
    norm2("Andrey", "no‚", "Boris", "no‚", _).
    norm3(_, "Dmitry", "no‚", "no‚", _).
    norm4(_, "no‚", "no‚", "Viktor", "Gregory").

    spisok(A, D, B, V, G) :-
        st_A(A),
        st_D(D),
        st_B(B),
        st_V(V),
        st_G(G),
        norm1(A, D, B, V, G),
        ogr1(A, D, B, V, G),
        ogr2(A, D, B, V, G)
        or
        st_A(A),
        st_D(D),
        st_B(B),
        st_V(V),
        st_G(G),
        norm2(A, D, B, V, G),
        ogr1(A, D, B, V, G),
        ogr2(A, D, B, V, G)
        or
        st_A(A),
        st_D(D),
        st_B(B),
        st_V(V),
        st_G(G),
        norm3(A, D, B, V, G),
        ogr1(A, D, B, V, G),
        ogr2(A, D, B, V, G)
        or
        st_A(A),
        st_D(D),
        st_B(B),
        st_V(V),
        st_G(G),
        norm4(A, D, B, V, G),
        ogr1(A, D, B, V, G),
        ogr2(A, D, B, V, G)
        or
        st_A(A),
        st_D(D),
        st_B(B),
        st_V(V),
        st_G(G),
        not(norm1(A, D, B, V, G)),
        not(norm2(A, D, B, V, G)),
        not(norm3(A, D, B, V, G)),
        not(norm4(A, D, B, V, G)),
        ogr1(A, D, B, V, G),
        ogr2(A, D, B, V, G).

clauses
    run() :-
        console::init(),
        spisok(A, D, B, V, G),
        stdIO::writef("% % % % %\n", A, D, B, V, G),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
