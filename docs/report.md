How did we prepare for doing the lab? In what order did we develop each feature?

    The first thing that our group did was to meet in a zoom-conference to discuss if we understood the assignment as well as having done the 
    lab warm-up quiz. After this conference we agreed to individually try to implement a shell that could execute simple commands. A simple
    command would be a command with no flags, piping or arguments like ls or pwd.

    After some days we met in another zoom-conference to show our simple implementation of the agreed upon requirements from the previous conference. We
    decided that Johans implementation looked the nicest and chose to work of off this "starting" shell. The code was uploaded to github and each member
    of the group cloned the repository to their local machine to work further on the features.

    We decides to divided the remaining tasks/features amongst us based on our preferences. Martin decided to work on the pipeline feature, Johan decided
    to work on background execution, Ctrl+C, exit and cd commands and Sudeshna  decided to work on implementing IO-redirection.

    Each feature was developed on a separate branch that was made from the initial simple shell. After a feature was developed it was pushed onto github 
    and merged with the main branch, creating a more advanced shell.

    The order of which the features where implemented are the following:
        1. Simple command execution
                This was difficult to implemjoy!ent, not necessarily because the code was complex, but rather because of our inexperience with working with
                the exec() family as well as c being somewhat non forgiving.
        2. Background processing
            This was rather simple to implement. Since we pass the NULL terminated array of flags to the execvp() function it will know that it would
            execute in the background. What had to be done was to let the parent know not to wait for its child to terminate, instead react to the SIGCHLD 
            signal.
        3. cd and exit commands
            These commands were quite easy to implement. Before parsing the command with the parse() function we just check if the first word happens
            to be equal to "cd" or "exit". If it equals cd then we call the chdir() function instead of executing a simple command.
            If the first word would equal exit we just break the main loop of the shell. This terminates any child process of the shell so no zombies
            are left after exiting.
        4. Handling the signals for ctrl+c and also the sigchld signal
            These were somewhat difficult to implement. But this is discussed in the challenges section.
        5. Piping
            It was difficult because it needed a lot of documentation reading to understand well. This is also discussed in the challenges
            section.
        6. IO-redirection
            This was the last implementation. We did the piping before this and we believe it was a good choice. It would have been difficult 
            to implement IO-redirection before piping due to how we call the piping functionality in the code. It was not very hard to understand
            the duping of stdin, stdout and strerr to the new file that was created with the open() call. What was difficult to understand was
            which flags to use with the open() call. We want to create a new file with read and write permission and we also want the process
            to have read, write and execute permissions.


    After implementing all the features the final code was pushed onto the github repository.



What challenges did we encounter in meeting each specification?

    The first challenge was to understand the program structure. Just looking at the base file was not easy. A lot of pointers as well as functions to understand.
    Also first of all, we had to have a basic idea visualization about all the files provided in the lab assignment. And going through each files , we had to understand about which file is relevant  or related to which other files. We actually had the challenge to understand the process on which file works in which way and in which way they were connected  to each other. 
    
    Since most of us are also not familiar with github so, it was also a challenge to first understand about it. Then by seeing some reference videos online , firstly we try to understand about what repository is and even created it for ourselves. Guess it was just a storage space for our codes for future use. 

    Another challenge that we encountered was understanding which command in the exec() family to use. We chose to use execvp() since the path
    would be known by the shell and it was comfortable and easy to use since it only required the base command, like ls, as well as 
    the arguments in a NULL terminated array. This array is provided by the pgm structure that the parser returns.

    Another challenge was to find good/relevant documentation showed examples on how to build a shell application. The best documentation was
    found either on geeksforgeeks or on github projects.

    Another thing that was hard to grasp was the execution of the test file written in python. If run locally the test file shows that all the tests are
    approved/passed but when pushing the code to github all the tests are failing. This phenomena is interpreted  as a pass on the tests, perhaps the github
    environments does something different from that of our local executions on Linux based systems.

    Moreover, the pipeline implementation was a real challenge, due to the recursive function that we used, it was difficult to understand the timing to call 
    the function or when to end the recursive part. 


    Understanding the SIGINT and SIGCHLD signals where also somewhat difficult. Since a child process would be in the same process group as that of the parent
    it would also terminate when a SIGINT signal was sent from the user. The SIGINT signal will interrupt all processes that are in the same process group
    as the current foreground process. By switching the process group id, with the function setpgid(0,0), the child process receives a unique process group
    and manages to survive the SIGINT signal that the parent has to resolve. Another thing that caused confusion was that the test file showed
    incorrect results for the handling of the SIGINT signal, this was fixed rather quickly but was still confusing for the developer.

    Another challenge, regarding physical meetings, was the difficulty of meeting in person. We elected to meet physically twice and online three times. This may 
    have caused some communication errors. In upcoming labs we will try to meet more in person to improve this quality.


Feedback for improving the lab materials

    One thing that the TA's should look at is how github executes the test file. We manage to pass all the tests if we run the test file locally
    but if we push the code to github then all the tests fail, returning weird error messages.

    It was good to attend the lab consulting sessions. A lot of questions came up and it was helpful to talk to the TA's about these. One thing to maybe
    consider: Instead of booking a time-slot on canvas perhaps you could just walk into the lab session and write your group number on one of the whiteboards
    to create a queue(FIFO) of who wants help. Or maybe use both systems and divide the TA's to either serve canvas booking or the whiteboard queue.

    Perhaps, before the lab session during the lab introductory period, it would be very good if the TA's could explain to us more in more detail about the concept of what we are going to do in the lab session. Also, when the TA's introduce us to their codes in the lab introductory period, it would be better if they could at the very least give us the viewpoint or some explanation about what the process are being done in the codes or what is actually being done in the code processes.
    This way, it might be possible for most of us to have a better view about what we are going to do in the lab.