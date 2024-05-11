#!/bin/gprolog --consult-file

:- include('data.pl').

/*Checks to see if there is overlap in the slots aka my timelte*/
overlaps(slot(X1,Y1),slot(X2,_)) :- isEarly(X1,X2),isLate(Y1,X2).
overlaps(slot(X1,Y1),slot(_,Y2)) :- isEarly(X1,Y2),isLate(Y1,Y2).
overlaps(slot(X1,Y1),slot(X2,Y2)) :- isEarly(Y1,Y2),isLate(X1,X2).
overlaps(slot(X1,Y1),slot(X2,Y2)) :- isEarly(X1,X2),isLate(Y1,Y2).

/*checks to see if in same part of day*/
isEqual(S1,S2) :- (S1=am,S2=am);(S1=pm,S2=pm).

/*Checks to see if in am*/
isAM(S1,S2) :- S1=am,S2=pm.

/*checks to see if in pm*/
isPM(S1,S2) :- S1=pm,S2=am.

/* time 1 is after time 2*/
isLate(time(H1,_,S1),time(H2,_,S2)) :- H1>H2,isEqual(S1,S2).
isLate(time(H1,M1,S1),time(H2,M2,S2)) :- H1=H2, M1>M2, isEqual(S1,S2).
isLate(time(_,_,S1),time(_,_,S2)) :- isPM(S1,S2).

/*time 1 is before time 2*/
isEarly(time(H1,_,S1),time(H2,_,S2)) :- H1<H2, isEqual(S1,S2).
isEarly(time(H1,M1,S1),time(H2,M2,S2)) :- H1=H2, M1<M2, isEqual(S1,S2).
isEarly(time(_,_,S1),time(_,_,S2)) :- isAM(S1,S2).

/*checks to see if the person can meet in the slot*/
meetone(Person, Slot2) :- free(Person, Slot1), overlaps(Slot1, Slot2).

/* The Main Driver rule */
main :- setof(Person,
		meetone(Person,slot(time(8,30,am),time(8,45,am))),
		People),
	write(People), nl, halt.

/*initialization predicate*/
:- initialization(main).
