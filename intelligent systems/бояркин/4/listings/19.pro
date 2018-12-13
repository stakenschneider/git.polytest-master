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
        A = "Андрей"
        or
        A = "нет".

    st_D(D) :-
        D = "Дмитрий"
        or
        D = "нет".

    st_B(B) :-
        B = "Борис"
        or
        B = "нет".

    st_V(V) :-
        V = "Виктор"
        or
        V = "нет".

    st_G(G) :-
        G = "Григорий"
        or
        G = "нет".

    ogr1("Андрей", _, _, "нет", _).
    ogr1("нет", _, _, "Виктор", _).
    ogr2(_, "Дмитрий", _, _, "нет").
    ogr2(_, "нет", _, _, _).
    norm1("Андрей", "Дмитрий", "нет", _, _).
    norm2("Андрей", "нет", "Борис", "нет", _).
    norm3(_, "Дмитрий", "нет", "нет", _).
    norm4(_, "нет", "нет", "Виктор", "Григорий").

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
