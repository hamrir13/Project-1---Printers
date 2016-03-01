Names: B. Hamrick, T. Ferguson, R. Stingel
Class: CSC-3710
Project: Priority Print Queing Simulation

This code simulates jobs being sent to the printer. The user sets up parameters including:	the number of printers, 
      the maximum number of pages one job can have,
      the number of jobs to complete, 
      the average number of jobs per min,
      the number of pages the printer can print/time unit, 
      the cost of the printers (per page),
      the number of tiers in the tiered queue,
      the maximum number of pages a tier can hold (cutoffs)
      the maximum number of pages a printer prints before needing maintenece,
      the amount of time a printer spends under maintenence,
      the percent chance that a printer fails printing a job,
      the amount of time the printer spends offline due to failure.

Once the parameters are set, the code then creates print jobs based on the average number of jobs per minute. Then the code randomly selects a tier and the number of pages in a jobis between the cutoff of one tier less than the selected tier and the selected tier (i.e. if the selected tier is 3 and has a cutoff of 30 and tier 2 has cutoff of 20 pages, then the number of pages in that job will be between 21-30). These jobs are placed into a tiered queue size based on the user input. The jobs are printed from high priority to low priority, in the order in which they were received. The jobs are sent to printers randomly, not sequentially, so the printers print around the same number of jobs. Once the simulation is complete, the total average wait time for a job to be printed and the average wait time  in each queue is calculated. The percent utilization (time printing/total simulation time) is caluculated and the total cost of each printer and the total cost of all the pages    printed is calculated. 
