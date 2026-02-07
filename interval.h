#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct s_interval
{
	double min;
	double max;
}	t_interval;

void	interval_fillInterval(t_interval *interval, double min, double max);
#endif
