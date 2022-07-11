# minishell

Here is the minishell project wroted by [Luthernmr](https://github.com/Luthernmr) and me.

The goal of this project is to achieve a basic shell in C with some missing features but fully functional.
We divde the work in two different parts, I managed parsing then [Luthernmr](https://github.com/Luthernmr) execute.

The rules:

* Display a prompt
* Functionnal history
* Search & execute basing on the relative and absolute path
* No more than one global variable
* Implement redirections
* Implement pipes
* Manage environnement variables and "$?"
* Manage signals ctrl-C, ctrl-D & ctrl-\
* Write somes builtins; echo (with -n option), cd, pwd, export, unset, env, exit.
* Like all C project from 42 you have to follow the 42 norm and leaks are not allowed.

You want to play with it? Start a beautifull shell (inception) and type > Make && ./minishell
