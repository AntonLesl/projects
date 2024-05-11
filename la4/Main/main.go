// Import necessary packages
package main

import (
    "local/Main/bank/account"
    "local/Main/bank"
    "local/Main/bank/account/customer"
    "fmt"
)

// Define main function
func main() {
    // Create new bank
    bank := bank.NewBank()
    // Create new customer
    c := customer.NewCustomer("Ann")

    // Add new checking and saving accounts to bank for customer
    checkingAccount := account.NewCheckingAccount("01001", c, 100.00)
    bank.Add(checkingAccount.AccountData)
    savingAccount := account.NewSavingAccount("01002", c, 200.00)
    bank.Add(savingAccount.AccountData)

    // Accrue interest for all accounts in the bank
    bank.Accrue(0.02)

    // Print the details of all accounts in the bank
    fmt.Println(bank)
}
