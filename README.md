# tcp-client
Simple tcp client which sends a request to a server and print response into the stdout. Is possible send two requests - for cpu utilization or mem usage.

Compilation: Download project from git into an arbitrary directory and then make it. Makefile is placed in the /prj directory.

1) Make in debug mode - There is enabled debug messages that are printed into the stdout.
                        If you want make project in debug mode you have to execute make with BUILD_MODE parameter.
                        For example: make BUILD_MODE=debug

2) Make in run mode (default) - There is disabled debug messages that are printed into the stdout.
                                If you want make project in run mode you can execute make without BUILD_MODE parameter.
                                For example: make or make BUILD_MODE=run
                                
note that: After compile this project you can run client's help by ./tcp_client --help in command line
