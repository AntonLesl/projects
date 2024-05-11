****************
* Lab Assignment #3: Critical Path Analysis (Extra Credits: 40 pts)
* CS421-Summer
* 08/1/2023
* Anton Leslie
**************** 

OVERVIEW:
This assignment focuses on critical path analysis, a concept widely used in project management to schedule tasks associated with a project. The goal is to find the critical path and other important information from a directed acyclic graph (DAG) representing the tasks in the project.
Background: DAG Representation of a Project:
The project's activities are represented as vertices in a DAG, where edges indicate the precedence relationships. Each vertex represents an activity with its required completion time. Critical path analysis finds the earliest and latest completion times for each activity, along with the slack time (delay that can be tolerated without affecting the project's overall completion time).

Design of the Program:
The program should read in an activity-node graph from a provided file and store it using an adjacency-list representation. Then, it transforms the activity-node graph to the corresponding event-node graph following certain guidelines. It efficiently computes the earliest completion times (EC) and latest completion times (LC) for each activity using topological order and reverse topological order, respectively. Finally, it outputs the EC, LC, and Slack times for each activity.

Compile the Java program:
javac CriticalPath.java

Run the program with the input file 

java CriticalPath <file name>

Replace <file name> with the path to the input file.