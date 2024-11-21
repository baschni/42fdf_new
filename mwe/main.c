#include <stdlib.h>
#include "mlx.h"

int main(void)
{
	void *mlx;

	mlx = mlx_init();
	mlx_destroy_display(mlx);
	free(mlx);
}