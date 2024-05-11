Account subclass: CheckingAccount [
    CheckingAccount class[  "Create a new class method for CheckingAccount"
        new: passNumber customer: passCustomer balance: passBalance[  "Create a constructor for CheckingAccount that takes 3 arguments"
            ^self new init: passNumber customer: passCustomer balance: passBalance  "Return a new instance of CheckingAccount and call its init method with the passed arguments"
        ]
    ]
    
    init: passNumber customer: passCustomer balance: passBalance [  "Create an instance method called init for CheckingAccount that takes 3 arguments"
        number:=passNumber.  "Initialize the instance variable 'number' with the passed 'passNumber'"
        balance:=passBalance.  "Initialize the instance variable 'balance' with the passed 'passBalance'"
        customer:=passCustomer  "Initialize the instance variable 'customer' with the passed 'passCustomer'"
    ]

    accrue: rate[  "Create an instance method called accrue for CheckingAccount that takes 1 argument"
        "does not gain interest"  "This method does not do anything, as CheckingAccounts typically do not accrue interest"
    ]
]
