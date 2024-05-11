// Author Anton Leslie

// This code defines a package "account" which contains a struct type "SavingAccount".
// The "SavingAccount" struct embeds an "AccountData" struct which presumably contains fields for the account number, customer information, balance, and account type.

package account

// Importing package "customer" which contains the "Customer" type used as a parameter in the NewSavingAccount function.
import  "local/Main/bank/account/customer"

// Defining SavingAccount struct which embeds AccountData.
type SavingAccount struct {
	*AccountData
}

// NewSavingAccount function takes in an account number, customer information, and an initial balance,
// then creates a new instance of SavingAccount struct and initializes it with provided data.
// It returns a pointer to the new SavingAccount instance.
func NewSavingAccount(number string, customer *customer.Customer, balance float64) *SavingAccount {
	return &SavingAccount{&AccountData{number: number, customer: customer, balance: balance}}
}

// Accrue method on the SavingAccount type calculates the new balance with an interest rate and updates it.
func (sa *SavingAccount) accrue(rate float64) {
	sa.balance *= (1 + rate) // Calculate new balance by adding interest and updating it.
}
