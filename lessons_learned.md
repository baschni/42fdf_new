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