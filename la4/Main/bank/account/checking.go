// Author Anton Leslie

// This code defines a package "account" which contains a struct type "CheckingAccount".
// The "CheckingAccount" struct embeds an "AccountData" struct which presumably contains fields for the account number, customer information, balance, and account type.

package account

// Importing package "customer" which contains the "Customer" type used as a parameter in the NewCheckingAccount function.
import  "local/Main/bank/account/customer" 

// Defining CheckingAccount struct which embeds AccountData.
type CheckingAccount struct {
	*AccountData
}

// NewCheckingAccount function takes in an account number, customer information, and an initial balance,
// then creates a new instance of CheckingAccount struct and initializes it with provided data.
// It returns a pointer to the new CheckingAccount instance.
func NewCheckingAccount(number string, customer *customer.Customer, balance float64) *CheckingAccount {
	return &CheckingAccount{&AccountData{number: number, customer: customer, balance: balance, isChecking: true}}
}

// Accrue method on the CheckingAccount type is empty and does not do anything because checking account does not accrue.
func (ca *CheckingAccount) accrue(rate float64) {}
