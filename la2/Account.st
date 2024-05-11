Object subclass: Account [
| number customer balance | "Declares instance variables for account number, customer, and balance"

   Account class [
    "Class method for creating a new instance of Account with the given values"
    new: passNumber customer: passCustomer balance: passBalance [
        ^self new init: passNumber customer: passCustomer balance: passBalance
    ]
]

"Initializer method for Account instances"
init: passNumber customer: passCustomer balance: passBalance [
    ^self subclassResponsibility  "This method is marked as abstract and expects subclasses to implement it"
]

"Method for getting the current balance of the account"
balance [
    ^balance  "Return the account balance"
]

"Method for depositing funds into the account"
deposit: amount [
    balance:= balance + amount.  "Add the amount to the account balance"
]

"Method for withdrawing funds from the account"
withdraw: amount [
    balance:= balance - amount.  "Subtract the amount from the account balance"
]

"Method for returning a string representation of the account"
asString [
    ^number asString, ': ', customer asString, ': $', balance asString  "Return a string with the account number, customer name, and balance"
]

]