// Author Anton Leslie

package account


    
import (
    "local/Main/bank/account/customer"
    "fmt"
)


// Account interface defines a set of methods that any account type must implement.
type Account interface {
    Accrue(rate float64) // fix: changed to take in a pointer receiver
    GetBalance() float64
    Deposit(amount float64)
    Withdraw(amount float64)
    ToString() string
    GetNumber() string
}

// AccountData struct defines fields for an account's number, customer information, balance, and account type.
// The isChecking field is added to indicate if the account is a checking account or not.
type AccountData struct {
    number     string
    customer   *customer.Customer
    balance    float64
    isChecking bool // added field to indicate if the account is a checking account
}

// Accrue method on the AccountData type calculates the new balance with an interest rate and updates it.
// If the account is a checking account, no interest will be added.
func (acc *AccountData) Accrue(rate float64) {
    if !acc.isChecking {
        interest := acc.balance * (rate / 1)
        acc.balance += interest
    }
}

// GetBalance method on the AccountData type returns the account balance.
func (acc *AccountData) GetBalance() float64 {
    return acc.balance
}

// Deposit method on the AccountData type adds the provided amount to the account balance.
func (acc *AccountData) Deposit(amount float64) {
    acc.balance += amount
}

// Withdraw method on the AccountData type subtracts the provided amount from the account balance.
func (acc *AccountData) Withdraw(amount float64) {
    acc.balance -= amount
}

// ToString method on the AccountData type returns a string representation of the account.
func (acc *AccountData) ToString() string {
    return acc.number + ":" + acc.customer.String() + ":" + fmt.Sprintf("%.2f", acc.balance)
}

// GetNumber method on the AccountData type returns the account number.
func (acc *AccountData) GetNumber() string {
    return acc.number
}
