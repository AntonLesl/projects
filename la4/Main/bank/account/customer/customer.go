// Author Anton Leslie

package customer

// Customer defines a type for a bank customer with a single field `name`.
type Customer struct {
    name string
}

// NewCustomer is a constructor function that takes a `name` argument and returns
// a pointer to a new `Customer` instance with the `name` field set.
func NewCustomer(name string) *Customer {
    return &Customer{name: name}
}

// String is a method that returns the name of the customer as a string. This
// method implements the `Stringer` interface in Go, which allows a custom
// string representation of a type to be defined.
func (c *Customer) String() string {
    return c.name
}
