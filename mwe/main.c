#include <stdlib.h>
# include <X11/Xlib.h>
#include "mlx.h"

int main(void)
{
	void *mlx;

	XInitThreads();
	mlx = mlx_init();
	mlx_destroy_display(mlx);
	free(mlx);
	XFreeThreads();
}