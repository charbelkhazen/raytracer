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

typedef enum
{
	SPHERE_TYPE,
	CYLINDER_TYPE,
	PLANE_TYPE,
}	shape_type;

typedef enum
{
	MATTE_TYPE,
	MIRROR_TYPE,
	PLASTIC_TYPE,
}	material_type;
#endif
