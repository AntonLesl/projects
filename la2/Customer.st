Object subclass: Customer [
| name | "Declares an instance variable to hold the customer's name"

"Class method for creating a new instance of Customer"
Customer class[
new: n[
^self new init: n "Return a new instance of Customer initialized with the given name"
]
]

"Initializer method for Customer instances"
init: n[
name:= n. "Set the customer's name"
]

"Method for returning the customer's name as a string"
asString [
^name "Return the customer's name"
]
]