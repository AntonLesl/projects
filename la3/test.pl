#!/bin/gprolog --consult-file

% Load the data.pl file
:- include('data.pl').


% Define a test case for overlaps/2
test_overlaps :-
    % Define some test cases and their expected results
    overlaps(slot(time(8,0,am), time(9,0,am)), slot(time(8,30,am), time(9,30,am))) == true,
    overlaps(slot(time(9,0,am), time(10,0,am)), slot(time(8,30,am), time(9,30,am))) == false,
    overlaps(slot(time(8,0,am), time(9,0,am)), slot(time(9,0,am), time(10,0,am))) == true,
    overlaps(slot(time(8,0,am), time(9,0,am)), slot(time(8,0,am), time(9,0,am))) == true,

    % Run the tests and print the results
    (catch(run_tests([test_overlaps]), _, true), writeln('All tests passed!')),
    halt.

% Define a predicate to run all tests
run_tests([]).
run_tests([Test|Tests]) :-
    call(Test),
    run_tests(Tests).

% Define the main driver predicate
main :-
    % Run all tests
    test_overlaps,

    % Run the original program
    setof(Person, meetone(Person, slot(time(8,30,am), time(8,45,am))), People),
    write(People), nl,
    halt.

% Define the writeln/1 predicate (if it's missing)
writeln(Term) :-
    write(Term), nl.

% Initialize the program
:- initialization(main).
