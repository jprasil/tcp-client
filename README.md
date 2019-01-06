# tcp-client
Simple tcp client which sends a request to a server and prints response into the stdout. It is possible to send two requests - for cpu utilization or mem usage.

Compilation: Download the project from the git into an arbitrary directory and then do "make". Makefile is placed in the /prj directory.

1) Compilation in debug mode - There are enabled debug messages printed into the stdout.
                        If you want to compile the project in debug mode you have to execute "make" with BUILD_MODE parameter.
                        For example: make BUILD_MODE=debug

2) Compilation in run mode (default) - There are disabled debug messages printed into the stdout.
                        If you want to compile the project in run mode you can execute "make" without BUILD_MODE parameter.
                        For example: make or make BUILD_MODE=run
                                
note that: After the compilation of the project you can run client's help by ./tcp_client --help in command line
