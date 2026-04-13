#include "miniRT.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "MINIRT");
	(void)win;
	ft_putstr_fd("oi\n", 1);
	mlx_loop(mlx);
	return (0);
}
