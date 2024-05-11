// Author Anton Leslie

package bank

import (
    "local/Main/bank/account"
    
    "sync"
    "fmt"
)



// Bank represents a bank that holds a collection of accounts.
type Bank struct {
    accounts map[*account.AccountData]bool // change key type to *account.AccountData
}

// NewBank creates and returns a new Bank instance.
func NewBank() *Bank {
    return &Bank{accounts: make(map[*account.AccountData]bool)}
}

// Add adds an account to the bank's collection of accounts.
func (b *Bank) Add(account *account.AccountData) { // change parameter type to *account.AccountData
    b.accounts[account] = true
}

// Accrue accrues interest on each account in the bank's collection of accounts.
// The interest rate is specified by the rate argument.
// Accrue accrues interest on each account in the bank's collection of accounts.
// The interest rate is specified by the rate argument.
func (b *Bank) Accrue(rate float64) {
    ch := make(chan *account.AccountData)
    var wg sync.WaitGroup
    wg.Add(1)
    go func() {
        for acc := range b.accounts {
            ch <- acc // pass the account to the channel
        }
        close(ch)
        wg.Done()
    }()
    go func() {
        for acc := range ch {
            acc.Accrue(rate) // call Accrue method on the account
        }
    }()
    wg.Wait()
}


// String returns a string representation of the bank's collection of accounts.
func (b *Bank) String() string {
    r := ""
    for account := range b.accounts {
        r += fmt.Sprintf("%s\n", account.ToString())
    }
    return r
}
