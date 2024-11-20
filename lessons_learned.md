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