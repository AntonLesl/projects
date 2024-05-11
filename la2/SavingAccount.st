Account subclass: SavingsAccount [
| interest | "Declares an instance variable to hold the interest earned by the savings account"
"Initializer method for SavingsAccount instances"
init: passNumber customer: passCustomer balance: passBalance [
    number:= passNumber.  "Set the account number"
    customer:= passCustomer.  "Set the account customer"
    balance:= passBalance.  "Set the account balance"
    interest:= 0.0  "Initialize the interest earned to zero"
]

"Method for accruing interest on the savings account"
accrue: rate [
    balance:= balance + (balance * rate).  "Add the interest to the account balance"
    interest:= interest + (balance * rate).  "Add the interest to the interest earned"
]

]