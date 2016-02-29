Names: B. Hamrick, T. Ferguson, R. Stingel
Class: CSC-3710
Project: Priority Print Queing Simulation

This code simulates jobs being sent to the printer. The user sets up parameters including, the number
<<<<<<< HEAD
of printers, the maximum number of pages one job can have, the number of jobs to complete and the 
number of pages the printer can print/time unit. Once the parameters are set, the code them creates 
print jobs every time unit of size between 1 - max # of pages. These jobs are placed into a tiered
queue based on the number of pages they have: <= 10 pages high priority
					      <= 20 pages medium priority
  					      > 20 pages low priority.
The jobs are printed from high priority to low priority, in the order in which they were received. 
Once the simulation is complete, the average wait time for a job to be printed is calculated. Also,
based on research the total cost to print all the pages is calculated. This data is then outputted
and based on the average wait time, we decide what you should do to maximize efficiency and save
money. 
=======
of printers, the maximum number of pages one job can have, the number of jobs to complete and the
number of pages the printer can print/time unit. Once the parameters are set, the code them creates
print jobs every time unit of size between 1 - max # of pages. These jobs are placed into a tiered
queue based on the number of pages they have: <= 10 pages high priority
                                              <= 20 pages medium priority
                                               > 20 pages low priority.
The jobs are printed from high priority to low priority, in the order in which they were received.
Once the simulation is complete, the average wait time for a job to be printed is calculated. Also,
based on research the total cost to print all the pages is calculated. This data is then outputted
and based on the average wait time, we decide what you should do to maximize efficiency and save
money.
>>>>>>> 1037a37268155defb5f7d97feea817b19306fa77
