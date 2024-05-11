import java.io.*;

// The given Java code defines a class called "Code" that takes in two arguments -
// a string of code and an object of class Environment.
// It writes the input code to a C file named "Code.c" with the necessary prologue and epilogue using BufferedWriter.
// It also contains an array of strings called prologue and epilogue that store the necessary C code that is added to the C file.
// The class is initialized using a constructor. The code to be written to the file is passed as an argument to the constructor.
// If the file name is not found in the system environment variable, the program simply returns.
// If there is any exception while writing the code to the file, the error message is printed to the standard error stream.
public class Code {
	// Defining a private array of Strings called prologue
	private final String[] prologue = {
			"#include <stdio.h>",
			"int main() {",
	};

	// Defining a private array of Strings called epilogue
	private final String[] epilogue = {
			"return 0;",
			"}",
	};

	// Defining a constructor for Code class that takes two arguments - code and env
	public Code(String code, Environment env) {

		// Getting the file name from system environment variable
		String fn = System.getenv("Code");

		// If file name is not found, then return
		if (fn == null)
			return;

		try {
			// Creating a new file writer object and passing the file name with extension '.c'
			BufferedWriter f = new BufferedWriter(new FileWriter(fn + ".c"));

			// Writing prologue array strings to the file
			for (String s : prologue)
				f.write(s + "\n");

			// Writing environment to C language equivalent to the file
			f.write(env.toC());

			// Writing the code to the file
			f.write(code);

			// Writing epilogue array strings to the file
			for (String s : epilogue)
				f.write(s + "\n");

			// Closing the file writer object
			f.close();

		} catch (Exception e) {
			// Printing the error message to standard error stream
			System.err.println(e);
		}
	}
}