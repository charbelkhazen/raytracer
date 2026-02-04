//This module defines all enums used in one place. This prevents circular dependency issues
#ifndef TYPES_H
#define TYPES_H


typedef enum
{
	CAMERA_CMD,
	LIGHT_CMD,
	AMBIENT_CMD,
	SPHERE_CMD,
	CYLINDER_CMD,
	PLANE_CMD, //NOTE: cyl and plane already implemented here
}	t_cmd_type;

#endif
