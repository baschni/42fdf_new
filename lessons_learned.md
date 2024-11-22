warum wird das reinzoomen bei vielen edges langsamer?


bug with 

	if (in_or_out)
	{
		scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist * SCALE_ON_ZOOM;
	}
	{
		scene->target.scale_parallel = scene->target.scale_parallel / SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
	}


where else is missing and it is resetting the code of the if above



when compiling with fsanitize=address, threads mutexes do not work properly

https://stackoverflow.com/questions/2127797/significance-of-pthread-flag-when-compiling
https://stackoverflow.com/questions/68691430/pthread-mutex-lock-full-assertion-failed-error

if you want to do multithreading you need to manipulate mlx_init

oid	*mlx_init()
{
	t_xvar	*xvar;

	printf("Xinit %i\n", XInitThreads());
	if (!(xvar = malloc(sizeof(*xvar))))
		return ((void*)0);
	if ((xvar->display = XOpenDisplay("")) == 0)
	{
		free(xvar);



- make fsanitize=thread work:
https://stackoverflow.com/questions/2340259/how-to-turn-off-gcc-compiler-optimization-to-enable-buffer-overflow
setarch `uname -m` -R ./fdf test2.fdf
https://stackoverflow.com/questions/77850769/fatal-threadsanitizer-unexpected-memory-mapping-when-running-on-linux-kernels


valgrind --log-file=v.log --leak-check=full ./fdf test2.fdf

https://stackoverflow.com/questions/3840582/valgrind-still-reachable-leak-detected-by-valgrind


https://stackoverflow.com/questions/5610677/valgrind-memory-leak-errors-when-using-pthread-create

https://stackoverflow.com/questions/34258271/pthread-kill-kills-not-just-a-thread-but-the-whole-program

https://www.baeldung.com/linux/signals-multi-threaded-app





TODO:


- turning problems...
  

FINAL:

- set screen to maximized

normal


500.000 	0.11
100.000		0.09
1000		0.02

0.177609 log(0.00120263)


parallel