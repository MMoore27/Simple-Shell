Michael Moore, Andrew Grossane, Ryan Lee, Jacob Porter

Project #1--Clonsh shell

The goal of the project was to make a shell that, after receiving a user command, did the command the specified number of times (count) and executed those
processes in either a parallel or sequential fashion. Optionally, the user can also enter a timeout. If the process does not finish by the timeout 
specified, it will be terminated


Design choices -- Parallel or Sequential?

	The code for the parallel and sequential loops are pretty much identical, with one small difference. 

		For PARALLEL the processes are forked as they are being done (in the for loop), so it will be parallel 

		For SEQUENTIAL a new process won't start until after the first one is finished. This is why it is sequential.

	For implementing the timeouts:

		For PARALLEL 
			all the process ids are stored
			sleep happens outside of the for loop, after all the processes are created
			then the parent kills each child process

		For SEQUENTIAL
			sleep happens inside of the for loop --so after each (3rd, 4th, 5th, etc) child is created
			then the parent kills that child



Internet Resources we used to help:

http://unixhelp.ed.ac.uk/CGI/man-cgi?sleep+3

http://linux.die.net/man/2/waitpid

http://docs.oracle.com/cd/E51433_01/fscm92pbr2/eng/fscm/ecif/task_UsingSequentialandParallelProcessing-537fd1.html

http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html

http://stackoverflow.com/questions/4160935/how-to-use-fork-in-unix-why-not-something-of-the-form-forkpointertofunctiont

https://www.youtube.com/watch?v=z7TMZIh3oyU