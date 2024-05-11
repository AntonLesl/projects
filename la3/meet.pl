#!/bin/gprolog --consult-file

:- include('data.pl').
:- include('uniq.pl').

/* Checks to see if there is overlap in the slots */
overlaps(slot(X1,Y1),slot(X2,Y2)) :-
    isEarly(Y1,X2), isLate(X1,Y2),
    X1 \== Y2, X2 \== Y1.

/* Checks to see if in same part of day */
isEqual(S1,S2) :- (S1=am,S2=am);(S1=pm,S2=pm).

/* Checks to see if in am */
isAM(S1,S2) :- S1=am,S2=pm.

/* Checks to see if in pm */
isPM(S1,S2) :- S1=pm,S2=am.

/* Time 1 is after time 2 */
isLate(time(H1,_,S1),time(H2,_,S2)) :-
    H1>H2,isEqual(S1,S2).
isLate(time(H1,M1,S1),time(H2,M2,S2)) :-
    H1=H2, M1>M2, isEqual(S1,S2).
isLate(time(_,_,pm),time(_,_,am)).

/* Time 1 is before time 2 */
isEarly(time(H1,_,S1),time(H2,_,S2)) :-
    H1<H2, isEqual(S1,S2).
isEarly(time(H1,M1,S1),time(H2,M2,S2)) :-
    H1=H2, M1<M2, isEqual(S1,S2).
isEarly(time(_,_,am),time(_,_,pm)).

/* Checks to see if the person can meet in the slot */
meetone(Person, Slot2, Slot3) :-
    free(Person, Slot1),
    overlaps(Slot1, Slot2),
    overlaps(Slot1, Slot3),
    overlaps(Slot2, Slot3),
    write(Person), write(' is available from '), write(Slot1), nl.

/* Main driver rule */
main :-
    Slots = [slot(time(8,0,am),time(8,30,am)),
             slot(time(10,0,am),time(10,15,am)),
             slot(time(8,0,pm),time(8,30,pm))],
    findall(slot(X,Y),
            (member(Slot1, Slots),
             member(Slot2, Slots),
             Slot1 \== Slot2,
             meetone(ann, Slot1, slot(X,Y)),
             meetone(bob, Slot2, slot(X,Y)),
             meetone(carla, Slot2, slot(X,Y))),
            CompatibleSlots),
    list_times(CompatibleSlots),
    (CompatibleSlots = []
     -> write('No compatible meeting times.')
     ; nl),
    halt.

/* Prints the list of compatible meeting times */
list_times([]).
list_times([slot(X,Y)|T]) :-
    write('Compatible meeting time: '),
    write(X), write(' - '), write(Y), nl,
    list_times(T).

/* Initialization predicate */
:- initialization(main).
