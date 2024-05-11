// This class provides a stubbed-out environment.
// You are expected to implement the methods.
// Accessing an undefined variable should throw an exception.

// Hint!
// Use the Java API to implement your Environment.
// Browse:
//   https://docs.oracle.com/javase/tutorial/tutorialLearningPaths.html
// Read about Collections.
// Focus on the Map interface and HashMap implementation.
// Also:
//   https://www.tutorialspoint.com/java/java_map_interface.htm
//   http://www.javatpoint.com/java-map
// and elsewhere.

import java.util.HashMap;
// The given Java code defines a class called "Environment" that stores key-value pairs of Strings and Doubles using a HashMap.
// It has three public methods - put, get, and toC. The put method adds a key-value pair to the HashMap and returns the value.
// The get method returns the value of a key in the HashMap and throws an EvalException if the key is not found.
// The toC method returns a String that represents the keys of the HashMap separated by "," and the C code necessary for the environment.
// The class is used to convert the key-value pairs to C language code. If the HashMap is empty,
// the method returns an empty string. Otherwise, it returns "int" followed by the keys separated by "," with a new line and some additional C code.

public class Environment { // what even is this
	// Defining a private final object of class HashMap with key type String and value type Double
// HashMap object to store the key-value pairs
	private final HashMap<String, Double> map = new HashMap<String, Double>();

	// Adds a key-value pair to the HashMap and returns the value
	public double put(String var, double val) {
		map.put(var, val);
		return val;
	}

	// Returns the value of a key in the HashMap and throws an EvalException if the key is not found
	public double get(String var) throws EvalException {

		return map.get(var);
	}

	// Returns a String that represents the keys of the HashMap separated by "," and the C code necessary for the environment
	public String toC() {
		StringBuilder s = new StringBuilder();
		String sep = " ";
		for (String v : map.keySet()) {
			s.append(sep).append(v);
			sep = ",";
		}
		if (s.toString().equals("")) {
			return "";
		} else {
			return "int" + s.toString() + ";\nx=0;x=x;\n";
		}
	}
}