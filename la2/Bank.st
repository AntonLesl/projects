Object subclass: Bank [
| accounts |

"Class method for creating a new instance of Bank"
Bank class[
new [
^super new init
]
]

"Initializer method for Bank instances"
init [
accounts:= Set new
]
"Method for adding an account to the bank's accounts set"
add: aAccount [
    accounts add: aAccount.
]

"Method for accruing interest on all accounts in the bank"
accrue: aRate [
    accounts do: [ :aAccount | aAccount accrue: aRate ].
]

"Method for printing all the accounts in the bank"
printAccounts[
    | r |
    r:= String new.

    accounts do: [ :aAccount |
        r:= r, aAccount asString, (Character nl asString)
    ].

    ^r
]


]

"Create a new instance of Bank"
|bank| bank:= Bank new.

"Create a new instance of Customer"
|customer| c:= Customer new: 'Ann'.

"Add two accounts to the bank's accounts set"
bank add: (CheckingAccount new: '01001' customer: c balance: 100.00).
bank add: (SavingsAccount new: '01002' customer: c balance: 200.00).

"Accrue interest on all accounts in the bank"
bank accrue: 0.02.

"Print all the accounts in the bank"
bank printAccounts printNl.



